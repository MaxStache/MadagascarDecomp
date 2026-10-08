#ifndef __NAMEDOBJECT__
#define __NAMEDOBJECT__

namespace Script
{
    class NamedObject
    {
        virtual char * getName() = 0;
        virtual char * getTypeName() = 0;
    };
}

#endif