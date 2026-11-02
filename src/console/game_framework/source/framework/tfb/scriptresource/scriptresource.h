#ifndef _SCRIPTRESOURCE_H_
#define _SCRIPTRESOURCE_H_

//////////////////////////////////////////////////////////////////
//
// Renderware Studio Includes
//
#include "framework/core/resourcemanager/cresourcehandler.h"

namespace RWS
{
   /**
   *
   * \ingroup ScriptResource
   *
   *  Resource handler for script file resources.
   *
   */
   class CScriptResource: public CResourceHandler
   {
      public:

         virtual void *Load(const RwChar *psName, const RwChar *psType, const RwChar *psResourcePath, RwStream* pStream, RwUInt32 uiStreamSize,RwUInt32 &uiResourceSize);

         virtual RwBool UnLoad(const RwChar *pStrType, void *pResource);

         virtual RwBool IsHandled(const RwChar *psType);

         virtual void Update(const void *pResData,
            const void *pData,
            const RwChar *pStrType) {}
   };
}

#endif