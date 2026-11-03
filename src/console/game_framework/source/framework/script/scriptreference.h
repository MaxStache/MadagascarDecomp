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
        virtual const char *getName() { return NULL; }

        // FUNCTION: GAME 0x00416530 FOLDED
        virtual const char *addRef(int delta) { return NULL; }

        // SYNTHETIC: GAME 0x004025c0
        // Script::ScriptReference::`scalar deleting destructor'
        virtual ~ScriptReference() {}

        // FUNCTION: GAME 0x0043e6f0 FOLDED
        virtual ScriptReference *getType() { return NULL; }
        // FUNCTION: GAME 0x0043e6f0 FOLDED
        virtual ScriptReference *getElementType() { return NULL; }

        // FUNCTION: GAME 0x0042cbe0 FOLDED
        virtual int UNK0x18() { return 2; } // TODO: Figure out a name for this (+0x18)

        // FUNCTION: GAME 0x0043dc80 FOLDED
        virtual ScriptReference *getExposedMembers(int *outCount)
        {
            *outCount = 0;
            return NULL;
        }

        // FUNCTION: GAME 0x004025a0 FOLDED
        virtual void setObject(ScriptReference *value, ScriptReference *owner) {}
        // FUNCTION: GAME 0x004025b0 FOLDED
        virtual ScriptReference *getObject(ScriptReference* owner, bool noDeref) { return this; }

        // FUNCTION: GAME 0x00464ef0 FOLDED
        virtual void reset() {}
    };
}

#endif