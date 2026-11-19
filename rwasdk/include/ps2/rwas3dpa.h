/******************************************/
/*                                        */
/*    RenderWare(TM) Audio Library        */
/*                                        */
/******************************************/

/*
 * This file is a product of Criterion Software Ltd.
 *
 * This file is provided as is with no warranties of any kind and is
 * provided without any obligation on Criterion Software Ltd.
 * or Canon Inc. to assist in its use or modification.
 *
 * Criterion Software Ltd. and Canon Inc. will not, under any
 * circumstances, be liable for any lost revenue or other damages
 * arising from the use of this file.
 *
 * Copyright (c) 2001. Criterion Software Ltd.
 * All Rights Reserved.
 */

/*************************************************************************
 *
 * Filename: <d:/dev/rwa/include/ps2/rwas3dpa.h>
 * Automatically Generated on: Fri Nov 09 11:59:05 2001
 *
 ************************************************************************/

#ifndef RWAS3DPA_H
#define RWAS3DPA_H

/*--- System Header Files ---*/
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>


/*--- Automatically derived from: d:/dev/rwa/source/ps2/sensaura/src/rwasensaurawave.h ---*/

/******************************************************************************
 * Defines/Macros & Constants
 *****************************************************************************/

#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */

extern const RwaUUID rwaS3DPAWAVEDEFID;

/******************************************************************************
 * Function Prototypes
 *****************************************************************************/

/* register the Sensaura wave definition */
RwaWaveDef* RwaS3DPAWaveDefRegister(void);

#ifdef    __cplusplus
}
#endif /* __cplusplus */


/*--- Automatically derived from: d:/dev/rwa/source/ps2/sensaura/src/rwas3dpavoice.h ---*/

/******************************************************************************
 * Defines/Macros & Constants
 *****************************************************************************/
#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */

/*TGenSectionStart_S3DPAVoiceUUID*/
extern const RwaUUID rwaS3DPAVOICEID;
/*TGenSectionFinish_S3DPAVoiceUUID*/

#ifdef    __cplusplus
}
#endif /* __cplusplus */

/*TGenSectionStart_S3DPAVoiceDestroyMacro*/
#ifndef RWADEBUG
#define RwaS3DPAVoiceDestroy(_handle) \
    RwaObjectRelease(_handle)
#endif /* !RWADEBUG */
/*TGenSectionFinish_S3DPAVoiceDestroyMacro*/

/******************************************************************************
 * Types
 *****************************************************************************/

typedef struct RwaS3DPAVoiceCreationParams RwaS3DPAVoiceCreationParams;
/**
 * \ingroup S3DPAVoice 
 * Used as the creation parameters for this object
 */
struct RwaS3DPAVoiceCreationParams
{
    RwUInt32 mode; /**<processing mode of the S3DPAVoice <BR>
                    * rwaS3DPAVOICE_MODE_POSITION <BR>
                    * rwaS3DPAVOICE_MODE_PITCH    <BR>
                    * rwaS3DPAVOICE_MODE_DOPPLER  <BR>
                    * rwaS3DPAVOICE_MODE_ZOOMFX   <BR>
                    * rwaS3DPAVOICE_MODE_LISTENERRELATIVE <BR>*/
};

/******************************************************************************
 * Functions
 *****************************************************************************/

#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */

/*TGenSectionStart_S3DPAVoiceCreate*/
/* create S3DPAVoice */
RwaObjHandle *RwaS3DPAVoiceCreate(RwaS3DPAVoiceCreationParams *creationParams);
/*TGenSectionFinish_S3DPAVoiceCreate*/

/*TGenSectionStart_S3DPAVoiceDestroy*/
#ifdef RWADEBUG
/* destroy S3DPAVoice */
void RwaS3DPAVoiceDestroy(RwaObjHandle *objHandle);
#endif /* RWADEBUG */
/*TGenSectionFinish_S3DPAVoiceDestroy*/

/*TGenSectionStart_S3DPAVoiceRegister*/
/* register S3DPAVoice object definition */
RwaObjDef* RwaS3DPAVoiceRegister(void);
/*TGenSectionFinish_S3DPAVoiceRegister*/

#ifdef    __cplusplus
}
#endif /* __cplusplus */


/*--- Automatically derived from: d:/dev/rwa/source/ps2/sensaura/src/rwas3dpavoiceintf.h ---*/


/******************************************************************************
 * Defines/Macros & Constants
 *****************************************************************************/

/*TGenSectionStart_S3DPAVoiceInterfaceName*/
/* object interface's name */
#ifdef RWADEBUG
#define rwaS3DPAVOICEINTERFACENAME "S3DPAVoice Interface"
#else
#define rwaS3DPAVOICEINTERFACENAME ""
#endif /* RWADEBUG */
/*TGenSectionFinish_S3DPAVoiceInterfaceName*/

/*TGenSectionStart_S3DPAVoiceParameterNames*/
/* object interface's parameter names */
#ifdef RWADEBUG
#define rwaS3DPAVOICENAMEI_FREQUENCY "FrequencyI" 
#define rwaS3DPAVOICENAMEO_FREQUENCY "FrequencyO" 
#define rwaS3DPAVOICENAMEI_GAIN "GainI" 
#define rwaS3DPAVOICENAMEO_GAIN "GainO" 
#define rwaS3DPAVOICENAMEI_LOOPING "LoopingI" 
#define rwaS3DPAVOICENAMEO_LOOPING "LoopingO" 
#define rwaS3DPAVOICENAMEI_POSITION "PositionI" 
#define rwaS3DPAVOICENAMEO_POSITION "PositionO" 
#define rwaS3DPAVOICENAMEI_VELOCITY "VelocityI" 
#define rwaS3DPAVOICENAMEO_VELOCITY "VelocityO" 
#define rwaS3DPAVOICENAMEI_CONEDIR "ConeDirI" 
#define rwaS3DPAVOICENAMEO_CONEDIR "ConeDirO" 
#define rwaS3DPAVOICENAMEI_CONEINNER "ConeInnerI" 
#define rwaS3DPAVOICENAMEO_CONEINNER "ConeInnerO" 
#define rwaS3DPAVOICENAMEI_CONEOUTER "ConeOuterI" 
#define rwaS3DPAVOICENAMEO_CONEOUTER "ConeOuterO" 
#define rwaS3DPAVOICENAMEI_CONEOUTERGAIN "ConeOuterGainI" 
#define rwaS3DPAVOICENAMEO_CONEOUTERGAIN "ConeOuterGainO" 
#define rwaS3DPAVOICENAMEI_REFDISTANCE "RefDistanceI" 
#define rwaS3DPAVOICENAMEO_REFDISTANCE "RefDistanceO" 
#define rwaS3DPAVOICENAMEI_MAXDISTANCE "MaxDistanceI" 
#define rwaS3DPAVOICENAMEO_MAXDISTANCE "MaxDistanceO" 
#define rwaS3DPAVOICENAMEI_MACROFXLEVEL "MacroFXLevelI" 
#define rwaS3DPAVOICENAMEO_MACROFXLEVEL "MacroFXLevelO" 
#define rwaS3DPAVOICENAMEI_ZOOMFXBOXLT "ZoomFXBoxLTI" 
#define rwaS3DPAVOICENAMEO_ZOOMFXBOXLT "ZoomFXBoxLTO" 
#define rwaS3DPAVOICENAMEI_ZOOMFXBOXRB "ZoomFXBoxRBI" 
#define rwaS3DPAVOICENAMEO_ZOOMFXBOXRB "ZoomFXBoxRBO" 
#define rwaS3DPAVOICENAMEI_ZOOMFXBOXORIENT "ZoomFXBoxOrientI" 
#define rwaS3DPAVOICENAMEO_ZOOMFXBOXORIENT "ZoomFXBoxOrientO" 
#define rwaS3DPAVOICENAMEI_ZOOMFXBOXAT "ZoomFXBoxAtI" 
#define rwaS3DPAVOICENAMEO_ZOOMFXBOXAT "ZoomFXBoxAtO" 
#define rwaS3DPAVOICENAMEI_ZOOMFXBOXUP "ZoomFXBoxUpI" 
#define rwaS3DPAVOICENAMEO_ZOOMFXBOXUP "ZoomFXBoxUpO" 
#define rwaS3DPAVOICENAMEO_MODE "ModeO" 
#define rwaS3DPAVOICENAMEI_TRIGGER "TriggerI" 
#define rwaS3DPAVOICENAMEI_WAVE "WaveI" 
#define rwaS3DPAVOICENAMEO_PLAYING "PlayingO" 
#define rwaS3DPAVOICENAMEI_ENVFXDIRECT "EnvFXDirectI" 
#define rwaS3DPAVOICENAMEO_ENVFXDIRECT "EnvFXDirectO" 
#define rwaS3DPAVOICENAMEI_ENVFXDIRECTHF "EnvFXDirectHFI" 
#define rwaS3DPAVOICENAMEO_ENVFXDIRECTHF "EnvFXDirectHFO" 
#define rwaS3DPAVOICENAMEI_ENVFXLEVEL "EnvFXLevelI" 
#define rwaS3DPAVOICENAMEO_ENVFXLEVEL "EnvFXLevelO" 
#define rwaS3DPAVOICENAMEI_ENVFXLEVELHF "EnvFXLevelHFI" 
#define rwaS3DPAVOICENAMEO_ENVFXLEVELHF "EnvFXLevelHFO" 
#define rwaS3DPAVOICENAMEI_ENVFXROLLOFF "EnvFXRolloffI" 
#define rwaS3DPAVOICENAMEO_ENVFXROLLOFF "EnvFXRolloffO" 
#define rwaS3DPAVOICENAMEI_ENVFXOBSTR "EnvFXObstrI" 
#define rwaS3DPAVOICENAMEO_ENVFXOBSTR "EnvFXObstrO" 
#define rwaS3DPAVOICENAMEI_ENVFXOBSTRLF "EnvFXObstrLFI" 
#define rwaS3DPAVOICENAMEO_ENVFXOBSTRLF "EnvFXObstrLFO" 
#define rwaS3DPAVOICENAMEI_ENVFXOCCL "EnvFXOcclI" 
#define rwaS3DPAVOICENAMEO_ENVFXOCCL "EnvFXOcclO" 
#define rwaS3DPAVOICENAMEI_ENVFXOCCLLF "EnvFXOcclLFI" 
#define rwaS3DPAVOICENAMEO_ENVFXOCCLLF "EnvFXOcclLFO" 
#define rwaS3DPAVOICENAMEO_WAVE "WaveO" 
#define rwaS3DPAVOICENAMEI_WAVEPOSITION "WavePositionI" 
#define rwaS3DPAVOICENAMEO_WAVEPOSITION "WavePositionO" 
#define rwaS3DPAVOICENAMEI_PAN "PanI" 
#define rwaS3DPAVOICENAMEO_PAN "PanO" 
#define rwaS3DPAVOICENAMEO_ISSTEREO "IsStereoO" 
#else
#define rwaS3DPAVOICENAMEI_FREQUENCY "" 
#define rwaS3DPAVOICENAMEO_FREQUENCY "" 
#define rwaS3DPAVOICENAMEI_GAIN "" 
#define rwaS3DPAVOICENAMEO_GAIN "" 
#define rwaS3DPAVOICENAMEI_LOOPING "" 
#define rwaS3DPAVOICENAMEO_LOOPING "" 
#define rwaS3DPAVOICENAMEI_POSITION "" 
#define rwaS3DPAVOICENAMEO_POSITION "" 
#define rwaS3DPAVOICENAMEI_VELOCITY "" 
#define rwaS3DPAVOICENAMEO_VELOCITY "" 
#define rwaS3DPAVOICENAMEI_CONEDIR "" 
#define rwaS3DPAVOICENAMEO_CONEDIR "" 
#define rwaS3DPAVOICENAMEI_CONEINNER "" 
#define rwaS3DPAVOICENAMEO_CONEINNER "" 
#define rwaS3DPAVOICENAMEI_CONEOUTER "" 
#define rwaS3DPAVOICENAMEO_CONEOUTER "" 
#define rwaS3DPAVOICENAMEI_CONEOUTERGAIN "" 
#define rwaS3DPAVOICENAMEO_CONEOUTERGAIN "" 
#define rwaS3DPAVOICENAMEI_REFDISTANCE "" 
#define rwaS3DPAVOICENAMEO_REFDISTANCE "" 
#define rwaS3DPAVOICENAMEI_MAXDISTANCE "" 
#define rwaS3DPAVOICENAMEO_MAXDISTANCE "" 
#define rwaS3DPAVOICENAMEI_MACROFXLEVEL "" 
#define rwaS3DPAVOICENAMEO_MACROFXLEVEL "" 
#define rwaS3DPAVOICENAMEI_ZOOMFXBOXLT "" 
#define rwaS3DPAVOICENAMEO_ZOOMFXBOXLT "" 
#define rwaS3DPAVOICENAMEI_ZOOMFXBOXRB "" 
#define rwaS3DPAVOICENAMEO_ZOOMFXBOXRB "" 
#define rwaS3DPAVOICENAMEI_ZOOMFXBOXORIENT "" 
#define rwaS3DPAVOICENAMEO_ZOOMFXBOXORIENT "" 
#define rwaS3DPAVOICENAMEI_ZOOMFXBOXAT "" 
#define rwaS3DPAVOICENAMEO_ZOOMFXBOXAT "" 
#define rwaS3DPAVOICENAMEI_ZOOMFXBOXUP "" 
#define rwaS3DPAVOICENAMEO_ZOOMFXBOXUP "" 
#define rwaS3DPAVOICENAMEO_MODE "" 
#define rwaS3DPAVOICENAMEI_TRIGGER "" 
#define rwaS3DPAVOICENAMEI_WAVE "" 
#define rwaS3DPAVOICENAMEO_PLAYING "" 
#define rwaS3DPAVOICENAMEI_ENVFXDIRECT "" 
#define rwaS3DPAVOICENAMEO_ENVFXDIRECT "" 
#define rwaS3DPAVOICENAMEI_ENVFXDIRECTHF "" 
#define rwaS3DPAVOICENAMEO_ENVFXDIRECTHF "" 
#define rwaS3DPAVOICENAMEI_ENVFXLEVEL "" 
#define rwaS3DPAVOICENAMEO_ENVFXLEVEL "" 
#define rwaS3DPAVOICENAMEI_ENVFXLEVELHF "" 
#define rwaS3DPAVOICENAMEO_ENVFXLEVELHF "" 
#define rwaS3DPAVOICENAMEI_ENVFXROLLOFF "" 
#define rwaS3DPAVOICENAMEO_ENVFXROLLOFF "" 
#define rwaS3DPAVOICENAMEI_ENVFXOBSTR "" 
#define rwaS3DPAVOICENAMEO_ENVFXOBSTR "" 
#define rwaS3DPAVOICENAMEI_ENVFXOBSTRLF "" 
#define rwaS3DPAVOICENAMEO_ENVFXOBSTRLF "" 
#define rwaS3DPAVOICENAMEI_ENVFXOCCL "" 
#define rwaS3DPAVOICENAMEO_ENVFXOCCL "" 
#define rwaS3DPAVOICENAMEI_ENVFXOCCLLF "" 
#define rwaS3DPAVOICENAMEO_ENVFXOCCLLF "" 
#define rwaS3DPAVOICENAMEO_WAVE "" 
#define rwaS3DPAVOICENAMEI_WAVEPOSITION "" 
#define rwaS3DPAVOICENAMEO_WAVEPOSITION "" 
#define rwaS3DPAVOICENAMEI_PAN "" 
#define rwaS3DPAVOICENAMEO_PAN "" 
#define rwaS3DPAVOICENAMEO_ISSTEREO "" 
#endif /* RWADEBUG */
/*TGenSectionFinish_S3DPAVoiceParameterNames*/

#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */

