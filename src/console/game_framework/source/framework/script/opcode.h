#ifndef __OPCODE__
#define __OPCODE__

#include "scriptreference.h"
#include "opcontext.h"

namespace Script
{
    extern RwUInt32 tfb_current_instruction_index;
    extern OpContext *tfb_currentScript;
    extern RwUInt32 *tfb_opArena;

    // VTABLE: GAME 0x005cdc80
    class OpCode : public ScriptReference
    {
    public:
        // FUNCTION: GAME 0x0043e6f0 FOLDED
        virtual int IsBlock() { return 0; }

        // FUNCTION: GAME 0x0043e6f0 FOLDED
        virtual OpCode *Clone() { return NULL; }

        virtual int Execute();

        // FUNCTION: GAME 0x0043e6f0 FOLDED
        virtual int Parse() { return 0; }

    public:
        RwUInt32 flags;
    };
}

#endif