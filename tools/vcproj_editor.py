#!/usr/bin/env python3
"""Viewer/editor for Visual Studio .NET 2003 (.vcproj 7.10) project files.

GUI (default):
    python tools/vcproj_editor.py [path/to/project.vcproj]

CLI:
    python tools/vcproj_editor.py PROJ tree              print filter/file tree
    python tools/vcproj_editor.py PROJ configs           list configurations
    python tools/vcproj_editor.py PROJ add FILTER FILE.. add files to filter ("Source Files/Modules/FX")
    python tools/vcproj_editor.py PROJ remove FILE..     remove files (match on RelativePath suffix)
    python tools/vcproj_editor.py PROJ fixconfigs        give source files missing per-config blocks the defaults
    python tools/vcproj_editor.py PROJ check             verify parse/save round-trips byte-identically

Saving reproduces Visual Studio's own formatting (tabs, one attribute per line,
CRLF, Windows-1252), so diffs stay minimal.
"""

import os
import sys
import xml.etree.ElementTree as ET

DEFAULT_PROJ = os.path.join(
    os.path.dirname(os.path.abspath(__file__)), "..",
    "src", "console", "game_framework", "win32", "game_framework", "game_framework.vcproj")

# Elements Visual Studio writes as <Tag .../> when they have no children.
SELF_CLOSING = {"Tool", "Platform", "DefaultToolFile", "ToolFile"}


# --------------------------------------------------------------------------- model

