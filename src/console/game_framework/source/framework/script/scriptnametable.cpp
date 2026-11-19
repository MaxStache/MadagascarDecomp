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

        DECOMP_DEBUG_PRINT("Loading Name in Table: %u, %s", i, e.name );

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