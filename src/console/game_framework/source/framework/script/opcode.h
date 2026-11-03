#ifndef __OPCODE__
#define __OPCODE__

#include "scriptreference.h"
#include "opcontext.h"

namespace Script
{
    extern RwUInt32 tfb_current_instruction_index;
    extern OpContext *tfb_currentScript;

    // VTABLE: GAME 0x005cdc80
    class OpCode : public ScriptReference
    {
    public:
        // FUNCTION: GAME 0x0043e6f0 FOLDED
        virtual int getScopeType() { return 0; }

        // FUNCTION: GAME 0x0043e6f0 FOLDED
        virtual OpCode *instantiate() { return NULL; }

        virtual int execute();

        // FUNCTION: GAME 0x0043e6f0 FOLDED
        virtual int parse() { return 0; }

    public:
        RwUInt32 flags;
    };
}

#endif