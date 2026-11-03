/*****************************************************************************
 *
 * File :     loadgamedatabase.cpp
 *
 * Abstract : Utility function used to load a game database from a file.
 *
 *****************************************************************************
 *
 * This file is a product of Criterion Software Ltd.
 *
 * This file is provided as is with no warranties of any kind and is
 * provided without any obligation on Criterion Software Ltd. or
 * Canon Inc. to assist in its use or modification.
 *
 * Criterion Software Ltd. will not, under any
 * circumstances, be liable for any lost revenue or other damages arising
 * from the use of this file.
 *
 * Copyright (c) 2000 Criterion Software Ltd.
 * All Rights Reserved.
 *
 * RenderWare is a trademark of Canon Inc.
 *
 *****************************************************************************/
#include "precomp.h"

//////////////////////////////////////////////////////////////////
// 
// RenderWare Studio Includes
//
#include "framework/core/macros/debugmacros.h"
#include "framework/core/streamhandler/streamhandler.h"

#include "framework/decomp_helpers.h"

namespace RWS
{
   namespace StartUp
   {
      /**
      *
      *  \ingroup StartUp
      *
      *  Loads a RenderWare Studio Stream from a file, RenderWare studio streams
      *  contain the description of a complete level.
      *
      *  \param pFileName String containing the name of the game database file to load.
      *
      */
      bool LoadGameDatabaseFile(RwChar *pFileName, RwBool checkExistsOnly)
      {
         RWS_FUNCTION("Startup::LoadGameDatabaseFile");

         DECOMP_DEBUG_PRINT("LOAD %s\n",pFileName);

         RwStream* pStream = RwStreamOpen(rwSTREAMFILENAME, rwSTREAMREAD, pFileName);

         DECOMP_DEBUG_PRINT("[ProcessStream] LOAD Was stream opened?: %d\n", pStream != NULL);

         if (pStream)
         {
            DECOMP_DEBUG_PRINT("Processing %s\n",pFileName);
            CStreamHandler::ProcessStream(pStream);
            DECOMP_DEBUG_PRINT("Closing %s\n",pFileName);

            RwStreamClose(pStream, pFileName);

            RWS_RETURN(true);
         }

         RWS_RETURN(false);
      }
   }
}