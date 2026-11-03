#ifndef __OPCONTEXT__
#define __OPCONTEXT__

#include "namedobject.h"
#include "scriptreference.h"

namespace Script
{
    class OpCode;

    // VTABLE: GAME 0x005cd2bc
    class OpContext : public NamedObject
    {
        // FUNCTION: GAME 0x00429750
        virtual const char *getName() { return "script"; }
        // FUNCTION: GAME 0x00429740
        virtual const char *getTypeName() { return "TFB Script"; }

    public:
        bool load(char *pszTypeName, void **ppData);

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