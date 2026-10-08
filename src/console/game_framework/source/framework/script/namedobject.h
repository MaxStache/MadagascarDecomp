#ifndef __NAMEDOBJECT__
#define __NAMEDOBJECT__

namespace Script
{
    class NamedObject
    {
    public:
        virtual const char* getName() = 0;
        virtual const char* getTypeName() { return getName(); }
    };
}

#endif