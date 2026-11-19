#ifndef __SCRIPTREFERENCE__
#define __SCRIPTREFERENCE__

#include "namedobject.h"

namespace Script
{
    // VTABLE: GAME 0x005ca3ec
    class ScriptReference : public NamedObject
    {
    public:
        // FUNCTION: GAME 0x0043e6f0 FOLDED
        virtual const char *GetName() { return NULL; }

        // FUNCTION: GAME 0x00416530 FOLDED
        virtual const char *ChangeRefCount(int delta) { return NULL; }

        // Script::ScriptReference::`scalar deleting destructor'
        // SYNTHETIC: GAME 0x004025c0
        virtual ~ScriptReference() {}

        // FUNCTION: GAME 0x0043e6f0 FOLDED
        virtual ScriptReference *GetType() { return NULL; }
        // FUNCTION: GAME 0x0043e6f0 FOLDED
        virtual ScriptReference *GetBaseType() { return NULL; }

        // FUNCTION: GAME 0x0042cbe0 FOLDED
        virtual int GetKind() { return 2; }

        // FUNCTION: GAME 0x0043dc80 FOLDED
        virtual ScriptReference *GetExposes(int *outCount)
        {
            *outCount = 0;
            return NULL;
        }

        // FUNCTION: GAME 0x004025a0 FOLDED
        virtual void SetReferent(ScriptReference *value, ScriptReference *owner) {}
        // FUNCTION: GAME 0x004025b0 FOLDED
        virtual ScriptReference *Deref(ScriptReference* owner, int flags) { return this; }

        // FUNCTION: GAME 0x00464ef0 FOLDED
        virtual void ResetStatics() {}
    };
}

#endif