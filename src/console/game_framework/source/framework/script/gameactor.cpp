#include "precomp.h"
#include "opcontext.h"

namespace Script
{
    // SIZE: 0x24
    struct ScriptEntry
    {
        void              *pResource;
        unsigned int       uiResourceSize;
        Script::OpContext  script;
    };

    // GLOBAL: GAME 0x00618390
    ScriptEntry   s_scripts[800];

    // GLOBAL: GAME 0x00618378
    unsigned int  s_numScripts;
}
