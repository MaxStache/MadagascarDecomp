#ifndef __OPCONTEXT__
#define __OPCONTEXT__
namespace Script
{
    class OpContext : public OpContext
    {
    public:
        bool load(char *pszTypeName, void **ppData);
    };
}

#endif