class VcProj:
    def __init__(self, path):
        self.path = os.path.abspath(path)
        with open(self.path, "rb") as f:
            raw = f.read()
        self.encoding = "Windows-1252"
        head = raw[:200].decode("ascii", "replace")
        if 'encoding="' in head:
            self.encoding = head.split('encoding="', 1)[1].split('"', 1)[0]
        self.root = ET.fromstring(raw)
        self.parents = {}
        self._reindex()

    def _reindex(self):
        self.parents = {c: p for p in self.root.iter() for c in p}

    @property
    def dir(self):
        return os.path.dirname(self.path)

    def files_root(self):
        return self.root.find("Files")

    def config_names(self):
        return [c.get("Name") for c in self.root.iterfind("Configurations/Configuration")]

    def filter_path(self, elem):
        names = []
        while elem is not None and elem.tag == "Filter":
            names.append(elem.get("Name", ""))
            elem = self.parents.get(elem)
        return "/".join(reversed(names))

    def all_filters(self):
        return [e for e in self.files_root().iter("Filter")]

    def find_filter(self, path, create=False):
        node = self.files_root()
        for part in [p for p in path.replace("\\", "/").split("/") if p]:
            nxt = next((f for f in node.findall("Filter") if f.get("Name") == part), None)
            if nxt is None:
                if not create:
                    return None
                nxt = self.add_filter(node, part)
            node = nxt
        return node

    # ---- mutations
    def add_filter(self, parent, name):
        f = ET.Element("Filter", {"Name": name, "Filter": ""})
        # Filters come before Files inside a Filter in VS-written projects.
        idx = sum(1 for c in parent if c.tag == "Filter")
        parent.insert(idx, f)
        self.parents[f] = parent
        return f

    def rel_path(self, abs_path):
        return os.path.relpath(os.path.abspath(abs_path), self.dir).replace("/", "\\")

    def add_file(self, parent, rel_path, default_configs=True):
        f = ET.Element("File", {"RelativePath": rel_path})
        parent.append(f)
        self._reindex()
        if default_configs and is_source(rel_path):
            self.apply_default_configs(f)
        return f

    def default_file_configs(self):
        """The per-configuration block set most source files share (ExcludedFromBuild stripped).

        Learned from the project itself; configurations no file covers yet get a
        generic VCCLCompilerTool block (Optimization 0 for Debug, 2 otherwise)."""
        counts, sample = {}, {}
        for f in self.files_root().iter("File"):
            fcs = f.findall("FileConfiguration")
            if not fcs or not is_source(f.get("RelativePath", "")):
                continue
            sig = tuple(_signature(fc) for fc in fcs)
            counts[sig] = counts.get(sig, 0) + 1
            sample.setdefault(sig, fcs)
        result = []
        if counts:
            for fc in sample[max(counts, key=counts.get)]:
                c = _deepcopy(fc)
                c.attrib.pop("ExcludedFromBuild", None)
                result.append(c)
        have = {fc.get("Name") for fc in result}
        for name in self.config_names():
            if name not in have:
                fc = ET.Element("FileConfiguration", {"Name": name})
                ET.SubElement(fc, "Tool", {
                    "Name": "VCCLCompilerTool",
                    "Optimization": "0" if "debug" in name.lower() else "2",
                    "AdditionalIncludeDirectories": "",
                    "PreprocessorDefinitions": ""})
                result.append(fc)
        return result

    def apply_default_configs(self, file_elem, defaults=None):
        """Add any default FileConfiguration the file is missing. Existing ones are kept.
        Returns the number of blocks added."""
        defaults = defaults if defaults is not None else self.default_file_configs()
        existing = {fc.get("Name") for fc in file_elem.findall("FileConfiguration")}
        added = 0
        for fc in defaults:
            if fc.get("Name") not in existing:
                file_elem.append(_deepcopy(fc))
                added += 1
        if added:
            self._reindex()
        return added

    def files_missing_configs(self):
        names = set(self.config_names())
        return [f for f in self.files_root().iter("File") if is_source(f.get("RelativePath", ""))
                and not names <= {fc.get("Name") for fc in f.findall("FileConfiguration")}]

    def remove(self, elem):
        parent = self.parents.get(elem)
        if parent is not None:
            parent.remove(elem)
            self._reindex()

    def move(self, elem, new_parent):
        self.remove(elem)
        if elem.tag == "Filter":
            idx = sum(1 for c in new_parent if c.tag == "Filter")
            new_parent.insert(idx, elem)
        else:
            new_parent.append(elem)
        self._reindex()

    def shift(self, elem, delta):
        parent = self.parents.get(elem)
        if parent is None:
            return False
        kids = list(parent)
        i = kids.index(elem)
        j = i + delta
        if not 0 <= j < len(kids) or kids[j].tag != elem.tag:
            return False
        parent.remove(elem)
        parent.insert(j, elem)
        return True

    def is_excluded(self, file_elem, config):
        fc = self._file_config(file_elem, config)
        return fc is not None and fc.get("ExcludedFromBuild", "").upper() == "TRUE"

    def set_excluded(self, file_elem, config, excluded):
        fc = self._file_config(file_elem, config)
        if excluded:
            if fc is None:
                fc = ET.SubElement(file_elem, "FileConfiguration", {"Name": config})
                ET.SubElement(fc, "Tool", {"Name": "VCCLCompilerTool"})
                self.parents[fc] = file_elem
            set_attr_after(fc, "ExcludedFromBuild", "TRUE", after="Name")
        elif fc is not None:
            fc.attrib.pop("ExcludedFromBuild", None)

    def _file_config(self, file_elem, config):
        return next((fc for fc in file_elem.findall("FileConfiguration")
                     if fc.get("Name") == config), None)

    # ---- serialisation
    def serialize(self):
        out = ['<?xml version="1.0" encoding="%s"?>' % self.encoding]
        _write(self.root, 0, out)
        return ("\r\n".join(out) + "\r\n").encode(self.encoding, "xmlcharrefreplace")

    def save(self, path=None):
        data = self.serialize()
        with open(path or self.path, "wb") as f:
            f.write(data)


SOURCE_EXTS = (".cpp", ".c", ".cxx", ".cc")


def is_source(path):
    return path.lower().endswith(SOURCE_EXTS)


def _signature(e):
    attrs = tuple((k, v) for k, v in e.attrib.items() if k != "ExcludedFromBuild")
    return (e.tag, attrs, tuple(_signature(c) for c in e))


def _deepcopy(e):
    n = ET.Element(e.tag, dict(e.attrib))
    for c in e:
        n.append(_deepcopy(c))
    return n


def set_attr_after(elem, key, value, after=None):
    if key in elem.attrib or after not in elem.attrib:
        elem.set(key, value)
        return
    items = []
    for k, v in elem.attrib.items():
        items.append((k, v))
        if k == after:
            items.append((key, value))
    elem.attrib.clear()
    elem.attrib.update(items)


def _esc(v):
    return (v.replace("&", "&amp;").replace("<", "&lt;").replace(">", "&gt;")
             .replace('"', "&quot;").replace("\r", "&#x0d;").replace("\n", "&#x0a;"))


