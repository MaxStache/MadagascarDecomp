#include "precomp.h"
#include "opcontext.h"
#include "opcode.h"
#include "framework/tfb/reader.h"
#include <string.h>
#include <vector>
namespace Script
{
    // GLOBAL: GAME 0x0061f87c
    int g_tfbNextInstrPos;
    // GLOBAL: GAME 0x0061f884
    char* g_tfbLoadArg;
    //OpContext::OpContext() {}

    // FUNCTION: GAME 0x004349e0
    bool OpContext::Load(char *pszTypeName, unsigned char **ppData)
    {
        g_tfbLoadArg = pszTypeName;
        g_tfbNextInstrPos = 0;
        g_tfbReadPos = 0;
        g_tfbReadBuf = *ppData;
        ops = NULL;

        std::vector<int> myVec;

	    char typeName[0x100];
	    TFBRead_pstr(typeName);

        unsigned arenaDwords;
        TFBRead_u32(&arenaDwords);
        void* tfb_opArena = ::RWS_OP_NEW(arenaDwords * 4);

        OpCode op;
        return true;
    }

} // namespace Script
