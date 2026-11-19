#include "precomp.h"
#include "opcode.h"

namespace Script
{
    // GLOBAL: GAME 0x0061f658
    RwUInt32 tfb_current_instruction_index;
    // GLOBAL: GAME 0x0061f65c
    OpContext *tfb_currentScript;

    // FUNCTION: GAME 0x00431130
    int OpCode::Execute()
    {
        RwUInt32 end = (flags >> 11) + tfb_current_instruction_index;

        while (tfb_current_instruction_index < end)
        {
            RwUInt32 i = tfb_current_instruction_index++;
            OpCode *op = tfb_currentScript->ops[i];
            if (op)
            {
                int result = op->Execute() - 1;
                if (result != 0)
                {
                    tfb_current_instruction_index = end;
                    flags &= ~0x80;
                    return result;
                }
            }
        }

        flags |= 0x80;
        return flags & 7;
    }

} // namespace Script
