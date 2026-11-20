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

    // Splits up strings like: name::sub::type, example: MyCounter::user::value
    void SplitTypedName(const char *src, char *name, char *sub, char *type);

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

    extern SymbolScope *tfb_scopes;
}

#endif