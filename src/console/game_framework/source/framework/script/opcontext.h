#ifndef __OPCONTEXT__
#define __OPCONTEXT__

#include "namedobject.h"
#include "scriptreference.h"

#include "framework/decomp_helpers.h"

namespace Script
{
    extern int g_tfbNextInstrPos;
    extern char* g_tfbLoadArg;

    class OpCode;

    // VTABLE: GAME 0x005cd2bc
    class OpContext : public NamedObject
    {
        // FUNCTION: GAME 0x00429750
        virtual const char *GetName() { return "script"; }
        // FUNCTION: GAME 0x00429740
        virtual const char *GetTypeName() { return "TFB Script"; }

    public:
        bool Load(char *pszTypeName, unsigned char **ppData);

    public:
        RwUInt32 behaviorInstructionIndex;
        RwUInt32 startTime;
        RwUInt32 pauseStartTime;
        OpCode **ops;
        RwUInt32 localCount;
        ScriptReference **locals;
    };
}

#endif