/*TGenSectionStart_S3DPAVoiceInterfaceUUID*/
extern const RwaUUID rwaS3DPAVOICEINTERFACEID;  /* object interface's UUID */
/*TGenSectionFinish_S3DPAVoiceInterfaceUUID*/

/*----------------------------------------------------------------------------
 - object interface's input and output UUIDs
 ---------------------------------------------------------------------------*/
/*TGenSectionStart_S3DPAVoiceParameterUUIDs*/
extern const RwaUUID rwaS3DPAVOICEIDI_CONEDIR;
extern const RwaUUID rwaS3DPAVOICEIDO_CONEDIR;
extern const RwaUUID rwaS3DPAVOICEIDI_CONEINNER;
extern const RwaUUID rwaS3DPAVOICEIDO_CONEINNER;
extern const RwaUUID rwaS3DPAVOICEIDI_CONEOUTER;
extern const RwaUUID rwaS3DPAVOICEIDO_CONEOUTER;
extern const RwaUUID rwaS3DPAVOICEIDI_CONEOUTERGAIN;
extern const RwaUUID rwaS3DPAVOICEIDO_CONEOUTERGAIN;
extern const RwaUUID rwaS3DPAVOICEIDI_MACROFXLEVEL;
extern const RwaUUID rwaS3DPAVOICEIDO_MACROFXLEVEL;
extern const RwaUUID rwaS3DPAVOICEIDI_ZOOMFXBOXLT;
extern const RwaUUID rwaS3DPAVOICEIDO_ZOOMFXBOXLT;
extern const RwaUUID rwaS3DPAVOICEIDI_ZOOMFXBOXRB;
extern const RwaUUID rwaS3DPAVOICEIDO_ZOOMFXBOXRB;
extern const RwaUUID rwaS3DPAVOICEIDI_ZOOMFXBOXORIENT;
extern const RwaUUID rwaS3DPAVOICEIDO_ZOOMFXBOXORIENT;
extern const RwaUUID rwaS3DPAVOICEIDI_ZOOMFXBOXAT;
extern const RwaUUID rwaS3DPAVOICEIDO_ZOOMFXBOXAT;
extern const RwaUUID rwaS3DPAVOICEIDI_ZOOMFXBOXUP;
extern const RwaUUID rwaS3DPAVOICEIDO_ZOOMFXBOXUP;
extern const RwaUUID rwaS3DPAVOICEIDO_MODE;
extern const RwaUUID rwaS3DPAVOICEIDI_TRIGGER;
extern const RwaUUID rwaS3DPAVOICEIDO_PLAYING;
extern const RwaUUID rwaS3DPAVOICEIDI_ENVFXDIRECT;
extern const RwaUUID rwaS3DPAVOICEIDO_ENVFXDIRECT;
extern const RwaUUID rwaS3DPAVOICEIDI_ENVFXDIRECTHF;
extern const RwaUUID rwaS3DPAVOICEIDO_ENVFXDIRECTHF;
extern const RwaUUID rwaS3DPAVOICEIDI_ENVFXLEVEL;
extern const RwaUUID rwaS3DPAVOICEIDO_ENVFXLEVEL;
extern const RwaUUID rwaS3DPAVOICEIDI_ENVFXLEVELHF;
extern const RwaUUID rwaS3DPAVOICEIDO_ENVFXLEVELHF;
extern const RwaUUID rwaS3DPAVOICEIDI_ENVFXROLLOFF;
extern const RwaUUID rwaS3DPAVOICEIDO_ENVFXROLLOFF;
extern const RwaUUID rwaS3DPAVOICEIDI_ENVFXOBSTR;
extern const RwaUUID rwaS3DPAVOICEIDO_ENVFXOBSTR;
extern const RwaUUID rwaS3DPAVOICEIDI_ENVFXOBSTRLF;
extern const RwaUUID rwaS3DPAVOICEIDO_ENVFXOBSTRLF;
extern const RwaUUID rwaS3DPAVOICEIDI_ENVFXOCCL;
extern const RwaUUID rwaS3DPAVOICEIDO_ENVFXOCCL;
extern const RwaUUID rwaS3DPAVOICEIDI_ENVFXOCCLLF;
extern const RwaUUID rwaS3DPAVOICEIDO_ENVFXOCCLLF;

/*TGenSectionFinish_S3DPAVoiceParameterUUIDs*/

#ifdef    __cplusplus
}
#endif /* __cplusplus */

/*----------------------------------------------------------------------------
 - Defaults / flags and ranges
 ---------------------------------------------------------------------------*/
#ifndef FLT_MIN
#define FLT_MIN 1.175494351e-38F        /* Minimum +ve floating-point value */
#endif
#ifndef FLT_MAX
#define FLT_MAX 3.402823466e+38F        /* Maximum +ve floating-point value */
#endif
 
 /* defaults and ranges */
#define rwaS3DPAVOICE_DEFAULT_FREQUENCY 22050

#define rwaS3DPAVOICE_MIN_GAIN             0.0f
#define rwaS3DPAVOICE_MAX_GAIN             2.0f
#define rwaS3DPAVOICE_UNITY_GAIN           1.0f
#define rwaS3DPAVOICE_DEFAULT_GAIN         rwaS3DPAVOICE_UNITY_GAIN

#define rwaS3DPAVOICE_DEFAULT_LOOPING      FALSE

#define rwaS3DPAVOICE_MIN_DISTANCE         0.0f
#define rwaS3DPAVOICE_MAX_DISTANCE         FLT_MAX
#define rwaS3DPAVOICE_DEFAULT_DISTANCE     1.0f

#define rwaS3DPAVOICE_MIN_MACROFXLEVEL     0.0f
#define rwaS3DPAVOICE_MAX_MACROFXLEVEL     2.0f
#define rwaS3DPAVOICE_DEFAULT_MACROFXLEVEL 1.0f

#define rwaS3DPAVOICE_MIN_ENVFX_DIRECT     -10000
#define rwaS3DPAVOICE_MAX_ENVFX_DIRECT     1000
#define rwaS3DPAVOICE_DEFAULT_ENVFX_DIRECT 0

#define rwaS3DPAVOICE_MIN_ENVFX_DIRECTHF     -10000
#define rwaS3DPAVOICE_MAX_ENVFX_DIRECTHF     0
#define rwaS3DPAVOICE_DEFAULT_ENVFX_DIRECTHF 0

#define rwaS3DPAVOICE_MIN_ENVFX_ENVFX      -10000
#define rwaS3DPAVOICE_MAX_ENVFX_ENVFX       1000
#define rwaS3DPAVOICE_DEFAULT_ENVFX_ENVFX   0

#define rwaS3DPAVOICE_MIN_ENVFX_ENVHF      -10000
#define rwaS3DPAVOICE_MAX_ENVFX_ENVHF      1000
#define rwaS3DPAVOICE_DEFAULT_ENVFX_ENVHF  0

#define rwaS3DPAVOICE_MIN_ENVFX_ROLLOFF      0.0f
#define rwaS3DPAVOICE_MAX_ENVFX_ROLLOFF      10.0f
#define rwaS3DPAVOICE_DEFAULT_ENVFX_ROLLOFF  0.0f

#define rwaS3DPAVOICE_MIN_ENVFX_OBSTRUCTION     -10000
#define rwaS3DPAVOICE_MAX_ENVFX_OBSTRUCTION     0
#define rwaS3DPAVOICE_DEFAULT_ENVFX_OBSTRUCTION 0

#define rwaS3DPAVOICE_MIN_ENVFX_OBSTRUCTIONLF     0.0f
#define rwaS3DPAVOICE_MAX_ENVFX_OBSTRUCTIONLF     1.0f
#define rwaS3DPAVOICE_DEFAULT_ENVFX_OBSTRUCTIONLF 0.0f

#define rwaS3DPAVOICE_MIN_ENVFX_OCCLUSION     -10000
#define rwaS3DPAVOICE_MAX_ENVFX_OCCLUSION     0
#define rwaS3DPAVOICE_DEFAULT_ENVFX_OCCLUSION 0

#define rwaS3DPAVOICE_MIN_ENVFX_OCCLUSIONLF     0.0f
#define rwaS3DPAVOICE_MAX_ENVFX_OCCLUSIONLF     1.0f
#define rwaS3DPAVOICE_DEFAULT_ENVFX_OCCLUSIONLF 0.25f

/* voice mode flags */
#define rwaS3DPAVOICE_MODE_POSITION         0x00000001
#define rwaS3DPAVOICE_MODE_PITCH            0x00000002
#define rwaS3DPAVOICE_MODE_DOPPLER          0x00000004
#define rwaS3DPAVOICE_MODE_ZOOMFX           0x00000008
#define rwaS3DPAVOICE_MODE_LISTENERRELATIVE 0x00000010
#define rwaS3DPAVOICE_MODE_DEFAULT          \
    (rwaS3DPAVOICE_MODE_POSITION | rwaS3DPAVOICE_MODE_PITCH | \
     rwaS3DPAVOICE_MODE_DOPPLER | rwaS3DPAVOICE_MODE_ZOOMFX)

/******************************************************************************
 * Types
 *****************************************************************************/

/* object input and output indexes */
/*TGenSectionStart_S3DPAVoiceIndexes*/
typedef enum
{   
    rwaS3DPAVOICEIDXIN_FREQUENCY = 0,
    rwaS3DPAVOICEIDXIN_GAIN = 1,
    rwaS3DPAVOICEIDXIN_LOOPING = 2,
    rwaS3DPAVOICEIDXIN_POSITION = 3,
    rwaS3DPAVOICEIDXIN_VELOCITY = 4,
    rwaS3DPAVOICEIDXIN_CONEDIR = 5,
    rwaS3DPAVOICEIDXIN_CONEINNER = 6,
    rwaS3DPAVOICEIDXIN_CONEOUTER = 7,
    rwaS3DPAVOICEIDXIN_CONEOUTERGAIN = 8,
    rwaS3DPAVOICEIDXIN_REFDISTANCE = 9,
    rwaS3DPAVOICEIDXIN_MAXDISTANCE = 10,
    rwaS3DPAVOICEIDXIN_MACROFXLEVEL = 11,
    rwaS3DPAVOICEIDXIN_ZOOMFXBOXLT = 12,
    rwaS3DPAVOICEIDXIN_ZOOMFXBOXRB = 13,
    rwaS3DPAVOICEIDXIN_ZOOMFXBOXORIENT = 14,
    rwaS3DPAVOICEIDXIN_ZOOMFXBOXAT = 15,
    rwaS3DPAVOICEIDXIN_ZOOMFXBOXUP = 16,
    rwaS3DPAVOICEIDXIN_TRIGGER = 17,
    rwaS3DPAVOICEIDXIN_WAVE = 18,
    rwaS3DPAVOICEIDXIN_ENVFXDIRECT = 19,
    rwaS3DPAVOICEIDXIN_ENVFXDIRECTHF = 20,
    rwaS3DPAVOICEIDXIN_ENVFXLEVEL = 21,
    rwaS3DPAVOICEIDXIN_ENVFXLEVELHF = 22,
    rwaS3DPAVOICEIDXIN_ENVFXROLLOFF = 23,
    rwaS3DPAVOICEIDXIN_ENVFXOBSTR = 24,
    rwaS3DPAVOICEIDXIN_ENVFXOBSTRLF = 25,
    rwaS3DPAVOICEIDXIN_ENVFXOCCL = 26,
    rwaS3DPAVOICEIDXIN_ENVFXOCCLLF = 27,
    rwaS3DPAVOICEIDXIN_WAVEPOSITION = 28,
    rwaS3DPAVOICEIDXIN_PAN = 29,
    rwaS3DPAVOICEIDXIN_FORCEENUMSIZEINT = RWFORCEENUMSIZEINT
} rwaS3DPAVOICEIDXIN;

typedef enum
{
    rwaS3DPAVOICEIDXOUT_FREQUENCY = 0,
    rwaS3DPAVOICEIDXOUT_GAIN = 1,
    rwaS3DPAVOICEIDXOUT_LOOPING = 2,
    rwaS3DPAVOICEIDXOUT_POSITION = 3,
    rwaS3DPAVOICEIDXOUT_VELOCITY = 4,
    rwaS3DPAVOICEIDXOUT_CONEDIR = 5,
    rwaS3DPAVOICEIDXOUT_CONEINNER = 6,
    rwaS3DPAVOICEIDXOUT_CONEOUTER = 7,
    rwaS3DPAVOICEIDXOUT_CONEOUTERGAIN = 8,
    rwaS3DPAVOICEIDXOUT_REFDISTANCE = 9,
    rwaS3DPAVOICEIDXOUT_MAXDISTANCE = 10,
    rwaS3DPAVOICEIDXOUT_MACROFXLEVEL = 11,
    rwaS3DPAVOICEIDXOUT_ZOOMFXBOXLT = 12,
    rwaS3DPAVOICEIDXOUT_ZOOMFXBOXRB = 13,
    rwaS3DPAVOICEIDXOUT_ZOOMFXBOXORIENT = 14,
    rwaS3DPAVOICEIDXOUT_ZOOMFXBOXAT = 15,
    rwaS3DPAVOICEIDXOUT_ZOOMFXBOXUP = 16,
    rwaS3DPAVOICEIDXOUT_MODE = 17,
    rwaS3DPAVOICEIDXOUT_PLAYING = 18,
    rwaS3DPAVOICEIDXOUT_ENVFXDIRECT = 19,
    rwaS3DPAVOICEIDXOUT_ENVFXDIREHF = 20,
    rwaS3DPAVOICEIDXOUT_ENVFXLEVEL = 21,
    rwaS3DPAVOICEIDXOUT_ENVFXLEVELHF = 22,
    rwaS3DPAVOICEIDXOUT_ENVFXROLLOFF = 23,
    rwaS3DPAVOICEIDXOUT_ENVFXOBSTR = 24,
    rwaS3DPAVOICEIDXOUT_ENVFXOBSTRLF = 25,
    rwaS3DPAVOICEIDXOUT_ENVFXOCCL = 26,
    rwaS3DPAVOICEIDXOUT_ENVFXOCCLLF = 27,
    rwaS3DPAVOICEIDXOUT_WAVE = 28,
    rwaS3DPAVOICEIDXOUT_WAVEPOSITION = 29,
    rwaS3DPAVOICEIDXOUT_PAN = 30,
    rwaS3DPAVOICEIDXOUT_ISSTEREO = 31,
    rwaS3DPAVOICEIDXOUT_FORCEENUMSIZEINT = RWFORCEENUMSIZEINT
} rwaS3DPAVOICEIDXOUT;
/*TGenSectionFinish_S3DPAVoiceIndexes*/

/******************************************************************************
 * Functions
 *****************************************************************************/

#ifdef RWADEBUG
#if !defined (RWADOXYGEN)
#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */

