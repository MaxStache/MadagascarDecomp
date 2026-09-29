"""Reads a VS2003 (.vcproj 7.10) project and turns one configuration into cl/link settings."""

import os
import re
import xml.etree.ElementTree as ET
from dataclasses import dataclass

from .util import BuildError, quote, resolve_proj_path, split_list

LIBRARY = "4"  # ConfigurationType of a static library

_KNOWN_CL_SETTINGS = {
    "AdditionalIncludeDirectories",
    "AdditionalOptions",
    "AssemblerListingLocation",
    "BrowseInformation",
    "BrowseInformationFile",
    "CompileAs",
    "DebugInformationFormat",
    "EnableFunctionLevelLinking",
    "InlineFunctionExpansion",
    "ObjectFile",
    "Optimization",
    "OptimizeForProcessor",
    "PrecompiledHeaderFile",
    "PrecompiledHeaderThrough",
    "PreprocessorDefinitions",
    "ProgramDataBaseFileName",
    "RuntimeLibrary",
    "StringPooling",
    "SuppressStartupBanner",
    "UsePrecompiledHeader",
    "WarnAsError",
    "WarningLevel",
    "ExceptionHandling",
    "BasicRuntimeChecks",
    "RuntimeTypeInfo",
}

# Per-file list settings left empty mean "inherit" in VS2003 project files.
_INHERIT_IF_EMPTY = {"AdditionalIncludeDirectories", "PreprocessorDefinitions"}


@dataclass
class Unit:
    source: str
    obj: str
    flags: list[str]
    creates_pch: bool
    uses_pch: bool
    debug_info: bool


@dataclass
class Project:
    name: str
    dir: str
    obj_dir: str
    type: str
    units: list[Unit]
    pch: str | None
    runtime_library: str | None
    librarian: dict[str, str]
    linker: dict[str, str]
    output: str

    @property
    def is_library(self) -> bool:
        return self.type == LIBRARY


def _is_true(v: str | None) -> bool:
    return (v or "").upper() == "TRUE"


def _tool(node: ET.Element | None, name: str) -> dict[str, str]:
    if node is None:
        return {}
    tool = node.find(f"Tool[@Name='{name}']")
    if tool is None:
        return {}
    return {k: v for k, v in tool.attrib.items() if k != "Name"}


def cl_flags(t: dict[str, str], proj_dir: str, st_debug_crt: bool) -> list[str]:
    unknown = set(t) - _KNOWN_CL_SETTINGS
    if unknown:
        raise BuildError(
            f"Unsupported compiler setting '{sorted(unknown)[0]}' in project file."
        )

    f: list[str] = []
    if _is_true(t.get("SuppressStartupBanner")):
        f.append("/nologo")
    f += {"0": ["/Od"], "1": ["/O1"], "2": ["/O2"], "3": ["/Ox"]}.get(
        t.get("Optimization"), []
    )
    f += {"1": ["/Ob1"], "2": ["/Ob2"]}.get(t.get("InlineFunctionExpansion"), [])
    f += {"1": ["/G5"], "2": ["/G6"], "3": ["/G7"]}.get(
        t.get("OptimizeForProcessor"), []
    )
    f += [
        "/I" + quote(resolve_proj_path(proj_dir, d))
        for d in split_list(t.get("AdditionalIncludeDirectories"))
    ]
    f += ["/D" + quote(d) for d in split_list(t.get("PreprocessorDefinitions"), ";")]
    if _is_true(t.get("StringPooling")):
        f.append("/GF")
    if (t.get("ExceptionHandling") or "").upper() != "FALSE":
        f.append("/EHsc")
    f += {"1": ["/RTCs"], "2": ["/RTCu"], "3": ["/RTC1"]}.get(
        t.get("BasicRuntimeChecks"), []
    )
    f += {
        "0": ["/MT"],
        "1": ["/MLd" if st_debug_crt else "/MTd"],
        "2": ["/MD"],
        "3": ["/MDd"],
        "4": ["/ML"],
        "5": ["/MLd"],
    }.get(t.get("RuntimeLibrary"), [])
    if _is_true(t.get("EnableFunctionLevelLinking")):
        f.append("/Gy")
    if _is_true(t.get("RuntimeTypeInfo")):
        f.append("/GR")
    if t.get("WarningLevel"):
        f.append("/W" + t["WarningLevel"])
    if _is_true(t.get("WarnAsError")):
        f.append("/WX")
    f += {"1": ["/Z7"], "3": ["/Zi"], "4": ["/ZI"]}.get(
        t.get("DebugInformationFormat"), []
    )
    f += {"1": ["/TC"], "2": ["/TP"]}.get(t.get("CompileAs"), [])
    if t.get("ProgramDataBaseFileName"):
        pdb = t["ProgramDataBaseFileName"]
        if pdb.endswith(("\\", "/")):
            pdb += "vc70.pdb"
        f.append("/Fd" + quote(resolve_proj_path(proj_dir, pdb)))
    f += split_list(t.get("AdditionalOptions"), r"\s+")
    # BrowseInformation (.sbr) is skipped: the toolkit has no bscmake.
    return f


