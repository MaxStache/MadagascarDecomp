#include "precomp.h"
// Left to its own devices, the MW linker will dead-strip the registrar ctors, so...
#ifdef __MWERKS__
#pragma force_active on
#endif

//#define RWS_CALLSTACKENABLE
//#define RWS_TRACEENABLE

//////////////////////////////////////////////////////////////////
//
// RenderWare Studio Includes
//
#include "framework/core/macros/debugmacros.h"
#include "scriptresource.h"

namespace RWS
{
   /**
   *
   * Load a script file resource.
   *
   *  \param psName pointer to a string defining the resource name.
   *
   *  \param psType pointer to a string defining the resource type.
   *
   *  \param psResourcePath pointer to a string containing a path where files referenced
   *  by this file can be found.
   *
   *  \param pStream pointer to a RenderWare stream.
   *
   *  \param uiStreamSize size of the file associated with this resource.
   *
   *  \returns If successful returns a pointer to the loaded resource, otherwise 0.
   *
   */
   void *CScriptResource::Load(const RwChar *psName, const RwChar *psType, const RwChar *psResourcePath, RwStream* pStream, RwUInt32 uiStreamSize,RwUInt32 &uiResourceSize)
   {
      RWS_FUNCTION("RWS::CScriptResource::Load");
      RWS_PRE(pStream);
      void * pBuffer = 0;

      //printf("%s", psName);
  
      if (uiStreamSize > 0) {
         // TODO: Invenstiate why there are + 0x20 here
         pBuffer = ::RWS_OP_NEW(uiStreamSize + 0x20);
         RwStreamRead(pStream, pBuffer, uiStreamSize);
         *(RwUInt32 *)&uiResourceSize = uiStreamSize;
      }

      uiResourceSize = uiStreamSize;

      RWS_RETURN(pBuffer);
   }

   /**
   *
   * Unload script file resource.
   *
   *  \param pStrType pointer to a string defining the resource type.
   *
   *  \param pResource pointer to the resource.
   *
   *  \returns True if the resource was successfully unloaded otherwise false.
   *
   */
   RwBool CScriptResource::UnLoad(const RwChar *pStrType, void *pResource)
   {
      RWS_FUNCTION("RWS::CScriptResource::UnLoad");

      operator delete(pResource);

      RWS_RETURN(TRUE);
   }

   /**
   *
   *  Check if the resource is handled by this resource handler.
   *
   *  \param psType pointer to a string defining the resource type.
   *
   *  \returns TRUE if the resource is of type "SCRIPT" otherwise returns FALSE.
   *
   */
   RwBool CScriptResource::IsHandled(const RwChar *psType)
   {
      RWS_FUNCTION("RWS::CScriptResource::IsHandled");
      RWS_PRE(psType);

      if (!rwstrcmp(psType, RWSTRING("SCRIPT")))
      {
         RWS_RETURN(TRUE);
      }

      RWS_RETURN(FALSE);
   }

   /*
   *
   * Create an instance of the Text Resource handler, this is required in order to register the handler.
   *
   */
   namespace { CScriptResource gCScriptResource; }
}
