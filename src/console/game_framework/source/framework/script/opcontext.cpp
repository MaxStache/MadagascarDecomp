#include "precomp.h"
#include "opcontext.h"
#include "scriptnametable.h"
#include "opcode.h"
#include "framework/tfb/reader.h"
#include <string.h>
#include <vector>
namespace Script
{
    // GLOBAL: GAME 0x0061f874
    SymbolScope *tfb_scopes;
    // GLOBAL: GAME 0x0061f87c
    int g_tfbNextInstrPos;
    // GLOBAL: GAME 0x0061f884
    char *g_tfbLoadArg;
    // GLOBAL: GAME 0x0061f890
    RwUInt32 *tfb_opArena;
    // OpContext::OpContext() {}

    // FUNCTION: GAME 0x004349e0
    bool OpContext::Load(char *pszTypeName, unsigned char **ppData)
    {
        DECOMP_DEBUG_PRINT("SCRIPT LOADING....");
        bool ret;

        g_tfbLoadArg = pszTypeName;
        g_tfbNextInstrPos = 0;
        g_tfbReadPos = 0;
        g_tfbReadBuf = *ppData;
        ops = NULL;

        char typeName[0x100];
        TFBRead_pstr(typeName);

        // TODO: URENT: FIXME: TEMP: original allocates this in ScriptReference::resolveOrDeclareSymbol (not decompiled yet)
        if (tfb_scopes == NULL)
            tfb_scopes = RWS_NEW SymbolScope[3];

        unsigned arenaDwords;
        if (strcmp(typeName, GetTypeName()) == 0 && (TFBRead_u32(&arenaDwords), arenaDwords != 0))
        {
            tfb_opArena = (RwUInt32 *)RWS_OP_NEW(arenaDwords * 4);
            OpContext *savedCurrentScript = tfb_currentScript;
            RwUInt32 savedPC = tfb_current_instruction_index;
            tfb_currentScript = this;

            NameTable opcodeNames;
            opcodeNames.Read();
            tfb_scopes[0].table.Read();
            tfb_scopes[1].table.Read();

            unsigned int instrCount;
            TFBRead_u32(&instrCount);
            if (instrCount < 3)
            {
                instrCount = 0;
            }
            RwUInt32 *arena = tfb_opArena;
            tfb_opArena = arena + instrCount + 1;
            ops = (OpCode **)arena;

            unsigned int declCount = tfb_scopes[1].table.size();
            DECOMP_DEBUG_PRINT("declCount: %u, %s", declCount, tfb_scopes[1].table.front().name );
            this->locals = (ScriptReference **)RWS_OP_NEW((declCount - 1) * sizeof(ScriptReference *));
            this->localCount = 0;

            // LdTypeList *types = TFB_GetTypeList();

            NameEntry *entry = &tfb_scopes[1].table.front();
            for (unsigned i = 0; i < tfb_scopes[1].table.size() - 1; entry++, i++)
            {
                DECOMP_DEBUG_PRINT("I: %u %s", i, entry->name);
                // tfb_splitQualifiedName
                //(entry->name, declName, (char *)headerName_declMiddle,
                //  (int)declType );

                // -PLACEHOLDER DECMP127-186
            }

            // -PLACEHOLDER DECMP188-287

            // TODO: RE ENABLE
            // if (ops != NULL)
            //{
            //    ops[tfb_current_instruction_index] = NULL;
            //}
            tfb_current_instruction_index = savedPC;
            tfb_currentScript = savedCurrentScript;
            tfb_scopes[1].map.clear();
            tfb_scopes[1].table.Clear();
            tfb_scopes[0].table.Clear();
            ret = this->ops != NULL;
        }
        else
        {
            ret = false;
        }

        return ret;
    }

} // namespace Script
