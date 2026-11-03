// MADDECOMP_CREATED

#ifndef __CTFBWORLD_H__
#define __CTFBWORLD_H__

//////////////////////////////////////////////////////////////////
//
// RenderWare Includes
//
#include <rwcore.h>
#include <rpworld.h>
#include <rtcharse.h>

#ifdef _MSC_VER
#pragma comment(lib, "rwcore.lib")
#pragma comment(lib, "rpworld.lib")
#pragma comment(lib, "rtcharse.lib")
#endif

//////////////////////////////////////////////////////////////////
//
// RenderWare Studio Includes
//
#include "framework/core/eventhandler/ceventhandler.h"
#include "framework/core/attributehandler/cattributehandler.h"
#include "framework/core/attributehandler/csystemcommands.h"
#include "framework/core/streamhandler/strfunc.h"
#include "framework/core/attributehandler/allocation policies/LinearAllocationPolicy.h"

namespace RWS
{
    namespace TFB
    {
        class CTFBWorld : public CEventHandler,
                          public CAttributeHandler,
                          public CSystemCommands,
                          public LinearAllocationPolicy
        {
        public:
            RWS_MAKENEWCLASS(CTFBWorld);
            RWS_DECLARE_CLASSID(CTFBWorld);
            RWS_CATEGORY("TFB");

            CTFBWorld(const CAttributePacket &) {}

            virtual void HandleAttributes(const CAttributePacket &attr);

            virtual void HandleEvents(CMsg &msg);

            RWS_BEGIN_COMMANDS
            // TODO: APPROPRIATE TYPES AND CONTROLS

            RWS_ATTRIBUTE(CMD_Geometry, "Geometry", "", EDIT, RwChar, DEFAULT(""))

            RWS_ATTRIBUTE(CMD_UNKNOWN, "Unknown", "", EDIT, RwChar, DEFAULT(""))

            RWS_ATTRIBUTE(CMD_NearClip, "Near Clip", "", EDIT, RwReal, DEFAULT(6)) // MAX 6
            RWS_ATTRIBUTE(CMD_FarClip, "Far Clip", "", EDIT, RwReal, DEFAULT(5000))

            RWS_MESSAGE(CMD_RenderMessage, "Render event", "", RECEIVE, 0, "3rd_person_cam")

            RWS_END_COMMANDS;


            CEventId m_renderEvent;
        };
    } // namespace TFB
} // namespace RWS

#endif