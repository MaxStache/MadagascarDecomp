#include "precomp.h"

// Left to its own devices, the MW linker will dead-strip the registrar ctors, so...
#ifdef __MWERKS__
#pragma force_active on
#pragma exceptions off // Turn off exceptions due to bug in MW Dwarf Generator for PS2, present in CW 3.04
#endif

//////////////////////////////////////////////////////////////////
//
// RenderWare Studio Includes
//
#include "ctfbworld.h"

#include "framework/core/macros/debugmacros.h"

#include "framework/decomp_helpers.h"

namespace RWS
{
    namespace TFB
    {
        RWS_IMPLEMENT_CLASSID(CTFBWorld);
        RWS_REGISTERCLASS(CTFBWorld);

        /**
         *
         *  Handle attribute updates associated with the CTFBWorld class
         *
         */
        void CTFBWorld::HandleAttributes(const CAttributePacket &attr)
        {
            RWS_FUNCTION("RWS::TFB::CTFBWorld::HandleAttributes");

            DECOMP_DEBUG_PRINT("WORLD HANDLE ATTRIBUTES \n");

            CAttributeHandler::HandleAttributes(attr);

            // TODO: HandleSystemCommands(attr);

            CAttributeCommandIterator attrIt(attr, RWS_CLASSID_OF(CTFBWorld));

            while (!attrIt.IsFinished())
            {
                DECOMP_DEBUG_PRINT("WORLDCOMMANDID %d\n", attrIt->GetCommandId());

                switch (attrIt->GetCommandId())
                {
                case CMD_RenderMessage:
                {
                    CEventId &id = m_renderEvent;
                    int priority = GetLinkedPriority(id);
                    if (priority < 0)
                        priority = 0xFFFF;

                    UnLinkMsg(id);
                    UnRegisterMsg(id);
                    RegisterMsg(id, attrIt->GetAs_RwChar_ptr(), "RwCamera*");
                    LinkMsg(id, "RwCamera*", (unsigned short)priority);
                    break;
                }
                break;
                }
                ++attrIt;
            }

            RWS_RETURNVOID();
        }

        // FUNCTION: GAME 0x0041c310
        void CTFBWorld::HandleEvents(CMsg &msg)
        {
            if (msg.Id == m_renderEvent)
            {
                DECOMP_DEBUG_PRINT("RENDEREVENT, has camera? %d\n", msg.pData != NULL);
                // LevelWorldsSetReady();
                // RenderFrame((RwCamera *)msg.pData);
                // SendLinkedMessage(m_afterRenderEvent, msg.pData);
            }

            RWS_RETURNVOID();
        }
    }
}