def _write(e, depth, out):
    ind = "\t" * depth
    kids = list(e)
    end = "/>" if not kids and e.tag in SELF_CLOSING else ">"
    attrs = list(e.attrib.items())
    if attrs:
        out.append(ind + "<" + e.tag)
        for i, (k, v) in enumerate(attrs):
            out.append('%s\t%s="%s"%s' % (ind, k, _esc(v), end if i == len(attrs) - 1 else ""))
    else:
        out.append(ind + "<" + e.tag + end)
    if end == ">":
        for c in kids:
            _write(c, depth + 1, out)
        out.append(ind + "</" + e.tag + ">")


# --------------------------------------------------------------------------- CLI

def cli(argv):
    proj = VcProj(argv[0])
    cmd, args = argv[1], argv[2:]
    if cmd == "tree":
        def walk(node, depth):
            for c in node:
                if c.tag == "Filter":
                    print("  " * depth + "[" + c.get("Name", "") + "]")
                    walk(c, depth + 1)
                elif c.tag == "File":
                    ex = [n for n in proj.config_names() if proj.is_excluded(c, n)]
                    note = "  (excluded in %d configs)" % len(ex) if ex else ""
                    print("  " * depth + c.get("RelativePath", "") + note)
        walk(proj.files_root(), 0)
    elif cmd == "configs":
        print("\n".join(proj.config_names()))
    elif cmd == "add":
        flt = proj.find_filter(args[0], create=True)
        for p in args[1:]:
            rel = p.replace("/", "\\") if p.startswith(".") else proj.rel_path(p)
            proj.add_file(flt, rel)
            print("added", rel, "->", proj.filter_path(flt) or "<root>")
        proj.save()
    elif cmd == "fixconfigs":
        defaults = proj.default_file_configs()
        for f in proj.files_missing_configs():
            n = proj.apply_default_configs(f, defaults)
            print("added %d configuration block(s) to %s" % (n, f.get("RelativePath")))
        proj.save()
    elif cmd == "remove":
        for p in args:
            needle = p.replace("/", "\\").lower()
            hits = [f for f in proj.files_root().iter("File")
                    if f.get("RelativePath", "").lower().endswith(needle)]
            for h in hits:
                print("removed", h.get("RelativePath"))
                proj.remove(h)
            if not hits:
                print("no match:", p)
        proj.save()
    elif cmd == "check":
        with open(proj.path, "rb") as f:
            orig = f.read()
        new = proj.serialize()
        if orig == new:
            print("OK: round-trip is byte-identical")
        else:
            a, b = orig.split(b"\r\n"), new.split(b"\r\n")
            n = next((i for i, (x, y) in enumerate(zip(a, b)) if x != y), min(len(a), len(b)))
            print("DIFFERS at line %d:\n  orig: %r\n  new:  %r" % (
                n + 1, a[n] if n < len(a) else None, b[n] if n < len(b) else None))
            return 1
    else:
        print(__doc__)
        return 2
    return 0


# --------------------------------------------------------------------------- GUI

