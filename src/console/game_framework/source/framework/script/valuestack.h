#ifndef __REFERENCEPATH__
#define __REFERENCEPATH__

#include "scriptreference.h"
#include "opcode.h"
#include <rwplcore.h>

namespace Script
{
    // GLOBAL: GAME 0x00621f10
    ScriptReference *gSenderRef;
    // GLOBAL: GAME 0x00621f14
    ScriptReference *gSelfRef;
    // GLOBAL: GAME 0x00621f1c
    ScriptReference *gEachRef;
    // GLOBAL: GAME 0x00621f20
    ScriptReference *gFoundRef;
    // GLOBAL: GAME 0x00621f2c
    ScriptReference *gControllerRef;
    // GLOBAL: GAME 0x00622004
    ScriptReference *gSubsetRef;

    class ValueStack
    {
    public:
        RwUInt32 raw;

        // FUNCTION: GAME 0x0043c5a0
        void Resolve(void **ppOwner, ScriptReference **ppSet, bool resolveChain)
        {
        }
    };
}

#endif