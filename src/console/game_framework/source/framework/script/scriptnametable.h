#ifndef _SCRIPTNAMETABLE_H_
#define _SCRIPTNAMETABLE_H_

#include <map>
#include <vector>

namespace Script
{
    struct NameEntry
    {
        char         name[256];
        unsigned int value;
        unsigned int nameHash;
        unsigned int refCount;
    };

    unsigned int NameHashNoCase(const char* pszName);

    class NameTable : public std::vector<NameEntry>
    {
    public:
        void Read();
        void Clear();
    };

    struct SymbolScope
    {
        std::map<unsigned int, unsigned int> map;
        NameTable table;
    };

    // new SymbolScope[3] in ScriptReference::resolveOrDeclareSymbol
    extern SymbolScope *tfb_scopes;
}

#endif