def gui(path):
    import tkinter as tk
    from tkinter import ttk, filedialog, messagebox, simpledialog

    class App:
        def __init__(self, root):
            self.tk = root
            self.proj = None
            self.dirty = False
            self.show_settings = tk.BooleanVar(value=False)
            self.search = tk.StringVar()
            self.search.trace_add("write", lambda *_: self.rebuild())
            self.elems = {}

            root.geometry("1300x800")
            root.protocol("WM_DELETE_WINDOW", self.quit)
            self._menu()

            top = ttk.Frame(root, padding=4)
            top.pack(fill="x")
            ttk.Label(top, text="Search:").pack(side="left")
            ent = ttk.Entry(top, textvariable=self.search, width=40)
            ent.pack(side="left", padx=4)
            ttk.Checkbutton(top, text="Show build settings (FileConfiguration / Tool)",
                            variable=self.show_settings, command=self.rebuild).pack(side="left", padx=8)
            for txt, cmd in [("Add Files", self.add_files), ("Add Filter", self.add_filter),
                             ("Delete", self.delete), ("Up", lambda: self.shift(-1)),
                             ("Down", lambda: self.shift(1)), ("Move to…", self.move_to),
                             ("Exclude/Include…", self.exclude_dialog)]:
                ttk.Button(top, text=txt, command=cmd).pack(side="left", padx=1)

            pane = ttk.PanedWindow(root, orient="horizontal")
            pane.pack(fill="both", expand=True)

            lf = ttk.Frame(pane)
            self.tree = ttk.Treeview(lf, columns=("info",), selectmode="extended")
            self.tree.heading("#0", text="Element")
            self.tree.heading("info", text="Path / details")
            self.tree.column("#0", width=380)
            self.tree.column("info", width=420)
            sb = ttk.Scrollbar(lf, orient="vertical", command=self.tree.yview)
            self.tree.configure(yscrollcommand=sb.set)
            self.tree.pack(side="left", fill="both", expand=True)
            sb.pack(side="right", fill="y")
            self.tree.tag_configure("excluded", foreground="#999999")
            self.tree.tag_configure("filter", foreground="#1f5fa8")
            self.tree.tag_configure("missing", foreground="#c0392b")
            self.tree.bind("<<TreeviewSelect>>", lambda e: self.show_attrs())
            self.tree.bind("<Button-3>", self.context_menu)
            self.tree.bind("<Delete>", lambda e: self.delete())
            pane.add(lf, weight=3)

            rf = ttk.Frame(pane)
            self.title = ttk.Label(rf, text="", font=("TkDefaultFont", 10, "bold"))
            self.title.pack(anchor="w", padx=4, pady=2)
            style = ttk.Style()
            style.configure("Attrs.Treeview", rowheight=24)
            self.attrs = ttk.Treeview(rf, columns=("value",), show="tree headings",
                                      selectmode="browse", style="Attrs.Treeview")
            self.attrs.heading("#0", text="Attribute")
            self.attrs.heading("value", text="Value")
            self.attrs.column("#0", width=190, stretch=False)
            self.attrs.column("value", width=400)
            self.attrs.tag_configure("odd", background="#f3f5f8")
            self.attrs.tag_configure("empty", foreground="#999999")
            self.attrs.pack(fill="both", expand=True)
            self.attrs.bind("<Double-1>", self.on_attr_dblclick)
            self.attrs.bind("<Return>", lambda e: self.begin_edit(self.attrs.focus(), "value"))
            self.attrs.bind("<F2>", lambda e: self.begin_edit(self.attrs.focus(), "value"))
            self.attrs.bind("<Delete>", lambda e: self.del_attr())
            self.attrs.bind("<Configure>", lambda e: self.cancel_edit())
            self.attrs.bind("<MouseWheel>", lambda e: self.commit_edit(), add="+")
            self.cell_editor = None
            ab = ttk.Frame(rf)
            ab.pack(fill="x", pady=2)
            ttk.Button(ab, text="+ Add attribute", command=self.add_attr).pack(side="left")
            ttk.Button(ab, text="Delete attribute", command=self.del_attr).pack(side="left")
            ttk.Button(ab, text="Edit as list…", command=self.edit_attr_dialog).pack(side="left")
            ttk.Label(ab, foreground="#777777",
                      text="Double-click / F2 to edit · Enter save · Esc cancel · Tab next").pack(side="right")
            pane.add(rf, weight=2)

            self.status = ttk.Label(root, anchor="w", relief="sunken")
            self.status.pack(fill="x")

            root.bind("<Control-s>", lambda e: self.save())
            root.bind("<Control-o>", lambda e: self.open())
            root.bind("<Control-f>", lambda e: ent.focus_set())

            if path and os.path.exists(path):
                self.load(path)

        # ---- plumbing
        def _menu(self):
            m = tk.Menu(self.tk)
            fm = tk.Menu(m, tearoff=0)
            fm.add_command(label="Open…  Ctrl+O", command=self.open)
            fm.add_command(label="Save  Ctrl+S", command=self.save)
            fm.add_command(label="Save As…", command=lambda: self.save(ask=True))
            fm.add_command(label="Reload", command=lambda: self.load(self.proj.path))
            fm.add_separator()
            fm.add_command(label="Exit", command=self.quit)
            m.add_cascade(label="File", menu=fm)
            pm = tk.Menu(m, tearoff=0)
            pm.add_command(label="Add default build configs to selection", command=self.apply_defaults)
            pm.add_command(label="Add default build configs to all source files missing them",
                           command=lambda: self.apply_defaults(all_missing=True))
            m.add_cascade(label="Project", menu=pm)
            self.tk.config(menu=m)

        def apply_defaults(self, all_missing=False):
            if not self.proj:
                return
            if all_missing:
                files = self.proj.files_missing_configs()
            else:
                files = []
                for e in self.selected():
                    files += [e] if e.tag == "File" else list(e.iter("File"))
                files = [f for f in files if is_source(f.get("RelativePath", ""))]
            defaults = self.proj.default_file_configs()
            changed = [f for f in files if self.proj.apply_default_configs(f, defaults)]
            if changed:
                self.touch()
            messagebox.showinfo("Default build configs", "Added default configuration blocks to %d file(s).%s" % (
                len(changed), "\n\n" + "\n".join(f.get("RelativePath") for f in changed[:20]) if changed else ""))

        def load(self, path):
            try:
                self.proj = VcProj(path)
            except Exception as ex:
                messagebox.showerror("Load failed", str(ex))
                return
            self.dirty = False
            self.rebuild()
            self.update_title()

        def open(self):
            if not self.confirm_discard():
                return
            p = filedialog.askopenfilename(filetypes=[("VC++ project", "*.vcproj"), ("All", "*.*")])
            if p:
                self.load(p)

        def save(self, ask=False):
            if not self.proj:
                return
            path = self.proj.path
            if ask:
                path = filedialog.asksaveasfilename(defaultextension=".vcproj",
                                                    initialfile=os.path.basename(path))
                if not path:
                    return
                self.proj.path = os.path.abspath(path)
            self.proj.save()
            self.dirty = False
            self.update_title()

        def confirm_discard(self):
            return not self.dirty or messagebox.askyesno("Unsaved changes", "Discard unsaved changes?")

        def quit(self):
            if self.confirm_discard():
                self.tk.destroy()

        def touch(self):
            self.dirty = True
            self.update_title()
            self.rebuild()

        def update_title(self):
            name = os.path.basename(self.proj.path) if self.proj else ""
            self.tk.title("vcproj editor - %s%s" % (name, " *" if self.dirty else ""))
            if self.proj:
                files = sum(1 for _ in self.proj.files_root().iter("File"))
                self.status.config(text="%s   |   %d files, %d filters, %d configurations" % (
                    self.proj.path, files, len(self.proj.all_filters()), len(self.proj.config_names())))

        def selected(self):
            return [self.elems[i] for i in self.tree.selection() if i in self.elems]

        # ---- tree
        def label(self, e):
            t = e.tag
            if t == "VisualStudioProject":
                return "Project: " + e.get("Name", ""), "VS " + e.get("Version", ""), ()
            if t == "Filter":
                return e.get("Name", ""), e.get("Filter", ""), ("filter",)
            if t == "File":
                rp = e.get("RelativePath", "")
                tags = ()
                ex = sum(1 for n in self.proj.config_names() if self.proj.is_excluded(e, n))
                info = rp
                if ex:
                    info += "   [excluded in %d/%d]" % (ex, len(self.proj.config_names()))
                    tags = ("excluded",)
                if is_source(rp) and len(e.findall("FileConfiguration")) < len(self.proj.config_names()):
                    tags += ("missing",)
                    info += "   [no default build configs]"
                if not os.path.exists(os.path.join(self.proj.dir, rp.replace("\\", os.sep))):
                    tags += ("missing",)
                    info += "   [missing on disk]"
                return rp.replace("/", "\\").split("\\")[-1], info, tags
            if t in ("Configuration", "FileConfiguration"):
                ex = " (excluded)" if e.get("ExcludedFromBuild", "").upper() == "TRUE" else ""
                return t + ": " + e.get("Name", "") + ex, "", ()
            if t == "Tool":
                return "Tool: " + e.get("Name", ""), "%d attrs" % (len(e.attrib) - 1), ()
            return t, "", ()

        def visible(self, e, needle):
            if not self.show_settings.get() and e.tag in ("FileConfiguration",):
                return False
            if not needle:
                return True
            if e.tag == "File":
                return needle in e.get("RelativePath", "").lower()
            if e.tag == "Filter":
                return needle in e.get("Name", "").lower() or any(
                    self.visible(c, needle) for c in e if c.tag in ("Filter", "File"))
            if e.tag == "Files":
                return True
            return False

        def rebuild(self):
            if not self.proj:
                return
            opened = {i for i in self._all_iids() if self.tree.item(i, "open")}
            sel = self.tree.selection()
            yv = self.tree.yview()[0]
            self.tree.delete(*self.tree.get_children())
            self.elems = {}
            needle = self.search.get().strip().lower()

            def add(e, parent_iid):
                iid = str(id(e))
                self.elems[iid] = e
                text, info, tags = self.label(e)
                is_open = iid in opened or (needle and e.tag in ("Filter", "Files"))
                self.tree.insert(parent_iid, "end", iid=iid, text=text, values=(info,),
                                 tags=tags, open=bool(is_open) or e.tag == "VisualStudioProject")
                for c in e:
                    if self.visible(c, needle):
                        add(c, iid)

            if needle:
                add(self.proj.files_root(), "")
            else:
                add(self.proj.root, "")
                if not opened:
                    self.tree.item(str(id(self.proj.files_root())), open=True)
            keep = [s for s in sel if self.tree.exists(s)]
            if keep:
                self.tree.selection_set(keep)
            self.tree.yview_moveto(yv)
            self.show_attrs()

        def _all_iids(self, parent=""):
            for i in self.tree.get_children(parent):
                yield i
                yield from self._all_iids(i)

        def reveal(self, e):
            iid = str(id(e))
            if self.tree.exists(iid):
                self.tree.see(iid)
                self.tree.selection_set(iid)

        # ---- attributes pane
        NEW_ROW = "__new_attr__"

        def current_elem(self):
            sel = self.selected()
            return sel[0] if len(sel) == 1 else None

        def show_attrs(self, focus=None):
            self.cancel_edit()
            self.attrs.delete(*self.attrs.get_children())
            e = self.current_elem()
            if e is None:
                n = len(self.selected())
                self.title.config(text="%d selected" % n if n else "")
                return
            self.title.config(text="<%s>" % e.tag)
            for i, (k, v) in enumerate(e.attrib.items()):
                tags = ("odd",) if i % 2 else ()
                if v == "":
                    tags += ("empty",)
                self.attrs.insert("", "end", iid=k, text=k, values=(v if v else "(empty)",), tags=tags)
            if focus and self.attrs.exists(focus):
                self.attrs.selection_set(focus)
                self.attrs.focus(focus)
                self.attrs.see(focus)

        def mark_changed(self, e):
            """Lightweight alternative to touch() for attribute edits: no full tree rebuild."""
            self.dirty = True
            self.update_title()
            iid = str(id(e))
            if self.tree.exists(iid):
                text, info, tags = self.label(e)
                self.tree.item(iid, text=text, values=(info,), tags=tags)

        def on_attr_dblclick(self, ev):
            row = self.attrs.identify_row(ev.y)
            if not row:
                self.add_attr()
            else:
                self.begin_edit(row, "name" if self.attrs.identify_column(ev.x) == "#0" else "value")
            return "break"

        def begin_edit(self, row, field):
            self.commit_edit()
            e = self.current_elem()
            if e is None or not row or not self.attrs.exists(row):
                return
            self.attrs.see(row)
            self.attrs.update_idletasks()
            bbox = self.attrs.bbox(row, "#0" if field == "name" else "value")
            if not bbox:
                return
            x, y, w, h = bbox
            if field == "value":
                w = max(w, self.attrs.winfo_width() - x - 2)
            if field == "name":
                initial = "" if row == self.NEW_ROW else row
            else:
                initial = e.get(row, "")
            var = tk.StringVar(value=initial)
            ent = ttk.Entry(self.attrs, textvariable=var)
            ent.place(x=x, y=y, width=w, height=h)
            ent.focus_set()
            ent.select_range(0, "end")
            ent.icursor("end")
            self.cell_editor = (ent, var, row, field, e)

            def on_key(fn):
                def handler(_ev):
                    fn()
                    return "break"
                return handler
            ent.bind("<Return>", on_key(self.commit_edit))
            ent.bind("<KP_Enter>", on_key(self.commit_edit))
            ent.bind("<Escape>", on_key(self.cancel_edit))
            ent.bind("<Tab>", on_key(lambda: self.commit_edit(advance=True)))
            ent.bind("<FocusOut>", lambda _ev: self.commit_edit())

        def cancel_edit(self):
            if not self.cell_editor:
                return
            ent, _, row, _, _ = self.cell_editor
            self.cell_editor = None
            ent.destroy()
            if row == self.NEW_ROW and self.attrs.exists(row):
                self.attrs.delete(row)
            self.attrs.focus_set()

        def commit_edit(self, advance=False):
            if not self.cell_editor:
                return
            ent, var, row, field, e = self.cell_editor
            self.cell_editor = None  # before destroy(): its FocusOut would re-enter
            val = var.get()
            ent.destroy()
            nxt = None
            changed = False
            if field == "name":
                name = val.strip()
                if row == self.NEW_ROW:
                    if not name or name in e.attrib:
                        if name:
                            self.tk.bell()
                        self.show_attrs()
                        return
                    e.set(name, "")
                    changed, row, nxt = True, name, (name, "value")
                elif name and name != row:
                    if name in e.attrib:
                        self.tk.bell()
                    else:
                        items = [(name if k == row else k, v) for k, v in e.attrib.items()]
                        e.attrib.clear()
                        e.attrib.update(items)
                        changed, row = True, name
                if advance and nxt is None:
                    nxt = (row, "value")
            else:
                if val != e.get(row):
                    e.set(row, val)
                    changed = True
                if advance:
                    nxt = (self.attrs.next(row), "value")
            if changed:
                self.mark_changed(e)
            if e is self.current_elem():
                self.show_attrs(focus=row)
                self.attrs.focus_set()
                if nxt and nxt[0]:
                    self.begin_edit(*nxt)

        def text_dialog(self, title, value):
            d = tk.Toplevel(self.tk)
            d.title(title)
            d.transient(self.tk)
            split = ";" in value and len(value) > 60
            txt = tk.Text(d, width=90, height=18 if split else 4, wrap="none" if split else "char")
            txt.insert("1.0", value.replace(";", ";\n") if split else value)
            txt.pack(fill="both", expand=True)
            if split:
                ttk.Label(d, text="(semicolon list shown one entry per line)").pack(anchor="w")
            res = {}

            def ok():
                v = txt.get("1.0", "end-1c")
                res["v"] = v.replace(";\n", ";").replace("\n", "") if split else v.replace("\n", "")
                d.destroy()
            bf = ttk.Frame(d)
            bf.pack(fill="x")
            ttk.Button(bf, text="OK", command=ok).pack(side="right")
            ttk.Button(bf, text="Cancel", command=d.destroy).pack(side="right")
            txt.focus_set()
            d.grab_set()
            self.tk.wait_window(d)
            return res.get("v")

        def edit_attr_dialog(self):
            self.commit_edit()
            e, cur = self.current_elem(), self.attrs.focus()
            if e is None or not cur or cur not in e.attrib:
                return
            v = self.text_dialog("Edit " + cur, e.get(cur, ""))
            if v is not None and v != e.get(cur):
                e.set(cur, v)
                self.mark_changed(e)
                self.show_attrs(focus=cur)

        def add_attr(self):
            self.commit_edit()
            if self.current_elem() is None:
                return
            self.attrs.insert("", "end", iid=self.NEW_ROW, text="", values=("",))
            self.begin_edit(self.NEW_ROW, "name")

        def del_attr(self):
            self.commit_edit()
            e, cur = self.current_elem(), self.attrs.focus()
            if e is None or not cur or cur not in e.attrib:
                return
            nxt = self.attrs.next(cur) or self.attrs.prev(cur)
            del e.attrib[cur]
            self.mark_changed(e)
            self.show_attrs(focus=nxt)
            self.attrs.focus_set()

        # ---- element operations
        def target_container(self):
            sel = self.selected()
            e = sel[0] if sel else self.proj.files_root()
            while e is not None and e.tag not in ("Filter", "Files"):
                e = self.proj.parents.get(e)
            return e if e is not None else self.proj.files_root()

        def add_files(self):
            if not self.proj:
                return
            parent = self.target_container()
            paths = filedialog.askopenfilenames(initialdir=self.proj.dir, title="Add files to '%s'" % (
                self.proj.filter_path(parent) or "Files"))
            if not paths:
                return
            last = None
            for p in paths:
                last = self.proj.add_file(parent, self.proj.rel_path(p))
            self.tree.item(str(id(parent)), open=True)
            self.touch()
            self.reveal(last)

        def add_filter(self):
            if not self.proj:
                return
            parent = self.target_container()
            name = simpledialog.askstring("Add filter", "New filter under '%s':" % (
                self.proj.filter_path(parent) or "Files"), parent=self.tk)
            if name:
                f = self.proj.add_filter(parent, name)
                self.tree.item(str(id(parent)), open=True)
                self.touch()
                self.reveal(f)

        def delete(self):
            sel = [e for e in self.selected() if e is not self.proj.root]
            if not sel:
                return
            desc = ", ".join(self.label(e)[0] for e in sel[:5]) + (" …" if len(sel) > 5 else "")
            if messagebox.askyesno("Delete", "Delete %d element(s)?\n%s" % (len(sel), desc)):
                for e in sel:
                    self.proj.remove(e)
                self.touch()

        def shift(self, d):
            sel = self.selected()
            if len(sel) == 1 and self.proj.shift(sel[0], d):
                self.touch()
                self.reveal(sel[0])

        def move_to(self):
            sel = [e for e in self.selected() if e.tag in ("File", "Filter")]
            if not sel:
                return
            targets = [("Files (root)", self.proj.files_root())] + [
                (self.proj.filter_path(f), f) for f in self.proj.all_filters()
                if not any(f is s or _is_descendant(self.proj, f, s) for s in sel)]
            d = tk.Toplevel(self.tk)
            d.title("Move %d item(s) to…" % len(sel))
            d.transient(self.tk)
            lb = tk.Listbox(d, width=80, height=30)
            for name, _ in targets:
                lb.insert("end", name)
            lb.pack(fill="both", expand=True)

            def ok(*_):
                if lb.curselection():
                    dest = targets[lb.curselection()[0]][1]
                    for e in sel:
                        self.proj.move(e, dest)
                    self.tree.item(str(id(dest)), open=True)
                    d.destroy()
                    self.touch()
                    self.reveal(sel[0])
            lb.bind("<Double-1>", ok)
            ttk.Button(d, text="Move", command=ok).pack()
            d.grab_set()

        def exclude_dialog(self):
            files = [e for e in self.selected() if e.tag == "File"]
            for e in self.selected():
                if e.tag in ("Filter", "Files"):
                    files += list(e.iter("File"))
            if not files:
                messagebox.showinfo("Exclude", "Select one or more files or filters.")
                return
            names = self.proj.config_names()
            d = tk.Toplevel(self.tk)
            d.title("Excluded from build — %d file(s)" % len(files))
            d.transient(self.tk)
            ttk.Label(d, text="Checked = excluded from build in that configuration").pack(anchor="w", padx=6)
            vars_ = {}
            for n in names:
                states = {self.proj.is_excluded(f, n) for f in files}
                v = tk.IntVar(value=1 if states == {True} else 0)
                cb = ttk.Checkbutton(d, text=n + ("  (mixed)" if len(states) > 1 else ""), variable=v)
                cb.pack(anchor="w", padx=12)
                vars_[n] = (v, v.get(), len(states) > 1)

            def ok():
                for n, (v, initial, mixed) in vars_.items():
                    if v.get() != initial or mixed and v.get():
                        for f in files:
                            self.proj.set_excluded(f, n, bool(v.get()))
                d.destroy()
                self.touch()
            bf = ttk.Frame(d)
            bf.pack(fill="x", pady=4)
            ttk.Button(bf, text="All", command=lambda: [v[0].set(1) for v in vars_.values()]).pack(side="left")
            ttk.Button(bf, text="None", command=lambda: [v[0].set(0) for v in vars_.values()]).pack(side="left")
            ttk.Button(bf, text="OK", command=ok).pack(side="right")
            ttk.Button(bf, text="Cancel", command=d.destroy).pack(side="right")
            d.grab_set()

        def context_menu(self, ev):
            iid = self.tree.identify_row(ev.y)
            if iid and iid not in self.tree.selection():
                self.tree.selection_set(iid)
            m = tk.Menu(self.tk, tearoff=0)
            m.add_command(label="Add Files…", command=self.add_files)
            m.add_command(label="Add Filter…", command=self.add_filter)
            m.add_separator()
            m.add_command(label="Move to…", command=self.move_to)
            m.add_command(label="Move Up", command=lambda: self.shift(-1))
            m.add_command(label="Move Down", command=lambda: self.shift(1))
            m.add_command(label="Excluded from build…", command=self.exclude_dialog)
            m.add_command(label="Add default build configs", command=self.apply_defaults)
            m.add_separator()
            m.add_command(label="Copy path", command=self.copy_path)
            m.add_command(label="Delete", command=self.delete)
            m.tk_popup(ev.x_root, ev.y_root)

        def copy_path(self):
            sel = self.selected()
            if sel:
                e = sel[0]
                s = e.get("RelativePath") or self.proj.filter_path(e) or e.get("Name", "")
                self.tk.clipboard_clear()
                self.tk.clipboard_append(s)

    root = tk.Tk()
    App(root)
    root.mainloop()


def _is_descendant(proj, node, ancestor):
    p = proj.parents.get(node)
    while p is not None:
        if p is ancestor:
            return True
        p = proj.parents.get(p)
    return False


if __name__ == "__main__":
    if len(sys.argv) >= 3:
        sys.exit(cli(sys.argv[1:]))
    gui(sys.argv[1] if len(sys.argv) == 2 else os.path.normpath(DEFAULT_PROJ))