def load(vcproj: str, config: str, st_debug_crt: bool) -> Project:
    root = ET.parse(vcproj).getroot()
    proj_dir = os.path.dirname(vcproj)
    cfg_name = f"{config}|Win32"
    cfg = next(
        (c for c in root.iter("Configuration") if c.get("Name") == cfg_name), None
    )
    if cfg is None:
        raise BuildError(f"{vcproj} has no configuration '{cfg_name}'.")

    cl_base = _tool(cfg, "VCCLCompilerTool")
    obj_dir = resolve_proj_path(proj_dir, cfg.get("IntermediateDirectory", ""))
    pch = (
        resolve_proj_path(proj_dir, cl_base["PrecompiledHeaderFile"])
        if cl_base.get("PrecompiledHeaderFile")
        else None
    )

    units = []
    for file in root.iter("File"):
        rel = file.get("RelativePath", "")
        if not re.search(r"\.(c|cpp|cxx)$", rel, re.I):
            continue
        fc = next(
            (c for c in file.findall("FileConfiguration") if c.get("Name") == cfg_name),
            None,
        )
        if fc is not None and _is_true(fc.get("ExcludedFromBuild")):
            continue

        cl = dict(cl_base)
        for k, v in _tool(fc, "VCCLCompilerTool").items():
            if v != "" or k not in _INHERIT_IF_EMPTY:
                cl[k] = v

        src = resolve_proj_path(proj_dir, rel)
        obj = os.path.join(obj_dir, os.path.splitext(os.path.basename(src))[0] + ".obj")
        flags = cl_flags(cl, proj_dir, st_debug_crt)
        pch_mode = cl.get("UsePrecompiledHeader")
        if pch_mode in ("1", "3"):
            flags.append(
                ("/Yc" if pch_mode == "1" else "/Yu")
                + quote(cl.get("PrecompiledHeaderThrough", ""))
            )
            flags.append("/Fp" + quote(pch or ""))
        units.append(
            Unit(
                src,
                obj,
                flags,
                creates_pch=pch_mode == "1",
                uses_pch=pch_mode == "3",
                debug_info=bool(cl.get("DebugInformationFormat")),
            )
        )

    lib = _tool(cfg, "VCLibrarianTool")
    link = _tool(cfg, "VCLinkerTool")
    type_ = cfg.get("ConfigurationType", "")
    output = resolve_proj_path(
        proj_dir, (lib if type_ == LIBRARY else link).get("OutputFile", "")
    )
    return Project(
        root.get("Name", ""),
        proj_dir,
        obj_dir,
        type_,
        units,
        pch,
        cl_base.get("RuntimeLibrary"),
        lib,
        link,
        output,
    )
