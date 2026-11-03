#ifndef __NAMEDOBJECT__
#define __NAMEDOBJECT__

namespace Script
{
    // VTABLE: GAME 0x005ca418
    class NamedObject
    {
    public:
        virtual const char *getName() = 0;

        // FUNCTION: GAME 0x00436a40
        virtual const char *getTypeName() { return getName(); }
    };
}

#endif