/*TGenSectionStart_S3DPAVoiceSet0*/
RwaObjHandle* RwaS3DPAVoiceSetFrequency( RwaObjHandle *objHandle, RwInt32 value);
/*TGenSectionFinish_S3DPAVoiceSet0*/
/*TGenSectionStart_S3DPAVoiceGet0*/
RwInt32 RwaS3DPAVoiceGetFrequency( RwaObjHandle *object );
/*TGenSectionFinish_S3DPAVoiceGet0*/
/*TGenSectionStart_S3DPAVoiceSet1*/
RwaObjHandle* RwaS3DPAVoiceSetGain( RwaObjHandle *objHandle, RwReal value);
/*TGenSectionFinish_S3DPAVoiceSet1*/
/*TGenSectionStart_S3DPAVoiceGet1*/
RwReal RwaS3DPAVoiceGetGain( RwaObjHandle *object );
/*TGenSectionFinish_S3DPAVoiceGet1*/
/*TGenSectionStart_S3DPAVoiceSet2*/
RwaObjHandle* RwaS3DPAVoiceSetLoop( RwaObjHandle *objHandle, RwBool value);
/*TGenSectionFinish_S3DPAVoiceSet2*/
/*TGenSectionStart_S3DPAVoiceGet2*/
RwBool RwaS3DPAVoiceGetLoop( RwaObjHandle *object );
/*TGenSectionFinish_S3DPAVoiceGet2*/
/*TGenSectionStart_S3DPAVoiceSet3*/
RwaObjHandle* RwaS3DPAVoiceSetPos( RwaObjHandle *objHandle, RwV3d *data );
/*TGenSectionFinish_S3DPAVoiceSet3*/
/*TGenSectionStart_S3DPAVoiceGet3*/
RwaObjHandle* RwaS3DPAVoiceGetPos( RwaObjHandle *object, RwV3d *data );
/*TGenSectionFinish_S3DPAVoiceGet3*/
/*TGenSectionStart_S3DPAVoiceSet4*/
RwaObjHandle* RwaS3DPAVoiceSetVel( RwaObjHandle *objHandle, RwV3d *data );
/*TGenSectionFinish_S3DPAVoiceSet4*/
/*TGenSectionStart_S3DPAVoiceGet4*/
RwaObjHandle* RwaS3DPAVoiceGetVel( RwaObjHandle *object, RwV3d *data );
/*TGenSectionFinish_S3DPAVoiceGet4*/
/*TGenSectionStart_S3DPAVoiceSet5*/
RwaObjHandle* RwaS3DPAVoiceSetConeDir( RwaObjHandle *objHandle, RwV3d *data );
/*TGenSectionFinish_S3DPAVoiceSet5*/
/*TGenSectionStart_S3DPAVoiceGet5*/
RwaObjHandle* RwaS3DPAVoiceGetConeDir( RwaObjHandle *object, RwV3d *data );
/*TGenSectionFinish_S3DPAVoiceGet5*/
/*TGenSectionStart_S3DPAVoiceSet6*/
RwaObjHandle* RwaS3DPAVoiceSetConeInner( RwaObjHandle *objHandle, RwUInt32 value);
/*TGenSectionFinish_S3DPAVoiceSet6*/
/*TGenSectionStart_S3DPAVoiceGet6*/
RwUInt32 RwaS3DPAVoiceGetConeInner( RwaObjHandle *object );
/*TGenSectionFinish_S3DPAVoiceGet6*/
/*TGenSectionStart_S3DPAVoiceSet7*/
RwaObjHandle* RwaS3DPAVoiceSetConeOuter( RwaObjHandle *objHandle, RwUInt32 value);
/*TGenSectionFinish_S3DPAVoiceSet7*/
/*TGenSectionStart_S3DPAVoiceGet7*/
RwUInt32 RwaS3DPAVoiceGetConeOuter( RwaObjHandle *object );
/*TGenSectionFinish_S3DPAVoiceGet7*/
/*TGenSectionStart_S3DPAVoiceSet8*/
RwaObjHandle* RwaS3DPAVoiceSetConeOuterGain( RwaObjHandle *objHandle, RwReal value);
/*TGenSectionFinish_S3DPAVoiceSet8*/
/*TGenSectionStart_S3DPAVoiceGet8*/
RwReal RwaS3DPAVoiceGetConeOuterGain( RwaObjHandle *object );
/*TGenSectionFinish_S3DPAVoiceGet8*/
/*TGenSectionStart_S3DPAVoiceSet9*/
RwaObjHandle* RwaS3DPAVoiceSetMinDistance( RwaObjHandle *objHandle, RwReal value);
/*TGenSectionFinish_S3DPAVoiceSet9*/
/*TGenSectionStart_S3DPAVoiceGet9*/
RwReal RwaS3DPAVoiceGetMinDistance( RwaObjHandle *object );
/*TGenSectionFinish_S3DPAVoiceGet9*/
/*TGenSectionStart_S3DPAVoiceSet10*/
RwaObjHandle* RwaS3DPAVoiceSetMaxDistance( RwaObjHandle *objHandle, RwReal value);
/*TGenSectionFinish_S3DPAVoiceSet10*/
/*TGenSectionStart_S3DPAVoiceGet10*/
RwReal RwaS3DPAVoiceGetMaxDistance( RwaObjHandle *object );
/*TGenSectionFinish_S3DPAVoiceGet10*/
/*TGenSectionStart_S3DPAVoiceSet11*/
RwaObjHandle* RwaS3DPAVoiceSetMacroFXLevel( RwaObjHandle *objHandle, RwReal value);
/*TGenSectionFinish_S3DPAVoiceSet11*/
/*TGenSectionStart_S3DPAVoiceGet11*/
RwReal RwaS3DPAVoiceGetMacroFXLevel( RwaObjHandle *object );
/*TGenSectionFinish_S3DPAVoiceGet11*/
/*TGenSectionStart_S3DPAVoiceSet12*/
RwaObjHandle* RwaS3DPAVoiceSetZoomFXBoxLT( RwaObjHandle *objHandle, RwV3d *data );
/*TGenSectionFinish_S3DPAVoiceSet12*/
/*TGenSectionStart_S3DPAVoiceGet12*/
RwaObjHandle* RwaS3DPAVoiceGetZoomFXBoxLT( RwaObjHandle *object, RwV3d *data );
/*TGenSectionFinish_S3DPAVoiceGet12*/
/*TGenSectionStart_S3DPAVoiceSet13*/
RwaObjHandle* RwaS3DPAVoiceSetZoomFXBoxRB( RwaObjHandle *objHandle, RwV3d *data );
/*TGenSectionFinish_S3DPAVoiceSet13*/
/*TGenSectionStart_S3DPAVoiceGet13*/
RwaObjHandle* RwaS3DPAVoiceGetZoomFXBoxRB( RwaObjHandle *object, RwV3d *data );
/*TGenSectionFinish_S3DPAVoiceGet13*/
/*TGenSectionStart_S3DPAVoiceSet14*/
RwaObjHandle* RwaS3DPAVoiceSetZoomFXBoxOrient( RwaObjHandle *objHandle, RwMatrix *data );
/*TGenSectionFinish_S3DPAVoiceSet14*/
/*TGenSectionStart_S3DPAVoiceGet14*/
RwaObjHandle* RwaS3DPAVoiceGetZoomFXBoxOrient( RwaObjHandle *object, RwMatrix *data );
/*TGenSectionFinish_S3DPAVoiceGet14*/
/*TGenSectionStart_S3DPAVoiceSet15*/
RwaObjHandle* RwaS3DPAVoiceSetZoomFXBoxAt( RwaObjHandle *objHandle, RwV3d *data );
/*TGenSectionFinish_S3DPAVoiceSet15*/
/*TGenSectionStart_S3DPAVoiceGet15*/
RwaObjHandle* RwaS3DPAVoiceGetZoomFXBoxAt( RwaObjHandle *object, RwV3d *data );
/*TGenSectionFinish_S3DPAVoiceGet15*/
/*TGenSectionStart_S3DPAVoiceSet16*/
RwaObjHandle* RwaS3DPAVoiceSetZoomFXBoxUp( RwaObjHandle *objHandle, RwV3d *data );
/*TGenSectionFinish_S3DPAVoiceSet16*/
/*TGenSectionStart_S3DPAVoiceGet16*/
RwaObjHandle* RwaS3DPAVoiceGetZoomFXBoxUp( RwaObjHandle *object, RwV3d *data );
/*TGenSectionFinish_S3DPAVoiceGet16*/
/*TGenSectionStart_S3DPAVoiceGet17*/
RwUInt32 RwaS3DPAVoiceGetMode( RwaObjHandle *object );
/*TGenSectionFinish_S3DPAVoiceGet17*/
/*TGenSectionStart_S3DPAVoiceSet17*/
RwaObjHandle* RwaS3DPAVoiceSetTrigger( RwaObjHandle *objHandle, RwBool value);
/*TGenSectionFinish_S3DPAVoiceSet17*/
/*TGenSectionStart_S3DPAVoiceSet18*/
RwaObjHandle* RwaS3DPAVoiceSetWave( RwaObjHandle *objHandle, RwaWave *data );
/*TGenSectionFinish_S3DPAVoiceSet18*/
/*TGenSectionStart_S3DPAVoiceGet18*/
RwBool RwaS3DPAVoiceGetPlaying( RwaObjHandle *object );
/*TGenSectionFinish_S3DPAVoiceGet18*/
/*TGenSectionStart_S3DPAVoiceSet19*/
RwaObjHandle* RwaS3DPAVoiceSetEnvFXDirect( RwaObjHandle *objHandle, RwInt32 value);
/*TGenSectionFinish_S3DPAVoiceSet19*/
/*TGenSectionStart_S3DPAVoiceGet19*/
RwInt32 RwaS3DPAVoiceGetEnvFXDirect( RwaObjHandle *object );
/*TGenSectionFinish_S3DPAVoiceGet19*/
/*TGenSectionStart_S3DPAVoiceSet20*/
RwaObjHandle* RwaS3DPAVoiceSetEnvFXDirectHF( RwaObjHandle *objHandle, RwInt32 value);
/*TGenSectionFinish_S3DPAVoiceSet20*/
/*TGenSectionStart_S3DPAVoiceGet20*/
RwInt32 RwaS3DPAVoiceGetEnvFXDirectHF( RwaObjHandle *object );
/*TGenSectionFinish_S3DPAVoiceGet20*/
/*TGenSectionStart_S3DPAVoiceSet21*/
RwaObjHandle* RwaS3DPAVoiceSetEnvFXLevel( RwaObjHandle *objHandle, RwInt32 value);
/*TGenSectionFinish_S3DPAVoiceSet21*/
/*TGenSectionStart_S3DPAVoiceGet21*/
RwInt32 RwaS3DPAVoiceGetEnvFXLevel( RwaObjHandle *object );
/*TGenSectionFinish_S3DPAVoiceGet21*/
/*TGenSectionStart_S3DPAVoiceSet22*/
RwaObjHandle* RwaS3DPAVoiceSetEnvFXLevelHF( RwaObjHandle *objHandle, RwInt32 value);
/*TGenSectionFinish_S3DPAVoiceSet22*/
/*TGenSectionStart_S3DPAVoiceGet22*/
RwInt32 RwaS3DPAVoiceGetEnvFXLevelHF( RwaObjHandle *object );
/*TGenSectionFinish_S3DPAVoiceGet22*/
/*TGenSectionStart_S3DPAVoiceSet23*/
RwaObjHandle* RwaS3DPAVoiceSetEnvFXRolloff( RwaObjHandle *objHandle, RwReal value);
/*TGenSectionFinish_S3DPAVoiceSet23*/
/*TGenSectionStart_S3DPAVoiceGet23*/
RwReal RwaS3DPAVoiceGetEnvFXRolloff( RwaObjHandle *object );
/*TGenSectionFinish_S3DPAVoiceGet23*/
/*TGenSectionStart_S3DPAVoiceSet24*/
RwaObjHandle* RwaS3DPAVoiceSetEnvFXObstr( RwaObjHandle *objHandle, RwInt32 value);
/*TGenSectionFinish_S3DPAVoiceSet24*/
/*TGenSectionStart_S3DPAVoiceGet24*/
RwInt32 RwaS3DPAVoiceGetEnvFXObstr( RwaObjHandle *object );
/*TGenSectionFinish_S3DPAVoiceGet24*/
/*TGenSectionStart_S3DPAVoiceSet25*/
RwaObjHandle* RwaS3DPAVoiceSetEnvFXObstrLF( RwaObjHandle *objHandle, RwReal value);
/*TGenSectionFinish_S3DPAVoiceSet25*/
/*TGenSectionStart_S3DPAVoiceGet25*/
RwReal RwaS3DPAVoiceGetEnvFXObstrLF( RwaObjHandle *object );
/*TGenSectionFinish_S3DPAVoiceGet25*/
/*TGenSectionStart_S3DPAVoiceSet26*/
RwaObjHandle* RwaS3DPAVoiceSetEnvFXOccl( RwaObjHandle *objHandle, RwInt32 value);
/*TGenSectionFinish_S3DPAVoiceSet26*/
/*TGenSectionStart_S3DPAVoiceGet26*/
RwInt32 RwaS3DPAVoiceGetEnvFXOccl( RwaObjHandle *object );
/*TGenSectionFinish_S3DPAVoiceGet26*/
/*TGenSectionStart_S3DPAVoiceSet27*/
RwaObjHandle* RwaS3DPAVoiceSetEnvFXOcclLF( RwaObjHandle *objHandle, RwReal value);
/*TGenSectionFinish_S3DPAVoiceSet27*/
/*TGenSectionStart_S3DPAVoiceGet27*/
RwReal RwaS3DPAVoiceGetEnvFXOcclLF( RwaObjHandle *object );
/*TGenSectionFinish_S3DPAVoiceGet27*/
/*TGenSectionStart_S3DPAVoiceGet28*/
RwaObjHandle* RwaS3DPAVoiceGetWave( RwaObjHandle *object, RwaWave *data );
/*TGenSectionFinish_S3DPAVoiceGet28*/
/*TGenSectionStart_S3DPAVoiceSet28*/
RwaObjHandle* RwaS3DPAVoiceSetWavePosition( RwaObjHandle *objHandle, RwUInt32 value);
/*TGenSectionFinish_S3DPAVoiceSet28*/
/*TGenSectionStart_S3DPAVoiceGet29*/
RwUInt32 RwaS3DPAVoiceGetWavePosition( RwaObjHandle *object );
/*TGenSectionFinish_S3DPAVoiceGet29*/
/*TGenSectionStart_S3DPAVoiceSet29*/
RwaObjHandle* RwaS3DPAVoiceSetPan( RwaObjHandle *objHandle, RwReal value);
/*TGenSectionFinish_S3DPAVoiceSet29*/
/*TGenSectionStart_S3DPAVoiceGet30*/
RwReal RwaS3DPAVoiceGetPan( RwaObjHandle *object );
/*TGenSectionFinish_S3DPAVoiceGet30*/
/*TGenSectionStart_S3DPAVoiceGet31*/
RwBool RwaS3DPAVoiceGetIsStereo( RwaObjHandle *object );
/*TGenSectionFinish_S3DPAVoiceGet31*/
#ifdef    __cplusplus
}
#endif /* __cplusplus */
#endif /* RWADOXYGEN */
#else
/*-----------------------------------------------------------------------------
 - Set parameter and get parameter functions and macros
 ----------------------------------------------------------------------------*/

