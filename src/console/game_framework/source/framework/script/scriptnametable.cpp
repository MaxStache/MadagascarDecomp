#include "precomp.h"
#include "scriptnametable.h"
#include "framework/tfb/reader.h"
#include <string.h>

#include "framework/decomp_helpers.h"

// FUNCTION: GAME 0x00434100
void Script::NameTable::Read()
{
    unsigned int count;
    TFBRead_u32(&count);

    for (unsigned int i = 0; i < count; ++i)
    {
        char buf[256];
        TFBRead_pstr(buf);

        NameEntry e;
        TFBRead_u32(&e.value);
        e.nameHash = NameHashNoCase(buf);
        e.refCount = 0;
        strcpy(e.name, buf);

        push_back(e);
    }
}

// FUNCTION: GAME 0x004341f0
void Script::NameTable::Clear()
{
    NameEntry empty;
    empty.refCount = 0;
    std::vector<NameEntry> tmp(0, empty);
    swap(tmp);
}

// name::sub::type
// FUNCTION: GAME 0x00432a10
void Script::SplitTypedName(const char *src, char *name, char *sub, char *type)
{
    const char *p = src;

    // skip past the first "::"
    do
    {
        p = strchr(p, ':');
        if (p == NULL)
            return;
        p++;
    } while (*p != ':');
    while (*++p == ':')
        ;

    int nameLen = p - src - 2;
    strncpy(name, src, nameLen);
    name[nameLen] = '\0';

    const char *subStart = p;

    // skip past the second "::"
    do
    {
        p = strchr(p, ':');
        if (p == NULL)
        {
            // no second "::": sub and type both get the rest
            strcpy(sub, subStart);
            strcpy(type, sub);
            return;
        }
        p++;
    } while (*p != ':');
    while (*++p == ':')
        ;

    int subLen = p - subStart - 2;
    strncpy(sub, subStart, subLen);
    sub[subLen] = '\0';
    strcpy(type, p);
}