/*TGenSectionStart_S3DPAVoiceSet0Macro*/
#define RwaS3DPAVoiceSetFrequency(_object, _value) \
            RwaObjectSetParamInt32(_object, \
                rwaS3DPAVOICEIDXIN_FREQUENCY, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_S3DPAVoiceSet0Macro*/
/*TGenSectionStart_S3DPAVoiceGet0Macro*/
#define RwaS3DPAVoiceGetFrequency(_object) \
            RwaObjectGetParamInt32(_object, \
                rwaS3DPAVOICEIDXOUT_FREQUENCY, rwaIOPARAM_OUTPUT, NULL)
/*TGenSectionFinish_S3DPAVoiceGet0Macro*/
/*TGenSectionStart_S3DPAVoiceSet1Macro*/
#define RwaS3DPAVoiceSetGain(_object, _value) \
            RwaObjectSetParamReal(_object, \
                rwaS3DPAVOICEIDXIN_GAIN, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_S3DPAVoiceSet1Macro*/
/*TGenSectionStart_S3DPAVoiceGet1Macro*/
#define RwaS3DPAVoiceGetGain(_object) \
            RwaObjectGetParamReal(_object, \
                rwaS3DPAVOICEIDXOUT_GAIN, rwaIOPARAM_OUTPUT, NULL)
/*TGenSectionFinish_S3DPAVoiceGet1Macro*/
/*TGenSectionStart_S3DPAVoiceSet2Macro*/
#define RwaS3DPAVoiceSetLoop(_object, _value) \
            RwaObjectSetParamBool(_object, \
                rwaS3DPAVOICEIDXIN_LOOPING, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_S3DPAVoiceSet2Macro*/
/*TGenSectionStart_S3DPAVoiceGet2Macro*/
#define RwaS3DPAVoiceGetLoop(_object) \
            RwaObjectGetParamBool(_object, \
                rwaS3DPAVOICEIDXOUT_LOOPING, rwaIOPARAM_OUTPUT, NULL)
/*TGenSectionFinish_S3DPAVoiceGet2Macro*/
/*TGenSectionStart_S3DPAVoiceSet3Macro*/
#define RwaS3DPAVoiceSetPos(_object, _ptr) \
            RwaObjectSetParamData(_object, \
                rwaS3DPAVOICEIDXIN_POSITION, rwaIOPARAM_INPUT, _ptr)
/*TGenSectionFinish_S3DPAVoiceSet3Macro*/
/*TGenSectionStart_S3DPAVoiceGet3Macro*/
#define RwaS3DPAVoiceGetPos(_object, _ptr) \
            RwaObjectGetParamData(_object, \
                rwaS3DPAVOICEIDXOUT_POSITION, rwaIOPARAM_OUTPUT, _ptr)
/*TGenSectionFinish_S3DPAVoiceGet3Macro*/
/*TGenSectionStart_S3DPAVoiceSet4Macro*/
#define RwaS3DPAVoiceSetVel(_object, _ptr) \
            RwaObjectSetParamData(_object, \
                rwaS3DPAVOICEIDXIN_VELOCITY, rwaIOPARAM_INPUT, _ptr)
/*TGenSectionFinish_S3DPAVoiceSet4Macro*/
/*TGenSectionStart_S3DPAVoiceGet4Macro*/
#define RwaS3DPAVoiceGetVel(_object, _ptr) \
            RwaObjectGetParamData(_object, \
                rwaS3DPAVOICEIDXOUT_VELOCITY, rwaIOPARAM_OUTPUT, _ptr)
/*TGenSectionFinish_S3DPAVoiceGet4Macro*/
/*TGenSectionStart_S3DPAVoiceSet5Macro*/
#define RwaS3DPAVoiceSetConeDir(_object, _ptr) \
            RwaObjectSetParamData(_object, \
                rwaS3DPAVOICEIDXIN_CONEDIR, rwaIOPARAM_INPUT, _ptr)
/*TGenSectionFinish_S3DPAVoiceSet5Macro*/
/*TGenSectionStart_S3DPAVoiceGet5Macro*/
#define RwaS3DPAVoiceGetConeDir(_object, _ptr) \
            RwaObjectGetParamData(_object, \
                rwaS3DPAVOICEIDXOUT_CONEDIR, rwaIOPARAM_OUTPUT, _ptr)
/*TGenSectionFinish_S3DPAVoiceGet5Macro*/
/*TGenSectionStart_S3DPAVoiceSet6Macro*/
#define RwaS3DPAVoiceSetConeInner(_object, _value) \
            RwaObjectSetParamUInt32(_object, \
                rwaS3DPAVOICEIDXIN_CONEINNER, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_S3DPAVoiceSet6Macro*/
/*TGenSectionStart_S3DPAVoiceGet6Macro*/
#define RwaS3DPAVoiceGetConeInner(_object) \
            RwaObjectGetParamUInt32(_object, \
                rwaS3DPAVOICEIDXOUT_CONEINNER, rwaIOPARAM_OUTPUT, NULL)
/*TGenSectionFinish_S3DPAVoiceGet6Macro*/
/*TGenSectionStart_S3DPAVoiceSet7Macro*/
#define RwaS3DPAVoiceSetConeOuter(_object, _value) \
            RwaObjectSetParamUInt32(_object, \
                rwaS3DPAVOICEIDXIN_CONEOUTER, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_S3DPAVoiceSet7Macro*/
/*TGenSectionStart_S3DPAVoiceGet7Macro*/
#define RwaS3DPAVoiceGetConeOuter(_object) \
            RwaObjectGetParamUInt32(_object, \
                rwaS3DPAVOICEIDXOUT_CONEOUTER, rwaIOPARAM_OUTPUT, NULL)
/*TGenSectionFinish_S3DPAVoiceGet7Macro*/
/*TGenSectionStart_S3DPAVoiceSet8Macro*/
#define RwaS3DPAVoiceSetConeOuterGain(_object, _value) \
            RwaObjectSetParamReal(_object, \
                rwaS3DPAVOICEIDXIN_CONEOUTERGAIN, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_S3DPAVoiceSet8Macro*/
/*TGenSectionStart_S3DPAVoiceGet8Macro*/
#define RwaS3DPAVoiceGetConeOuterGain(_object) \
            RwaObjectGetParamReal(_object, \
                rwaS3DPAVOICEIDXOUT_CONEOUTERGAIN, rwaIOPARAM_OUTPUT, NULL)
/*TGenSectionFinish_S3DPAVoiceGet8Macro*/
/*TGenSectionStart_S3DPAVoiceSet9Macro*/
#define RwaS3DPAVoiceSetMinDistance(_object, _value) \
            RwaObjectSetParamReal(_object, \
                rwaS3DPAVOICEIDXIN_REFDISTANCE, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_S3DPAVoiceSet9Macro*/
/*TGenSectionStart_S3DPAVoiceGet9Macro*/
#define RwaS3DPAVoiceGetMinDistance(_object) \
            RwaObjectGetParamReal(_object, \
                rwaS3DPAVOICEIDXOUT_REFDISTANCE, rwaIOPARAM_OUTPUT, NULL)
/*TGenSectionFinish_S3DPAVoiceGet9Macro*/
/*TGenSectionStart_S3DPAVoiceSet10Macro*/
#define RwaS3DPAVoiceSetMaxDistance(_object, _value) \
            RwaObjectSetParamReal(_object, \
                rwaS3DPAVOICEIDXIN_MAXDISTANCE, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_S3DPAVoiceSet10Macro*/
/*TGenSectionStart_S3DPAVoiceGet10Macro*/
#define RwaS3DPAVoiceGetMaxDistance(_object) \
            RwaObjectGetParamReal(_object, \
                rwaS3DPAVOICEIDXOUT_MAXDISTANCE, rwaIOPARAM_OUTPUT, NULL)
/*TGenSectionFinish_S3DPAVoiceGet10Macro*/
/*TGenSectionStart_S3DPAVoiceSet11Macro*/
#define RwaS3DPAVoiceSetMacroFXLevel(_object, _value) \
            RwaObjectSetParamReal(_object, \
                rwaS3DPAVOICEIDXIN_MACROFXLEVEL, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_S3DPAVoiceSet11Macro*/
/*TGenSectionStart_S3DPAVoiceGet11Macro*/
#define RwaS3DPAVoiceGetMacroFXLevel(_object) \
            RwaObjectGetParamReal(_object, \
                rwaS3DPAVOICEIDXOUT_MACROFXLEVEL, rwaIOPARAM_OUTPUT, NULL)
/*TGenSectionFinish_S3DPAVoiceGet11Macro*/
/*TGenSectionStart_S3DPAVoiceSet12Macro*/
#define RwaS3DPAVoiceSetZoomFXBoxLT(_object, _ptr) \
            RwaObjectSetParamData(_object, \
                rwaS3DPAVOICEIDXIN_ZOOMFXBOXLT, rwaIOPARAM_INPUT, _ptr)
/*TGenSectionFinish_S3DPAVoiceSet12Macro*/
/*TGenSectionStart_S3DPAVoiceGet12Macro*/
#define RwaS3DPAVoiceGetZoomFXBoxLT(_object, _ptr) \
            RwaObjectGetParamData(_object, \
                rwaS3DPAVOICEIDXOUT_ZOOMFXBOXLT, rwaIOPARAM_OUTPUT, _ptr)
/*TGenSectionFinish_S3DPAVoiceGet12Macro*/
/*TGenSectionStart_S3DPAVoiceSet13Macro*/
#define RwaS3DPAVoiceSetZoomFXBoxRB(_object, _ptr) \
            RwaObjectSetParamData(_object, \
                rwaS3DPAVOICEIDXIN_ZOOMFXBOXRB, rwaIOPARAM_INPUT, _ptr)
/*TGenSectionFinish_S3DPAVoiceSet13Macro*/
/*TGenSectionStart_S3DPAVoiceGet13Macro*/
#define RwaS3DPAVoiceGetZoomFXBoxRB(_object, _ptr) \
            RwaObjectGetParamData(_object, \
                rwaS3DPAVOICEIDXOUT_ZOOMFXBOXRB, rwaIOPARAM_OUTPUT, _ptr)
/*TGenSectionFinish_S3DPAVoiceGet13Macro*/
/*TGenSectionStart_S3DPAVoiceSet14Macro*/
#define RwaS3DPAVoiceSetZoomFXBoxOrient(_object, _ptr) \
            RwaObjectSetParamData(_object, \
                rwaS3DPAVOICEIDXIN_ZOOMFXBOXORIENT, rwaIOPARAM_INPUT, _ptr)
/*TGenSectionFinish_S3DPAVoiceSet14Macro*/
/*TGenSectionStart_S3DPAVoiceGet14Macro*/
#define RwaS3DPAVoiceGetZoomFXBoxOrient(_object, _ptr) \
            RwaObjectGetParamData(_object, \
                rwaS3DPAVOICEIDXOUT_ZOOMFXBOXORIENT, rwaIOPARAM_OUTPUT, _ptr)
/*TGenSectionFinish_S3DPAVoiceGet14Macro*/
/*TGenSectionStart_S3DPAVoiceSet15Macro*/
#define RwaS3DPAVoiceSetZoomFXBoxAt(_object, _ptr) \
            RwaObjectSetParamData(_object, \
                rwaS3DPAVOICEIDXIN_ZOOMFXBOXAT, rwaIOPARAM_INPUT, _ptr)
/*TGenSectionFinish_S3DPAVoiceSet15Macro*/
/*TGenSectionStart_S3DPAVoiceGet15Macro*/
#define RwaS3DPAVoiceGetZoomFXBoxAt(_object, _ptr) \
            RwaObjectGetParamData(_object, \
                rwaS3DPAVOICEIDXOUT_ZOOMFXBOXAT, rwaIOPARAM_OUTPUT, _ptr)
/*TGenSectionFinish_S3DPAVoiceGet15Macro*/
/*TGenSectionStart_S3DPAVoiceSet16Macro*/
#define RwaS3DPAVoiceSetZoomFXBoxUp(_object, _ptr) \
            RwaObjectSetParamData(_object, \
                rwaS3DPAVOICEIDXIN_ZOOMFXBOXUP, rwaIOPARAM_INPUT, _ptr)
/*TGenSectionFinish_S3DPAVoiceSet16Macro*/
/*TGenSectionStart_S3DPAVoiceGet16Macro*/
#define RwaS3DPAVoiceGetZoomFXBoxUp(_object, _ptr) \
            RwaObjectGetParamData(_object, \
                rwaS3DPAVOICEIDXOUT_ZOOMFXBOXUP, rwaIOPARAM_OUTPUT, _ptr)
/*TGenSectionFinish_S3DPAVoiceGet16Macro*/
/*TGenSectionStart_S3DPAVoiceGet17Macro*/
#define RwaS3DPAVoiceGetMode(_object) \
            RwaObjectGetParamUInt32(_object, \
                rwaS3DPAVOICEIDXOUT_MODE, rwaIOPARAM_OUTPUT, NULL)
/*TGenSectionFinish_S3DPAVoiceGet17Macro*/
/*TGenSectionStart_S3DPAVoiceSet17Macro*/
#define RwaS3DPAVoiceSetTrigger(_object, _value) \
            RwaObjectSetParamBool(_object, \
                rwaS3DPAVOICEIDXIN_TRIGGER, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_S3DPAVoiceSet17Macro*/
/*TGenSectionStart_S3DPAVoiceSet18Macro*/
#define RwaS3DPAVoiceSetWave(_object, _ptr) \
            RwaObjectSetParamData(_object, \
                rwaS3DPAVOICEIDXIN_WAVE, rwaIOPARAM_INPUT, &_ptr)
/*TGenSectionFinish_S3DPAVoiceSet18Macro*/
/*TGenSectionStart_S3DPAVoiceGet18Macro*/
#define RwaS3DPAVoiceGetPlaying(_object) \
            RwaObjectGetParamBool(_object, \
                rwaS3DPAVOICEIDXOUT_PLAYING, rwaIOPARAM_OUTPUT, NULL)
/*TGenSectionFinish_S3DPAVoiceGet18Macro*/
/*TGenSectionStart_S3DPAVoiceSet19Macro*/
#define RwaS3DPAVoiceSetEnvFXDirect(_object, _value) \
            RwaObjectSetParamInt32(_object, \
                rwaS3DPAVOICEIDXIN_ENVFXDIRECT, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_S3DPAVoiceSet19Macro*/
/*TGenSectionStart_S3DPAVoiceGet19Macro*/
#define RwaS3DPAVoiceGetEnvFXDirect(_object) \
            RwaObjectGetParamInt32(_object, \
                rwaS3DPAVOICEIDXOUT_ENVFXDIRECT, rwaIOPARAM_OUTPUT, NULL)
/*TGenSectionFinish_S3DPAVoiceGet19Macro*/
/*TGenSectionStart_S3DPAVoiceSet20Macro*/
#define RwaS3DPAVoiceSetEnvFXDirectHF(_object, _value) \
            RwaObjectSetParamInt32(_object, \
                rwaS3DPAVOICEIDXIN_ENVFXDIRECTHF, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_S3DPAVoiceSet20Macro*/
/*TGenSectionStart_S3DPAVoiceGet20Macro*/
#define RwaS3DPAVoiceGetEnvFXDirectHF(_object) \
            RwaObjectGetParamInt32(_object, \
                rwaS3DPAVOICEIDXOUT_ENVFXDIRECTHF, rwaIOPARAM_OUTPUT, NULL)
/*TGenSectionFinish_S3DPAVoiceGet20Macro*/
/*TGenSectionStart_S3DPAVoiceSet21Macro*/
#define RwaS3DPAVoiceSetEnvFXLevel(_object, _value) \
            RwaObjectSetParamInt32(_object, \
                rwaS3DPAVOICEIDXIN_ENVFXLEVEL, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_S3DPAVoiceSet21Macro*/
/*TGenSectionStart_S3DPAVoiceGet21Macro*/
#define RwaS3DPAVoiceGetEnvFXLevel(_object) \
            RwaObjectGetParamInt32(_object, \
                rwaS3DPAVOICEIDXOUT_ENVFXLEVEL, rwaIOPARAM_OUTPUT, NULL)
/*TGenSectionFinish_S3DPAVoiceGet21Macro*/
/*TGenSectionStart_S3DPAVoiceSet22Macro*/
#define RwaS3DPAVoiceSetEnvFXLevelHF(_object, _value) \
            RwaObjectSetParamInt32(_object, \
                rwaS3DPAVOICEIDXIN_ENVFXLEVELHF, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_S3DPAVoiceSet22Macro*/
/*TGenSectionStart_S3DPAVoiceGet22Macro*/
#define RwaS3DPAVoiceGetEnvFXLevelHF(_object) \
            RwaObjectGetParamInt32(_object, \
                rwaS3DPAVOICEIDXOUT_ENVFXLEVELHF, rwaIOPARAM_OUTPUT, NULL)
/*TGenSectionFinish_S3DPAVoiceGet22Macro*/
/*TGenSectionStart_S3DPAVoiceSet23Macro*/
#define RwaS3DPAVoiceSetEnvFXRolloff(_object, _value) \
            RwaObjectSetParamReal(_object, \
                rwaS3DPAVOICEIDXIN_ENVFXROLLOFF, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_S3DPAVoiceSet23Macro*/
/*TGenSectionStart_S3DPAVoiceGet23Macro*/
#define RwaS3DPAVoiceGetEnvFXRolloff(_object) \
            RwaObjectGetParamReal(_object, \
                rwaS3DPAVOICEIDXOUT_ENVFXROLLOFF, rwaIOPARAM_OUTPUT, NULL)
/*TGenSectionFinish_S3DPAVoiceGet23Macro*/
/*TGenSectionStart_S3DPAVoiceSet24Macro*/
#define RwaS3DPAVoiceSetEnvFXObstr(_object, _value) \
            RwaObjectSetParamInt32(_object, \
                rwaS3DPAVOICEIDXIN_ENVFXOBSTR, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_S3DPAVoiceSet24Macro*/
/*TGenSectionStart_S3DPAVoiceGet24Macro*/
#define RwaS3DPAVoiceGetEnvFXObstr(_object) \
            RwaObjectGetParamInt32(_object, \
                rwaS3DPAVOICEIDXOUT_ENVFXOBSTR, rwaIOPARAM_OUTPUT, NULL)
/*TGenSectionFinish_S3DPAVoiceGet24Macro*/
/*TGenSectionStart_S3DPAVoiceSet25Macro*/
#define RwaS3DPAVoiceSetEnvFXObstrLF(_object, _value) \
            RwaObjectSetParamReal(_object, \
                rwaS3DPAVOICEIDXIN_ENVFXOBSTRLF, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_S3DPAVoiceSet25Macro*/
/*TGenSectionStart_S3DPAVoiceGet25Macro*/
#define RwaS3DPAVoiceGetEnvFXObstrLF(_object) \
            RwaObjectGetParamReal(_object, \
                rwaS3DPAVOICEIDXOUT_ENVFXOBSTRLF, rwaIOPARAM_OUTPUT, NULL)
/*TGenSectionFinish_S3DPAVoiceGet25Macro*/
/*TGenSectionStart_S3DPAVoiceSet26Macro*/
#define RwaS3DPAVoiceSetEnvFXOccl(_object, _value) \
            RwaObjectSetParamInt32(_object, \
                rwaS3DPAVOICEIDXIN_ENVFXOCCL, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_S3DPAVoiceSet26Macro*/
/*TGenSectionStart_S3DPAVoiceGet26Macro*/
#define RwaS3DPAVoiceGetEnvFXOccl(_object) \
            RwaObjectGetParamInt32(_object, \
                rwaS3DPAVOICEIDXOUT_ENVFXOCCL, rwaIOPARAM_OUTPUT, NULL)
/*TGenSectionFinish_S3DPAVoiceGet26Macro*/
/*TGenSectionStart_S3DPAVoiceSet27Macro*/
#define RwaS3DPAVoiceSetEnvFXOcclLF(_object, _value) \
            RwaObjectSetParamReal(_object, \
                rwaS3DPAVOICEIDXIN_ENVFXOCCLLF, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_S3DPAVoiceSet27Macro*/
/*TGenSectionStart_S3DPAVoiceGet27Macro*/
#define RwaS3DPAVoiceGetEnvFXOcclLF(_object) \
            RwaObjectGetParamReal(_object, \
                rwaS3DPAVOICEIDXOUT_ENVFXOCCLLF, rwaIOPARAM_OUTPUT, NULL)
/*TGenSectionFinish_S3DPAVoiceGet27Macro*/
/*TGenSectionStart_S3DPAVoiceGet28Macro*/
#define RwaS3DPAVoiceGetWave(_object, _ptr) \
            RwaObjectGetParamData(_object, \
                rwaS3DPAVOICEIDXOUT_WAVE, rwaIOPARAM_OUTPUT, _ptr)
/*TGenSectionFinish_S3DPAVoiceGet28Macro*/
/*TGenSectionStart_S3DPAVoiceSet28Macro*/
#define RwaS3DPAVoiceSetWavePosition(_object, _value) \
            RwaObjectSetParamUInt32(_object, \
                rwaS3DPAVOICEIDXIN_WAVEPOSITION, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_S3DPAVoiceSet28Macro*/
/*TGenSectionStart_S3DPAVoiceGet29Macro*/
#define RwaS3DPAVoiceGetWavePosition(_object) \
            RwaObjectGetParamUInt32(_object, \
                rwaS3DPAVOICEIDXOUT_WAVEPOSITION, rwaIOPARAM_OUTPUT, NULL)
/*TGenSectionFinish_S3DPAVoiceGet29Macro*/
/*TGenSectionStart_S3DPAVoiceSet29Macro*/
#define RwaS3DPAVoiceSetPan(_object, _value) \
            RwaObjectSetParamReal(_object, \
                rwaS3DPAVOICEIDXIN_PAN, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_S3DPAVoiceSet29Macro*/
/*TGenSectionStart_S3DPAVoiceGet30Macro*/
#define RwaS3DPAVoiceGetPan(_object) \
            RwaObjectGetParamReal(_object, \
                rwaS3DPAVOICEIDXOUT_PAN, rwaIOPARAM_OUTPUT, NULL)
/*TGenSectionFinish_S3DPAVoiceGet30Macro*/
/*TGenSectionStart_S3DPAVoiceGet31Macro*/
#define RwaS3DPAVoiceGetIsStereo(_object) \
            RwaObjectGetParamBool(_object, \
                rwaS3DPAVOICEIDXOUT_ISSTEREO, rwaIOPARAM_OUTPUT, NULL)
/*TGenSectionFinish_S3DPAVoiceGet31Macro*/
#endif /* RWADEBUG */


#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */

/* register S3DPAVoice object interface definition */
/*TGenSectionStart_S3DPAVoiceInterfaceRegister*/
RwaObjInterfaceDef* RwaS3DPAVoiceInterfaceRegister(void);
/*TGenSectionFinish_S3DPAVoiceInterfaceRegister*/

#ifdef    __cplusplus
}
#endif /* __cplusplus */


/*--- Automatically derived from: d:/dev/rwa/source/ps2/sensaura/src/rwas3dpaout.h ---*/

/******************************************************************************
 * Defines/Macros & Constants
 *****************************************************************************/
#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */


/*TGenSectionStart_S3DPAOutUUID*/
extern const RwaUUID rwaS3DPAOUTID;
/*TGenSectionFinish_S3DPAOutUUID*/

#ifdef    __cplusplus
}
#endif /* __cplusplus */

/*TGenSectionStart_S3DPAOutDestroyMacro*/
#ifndef RWADEBUG
#define RwaS3DPAOutDestroy(_handle) \
    RwaObjectRelease(_handle)
#endif /* !RWADEBUG */
/*TGenSectionFinish_S3DPAOutDestroyMacro*/

typedef struct RwaS3DPAOutCreationParams RwaS3DPAOutCreationParams;
/**
 * \ingroup sensauraoutputps2 
 * Used as the creation parameters for this object */
struct RwaS3DPAOutCreationParams
{
    RwUInt32 maxVoices; /**<Set maximum number of voices*/
    RwUInt32 minFps;    /**<Minimum number of updates a second (frames per second) */
    RwBool   envFX;     /**<Set whether EnvironmentFX is enabled */
};

/******************************************************************************
 * Functions
 *****************************************************************************/

#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */

/*TGenSectionStart_S3DPAOutCreate*/
/* create S3DPAOut */
RwaObjHandle *RwaS3DPAOutCreate(RwaS3DPAOutCreationParams *creationParams);
/*TGenSectionFinish_S3DPAOutCreate*/

/*TGenSectionStart_S3DPAOutDestroy*/
#ifdef RWADEBUG
/* destroy S3DPAOut */
void RwaS3DPAOutDestroy(RwaObjHandle *objHandle);
#endif /* RWADEBUG */
/*TGenSectionFinish_S3DPAOutDestroy*/

/*TGenSectionStart_S3DPAOutRegister*/
/* register S3DPAOut object definition */
RwaObjDef* RwaS3DPAOutRegister(void);
/*TGenSectionFinish_S3DPAOutRegister*/

RwBool RwaS3DPAOutGetDefaultCreateParams(RwaS3DPAOutCreationParams *createParams);
RwUInt32 RwaS3DPAGetMaxVoices(void);


#ifdef    __cplusplus
}
#endif /* __cplusplus */


/*--- Automatically derived from: d:/dev/rwa/source/ps2/sensaura/src/rwas3dpaoutintf.h ---*/


/******************************************************************************
 * Defines/Macros & Constants
 *****************************************************************************/

/*TGenSectionStart_S3DPAOutInterfaceName*/
/* object interface's name */
#ifdef RWADEBUG
#define rwaS3DPAOUTINTERFACENAME "S3DPAOut Interface"
#else
#define rwaS3DPAOUTINTERFACENAME ""
#endif /* RWADEBUG */
/*TGenSectionFinish_S3DPAOutInterfaceName*/

/*TGenSectionStart_S3DPAOutParameterNames*/
/* object interface's parameter names */
#ifdef RWADEBUG

#define rwaS3DPAOUTNAMEI_GAIN "GainI" 
#define rwaS3DPAOUTNAMEO_GAIN "GainO" 
#define rwaS3DPAOUTNAMEI_CONFIG "ConfigI" 
#define rwaS3DPAOUTNAMEO_CONFIG "ConfigO" 
#define rwaS3DPAOUTNAMEI_ENVFX "EnvFXI" 
#define rwaS3DPAOUTNAMEO_ENVFX "EnvFXO" 
#define rwaS3DPAOUTNAMEI_ENVFXLEVEL "EnvFXLevelI" 
#define rwaS3DPAOUTNAMEO_ENVFXLEVEL "EnvFXLevelO" 
#define rwaS3DPAOUTNAMEI_ENVFXLEVELHF "EnvFXLevelHFI" 
#define rwaS3DPAOUTNAMEO_ENVFXLEVELHF "EnvFXLevelHFO" 
#define rwaS3DPAOUTNAMEI_ENVFXROLLOFF "EnvFXRolloffI" 
#define rwaS3DPAOUTNAMEO_ENVFXROLLOFF "EnvFXRolloffO" 
#define rwaS3DPAOUTNAMEI_ENVFXDECAYTIME "EnvFXDecayTimeI" 
#define rwaS3DPAOUTNAMEO_ENVFXDECAYTIME "EnvFXDecayTimeO" 
#define rwaS3DPAOUTNAMEI_ENVFXDECAYHFRATIO "EnvFXDecayHFRatioI" 
#define rwaS3DPAOUTNAMEO_ENVFXDECAYHFRATIO "EnvFXDecayHFRatioO" 
#define rwaS3DPAOUTNAMEI_ENVFXREFLEVEL "EnvFXRefLevelI" 
#define rwaS3DPAOUTNAMEO_ENVFXREFLEVEL "EnvFXRefLevelO" 
#define rwaS3DPAOUTNAMEI_ENVFXREFDELAY "EnvFXRefDelayI" 
#define rwaS3DPAOUTNAMEO_ENVFXREFDELAY "EnvFXRefDelayO" 
#define rwaS3DPAOUTNAMEI_ENVFXREVLEVEL "EnvFXRevLevelI" 
#define rwaS3DPAOUTNAMEO_ENVFXREVLEVEL "EnvFXRevLevelO" 
#define rwaS3DPAOUTNAMEI_ENVFXREVDELAY "EnvFXRevDelayI" 
#define rwaS3DPAOUTNAMEO_ENVFXREVDELAY "EnvFXRevDelayO" 
#define rwaS3DPAOUTNAMEI_ENVFXDIFF "EnvFXDiffI" 
#define rwaS3DPAOUTNAMEO_ENVFXDIFF "EnvFXDiffO" 
#define rwaS3DPAOUTNAMEI_ENVFXDENSITY "EnvFXDensityI" 
#define rwaS3DPAOUTNAMEO_ENVFXDENSITY "EnvFXDensityO" 
#define rwaS3DPAOUTNAMEI_ENVFXHFREF "EnvFXHFRefI" 
#define rwaS3DPAOUTNAMEO_ENVFXHFREF "EnvFXHFRefO" 
#define rwaS3DPAOUTNAMEI_LISTENERPOS "ListenerPosI" 
#define rwaS3DPAOUTNAMEO_LISTENERPOS "ListenerPosO" 
#define rwaS3DPAOUTNAMEI_LISTENERVEL "ListenerVelI" 
#define rwaS3DPAOUTNAMEO_LISTENERVEL "ListenerVelO" 
#define rwaS3DPAOUTNAMEI_LISTENERORIENT "ListenerOrientI" 
#define rwaS3DPAOUTNAMEO_LISTENERORIENT "ListenerOrientO" 
#define rwaS3DPAOUTNAMEI_LISTENERAT "ListenerAtI" 
#define rwaS3DPAOUTNAMEO_LISTENERAT "ListenerAtO" 
#define rwaS3DPAOUTNAMEI_LISTENERUP "ListenerUpI" 
#define rwaS3DPAOUTNAMEO_LISTENERUP "ListenerUpO" 
#define rwaS3DPAOUTNAMEI_DOPPLERSPEED "DopplerSpeedI" 
#define rwaS3DPAOUTNAMEO_DOPPLERSPEED "DopplerSpeedO" 
#define rwaS3DPAOUTNAMEI_DOPPLERSCALE "DopplerScaleI" 
#define rwaS3DPAOUTNAMEO_DOPPLERSCALE "DopplerScaleO" 
#define rwaS3DPAOUTNAMEI_ROLLOFFFACTOR "RolloffFactorI" 
#define rwaS3DPAOUTNAMEO_ROLLOFFFACTOR "RolloffFactorO" 
#define rwaS3DPAOUTNAMEI_DISTANCEFACTOR "DistanceFactorI" 
#define rwaS3DPAOUTNAMEO_DISTANCEFACTOR "DistanceFactorO" 
#define rwaS3DPAOUTNAMEI_MACROFXFACTOR "MacroFXFactorI" 
#define rwaS3DPAOUTNAMEO_MACROFXFACTOR "MacroFXFactorO" 
#define rwaS3DPAOUTNAMEI_MACROFXDIST "MacroFXDistI" 
#define rwaS3DPAOUTNAMEO_MACROFXDIST "MacroFXDistO" 
#else

#define rwaS3DPAOUTNAMEI_GAIN "" 
#define rwaS3DPAOUTNAMEO_GAIN "" 
#define rwaS3DPAOUTNAMEI_CONFIG "" 
#define rwaS3DPAOUTNAMEO_CONFIG "" 
#define rwaS3DPAOUTNAMEI_ENVFX "" 
#define rwaS3DPAOUTNAMEO_ENVFX "" 
#define rwaS3DPAOUTNAMEI_ENVFXLEVEL "" 
#define rwaS3DPAOUTNAMEO_ENVFXLEVEL "" 
#define rwaS3DPAOUTNAMEI_ENVFXLEVELHF "" 
#define rwaS3DPAOUTNAMEO_ENVFXLEVELHF "" 
#define rwaS3DPAOUTNAMEI_ENVFXROLLOFF "" 
#define rwaS3DPAOUTNAMEO_ENVFXROLLOFF "" 
#define rwaS3DPAOUTNAMEI_ENVFXDECAYTIME "" 
#define rwaS3DPAOUTNAMEO_ENVFXDECAYTIME "" 
#define rwaS3DPAOUTNAMEI_ENVFXDECAYHFRATIO "" 
#define rwaS3DPAOUTNAMEO_ENVFXDECAYHFRATIO "" 
#define rwaS3DPAOUTNAMEI_ENVFXREFLEVEL "" 
#define rwaS3DPAOUTNAMEO_ENVFXREFLEVEL "" 
#define rwaS3DPAOUTNAMEI_ENVFXREFDELAY "" 
#define rwaS3DPAOUTNAMEO_ENVFXREFDELAY "" 
#define rwaS3DPAOUTNAMEI_ENVFXREVLEVEL "" 
#define rwaS3DPAOUTNAMEO_ENVFXREVLEVEL "" 
#define rwaS3DPAOUTNAMEI_ENVFXREVDELAY "" 
#define rwaS3DPAOUTNAMEO_ENVFXREVDELAY "" 
#define rwaS3DPAOUTNAMEI_ENVFXDIFF "" 
#define rwaS3DPAOUTNAMEO_ENVFXDIFF "" 
#define rwaS3DPAOUTNAMEI_ENVFXDENSITY "" 
#define rwaS3DPAOUTNAMEO_ENVFXDENSITY "" 
#define rwaS3DPAOUTNAMEI_ENVFXHFREF "" 
#define rwaS3DPAOUTNAMEO_ENVFXHFREF "" 
#define rwaS3DPAOUTNAMEI_LISTENERPOS "" 
#define rwaS3DPAOUTNAMEO_LISTENERPOS "" 
#define rwaS3DPAOUTNAMEI_LISTENERVEL "" 
#define rwaS3DPAOUTNAMEO_LISTENERVEL "" 
#define rwaS3DPAOUTNAMEI_LISTENERORIENT "" 
#define rwaS3DPAOUTNAMEO_LISTENERORIENT "" 
#define rwaS3DPAOUTNAMEI_LISTENERAT "" 
#define rwaS3DPAOUTNAMEO_LISTENERAT "" 
#define rwaS3DPAOUTNAMEI_LISTENERUP "" 
#define rwaS3DPAOUTNAMEO_LISTENERUP "" 
#define rwaS3DPAOUTNAMEI_DOPPLERSPEED "" 
#define rwaS3DPAOUTNAMEO_DOPPLERSPEED "" 
#define rwaS3DPAOUTNAMEI_DOPPLERSCALE "" 
#define rwaS3DPAOUTNAMEO_DOPPLERSCALE "" 
#define rwaS3DPAOUTNAMEI_ROLLOFFFACTOR "" 
#define rwaS3DPAOUTNAMEO_ROLLOFFFACTOR "" 
#define rwaS3DPAOUTNAMEI_DISTANCEFACTOR "" 
#define rwaS3DPAOUTNAMEO_DISTANCEFACTOR "" 
#define rwaS3DPAOUTNAMEI_MACROFXFACTOR "" 
#define rwaS3DPAOUTNAMEO_MACROFXFACTOR "" 
#define rwaS3DPAOUTNAMEI_MACROFXDIST "" 
#define rwaS3DPAOUTNAMEO_MACROFXDIST "" 
#endif /* RWADEBUG */
/*TGenSectionFinish_S3DPAOutParameterNames*/

#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */

/*TGenSectionStart_S3DPAOutInterfaceUUID*/
extern const RwaUUID rwaS3DPAOUTINTERFACEID;  /* object interface's UUID */
/*TGenSectionFinish_S3DPAOutInterfaceUUID*/

/*----------------------------------------------------------------------------
 - Ranges/Defaults and Flags
 ---------------------------------------------------------------------------*/
#ifndef FLT_MIN
#define FLT_MIN 1.175494351e-38F        /* Minimum +ve floating-point value */
#endif
#ifndef FLT_MAX
#define FLT_MAX 3.402823466e+38F        /* Maximum +ve floating-point value */
#endif

/* default creation parameters */
#define rwaS3DPAOUT_DEFAULT_MAXVOICES     16
#define rwaS3DPAOUT_DEFAULT_AUTODMA       TRUE
#define rwaS3DPAOUT_DEFAULT_MINFRAMERATE  25
#define rwaS3DPAOUT_DEFAULT_ENVFXENABLE   TRUE

#define rwaS3DPAOUT_MIN_GAIN              0.0f
#define rwaS3DPAOUT_MAX_GAIN              4.0f
#define rwaS3DPAOUT_DEFAULT_GAIN          1.0f

#define rwaS3DPAOUT_DEFAULT_MACROFXFACTOR 0.0f

/* Speaker Configuration Flags */
#define rwaS3DPAOUT_HEADPHONES    (0x00000001)
#define rwaS3DPAOUT_STEREO        (0x00000002)
#define rwaS3DPAOUT_NARROW        (0x00010000)
#define rwaS3DPAOUT_WIDE          (0x00020000)
#define rwaS3DPAOUT_STEREO_NARROW \
        (rwaS3DPAOUT_STEREO | rwaS3DPAOUT_NARROW)
#define rwaS3DPAOUT_STEREO_WIDE   \
        (rwaS3DPAOUT_STEREO | rwaS3DPAOUT_WIDE)
#define rwaS3DPAOUT_DEFAULT       \
        rwaS3DPAOUT_HEADPHONES

/* Min/max/default listener params  */
#define rwaS3DPAOUT_ENVFX_LEVEL_MIN                 (-10000)  
#define rwaS3DPAOUT_ENVFX_LEVEL_MAX                 0         
#define rwaS3DPAOUT_ENVFX_LEVEL_DEFAULT             (-10000)
#define rwaS3DPAOUT_ENVFX_LEVELHF_MIN               (-10000)
#define rwaS3DPAOUT_ENVFX_LEVELHF_MAX               0
#define rwaS3DPAOUT_ENVFX_LEVELHF_DEFAULT           0
#define rwaS3DPAOUT_ENVFX_ROLLOFFFACTOR_MIN         0.0f
#define rwaS3DPAOUT_ENVFX_ROLLOFFFACTOR_MAX         10.0f
#define rwaS3DPAOUT_ENVFX_ROLLOFFFACTOR_DEFAULT     0.0f
#define rwaS3DPAOUT_ENVFX_DECAYTIME_MIN             0.1f
#define rwaS3DPAOUT_ENVFX_DECAYTIME_MAX             20.0f
#define rwaS3DPAOUT_ENVFX_DECAYTIME_DEFAULT         1.0f
#define rwaS3DPAOUT_ENVFX_DECAYHFRATIO_MIN          0.1f
#define rwaS3DPAOUT_ENVFX_DECAYHFRATIO_MAX          2.0f
#define rwaS3DPAOUT_ENVFX_DECAYHFRATIO_DEFAULT      0.5f
#define rwaS3DPAOUT_ENVFX_REFLECTIONS_MIN           (-10000)
#define rwaS3DPAOUT_ENVFX_REFLECTIONS_MAX           1000
#define rwaS3DPAOUT_ENVFX_REFLECTIONS_DEFAULT       (-10000)
#define rwaS3DPAOUT_ENVFX_REFLECTIONSDELAY_MIN      0.0f
#define rwaS3DPAOUT_ENVFX_REFLECTIONSDELAY_MAX      0.3f
#define rwaS3DPAOUT_ENVFX_REFLECTIONSDELAY_DEFAULT  0.02f
#define rwaS3DPAOUT_ENVFX_REVERB_MIN                (-10000)
#define rwaS3DPAOUT_ENVFX_REVERB_MAX                2000
#define rwaS3DPAOUT_ENVFX_REVERB_DEFAULT            (-10000)
#define rwaS3DPAOUT_ENVFX_REVERBDELAY_MIN           0.0f
#define rwaS3DPAOUT_ENVFX_REVERBDELAY_MAX           0.1f
#define rwaS3DPAOUT_ENVFX_REVERBDELAY_DEFAULT       0.04f
#define rwaS3DPAOUT_ENVFX_DIFFUSION_MIN             0.0f
#define rwaS3DPAOUT_ENVFX_DIFFUSION_MAX             100.0f
#define rwaS3DPAOUT_ENVFX_DIFFUSION_DEFAULT         100.0f
#define rwaS3DPAOUT_ENVFX_DENSITY_MIN               0.0f
#define rwaS3DPAOUT_ENVFX_DENSITY_MAX               100.0f
#define rwaS3DPAOUT_ENVFX_DENSITY_DEFAULT           100.0f
#define rwaS3DPAOUT_ENVFX_HFREFERENCE_MIN           20.0f
#define rwaS3DPAOUT_ENVFX_HFREFERENCE_MAX           20000.0f
#define rwaS3DPAOUT_ENVFX_HFREFERENCE_DEFAULT       5000.0f

#define rwaS3DPAOUT_MIN_DOPPLERSCALE     0.0f
#define rwaS3DPAOUT_MAX_DOPPLERSCALE     10.0f
#define rwaS3DPAOUT_DEFAULT_DOPPLERSPEED  342.0f /* Speed of sound in air in m/s */
#define rwaS3DPAOUT_DEFAULT_DOPPLERSCALE 1.0f
#define rwaS3DPAOUT_MIN_DOPPLERSCALE     0.0f
#define rwaS3DPAOUT_MAX_DOPPLERSCALE     10.0f

#define rwaS3DPAOUT_MIN_MACROFX           0.0f
#define rwaS3DPAOUT_MAX_MACROFX           2.0f
#define rwaS3DPAOUT_DEFAULT_MACROFX       1.0f


/*----------------------------------------------------------------------------
 - object interface's input and output UUIDs
 ---------------------------------------------------------------------------*/
/*TGenSectionStart_S3DPAOutParameterUUIDs*/
extern const RwaUUID rwaS3DPAOUTIDI_ENVFXLEVELHF;
extern const RwaUUID rwaS3DPAOUTIDO_ENVFXLEVELHF;
extern const RwaUUID rwaS3DPAOUTIDI_ENVFXROLLOFF;
extern const RwaUUID rwaS3DPAOUTIDO_ENVFXROLLOFF;
extern const RwaUUID rwaS3DPAOUTIDI_ENVFXDECAYTIME;
extern const RwaUUID rwaS3DPAOUTIDO_ENVFXDECAYTIME;
extern const RwaUUID rwaS3DPAOUTIDI_ENVFXDECAYHFRATIO;
extern const RwaUUID rwaS3DPAOUTIDO_ENVFXDECAYHFRATIO;
extern const RwaUUID rwaS3DPAOUTIDI_ENVFXREFLEVEL;
extern const RwaUUID rwaS3DPAOUTIDO_ENVFXREFLEVEL;
extern const RwaUUID rwaS3DPAOUTIDI_ENVFXREFDELAY;
extern const RwaUUID rwaS3DPAOUTIDO_ENVFXREFDELAY;
extern const RwaUUID rwaS3DPAOUTIDI_ENVFXREVLEVEL;
extern const RwaUUID rwaS3DPAOUTIDO_ENVFXREVLEVEL;
extern const RwaUUID rwaS3DPAOUTIDI_ENVFXREVDELAY;
extern const RwaUUID rwaS3DPAOUTIDO_ENVFXREVDELAY;
extern const RwaUUID rwaS3DPAOUTIDI_ENVFXDIFF;
extern const RwaUUID rwaS3DPAOUTIDO_ENVFXDIFF;
extern const RwaUUID rwaS3DPAOUTIDI_ENVFXDENSITY;
extern const RwaUUID rwaS3DPAOUTIDO_ENVFXDENSITY;
extern const RwaUUID rwaS3DPAOUTIDI_ENVFXHFREF;
extern const RwaUUID rwaS3DPAOUTIDO_ENVFXHFREF;
extern const RwaUUID rwaS3DPAOUTIDI_LISTENERORIENT;
extern const RwaUUID rwaS3DPAOUTIDO_LISTENERORIENT;
extern const RwaUUID rwaS3DPAOUTIDI_DOPPLERSPEED;
extern const RwaUUID rwaS3DPAOUTIDO_DOPPLERSPEED;
extern const RwaUUID rwaS3DPAOUTIDI_MACROFXFACTOR;
extern const RwaUUID rwaS3DPAOUTIDO_MACROFXFACTOR;
extern const RwaUUID rwaS3DPAOUTIDI_MACROFXDIST;
extern const RwaUUID rwaS3DPAOUTIDO_MACROFXDIST;

/*TGenSectionFinish_S3DPAOutParameterUUIDs*/

#ifdef    __cplusplus
}
#endif /* __cplusplus */


/******************************************************************************
 * Types
 *****************************************************************************/

/* object input and output indexes */
/*TGenSectionStart_S3DPAOutIndexes*/
typedef enum
{   
    rwaS3DPAOUTIDXIN_GAIN = 0,
    rwaS3DPAOUTIDXIN_CONFIG = 1,
    rwaS3DPAOUTIDXIN_ENVFX = 2,
    rwaS3DPAOUTIDXIN_ENVFXLEVEL = 3,
    rwaS3DPAOUTIDXIN_ENVFXLEVELHF = 4,
    rwaS3DPAOUTIDXIN_ENVFXROLLOFF = 5,
    rwaS3DPAOUTIDXIN_ENVFXDECAYTIME = 6,
    rwaS3DPAOUTIDXIN_ENVFXDECAYHFRATIO = 7,
    rwaS3DPAOUTIDXIN_ENVFXREFLEVEL = 8,
    rwaS3DPAOUTIDXIN_ENVFXREFDELAY = 9,
    rwaS3DPAOUTIDXIN_ENVFXREVLEVEL = 10,
    rwaS3DPAOUTIDXIN_ENVFXREVDELAY = 11,
    rwaS3DPAOUTIDXIN_ENVFXDIFF = 12,
    rwaS3DPAOUTIDXIN_ENVFXDENSITY = 13,
    rwaS3DPAOUTIDXIN_ENVFXHFREF = 14,
    rwaS3DPAOUTIDXIN_LISTENERPOS = 15,
    rwaS3DPAOUTIDXIN_LISTENERVEL = 16,
    rwaS3DPAOUTIDXIN_LISTENERORIENT = 17,
    rwaS3DPAOUTIDXIN_LISTENERAT = 18,
    rwaS3DPAOUTIDXIN_LISTENERUP = 19,
    rwaS3DPAOUTIDXIN_DOPPLERSPEED = 20,
    rwaS3DPAOUTIDXIN_DOPPLERSCALE = 21,
    rwaS3DPAOUTIDXIN_ROLLOFFFACTOR = 22,
    rwaS3DPAOUTIDXIN_DISTANCEFACTOR = 23,
    rwaS3DPAOUTIDXIN_MACROFXFACTOR = 24,
    rwaS3DPAOUTIDXIN_MACROFXDIST = 25,
    rwaS3DPAOUTIDXIN_FORCEENUMSIZEINT = RWFORCEENUMSIZEINT
} rwaS3DPAOUTIDXIN;

typedef enum
{
    rwaS3DPAOUTIDXOUT_GAIN = 0,
    rwaS3DPAOUTIDXOUT_CONFIG = 1,
    rwaS3DPAOUTIDXOUT_ENVFX = 2,
    rwaS3DPAOUTIDXOUT_ENVFXLEVEL = 3,
    rwaS3DPAOUTIDXOUT_ENVFXLEVELHF = 4,
    rwaS3DPAOUTIDXOUT_ENVFXROLLOFF = 5,
    rwaS3DPAOUTIDXOUT_ENVFXDECAYTIME = 6,
    rwaS3DPAOUTIDXOUT_ENVFXDECAYHFRATIO = 7,
    rwaS3DPAOUTIDXOUT_ENVFXREFLEVEL = 8,
    rwaS3DPAOUTIDXOUT_ENVFXREFDELAY = 9,
    rwaS3DPAOUTIDXOUT_ENVFXREVLEVEL = 10,
    rwaS3DPAOUTIDXOUT_ENVFXREVDELAY = 11,
    rwaS3DPAOUTIDXOUT_ENVFXDIFF = 12,
    rwaS3DPAOUTIDXOUT_ENVFXDENSITY = 13,
    rwaS3DPAOUTIDXOUT_ENVFXHFREF = 14,
    rwaS3DPAOUTIDXOUT_LISTENERPOS = 15,
    rwaS3DPAOUTIDXOUT_LISTENERVEL = 16,
    rwaS3DPAOUTIDXOUT_LISTENERORIENT = 17,
    rwaS3DPAOUTIDXOUT_LISTENERAT = 18,
    rwaS3DPAOUTIDXOUT_LISTENERUP = 19,
    rwaS3DPAOUTIDXOUT_DOPPLERSPEED = 20,
    rwaS3DPAOUTIDXOUT_DOPPLERSCALE = 21,
    rwaS3DPAOUTIDXOUT_ROLLOFFFACTOR = 22,
    rwaS3DPAOUTIDXOUT_DISTANCEFACTOR = 23,
    rwaS3DPAOUTIDXOUT_MACROFXFACTOR = 24,
    rwaS3DPAOUTIDXOUT_MACROFXDIST = 25,
    rwaS3DPAOUTIDXOUT_FORCEENUMSIZEINT = RWFORCEENUMSIZEINT
} rwaS3DPAOUTIDXOUT;
/*TGenSectionFinish_S3DPAOutIndexes*/

/******************************************************************************
 * Functions
 *****************************************************************************/

#ifdef RWADEBUG
#if !defined (RWADOXYGEN)
#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */

/*TGenSectionStart_S3DPAOutSet0*/
RwaObjHandle* RwaS3DPAOutSetGain( RwaObjHandle *objHandle, RwReal value);
/*TGenSectionFinish_S3DPAOutSet0*/
/*TGenSectionStart_S3DPAOutGet0*/
RwReal RwaS3DPAOutGetGain( RwaObjHandle *object );
/*TGenSectionFinish_S3DPAOutGet0*/
/*TGenSectionStart_S3DPAOutSet1*/
RwaObjHandle* RwaS3DPAOutSetSpeakerConfig( RwaObjHandle *objHandle, RwUInt32 value);
/*TGenSectionFinish_S3DPAOutSet1*/
/*TGenSectionStart_S3DPAOutGet1*/
RwUInt32 RwaS3DPAOutGetSpeakerConfig( RwaObjHandle *object );
/*TGenSectionFinish_S3DPAOutGet1*/
/*TGenSectionStart_S3DPAOutSet2*/
RwaObjHandle* RwaS3DPAOutSetEnvFX( RwaObjHandle *objHandle, RwaEnvironment value);
/*TGenSectionFinish_S3DPAOutSet2*/
/*TGenSectionStart_S3DPAOutGet2*/
RwaEnvironment RwaS3DPAOutGetEnvFX( RwaObjHandle *object );
/*TGenSectionFinish_S3DPAOutGet2*/
/*TGenSectionStart_S3DPAOutSet3*/
RwaObjHandle* RwaS3DPAOutSetEnvFXLevel( RwaObjHandle *objHandle, RwReal value);
/*TGenSectionFinish_S3DPAOutSet3*/
/*TGenSectionStart_S3DPAOutGet3*/
RwReal RwaS3DPAOutGetEnvFXLevel( RwaObjHandle *object );
/*TGenSectionFinish_S3DPAOutGet3*/
/*TGenSectionStart_S3DPAOutSet4*/
RwaObjHandle* RwaS3DPAOutSetEnvFXLevelHF( RwaObjHandle *objHandle, RwInt32 value);
/*TGenSectionFinish_S3DPAOutSet4*/
/*TGenSectionStart_S3DPAOutGet4*/
RwInt32 RwaS3DPAOutGetEnvFXLevelHF( RwaObjHandle *object );
/*TGenSectionFinish_S3DPAOutGet4*/
/*TGenSectionStart_S3DPAOutSet5*/
RwaObjHandle* RwaS3DPAOutSetEnvFXRolloff( RwaObjHandle *objHandle, RwReal value);
/*TGenSectionFinish_S3DPAOutSet5*/
/*TGenSectionStart_S3DPAOutGet5*/
RwReal RwaS3DPAOutGetEnvFXRolloff( RwaObjHandle *object );
/*TGenSectionFinish_S3DPAOutGet5*/
/*TGenSectionStart_S3DPAOutSet6*/
RwaObjHandle* RwaS3DPAOutSetEnvFXDecayTime( RwaObjHandle *objHandle, RwReal value);
/*TGenSectionFinish_S3DPAOutSet6*/
/*TGenSectionStart_S3DPAOutGet6*/
RwReal RwaS3DPAOutGetEnvFXDecayTime( RwaObjHandle *object );
/*TGenSectionFinish_S3DPAOutGet6*/
/*TGenSectionStart_S3DPAOutSet7*/
RwaObjHandle* RwaS3DPAOutSetEnvFXDecayHFRatio( RwaObjHandle *objHandle, RwReal value);
/*TGenSectionFinish_S3DPAOutSet7*/
/*TGenSectionStart_S3DPAOutGet7*/
RwReal RwaS3DPAOutGetEnvFXDecayHFRatio( RwaObjHandle *object );
/*TGenSectionFinish_S3DPAOutGet7*/
/*TGenSectionStart_S3DPAOutSet8*/
RwaObjHandle* RwaS3DPAOutSetEnvFXRefLevel( RwaObjHandle *objHandle, RwInt32 value);
/*TGenSectionFinish_S3DPAOutSet8*/
/*TGenSectionStart_S3DPAOutGet8*/
RwInt32 RwaS3DPAOutGetEnvFXRefLevel( RwaObjHandle *object );
/*TGenSectionFinish_S3DPAOutGet8*/
/*TGenSectionStart_S3DPAOutSet9*/
RwaObjHandle* RwaS3DPAOutSetEnvFXRefDelay( RwaObjHandle *objHandle, RwReal value);
/*TGenSectionFinish_S3DPAOutSet9*/
/*TGenSectionStart_S3DPAOutGet9*/
RwReal RwaS3DPAOutGetEnvFXRefDelay( RwaObjHandle *object );
/*TGenSectionFinish_S3DPAOutGet9*/
/*TGenSectionStart_S3DPAOutSet10*/
RwaObjHandle* RwaS3DPAOutSetEnvFXRevLevel( RwaObjHandle *objHandle, RwInt32 value);
/*TGenSectionFinish_S3DPAOutSet10*/
/*TGenSectionStart_S3DPAOutGet10*/
RwInt32 RwaS3DPAOutGetEnvFXRevLevel( RwaObjHandle *object );
/*TGenSectionFinish_S3DPAOutGet10*/
/*TGenSectionStart_S3DPAOutSet11*/
RwaObjHandle* RwaS3DPAOutSetEnvFXRevDelay( RwaObjHandle *objHandle, RwReal value);
/*TGenSectionFinish_S3DPAOutSet11*/
/*TGenSectionStart_S3DPAOutGet11*/
RwReal RwaS3DPAOutGetEnvFXRevDelay( RwaObjHandle *object );
/*TGenSectionFinish_S3DPAOutGet11*/
/*TGenSectionStart_S3DPAOutSet12*/
RwaObjHandle* RwaS3DPAOutSetEnvFXDiff( RwaObjHandle *objHandle, RwReal value);
/*TGenSectionFinish_S3DPAOutSet12*/
/*TGenSectionStart_S3DPAOutGet12*/
RwReal RwaS3DPAOutGetEnvFXDiff( RwaObjHandle *object );
/*TGenSectionFinish_S3DPAOutGet12*/
/*TGenSectionStart_S3DPAOutSet13*/
RwaObjHandle* RwaS3DPAOutSetEnvFXDensity( RwaObjHandle *objHandle, RwReal value);
/*TGenSectionFinish_S3DPAOutSet13*/
/*TGenSectionStart_S3DPAOutGet13*/
RwReal RwaS3DPAOutGetEnvFXDensity( RwaObjHandle *object );
/*TGenSectionFinish_S3DPAOutGet13*/
/*TGenSectionStart_S3DPAOutSet14*/
RwaObjHandle* RwaS3DPAOutSetEnvFXHFRef( RwaObjHandle *objHandle, RwReal value);
/*TGenSectionFinish_S3DPAOutSet14*/
/*TGenSectionStart_S3DPAOutGet14*/
RwReal RwaS3DPAOutGetEnvFXHFRef( RwaObjHandle *object );
/*TGenSectionFinish_S3DPAOutGet14*/
/*TGenSectionStart_S3DPAOutSet15*/
RwaObjHandle* RwaS3DPAOutSetListenerPos( RwaObjHandle *objHandle, RwV3d *data );
/*TGenSectionFinish_S3DPAOutSet15*/
/*TGenSectionStart_S3DPAOutGet15*/
RwaObjHandle* RwaS3DPAOutGetListenerPos( RwaObjHandle *object, RwV3d *data );
/*TGenSectionFinish_S3DPAOutGet15*/
/*TGenSectionStart_S3DPAOutSet16*/
RwaObjHandle* RwaS3DPAOutSetListenerVel( RwaObjHandle *objHandle, RwV3d *data );
/*TGenSectionFinish_S3DPAOutSet16*/
/*TGenSectionStart_S3DPAOutGet16*/
RwaObjHandle* RwaS3DPAOutGetListenerVel( RwaObjHandle *object, RwV3d *data );
/*TGenSectionFinish_S3DPAOutGet16*/
/*TGenSectionStart_S3DPAOutSet17*/
RwaObjHandle* RwaS3DPAOutSetListenerOrient( RwaObjHandle *objHandle, RwMatrix *data );
/*TGenSectionFinish_S3DPAOutSet17*/
/*TGenSectionStart_S3DPAOutGet17*/
RwaObjHandle* RwaS3DPAOutGetListenerOrient( RwaObjHandle *object, RwMatrix *data );
/*TGenSectionFinish_S3DPAOutGet17*/
/*TGenSectionStart_S3DPAOutSet18*/
RwaObjHandle* RwaS3DPAOutSetListenerAt( RwaObjHandle *objHandle, RwV3d *data );
/*TGenSectionFinish_S3DPAOutSet18*/
/*TGenSectionStart_S3DPAOutGet18*/
RwaObjHandle* RwaS3DPAOutGetListenerAt( RwaObjHandle *object, RwV3d *data );
/*TGenSectionFinish_S3DPAOutGet18*/
/*TGenSectionStart_S3DPAOutSet19*/
RwaObjHandle* RwaS3DPAOutSetListenerUp( RwaObjHandle *objHandle, RwV3d *data );
/*TGenSectionFinish_S3DPAOutSet19*/
/*TGenSectionStart_S3DPAOutGet19*/
RwaObjHandle* RwaS3DPAOutGetListenerUp( RwaObjHandle *object, RwV3d *data );
/*TGenSectionFinish_S3DPAOutGet19*/
/*TGenSectionStart_S3DPAOutSet20*/
RwaObjHandle* RwaS3DPAOutSetDopplerSpeed( RwaObjHandle *objHandle, RwReal value);
/*TGenSectionFinish_S3DPAOutSet20*/
/*TGenSectionStart_S3DPAOutGet20*/
RwReal RwaS3DPAOutGetDopplerSpeed( RwaObjHandle *object );
/*TGenSectionFinish_S3DPAOutGet20*/
/*TGenSectionStart_S3DPAOutSet21*/
RwaObjHandle* RwaS3DPAOutSetDopplerScale( RwaObjHandle *objHandle, RwReal value);
/*TGenSectionFinish_S3DPAOutSet21*/
/*TGenSectionStart_S3DPAOutGet21*/
RwReal RwaS3DPAOutGetDopplerScale( RwaObjHandle *object );
/*TGenSectionFinish_S3DPAOutGet21*/
/*TGenSectionStart_S3DPAOutSet22*/
RwaObjHandle* RwaS3DPAOutSetRolloffFactor( RwaObjHandle *objHandle, RwReal value);
/*TGenSectionFinish_S3DPAOutSet22*/
/*TGenSectionStart_S3DPAOutGet22*/
RwReal RwaS3DPAOutGetRolloffFactor( RwaObjHandle *object );
/*TGenSectionFinish_S3DPAOutGet22*/
/*TGenSectionStart_S3DPAOutSet23*/
RwaObjHandle* RwaS3DPAOutSetDistanceFactor( RwaObjHandle *objHandle, RwReal value);
/*TGenSectionFinish_S3DPAOutSet23*/
/*TGenSectionStart_S3DPAOutGet23*/
RwReal RwaS3DPAOutGetDistanceFactor( RwaObjHandle *object );
/*TGenSectionFinish_S3DPAOutGet23*/
/*TGenSectionStart_S3DPAOutSet24*/
RwaObjHandle* RwaS3DPAOutSetMacroFXFactor( RwaObjHandle *objHandle, RwReal value);
/*TGenSectionFinish_S3DPAOutSet24*/
/*TGenSectionStart_S3DPAOutGet24*/
RwReal RwaS3DPAOutGetMacroFXFactor( RwaObjHandle *object );
/*TGenSectionFinish_S3DPAOutGet24*/
/*TGenSectionStart_S3DPAOutSet25*/
RwaObjHandle* RwaS3DPAOutSetMacroFXDist( RwaObjHandle *objHandle, RwReal value);
/*TGenSectionFinish_S3DPAOutSet25*/
/*TGenSectionStart_S3DPAOutGet25*/
RwReal RwaS3DPAOutGetMacroFXDist( RwaObjHandle *object );
/*TGenSectionFinish_S3DPAOutGet25*/
#ifdef    __cplusplus
}
#endif /* __cplusplus */
#endif /* RWADOXYGEN */
#else
/*-----------------------------------------------------------------------------
 - Set parameter and get parameter functions and macros
 ----------------------------------------------------------------------------*/

/*TGenSectionStart_S3DPAOutSet0Macro*/
#define RwaS3DPAOutSetGain(_object, _value) \
            RwaObjectSetParamReal(_object, \
                rwaS3DPAOUTIDXIN_GAIN, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_S3DPAOutSet0Macro*/
/*TGenSectionStart_S3DPAOutGet0Macro*/
#define RwaS3DPAOutGetGain(_object) \
            RwaObjectGetParamReal(_object, \
                rwaS3DPAOUTIDXOUT_GAIN, rwaIOPARAM_OUTPUT, NULL)
/*TGenSectionFinish_S3DPAOutGet0Macro*/
/*TGenSectionStart_S3DPAOutSet1Macro*/
#define RwaS3DPAOutSetSpeakerConfig(_object, _value) \
            RwaObjectSetParamInt32(_object, \
                rwaS3DPAOUTIDXIN_CONFIG, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_S3DPAOutSet1Macro*/
/*TGenSectionStart_S3DPAOutGet1Macro*/
#define RwaS3DPAOutGetSpeakerConfig(_object) \
            RwaObjectGetParamInt32(_object, \
                rwaS3DPAOUTIDXOUT_CONFIG, rwaIOPARAM_OUTPUT, NULL)
/*TGenSectionFinish_S3DPAOutGet1Macro*/
/*TGenSectionStart_S3DPAOutSet2Macro*/
#define RwaS3DPAOutSetEnvFX(_object, _value) \
            RwaObjectSetParamInt32(_object, \
                rwaS3DPAOUTIDXIN_ENVFX, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_S3DPAOutSet2Macro*/
/*TGenSectionStart_S3DPAOutGet2Macro*/
#define RwaS3DPAOutGetEnvFX(_object) \
            RwaObjectGetParamInt32(_object, \
                rwaS3DPAOUTIDXOUT_ENVFX, rwaIOPARAM_OUTPUT, NULL)
/*TGenSectionFinish_S3DPAOutGet2Macro*/
/*TGenSectionStart_S3DPAOutSet3Macro*/
#define RwaS3DPAOutSetEnvFXLevel(_object, _value) \
            RwaObjectSetParamReal(_object, \
                rwaS3DPAOUTIDXIN_ENVFXLEVEL, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_S3DPAOutSet3Macro*/
/*TGenSectionStart_S3DPAOutGet3Macro*/
#define RwaS3DPAOutGetEnvFXLevel(_object) \
            RwaObjectGetParamReal(_object, \
                rwaS3DPAOUTIDXOUT_ENVFXLEVEL, rwaIOPARAM_OUTPUT, NULL)
/*TGenSectionFinish_S3DPAOutGet3Macro*/
/*TGenSectionStart_S3DPAOutSet4Macro*/
#define RwaS3DPAOutSetEnvFXLevelHF(_object, _value) \
            RwaObjectSetParamInt32(_object, \
                rwaS3DPAOUTIDXIN_ENVFXLEVELHF, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_S3DPAOutSet4Macro*/
/*TGenSectionStart_S3DPAOutGet4Macro*/
#define RwaS3DPAOutGetEnvFXLevelHF(_object) \
            RwaObjectGetParamInt32(_object, \
                rwaS3DPAOUTIDXOUT_ENVFXLEVELHF, rwaIOPARAM_OUTPUT, NULL)
/*TGenSectionFinish_S3DPAOutGet4Macro*/
/*TGenSectionStart_S3DPAOutSet5Macro*/
#define RwaS3DPAOutSetEnvFXRolloff(_object, _value) \
            RwaObjectSetParamReal(_object, \
                rwaS3DPAOUTIDXIN_ENVFXROLLOFF, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_S3DPAOutSet5Macro*/
/*TGenSectionStart_S3DPAOutGet5Macro*/
#define RwaS3DPAOutGetEnvFXRolloff(_object) \
            RwaObjectGetParamReal(_object, \
                rwaS3DPAOUTIDXOUT_ENVFXROLLOFF, rwaIOPARAM_OUTPUT, NULL)
/*TGenSectionFinish_S3DPAOutGet5Macro*/
/*TGenSectionStart_S3DPAOutSet6Macro*/
#define RwaS3DPAOutSetEnvFXDecayTime(_object, _value) \
            RwaObjectSetParamReal(_object, \
                rwaS3DPAOUTIDXIN_ENVFXDECAYTIME, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_S3DPAOutSet6Macro*/
/*TGenSectionStart_S3DPAOutGet6Macro*/
#define RwaS3DPAOutGetEnvFXDecayTime(_object) \
            RwaObjectGetParamReal(_object, \
                rwaS3DPAOUTIDXOUT_ENVFXDECAYTIME, rwaIOPARAM_OUTPUT, NULL)
/*TGenSectionFinish_S3DPAOutGet6Macro*/
/*TGenSectionStart_S3DPAOutSet7Macro*/
#define RwaS3DPAOutSetEnvFXDecayHFRatio(_object, _value) \
            RwaObjectSetParamReal(_object, \
                rwaS3DPAOUTIDXIN_ENVFXDECAYHFRATIO, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_S3DPAOutSet7Macro*/
/*TGenSectionStart_S3DPAOutGet7Macro*/
#define RwaS3DPAOutGetEnvFXDecayHFRatio(_object) \
            RwaObjectGetParamReal(_object, \
                rwaS3DPAOUTIDXOUT_ENVFXDECAYHFRATIO, rwaIOPARAM_OUTPUT, NULL)
/*TGenSectionFinish_S3DPAOutGet7Macro*/
/*TGenSectionStart_S3DPAOutSet8Macro*/
#define RwaS3DPAOutSetEnvFXRefLevel(_object, _value) \
            RwaObjectSetParamInt32(_object, \
                rwaS3DPAOUTIDXIN_ENVFXREFLEVEL, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_S3DPAOutSet8Macro*/
/*TGenSectionStart_S3DPAOutGet8Macro*/
#define RwaS3DPAOutGetEnvFXRefLevel(_object) \
            RwaObjectGetParamInt32(_object, \
                rwaS3DPAOUTIDXOUT_ENVFXREFLEVEL, rwaIOPARAM_OUTPUT, NULL)
/*TGenSectionFinish_S3DPAOutGet8Macro*/
/*TGenSectionStart_S3DPAOutSet9Macro*/
#define RwaS3DPAOutSetEnvFXRefDelay(_object, _value) \
            RwaObjectSetParamReal(_object, \
                rwaS3DPAOUTIDXIN_ENVFXREFDELAY, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_S3DPAOutSet9Macro*/
/*TGenSectionStart_S3DPAOutGet9Macro*/
#define RwaS3DPAOutGetEnvFXRefDelay(_object) \
            RwaObjectGetParamReal(_object, \
                rwaS3DPAOUTIDXOUT_ENVFXREFDELAY, rwaIOPARAM_OUTPUT, NULL)
/*TGenSectionFinish_S3DPAOutGet9Macro*/
/*TGenSectionStart_S3DPAOutSet10Macro*/
#define RwaS3DPAOutSetEnvFXRevLevel(_object, _value) \
            RwaObjectSetParamInt32(_object, \
                rwaS3DPAOUTIDXIN_ENVFXREVLEVEL, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_S3DPAOutSet10Macro*/
/*TGenSectionStart_S3DPAOutGet10Macro*/
#define RwaS3DPAOutGetEnvFXRevLevel(_object) \
            RwaObjectGetParamInt32(_object, \
                rwaS3DPAOUTIDXOUT_ENVFXREVLEVEL, rwaIOPARAM_OUTPUT, NULL)
/*TGenSectionFinish_S3DPAOutGet10Macro*/
/*TGenSectionStart_S3DPAOutSet11Macro*/
#define RwaS3DPAOutSetEnvFXRevDelay(_object, _value) \
            RwaObjectSetParamReal(_object, \
                rwaS3DPAOUTIDXIN_ENVFXREVDELAY, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_S3DPAOutSet11Macro*/
/*TGenSectionStart_S3DPAOutGet11Macro*/
#define RwaS3DPAOutGetEnvFXRevDelay(_object) \
            RwaObjectGetParamReal(_object, \
                rwaS3DPAOUTIDXOUT_ENVFXREVDELAY, rwaIOPARAM_OUTPUT, NULL)
/*TGenSectionFinish_S3DPAOutGet11Macro*/
/*TGenSectionStart_S3DPAOutSet12Macro*/
#define RwaS3DPAOutSetEnvFXDiff(_object, _value) \
            RwaObjectSetParamReal(_object, \
                rwaS3DPAOUTIDXIN_ENVFXDIFF, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_S3DPAOutSet12Macro*/
/*TGenSectionStart_S3DPAOutGet12Macro*/
#define RwaS3DPAOutGetEnvFXDiff(_object) \
            RwaObjectGetParamReal(_object, \
                rwaS3DPAOUTIDXOUT_ENVFXDIFF, rwaIOPARAM_OUTPUT, NULL)
/*TGenSectionFinish_S3DPAOutGet12Macro*/
/*TGenSectionStart_S3DPAOutSet13Macro*/
#define RwaS3DPAOutSetEnvFXDensity(_object, _value) \
            RwaObjectSetParamReal(_object, \
                rwaS3DPAOUTIDXIN_ENVFXDENSITY, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_S3DPAOutSet13Macro*/
/*TGenSectionStart_S3DPAOutGet13Macro*/
#define RwaS3DPAOutGetEnvFXDensity(_object) \
            RwaObjectGetParamReal(_object, \
                rwaS3DPAOUTIDXOUT_ENVFXDENSITY, rwaIOPARAM_OUTPUT, NULL)
/*TGenSectionFinish_S3DPAOutGet13Macro*/
/*TGenSectionStart_S3DPAOutSet14Macro*/
#define RwaS3DPAOutSetEnvFXHFRef(_object, _value) \
            RwaObjectSetParamReal(_object, \
                rwaS3DPAOUTIDXIN_ENVFXHFREF, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_S3DPAOutSet14Macro*/
/*TGenSectionStart_S3DPAOutGet14Macro*/
#define RwaS3DPAOutGetEnvFXHFRef(_object) \
            RwaObjectGetParamReal(_object, \
                rwaS3DPAOUTIDXOUT_ENVFXHFREF, rwaIOPARAM_OUTPUT, NULL)
/*TGenSectionFinish_S3DPAOutGet14Macro*/
/*TGenSectionStart_S3DPAOutSet15Macro*/
#define RwaS3DPAOutSetListenerPos(_object, _ptr) \
            RwaObjectSetParamData(_object, \
                rwaS3DPAOUTIDXIN_LISTENERPOS, rwaIOPARAM_INPUT, _ptr)
/*TGenSectionFinish_S3DPAOutSet15Macro*/
/*TGenSectionStart_S3DPAOutGet15Macro*/
#define RwaS3DPAOutGetListenerPos(_object, _ptr) \
            RwaObjectGetParamData(_object, \
                rwaS3DPAOUTIDXOUT_LISTENERPOS, rwaIOPARAM_OUTPUT, _ptr)
/*TGenSectionFinish_S3DPAOutGet15Macro*/
/*TGenSectionStart_S3DPAOutSet16Macro*/
#define RwaS3DPAOutSetListenerVel(_object, _ptr) \
            RwaObjectSetParamData(_object, \
                rwaS3DPAOUTIDXIN_LISTENERVEL, rwaIOPARAM_INPUT, _ptr)
/*TGenSectionFinish_S3DPAOutSet16Macro*/
/*TGenSectionStart_S3DPAOutGet16Macro*/
#define RwaS3DPAOutGetListenerVel(_object, _ptr) \
            RwaObjectGetParamData(_object, \
                rwaS3DPAOUTIDXOUT_LISTENERVEL, rwaIOPARAM_OUTPUT, _ptr)
/*TGenSectionFinish_S3DPAOutGet16Macro*/
/*TGenSectionStart_S3DPAOutSet17Macro*/
#define RwaS3DPAOutSetListenerOrient(_object, _ptr) \
            RwaObjectSetParamData(_object, \
                rwaS3DPAOUTIDXIN_LISTENERORIENT, rwaIOPARAM_INPUT, _ptr)
/*TGenSectionFinish_S3DPAOutSet17Macro*/
/*TGenSectionStart_S3DPAOutGet17Macro*/
#define RwaS3DPAOutGetListenerOrient(_object, _ptr) \
            RwaObjectGetParamData(_object, \
                rwaS3DPAOUTIDXOUT_LISTENERORIENT, rwaIOPARAM_OUTPUT, _ptr)
/*TGenSectionFinish_S3DPAOutGet17Macro*/
/*TGenSectionStart_S3DPAOutSet18Macro*/
#define RwaS3DPAOutSetListenerAt(_object, _ptr) \
            RwaObjectSetParamData(_object, \
                rwaS3DPAOUTIDXIN_LISTENERAT, rwaIOPARAM_INPUT, _ptr)
/*TGenSectionFinish_S3DPAOutSet18Macro*/
/*TGenSectionStart_S3DPAOutGet18Macro*/
#define RwaS3DPAOutGetListenerAt(_object, _ptr) \
            RwaObjectGetParamData(_object, \
                rwaS3DPAOUTIDXOUT_LISTENERAT, rwaIOPARAM_OUTPUT, _ptr)
/*TGenSectionFinish_S3DPAOutGet18Macro*/
/*TGenSectionStart_S3DPAOutSet19Macro*/
#define RwaS3DPAOutSetListenerUp(_object, _ptr) \
            RwaObjectSetParamData(_object, \
                rwaS3DPAOUTIDXIN_LISTENERUP, rwaIOPARAM_INPUT, _ptr)
/*TGenSectionFinish_S3DPAOutSet19Macro*/
/*TGenSectionStart_S3DPAOutGet19Macro*/
#define RwaS3DPAOutGetListenerUp(_object, _ptr) \
            RwaObjectGetParamData(_object, \
                rwaS3DPAOUTIDXOUT_LISTENERUP, rwaIOPARAM_OUTPUT, _ptr)
/*TGenSectionFinish_S3DPAOutGet19Macro*/
/*TGenSectionStart_S3DPAOutSet20Macro*/
#define RwaS3DPAOutSetDopplerSpeed(_object, _value) \
            RwaObjectSetParamReal(_object, \
                rwaS3DPAOUTIDXIN_DOPPLERSPEED, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_S3DPAOutSet20Macro*/
/*TGenSectionStart_S3DPAOutGet20Macro*/
#define RwaS3DPAOutGetDopplerSpeed(_object) \
            RwaObjectGetParamReal(_object, \
                rwaS3DPAOUTIDXOUT_DOPPLERSPEED, rwaIOPARAM_OUTPUT, NULL)
/*TGenSectionFinish_S3DPAOutGet20Macro*/
/*TGenSectionStart_S3DPAOutSet21Macro*/
#define RwaS3DPAOutSetDopplerScale(_object, _value) \
            RwaObjectSetParamReal(_object, \
                rwaS3DPAOUTIDXIN_DOPPLERSCALE, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_S3DPAOutSet21Macro*/
/*TGenSectionStart_S3DPAOutGet21Macro*/
#define RwaS3DPAOutGetDopplerScale(_object) \
            RwaObjectGetParamReal(_object, \
                rwaS3DPAOUTIDXOUT_DOPPLERSCALE, rwaIOPARAM_OUTPUT, NULL)
/*TGenSectionFinish_S3DPAOutGet21Macro*/
/*TGenSectionStart_S3DPAOutSet22Macro*/
#define RwaS3DPAOutSetRolloffFactor(_object, _value) \
            RwaObjectSetParamReal(_object, \
                rwaS3DPAOUTIDXIN_ROLLOFFFACTOR, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_S3DPAOutSet22Macro*/
/*TGenSectionStart_S3DPAOutGet22Macro*/
#define RwaS3DPAOutGetRolloffFactor(_object) \
            RwaObjectGetParamReal(_object, \
                rwaS3DPAOUTIDXOUT_ROLLOFFFACTOR, rwaIOPARAM_OUTPUT, NULL)
/*TGenSectionFinish_S3DPAOutGet22Macro*/
/*TGenSectionStart_S3DPAOutSet23Macro*/
#define RwaS3DPAOutSetDistanceFactor(_object, _value) \
            RwaObjectSetParamReal(_object, \
                rwaS3DPAOUTIDXIN_DISTANCEFACTOR, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_S3DPAOutSet23Macro*/
/*TGenSectionStart_S3DPAOutGet23Macro*/
#define RwaS3DPAOutGetDistanceFactor(_object) \
            RwaObjectGetParamReal(_object, \
                rwaS3DPAOUTIDXOUT_DISTANCEFACTOR, rwaIOPARAM_OUTPUT, NULL)
/*TGenSectionFinish_S3DPAOutGet23Macro*/
/*TGenSectionStart_S3DPAOutSet24Macro*/
#define RwaS3DPAOutSetMacroFXFactor(_object, _value) \
            RwaObjectSetParamReal(_object, \
                rwaS3DPAOUTIDXIN_MACROFXFACTOR, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_S3DPAOutSet24Macro*/
/*TGenSectionStart_S3DPAOutGet24Macro*/
#define RwaS3DPAOutGetMacroFXFactor(_object) \
            RwaObjectGetParamReal(_object, \
                rwaS3DPAOUTIDXOUT_MACROFXFACTOR, rwaIOPARAM_OUTPUT, NULL)
/*TGenSectionFinish_S3DPAOutGet24Macro*/
/*TGenSectionStart_S3DPAOutSet25Macro*/
#define RwaS3DPAOutSetMacroFXDist(_object, _value) \
            RwaObjectSetParamReal(_object, \
                rwaS3DPAOUTIDXIN_MACROFXDIST, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_S3DPAOutSet25Macro*/
/*TGenSectionStart_S3DPAOutGet25Macro*/
#define RwaS3DPAOutGetMacroFXDist(_object) \
            RwaObjectGetParamReal(_object, \
                rwaS3DPAOUTIDXOUT_MACROFXDIST, rwaIOPARAM_OUTPUT, NULL)
/*TGenSectionFinish_S3DPAOutGet25Macro*/
#endif /* RWADEBUG */


#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */

/* register S3DPAOut object interface definition */
/*TGenSectionStart_S3DPAOutInterfaceRegister*/
RwaObjInterfaceDef* RwaS3DPAOutInterfaceRegister(void);
/*TGenSectionFinish_S3DPAOutInterfaceRegister*/

#ifdef    __cplusplus
}
#endif /* __cplusplus */


/*--- Automatically derived from: d:/dev/rwa/source/ps2/sensaura/src/rwasensaura.h ---*/
#ifdef __cplusplus
extern "C"
{
#endif

/* register all rwasensaura objects and wave definitions */
void RwaS3DPARegister(void);

#ifdef __cplusplus
}
#endif

#endif /* RWAS3DPA_H */
