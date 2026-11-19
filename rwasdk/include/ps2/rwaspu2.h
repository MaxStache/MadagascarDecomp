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
 * Filename: <d:/dev/rwa/include/ps2/rwaspu2.h>
 * Automatically Generated on: Thu Dec 06 11:59:20 2001
 *
 ************************************************************************/

#ifndef RWASPU2_H
#define RWASPU2_H

/*--- System Header Files ---*/
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>


/*--- Automatically derived from: d:/dev/rwa/source/ps2/spu2/common/rwaspu2outputcommon.h ---*/

/*--- Automatically derived from: d:/dev/rwa/source/ps2/spu2/common/rwaspu2voicecommon.h ---*/

/*--- Automatically derived from: d:/dev/rwa/source/ps2/spu2/common/rwaspu2dma.h ---*/

/*--- Automatically derived from: d:/dev/rwa/source/ps2/spu2/common/rwarpc.h ---*/

/*--- Automatically derived from: d:/dev/rwa/source/ps2/spu2/ee/src/rwaspu2encode.h ---*/

/*--- Automatically derived from: d:/dev/rwa/source/ps2/spu2/ee/src/rwaspu2wave.h ---*/

/******************************************************************************
 * Defines/Macros & Constants
 *****************************************************************************/

#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */

/* UUID of the SPU2 wave interface */
extern RwaUUID rwaSPU2WAVEDEFID;

#ifdef    __cplusplus
}
#endif /* __cplusplus */

/******************************************************************************
 * Function Prototypes
 *****************************************************************************/

#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */

/* register the SPU2 wave interface */
RwaWaveDef *RwaSPU2WaveDefRegister(void);
RwUInt32    RwaSPU2WaveGetFreeMemory();

#ifdef    __cplusplus
}
#endif /* __cplusplus */


/*--- Automatically derived from: d:/dev/rwa/source/ps2/spu2/ee/src/rwaspu2voiceint.h ---*/


/******************************************************************************
 * Defines/Macros & Constants
 *****************************************************************************/

/*TGenSectionStart_SPU2VoiceInterfaceName*/
/* object interface's name */
#ifdef RWADEBUG
#define rwaSPU2VOICEINTERFACENAME "SPU2Voice Interface"
#else
#define rwaSPU2VOICEINTERFACENAME ""
#endif /* RWADEBUG */
/*TGenSectionFinish_SPU2VoiceInterfaceName*/

/*TGenSectionStart_SPU2VoiceParameterNames*/
/* object interface's parameter names */
#ifdef RWADEBUG

#define rwaSPU2VOICENAMEI_TRIGGER "TriggerI" 
#define rwaSPU2VOICENAMEO_PLAYING "PlayingO" 
#define rwaSPU2VOICENAMEI_FREQUENCY "FrequencyI" 
#define rwaSPU2VOICENAMEO_FREQUENCY "FrequencyO" 
#define rwaSPU2VOICENAMEI_VOLUME "VolumeI" 
#define rwaSPU2VOICENAMEO_VOLUME "VolumeO" 
#define rwaSPU2VOICENAMEI_LOOPING "LoopingI" 
#define rwaSPU2VOICENAMEO_LOOPING "LoopingO" 
#define rwaSPU2VOICENAMEI_WAVE "WaveI" 
#define rwaSPU2VOICENAMEO_WAVE "WaveO" 
#define rwaSPU2VOICENAMEI_LOOPSTART "LoopStartI" 
#define rwaSPU2VOICENAMEO_LOOPSTART "LoopStartO" 
#define rwaSPU2VOICENAMEI_WAVEPOS "WavePosI" 
#define rwaSPU2VOICENAMEO_WAVEPOS "WavePosO" 
#define rwaSPU2VOICENAMEO_ISSTEREO "IsStereoO" 
#define rwaSPU2VOICENAMEI_PAN "PanI" 
#define rwaSPU2VOICENAMEO_PAN "PanO" 
#define rwaSPU2VOICENAMEI_POSITION "PositionI" 
#define rwaSPU2VOICENAMEO_POSITION "PositionO" 
#define rwaSPU2VOICENAMEI_VELOCITY "VelocityI" 
#define rwaSPU2VOICENAMEO_VELOCITY "VelocityO" 
#define rwaSPU2VOICENAMEI_MINDISTANCE "MinDistanceI" 
#define rwaSPU2VOICENAMEO_MINDISTANCE "MinDistanceO" 
#define rwaSPU2VOICENAMEI_MAXDISTANCE "MaxDistanceI" 
#define rwaSPU2VOICENAMEO_MAXDISTANCE "MaxDistanceO" 
#else

#define rwaSPU2VOICENAMEI_TRIGGER "" 
#define rwaSPU2VOICENAMEO_PLAYING "" 
#define rwaSPU2VOICENAMEI_FREQUENCY "" 
#define rwaSPU2VOICENAMEO_FREQUENCY "" 
#define rwaSPU2VOICENAMEI_VOLUME "" 
#define rwaSPU2VOICENAMEO_VOLUME "" 
#define rwaSPU2VOICENAMEI_LOOPING "" 
#define rwaSPU2VOICENAMEO_LOOPING "" 
#define rwaSPU2VOICENAMEI_WAVE "" 
#define rwaSPU2VOICENAMEO_WAVE "" 
#define rwaSPU2VOICENAMEI_LOOPSTART "" 
#define rwaSPU2VOICENAMEO_LOOPSTART "" 
#define rwaSPU2VOICENAMEI_WAVEPOS "" 
#define rwaSPU2VOICENAMEO_WAVEPOS "" 
#define rwaSPU2VOICENAMEO_ISSTEREO "" 
#define rwaSPU2VOICENAMEI_PAN "" 
#define rwaSPU2VOICENAMEO_PAN "" 
#define rwaSPU2VOICENAMEI_POSITION "" 
#define rwaSPU2VOICENAMEO_POSITION "" 
#define rwaSPU2VOICENAMEI_VELOCITY "" 
#define rwaSPU2VOICENAMEO_VELOCITY "" 
#define rwaSPU2VOICENAMEI_MINDISTANCE "" 
#define rwaSPU2VOICENAMEO_MINDISTANCE "" 
#define rwaSPU2VOICENAMEI_MAXDISTANCE "" 
#define rwaSPU2VOICENAMEO_MAXDISTANCE "" 
#endif /* RWADEBUG */
/*TGenSectionFinish_SPU2VoiceParameterNames*/

#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */

/*TGenSectionStart_SPU2VoiceInterfaceUUID*/
extern const RwaUUID rwaSPU2VOICEINTERFACEID;  /* object interface's UUID */
/*TGenSectionFinish_SPU2VoiceInterfaceUUID*/

/*----------------------------------------------------------------------------
 - object interface's input and output UUIDs
 ---------------------------------------------------------------------------*/
/*TGenSectionStart_SPU2VoiceParameterUUIDs*/
extern const RwaUUID rwaSPU2VOICEIDI_TRIGGER;
extern const RwaUUID rwaSPU2VOICEIDO_PLAYING;
extern const RwaUUID rwaSPU2VOICEIDI_FREQUENCY;
extern const RwaUUID rwaSPU2VOICEIDO_FREQUENCY;
extern const RwaUUID rwaSPU2VOICEIDI_VOLUME;
extern const RwaUUID rwaSPU2VOICEIDO_VOLUME;
extern const RwaUUID rwaSPU2VOICEIDI_LOOPING;
extern const RwaUUID rwaSPU2VOICEIDO_LOOPING;
extern const RwaUUID rwaSPU2VOICEIDI_WAVE;
extern const RwaUUID rwaSPU2VOICEIDO_WAVE;
extern const RwaUUID rwaSPU2VOICEIDI_LOOPSTART;
extern const RwaUUID rwaSPU2VOICEIDO_LOOPSTART;
extern const RwaUUID rwaSPU2VOICEIDI_WAVEPOS;
extern const RwaUUID rwaSPU2VOICEIDO_WAVEPOS;
extern const RwaUUID rwaSPU2VOICEIDO_ISSTEREO;
extern const RwaUUID rwaSPU2VOICEIDI_PAN;
extern const RwaUUID rwaSPU2VOICEIDO_PAN;
extern const RwaUUID rwaSPU2VOICEIDI_POSITION;
extern const RwaUUID rwaSPU2VOICEIDO_POSITION;
extern const RwaUUID rwaSPU2VOICEIDI_VELOCITY;
extern const RwaUUID rwaSPU2VOICEIDO_VELOCITY;
extern const RwaUUID rwaSPU2VOICEIDI_MINDISTANCE;
extern const RwaUUID rwaSPU2VOICEIDO_MINDISTANCE;
extern const RwaUUID rwaSPU2VOICEIDI_MAXDISTANCE;
extern const RwaUUID rwaSPU2VOICEIDO_MAXDISTANCE;

/*TGenSectionFinish_SPU2VoiceParameterUUIDs*/

#ifdef    __cplusplus
}
#endif /* __cplusplus */


/******************************************************************************
 * Types
 *****************************************************************************/

/* object input and output indexes */
/*TGenSectionStart_SPU2VoiceIndexes*/
typedef enum
{   

    rwaSPU2VOICEIDXIN_TRIGGER = 0,
    rwaSPU2VOICEIDXIN_FREQUENCY = 1,
    rwaSPU2VOICEIDXIN_VOLUME = 2,
    rwaSPU2VOICEIDXIN_LOOPING = 3,
    rwaSPU2VOICEIDXIN_WAVE = 4,
    rwaSPU2VOICEIDXIN_LOOPSTART = 5,
    rwaSPU2VOICEIDXIN_WAVEPOS = 6,
    rwaSPU2VOICEIDXIN_PAN = 7,
    rwaSPU2VOICEIDXIN_POSITION = 8,
    rwaSPU2VOICEIDXIN_VELOCITY = 9,
    rwaSPU2VOICEIDXIN_MINDISTANCE = 10,
    rwaSPU2VOICEIDXIN_MAXDISTANCE = 11,
    rwaSPU2VOICEIDXIN_FORCEENUMSIZEINT = RWFORCEENUMSIZEINT
} rwaSPU2VOICEIDXIN;

typedef enum
{

    rwaSPU2VOICEIDXOUT_PLAYING = 0,
    rwaSPU2VOICEIDXOUT_FREQUENCY = 1,
    rwaSPU2VOICEIDXOUT_VOLUME = 2,
    rwaSPU2VOICEIDXOUT_LOOPING = 3,
    rwaSPU2VOICEIDXOUT_WAVE = 4,
    rwaSPU2VOICEIDXOUT_LOOPSTART = 5,
    rwaSPU2VOICEIDXOUT_WAVEPOS = 6,
    rwaSPU2VOICEIDXOUT_ISSTEREO = 7,
    rwaSPU2VOICEIDXOUT_PAN = 8,
    rwaSPU2VOICEIDXOUT_POSITION = 9,
    rwaSPU2VOICEIDXOUT_VELOCITY = 10,
    rwaSPU2VOICEIDXOUT_MINDISTANCE = 11,
    rwaSPU2VOICEIDXOUT_MAXDISTANCE = 12,
    rwaSPU2VOICEIDXOUT_FORCEENUMSIZEINT = RWFORCEENUMSIZEINT
} rwaSPU2VOICEIDXOUT;
/*TGenSectionFinish_SPU2VoiceIndexes*/

/******************************************************************************
 * Functions
 *****************************************************************************/

#ifdef RWADEBUG
#if !defined (RWADOXYGEN)
#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */

/*TGenSectionStart_SPU2VoiceSet0*/
RwaObjHandle* RwaSPU2VoiceSetTrigger( RwaObjHandle *objHandle, RwInt32 value);
/*TGenSectionFinish_SPU2VoiceSet0*/
/*TGenSectionStart_SPU2VoiceGet0*/
RwInt32 RwaSPU2VoiceGetPlaying( RwaObjHandle *object );
/*TGenSectionFinish_SPU2VoiceGet0*/
/*TGenSectionStart_SPU2VoiceSet1*/
RwaObjHandle* RwaSPU2VoiceSetFreq( RwaObjHandle *objHandle, RwInt32 value);
/*TGenSectionFinish_SPU2VoiceSet1*/
/*TGenSectionStart_SPU2VoiceGet1*/
RwInt32 RwaSPU2VoiceGetFreq( RwaObjHandle *object );
/*TGenSectionFinish_SPU2VoiceGet1*/
/*TGenSectionStart_SPU2VoiceSet2*/
RwaObjHandle* RwaSPU2VoiceSetGain( RwaObjHandle *objHandle, RwReal value);
/*TGenSectionFinish_SPU2VoiceSet2*/
/*TGenSectionStart_SPU2VoiceGet2*/
RwReal RwaSPU2VoiceGetGain( RwaObjHandle *object );
/*TGenSectionFinish_SPU2VoiceGet2*/
/*TGenSectionStart_SPU2VoiceSet3*/
RwaObjHandle* RwaSPU2VoiceSetLoop( RwaObjHandle *objHandle, RwInt32 value);
/*TGenSectionFinish_SPU2VoiceSet3*/
/*TGenSectionStart_SPU2VoiceGet3*/
RwInt32 RwaSPU2VoiceGetLoop( RwaObjHandle *object );
/*TGenSectionFinish_SPU2VoiceGet3*/
/*TGenSectionStart_SPU2VoiceSet4*/
RwaObjHandle* RwaSPU2VoiceSetWave( RwaObjHandle *objHandle, void *data );
/*TGenSectionFinish_SPU2VoiceSet4*/
/*TGenSectionStart_SPU2VoiceGet4*/
RwaObjHandle* RwaSPU2VoiceGetWave( RwaObjHandle *object, void *data );
/*TGenSectionFinish_SPU2VoiceGet4*/
/*TGenSectionStart_SPU2VoiceSet5*/
RwaObjHandle* RwaSPU2VoiceSetLoopStart( RwaObjHandle *objHandle, RwInt32 value);
/*TGenSectionFinish_SPU2VoiceSet5*/
/*TGenSectionStart_SPU2VoiceGet5*/
RwInt32 RwaSPU2VoiceGetLoopStart( RwaObjHandle *object );
/*TGenSectionFinish_SPU2VoiceGet5*/
/*TGenSectionStart_SPU2VoiceSet6*/
RwaObjHandle* RwaSPU2VoiceSetWavePos( RwaObjHandle *objHandle, RwUInt32 value);
/*TGenSectionFinish_SPU2VoiceSet6*/
/*TGenSectionStart_SPU2VoiceGet6*/
RwUInt32 RwaSPU2VoiceGetWavePos( RwaObjHandle *object );
/*TGenSectionFinish_SPU2VoiceGet6*/
/*TGenSectionStart_SPU2VoiceGet7*/
RwInt32 RwaSPU2VoiceGetIsStereo( RwaObjHandle *object );
/*TGenSectionFinish_SPU2VoiceGet7*/
/*TGenSectionStart_SPU2VoiceSet7*/
RwaObjHandle* RwaSPU2VoiceSetPan( RwaObjHandle *objHandle, RwReal value);
/*TGenSectionFinish_SPU2VoiceSet7*/
/*TGenSectionStart_SPU2VoiceGet8*/
RwReal RwaSPU2VoiceGetPan( RwaObjHandle *object );
/*TGenSectionFinish_SPU2VoiceGet8*/
/*TGenSectionStart_SPU2VoiceSet8*/
RwaObjHandle* RwaSPU2VoiceSetPos( RwaObjHandle *objHandle, RwV3d *data );
/*TGenSectionFinish_SPU2VoiceSet8*/
/*TGenSectionStart_SPU2VoiceGet9*/
RwaObjHandle* RwaSPU2VoiceGetPos( RwaObjHandle *object, RwV3d *data );
/*TGenSectionFinish_SPU2VoiceGet9*/
/*TGenSectionStart_SPU2VoiceSet9*/
RwaObjHandle* RwaSPU2VoiceSetVel( RwaObjHandle *objHandle, RwV3d *data );
/*TGenSectionFinish_SPU2VoiceSet9*/
/*TGenSectionStart_SPU2VoiceGet10*/
RwaObjHandle* RwaSPU2VoiceGetVel( RwaObjHandle *object, RwV3d *data );
/*TGenSectionFinish_SPU2VoiceGet10*/
/*TGenSectionStart_SPU2VoiceSet10*/
RwaObjHandle* RwaSPU2VoiceSetMinDistance( RwaObjHandle *objHandle, RwReal value);
/*TGenSectionFinish_SPU2VoiceSet10*/
/*TGenSectionStart_SPU2VoiceGet11*/
RwReal RwaSPU2VoiceGetMinDistance( RwaObjHandle *object );
/*TGenSectionFinish_SPU2VoiceGet11*/
/*TGenSectionStart_SPU2VoiceSet11*/
RwaObjHandle* RwaSPU2VoiceSetMaxDistance( RwaObjHandle *objHandle, RwReal value);
/*TGenSectionFinish_SPU2VoiceSet11*/
/*TGenSectionStart_SPU2VoiceGet12*/
RwReal RwaSPU2VoiceGetMaxDistance( RwaObjHandle *object );
/*TGenSectionFinish_SPU2VoiceGet12*/
#ifdef    __cplusplus
}
#endif /* __cplusplus */
#endif /* RWADOXYGEN */
#else
/*-----------------------------------------------------------------------------
 - Set parameter and get parameter functions and macros
 ----------------------------------------------------------------------------*/

/*TGenSectionStart_SPU2VoiceSet0Macro*/
#define RwaSPU2VoiceSetTrigger(_object, _value) \
            RwaObjectSetParamInt32(_object, \
                rwaSPU2VOICEIDXIN_TRIGGER, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_SPU2VoiceSet0Macro*/
/*TGenSectionStart_SPU2VoiceGet0Macro*/
#define RwaSPU2VoiceGetPlaying(_object) \
            RwaObjectGetParamInt32(_object, \
                rwaSPU2VOICEIDXOUT_PLAYING, rwaIOPARAM_OUTPUT, (RwBool*)NULL)
/*TGenSectionFinish_SPU2VoiceGet0Macro*/
/*TGenSectionStart_SPU2VoiceSet1Macro*/
#define RwaSPU2VoiceSetFreq(_object, _value) \
            RwaObjectSetParamInt32(_object, \
                rwaSPU2VOICEIDXIN_FREQUENCY, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_SPU2VoiceSet1Macro*/
/*TGenSectionStart_SPU2VoiceGet1Macro*/
#define RwaSPU2VoiceGetFreq(_object) \
            RwaObjectGetParamInt32(_object, \
                rwaSPU2VOICEIDXOUT_FREQUENCY, rwaIOPARAM_OUTPUT, (RwBool*)NULL)
/*TGenSectionFinish_SPU2VoiceGet1Macro*/
/*TGenSectionStart_SPU2VoiceSet2Macro*/
#define RwaSPU2VoiceSetGain(_object, _value) \
            RwaObjectSetParamReal(_object, \
                rwaSPU2VOICEIDXIN_VOLUME, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_SPU2VoiceSet2Macro*/
/*TGenSectionStart_SPU2VoiceGet2Macro*/
#define RwaSPU2VoiceGetGain(_object) \
            RwaObjectGetParamReal(_object, \
                rwaSPU2VOICEIDXOUT_VOLUME, rwaIOPARAM_OUTPUT, (RwBool*)NULL)
/*TGenSectionFinish_SPU2VoiceGet2Macro*/
/*TGenSectionStart_SPU2VoiceSet3Macro*/
#define RwaSPU2VoiceSetLoop(_object, _value) \
            RwaObjectSetParamInt32(_object, \
                rwaSPU2VOICEIDXIN_LOOPING, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_SPU2VoiceSet3Macro*/
/*TGenSectionStart_SPU2VoiceGet3Macro*/
#define RwaSPU2VoiceGetLoop(_object) \
            RwaObjectGetParamInt32(_object, \
                rwaSPU2VOICEIDXOUT_LOOPING, rwaIOPARAM_OUTPUT, (RwBool*)NULL)
/*TGenSectionFinish_SPU2VoiceGet3Macro*/
/*TGenSectionStart_SPU2VoiceSet4Macro*/
#define RwaSPU2VoiceSetWave(_object, _ptr) \
            RwaObjectSetParamData(_object, \
                rwaSPU2VOICEIDXIN_WAVE, rwaIOPARAM_INPUT, &_ptr)
/*TGenSectionFinish_SPU2VoiceSet4Macro*/
/*TGenSectionStart_SPU2VoiceGet4Macro*/
#define RwaSPU2VoiceGetWave(_object, _ptr) \
            RwaObjectGetParamData(_object, \
                rwaSPU2VOICEIDXOUT_WAVE, rwaIOPARAM_OUTPUT, _ptr)
/*TGenSectionFinish_SPU2VoiceGet4Macro*/
/*TGenSectionStart_SPU2VoiceSet5Macro*/
#define RwaSPU2VoiceSetLoopStart(_object, _value) \
            RwaObjectSetParamInt32(_object, \
                rwaSPU2VOICEIDXIN_LOOPSTART, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_SPU2VoiceSet5Macro*/
/*TGenSectionStart_SPU2VoiceGet5Macro*/
#define RwaSPU2VoiceGetLoopStart(_object) \
            RwaObjectGetParamInt32(_object, \
                rwaSPU2VOICEIDXOUT_LOOPSTART, rwaIOPARAM_OUTPUT, (RwBool*)NULL)
/*TGenSectionFinish_SPU2VoiceGet5Macro*/
/*TGenSectionStart_SPU2VoiceSet6Macro*/
#define RwaSPU2VoiceSetWavePos(_object, _value) \
            RwaObjectSetParamUInt32(_object, \
                rwaSPU2VOICEIDXIN_WAVEPOS, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_SPU2VoiceSet6Macro*/
/*TGenSectionStart_SPU2VoiceGet6Macro*/
#define RwaSPU2VoiceGetWavePos(_object) \
            RwaObjectGetParamUInt32(_object, \
                rwaSPU2VOICEIDXOUT_WAVEPOS, rwaIOPARAM_OUTPUT, (RwBool*)NULL)
/*TGenSectionFinish_SPU2VoiceGet6Macro*/
/*TGenSectionStart_SPU2VoiceGet7Macro*/
#define RwaSPU2VoiceGetIsStereo(_object) \
            RwaObjectGetParamInt32(_object, \
                rwaSPU2VOICEIDXOUT_ISSTEREO, rwaIOPARAM_OUTPUT, (RwBool*)NULL)
/*TGenSectionFinish_SPU2VoiceGet7Macro*/
/*TGenSectionStart_SPU2VoiceSet7Macro*/
#define RwaSPU2VoiceSetPan(_object, _value) \
            RwaObjectSetParamReal(_object, \
                rwaSPU2VOICEIDXIN_PAN, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_SPU2VoiceSet7Macro*/
/*TGenSectionStart_SPU2VoiceGet8Macro*/
#define RwaSPU2VoiceGetPan(_object) \
            RwaObjectGetParamReal(_object, \
                rwaSPU2VOICEIDXOUT_PAN, rwaIOPARAM_OUTPUT, (RwBool*)NULL)
/*TGenSectionFinish_SPU2VoiceGet8Macro*/
/*TGenSectionStart_SPU2VoiceSet8Macro*/
#define RwaSPU2VoiceSetPos(_object, _ptr) \
            RwaObjectSetParamData(_object, \
                rwaSPU2VOICEIDXIN_POSITION, rwaIOPARAM_INPUT, _ptr)
/*TGenSectionFinish_SPU2VoiceSet8Macro*/
/*TGenSectionStart_SPU2VoiceGet9Macro*/
#define RwaSPU2VoiceGetPos(_object, _ptr) \
            RwaObjectGetParamData(_object, \
                rwaSPU2VOICEIDXOUT_POSITION, rwaIOPARAM_OUTPUT, _ptr)
/*TGenSectionFinish_SPU2VoiceGet9Macro*/
/*TGenSectionStart_SPU2VoiceSet9Macro*/
#define RwaSPU2VoiceSetVel(_object, _ptr) \
            RwaObjectSetParamData(_object, \
                rwaSPU2VOICEIDXIN_VELOCITY, rwaIOPARAM_INPUT, _ptr)
/*TGenSectionFinish_SPU2VoiceSet9Macro*/
/*TGenSectionStart_SPU2VoiceGet10Macro*/
#define RwaSPU2VoiceGetVel(_object, _ptr) \
            RwaObjectGetParamData(_object, \
                rwaSPU2VOICEIDXOUT_VELOCITY, rwaIOPARAM_OUTPUT, _ptr)
/*TGenSectionFinish_SPU2VoiceGet10Macro*/
/*TGenSectionStart_SPU2VoiceSet10Macro*/
#define RwaSPU2VoiceSetMinDistance(_object, _value) \
            RwaObjectSetParamReal(_object, \
                rwaSPU2VOICEIDXIN_MINDISTANCE, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_SPU2VoiceSet10Macro*/
/*TGenSectionStart_SPU2VoiceGet11Macro*/
#define RwaSPU2VoiceGetMinDistance(_object) \
            RwaObjectGetParamReal(_object, \
                rwaSPU2VOICEIDXOUT_MINDISTANCE, rwaIOPARAM_OUTPUT, (RwBool*)NULL)
/*TGenSectionFinish_SPU2VoiceGet11Macro*/
/*TGenSectionStart_SPU2VoiceSet11Macro*/
#define RwaSPU2VoiceSetMaxDistance(_object, _value) \
            RwaObjectSetParamReal(_object, \
                rwaSPU2VOICEIDXIN_MAXDISTANCE, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_SPU2VoiceSet11Macro*/
/*TGenSectionStart_SPU2VoiceGet12Macro*/
#define RwaSPU2VoiceGetMaxDistance(_object) \
            RwaObjectGetParamReal(_object, \
                rwaSPU2VOICEIDXOUT_MAXDISTANCE, rwaIOPARAM_OUTPUT, (RwBool*)NULL)
/*TGenSectionFinish_SPU2VoiceGet12Macro*/
#endif /* RWADEBUG */


#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */

/* register SPU2Voice object interface definition */
/*TGenSectionStart_SPU2VoiceInterfaceRegister*/
RwaObjInterfaceDef* RwaSPU2VoiceInterfaceRegister(void);
/*TGenSectionFinish_SPU2VoiceInterfaceRegister*/

#ifdef    __cplusplus
}
#endif /* __cplusplus */


/*--- Automatically derived from: d:/dev/rwa/source/ps2/spu2/ee/src/rwaspu2voice.h ---*/

/******************************************************************************
 * Defines/Macros & Constants
 *****************************************************************************/

#define RWASPU2MAXVOICES    48

#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */

/*TGenSectionStart_SPU2VoiceUUID*/
extern const RwaUUID rwaSPU2VOICEID;
/*TGenSectionFinish_SPU2VoiceUUID*/

#ifdef    __cplusplus
}
#endif /* __cplusplus */

/*TGenSectionStart_SPU2VoiceDestroyMacro*/
#ifndef RWADEBUG
#define RwaSPU2VoiceDestroy(_handle) \
    RwaObjectRelease(_handle)
#endif /* !RWADEBUG */
/*TGenSectionFinish_SPU2VoiceDestroyMacro*/

/*---------------------------------------------------------------------------
 - Creation parameters
 ---------------------------------------------------------------------------*/

typedef struct RwaSPU2VoiceCreationParamsTag
{
	RwInt32       Index;
	RwaObjHandle *Output;
} RwaSPU2VoiceCreationParams;

/******************************************************************************
 * Functions
 *****************************************************************************/

#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */

/*TGenSectionStart_SPU2VoiceCreate*/
/* create SPU2Voice */
RwaObjHandle *RwaSPU2VoiceCreate(void *creationParams);
/*TGenSectionFinish_SPU2VoiceCreate*/

/*TGenSectionStart_SPU2VoiceDestroy*/
#ifdef RWADEBUG
/* destroy SPU2Voice */
void RwaSPU2VoiceDestroy(RwaObjHandle *objHandle);
#endif /* RWADEBUG */
/*TGenSectionFinish_SPU2VoiceDestroy*/

/*TGenSectionStart_SPU2VoiceRegister*/
/* register SPU2Voice object definition */
RwaObjDef* RwaSPU2VoiceRegister(void);
/*TGenSectionFinish_SPU2VoiceRegister*/

#ifdef    __cplusplus
}
#endif /* __cplusplus */


/*--- Automatically derived from: d:/dev/rwa/source/ps2/spu2/ee/src/rwaspu2outint.h ---*/


/******************************************************************************
 * Defines/Macros & Constants
 *****************************************************************************/

/*TGenSectionStart_SPU2OutInterfaceName*/
/* object interface's name */
#ifdef RWADEBUG
#define rwaSPU2OUTINTERFACENAME "SPU2Out Interface"
#else
#define rwaSPU2OUTINTERFACENAME ""
#endif /* RWADEBUG */
/*TGenSectionFinish_SPU2OutInterfaceName*/

/*TGenSectionStart_SPU2OutParameterNames*/
/* object interface's parameter names */
#ifdef RWADEBUG

#define rwaSPU2OUTNAMEI_GAIN "GainI" 
#define rwaSPU2OUTNAMEO_GAIN "GainO" 
#define rwaSPU2OUTNAMEI_LISTENERPOS "ListenerPosI" 
#define rwaSPU2OUTNAMEO_LISTENERPOS "ListenerPosO" 
#define rwaSPU2OUTNAMEI_LISTENERVEL "ListenerVelI" 
#define rwaSPU2OUTNAMEO_LISTENERVEL "ListenerVelO" 
#define rwaSPU2OUTNAMEI_LISTENERUP "ListenerUpI" 
#define rwaSPU2OUTNAMEO_LISTENERUP "ListenerUpO" 
#define rwaSPU2OUTNAMEI_LISTENERAT "ListenerAtI" 
#define rwaSPU2OUTNAMEO_LISTENERAT "ListenerAtO" 
#define rwaSPU2OUTNAMEO_LISTENERRIGHT "ListenerRightO" 
#define rwaSPU2OUTNAMEI_DOPPLERSCALE "DopplerScaleI" 
#define rwaSPU2OUTNAMEO_DOPPLERSCALE "DopplerScaleO" 
#define rwaSPU2OUTNAMEI_DISTANCEFACTOR "DistanceFactorI" 
#define rwaSPU2OUTNAMEO_DISTANCEFACTOR "DistanceFactorO" 
#define rwaSPU2OUTNAMEI_ROLLOFFFACTOR "RolloffFactorI" 
#define rwaSPU2OUTNAMEO_ROLLOFFFACTOR "RolloffFactorO" 
#define rwaSPU2OUTNAMEI_REVERBTYPE "ReverbTypeI" 
#define rwaSPU2OUTNAMEO_REVERBTYPE "ReverbTypeO" 
#define rwaSPU2OUTNAMEI_REVERBGAIN "ReverbGainI" 
#define rwaSPU2OUTNAMEO_REVERBGAIN "ReverbGainO" 
#define rwaSPU2OUTNAMEI_SPEAKERCONFIG "SpeakerConfigI" 
#define rwaSPU2OUTNAMEO_SPEAKERCONFIG "SpeakerConfigO" 
#else

#define rwaSPU2OUTNAMEI_GAIN "" 
#define rwaSPU2OUTNAMEO_GAIN "" 
#define rwaSPU2OUTNAMEI_LISTENERPOS "" 
#define rwaSPU2OUTNAMEO_LISTENERPOS "" 
#define rwaSPU2OUTNAMEI_LISTENERVEL "" 
#define rwaSPU2OUTNAMEO_LISTENERVEL "" 
#define rwaSPU2OUTNAMEI_LISTENERUP "" 
#define rwaSPU2OUTNAMEO_LISTENERUP "" 
#define rwaSPU2OUTNAMEI_LISTENERAT "" 
#define rwaSPU2OUTNAMEO_LISTENERAT "" 
#define rwaSPU2OUTNAMEO_LISTENERRIGHT "" 
#define rwaSPU2OUTNAMEI_DOPPLERSCALE "" 
#define rwaSPU2OUTNAMEO_DOPPLERSCALE "" 
#define rwaSPU2OUTNAMEI_DISTANCEFACTOR "" 
#define rwaSPU2OUTNAMEO_DISTANCEFACTOR "" 
#define rwaSPU2OUTNAMEI_ROLLOFFFACTOR "" 
#define rwaSPU2OUTNAMEO_ROLLOFFFACTOR "" 
#define rwaSPU2OUTNAMEI_REVERBTYPE "" 
#define rwaSPU2OUTNAMEO_REVERBTYPE "" 
#define rwaSPU2OUTNAMEI_REVERBGAIN "" 
#define rwaSPU2OUTNAMEO_REVERBGAIN "" 
#define rwaSPU2OUTNAMEI_SPEAKERCONFIG "" 
#define rwaSPU2OUTNAMEO_SPEAKERCONFIG "" 
#endif /* RWADEBUG */
/*TGenSectionFinish_SPU2OutParameterNames*/

#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */

/*TGenSectionStart_SPU2OutInterfaceUUID*/
extern const RwaUUID rwaSPU2OUTINTERFACEID;  /* object interface's UUID */
/*TGenSectionFinish_SPU2OutInterfaceUUID*/

/*----------------------------------------------------------------------------
 - object interface's input and output UUIDs
 ---------------------------------------------------------------------------*/
/*TGenSectionStart_SPU2OutParameterUUIDs*/
extern const RwaUUID rwaSPU2OUTIDI_GAIN;
extern const RwaUUID rwaSPU2OUTIDO_GAIN;
extern const RwaUUID rwaSPU2OUTIDI_LISTENERPOS;
extern const RwaUUID rwaSPU2OUTIDO_LISTENERPOS;
extern const RwaUUID rwaSPU2OUTIDI_LISTENERVEL;
extern const RwaUUID rwaSPU2OUTIDO_LISTENERVEL;
extern const RwaUUID rwaSPU2OUTIDI_LISTENERUP;
extern const RwaUUID rwaSPU2OUTIDO_LISTENERUP;
extern const RwaUUID rwaSPU2OUTIDI_LISTENERAT;
extern const RwaUUID rwaSPU2OUTIDO_LISTENERAT;
extern const RwaUUID rwaSPU2OUTIDO_LISTENERRIGHT;
extern const RwaUUID rwaSPU2OUTIDI_DOPPLERSCALE;
extern const RwaUUID rwaSPU2OUTIDO_DOPPLERSCALE;
extern const RwaUUID rwaSPU2OUTIDI_DISTANCEFACTOR;
extern const RwaUUID rwaSPU2OUTIDO_DISTANCEFACTOR;
extern const RwaUUID rwaSPU2OUTIDI_ROLLOFFFACTOR;
extern const RwaUUID rwaSPU2OUTIDO_ROLLOFFFACTOR;
extern const RwaUUID rwaSPU2OUTIDI_REVERBTYPE;
extern const RwaUUID rwaSPU2OUTIDO_REVERBTYPE;
extern const RwaUUID rwaSPU2OUTIDI_REVERBGAIN;
extern const RwaUUID rwaSPU2OUTIDO_REVERBGAIN;
extern const RwaUUID rwaSPU2OUTIDI_SPEAKERCONFIG;
extern const RwaUUID rwaSPU2OUTIDO_SPEAKERCONFIG;

/*TGenSectionFinish_SPU2OutParameterUUIDs*/

#ifdef    __cplusplus
}
#endif /* __cplusplus */


/******************************************************************************
 * Types
 *****************************************************************************/

/* object input and output indexes */
/*TGenSectionStart_SPU2OutIndexes*/
typedef enum
{   

    rwaSPU2OUTIDXIN_GAIN = 0,
    rwaSPU2OUTIDXIN_LISTENERPOS = 1,
    rwaSPU2OUTIDXIN_LISTENERVEL = 2,
    rwaSPU2OUTIDXIN_LISTENERUP = 3,
    rwaSPU2OUTIDXIN_LISTENERAT = 4,
    rwaSPU2OUTIDXIN_DOPPLERSCALE = 5,
    rwaSPU2OUTIDXIN_DISTANCEFACTOR = 6,
    rwaSPU2OUTIDXIN_ROLLOFFFACTOR = 7,
    rwaSPU2OUTIDXIN_REVERBTYPE = 8,
    rwaSPU2OUTIDXIN_REVERBGAIN = 9,
    rwaSPU2OUTIDXIN_SPEAKERCONFIG = 10,
    rwaSPU2OUTIDXIN_FORCEENUMSIZEINT = RWFORCEENUMSIZEINT
} rwaSPU2OUTIDXIN;

typedef enum
{

    rwaSPU2OUTIDXOUT_GAIN = 0,
    rwaSPU2OUTIDXOUT_LISTENERPOS = 1,
    rwaSPU2OUTIDXOUT_LISTENERVEL = 2,
    rwaSPU2OUTIDXOUT_LISTENERUP = 3,
    rwaSPU2OUTIDXOUT_LISTENERAT = 4,
    rwaSPU2OUTIDXOUT_LISTENERRIGHT = 5,
    rwaSPU2OUTIDXOUT_DOPPLERSCALE = 6,
    rwaSPU2OUTIDXOUT_DISTANCEFACTOR = 7,
    rwaSPU2OUTIDXOUT_ROLLOFFFACTOR = 8,
    rwaSPU2OUTIDXOUT_REVERBTYPE = 9,
    rwaSPU2OUTIDXOUT_REVERBGAIN = 10,
    rwaSPU2OUTIDXOUT_SPEAKERCONFIG = 11,
    rwaSPU2OUTIDXOUT_FORCEENUMSIZEINT = RWFORCEENUMSIZEINT
} rwaSPU2OUTIDXOUT;
/*TGenSectionFinish_SPU2OutIndexes*/

/******************************************************************************
 * Functions
 *****************************************************************************/

#ifdef RWADEBUG
#if !defined (RWADOXYGEN)
#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */

/*TGenSectionStart_SPU2OutSet0*/
RwaObjHandle* RwaSPU2OutSetGain( RwaObjHandle *objHandle, RwReal value);
/*TGenSectionFinish_SPU2OutSet0*/
/*TGenSectionStart_SPU2OutGet0*/
RwReal RwaSPU2OutGetGain( RwaObjHandle *object );
/*TGenSectionFinish_SPU2OutGet0*/
/*TGenSectionStart_SPU2OutSet1*/
RwaObjHandle* RwaSPU2OutSetListenerPos( RwaObjHandle *objHandle, RwV3d *data );
/*TGenSectionFinish_SPU2OutSet1*/
/*TGenSectionStart_SPU2OutGet1*/
RwaObjHandle* RwaSPU2OutGetListenerPos( RwaObjHandle *object, RwV3d *data );
/*TGenSectionFinish_SPU2OutGet1*/
/*TGenSectionStart_SPU2OutSet2*/
RwaObjHandle* RwaSPU2OutSetListenerVel( RwaObjHandle *objHandle, RwV3d *data );
/*TGenSectionFinish_SPU2OutSet2*/
/*TGenSectionStart_SPU2OutGet2*/
RwaObjHandle* RwaSPU2OutGetListenerVel( RwaObjHandle *object, RwV3d *data );
/*TGenSectionFinish_SPU2OutGet2*/
/*TGenSectionStart_SPU2OutSet3*/
RwaObjHandle* RwaSPU2OutSetListenerUp( RwaObjHandle *objHandle, RwV3d *data );
/*TGenSectionFinish_SPU2OutSet3*/
/*TGenSectionStart_SPU2OutGet3*/
RwaObjHandle* RwaSPU2OutGetListenerUp( RwaObjHandle *object, RwV3d *data );
/*TGenSectionFinish_SPU2OutGet3*/
/*TGenSectionStart_SPU2OutSet4*/
RwaObjHandle* RwaSPU2OutSetListenerAt( RwaObjHandle *objHandle, RwV3d *data );
/*TGenSectionFinish_SPU2OutSet4*/
/*TGenSectionStart_SPU2OutGet4*/
RwaObjHandle* RwaSPU2OutGetListenerAt( RwaObjHandle *object, RwV3d *data );
/*TGenSectionFinish_SPU2OutGet4*/
/*TGenSectionStart_SPU2OutGet5*/
RwaObjHandle* RwaSPU2OutGetListenerRight( RwaObjHandle *object, RwV3d *data );
/*TGenSectionFinish_SPU2OutGet5*/
/*TGenSectionStart_SPU2OutSet5*/
RwaObjHandle* RwaSPU2OutSetDopplerScale( RwaObjHandle *objHandle, RwReal value);
/*TGenSectionFinish_SPU2OutSet5*/
/*TGenSectionStart_SPU2OutGet6*/
RwReal RwaSPU2OutGetDopplerScale( RwaObjHandle *object );
/*TGenSectionFinish_SPU2OutGet6*/
/*TGenSectionStart_SPU2OutSet6*/
RwaObjHandle* RwaSPU2OutSetDistanceFactor( RwaObjHandle *objHandle, RwReal value);
/*TGenSectionFinish_SPU2OutSet6*/
/*TGenSectionStart_SPU2OutGet7*/
RwReal RwaSPU2OutGetDistanceFactor( RwaObjHandle *object );
/*TGenSectionFinish_SPU2OutGet7*/
/*TGenSectionStart_SPU2OutSet7*/
RwaObjHandle* RwaSPU2OutSetRolloffFactor( RwaObjHandle *objHandle, RwReal value);
/*TGenSectionFinish_SPU2OutSet7*/
/*TGenSectionStart_SPU2OutGet8*/
RwReal RwaSPU2OutGetRolloffFactor( RwaObjHandle *object );
/*TGenSectionFinish_SPU2OutGet8*/
/*TGenSectionStart_SPU2OutSet8*/
RwaObjHandle* RwaSPU2OutSetReverbType( RwaObjHandle *objHandle, RwInt32 value);
/*TGenSectionFinish_SPU2OutSet8*/
/*TGenSectionStart_SPU2OutGet9*/
RwInt32 RwaSPU2OutGetReverbType( RwaObjHandle *object );
/*TGenSectionFinish_SPU2OutGet9*/
/*TGenSectionStart_SPU2OutSet9*/
RwaObjHandle* RwaSPU2OutSetReverbGain( RwaObjHandle *objHandle, RwReal value);
/*TGenSectionFinish_SPU2OutSet9*/
/*TGenSectionStart_SPU2OutGet10*/
RwReal RwaSPU2OutGetReverbGain( RwaObjHandle *object );
/*TGenSectionFinish_SPU2OutGet10*/
/*TGenSectionStart_SPU2OutSet10*/
RwaObjHandle* RwaSPU2OutSetSpeakerConfig( RwaObjHandle *objHandle, RwInt32 value);
/*TGenSectionFinish_SPU2OutSet10*/
/*TGenSectionStart_SPU2OutGet11*/
RwInt32 RwaSPU2OutGetSpeakerConfig( RwaObjHandle *object );
/*TGenSectionFinish_SPU2OutGet11*/
#ifdef    __cplusplus
}
#endif /* __cplusplus */
#endif /* RWADOXYGEN */
#else
/*-----------------------------------------------------------------------------
 - Set parameter and get parameter functions and macros
 ----------------------------------------------------------------------------*/

/*TGenSectionStart_SPU2OutSet0Macro*/
#define RwaSPU2OutSetGain(_object, _value) \
            RwaObjectSetParamReal(_object, \
                rwaSPU2OUTIDXIN_GAIN, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_SPU2OutSet0Macro*/
/*TGenSectionStart_SPU2OutGet0Macro*/
#define RwaSPU2OutGetGain(_object) \
            RwaObjectGetParamReal(_object, \
                rwaSPU2OUTIDXOUT_GAIN, rwaIOPARAM_OUTPUT, (RwBool*)NULL)
/*TGenSectionFinish_SPU2OutGet0Macro*/
/*TGenSectionStart_SPU2OutSet1Macro*/
#define RwaSPU2OutSetListenerPos(_object, _ptr) \
            RwaObjectSetParamData(_object, \
                rwaSPU2OUTIDXIN_LISTENERPOS, rwaIOPARAM_INPUT, _ptr)
/*TGenSectionFinish_SPU2OutSet1Macro*/
/*TGenSectionStart_SPU2OutGet1Macro*/
#define RwaSPU2OutGetListenerPos(_object, _ptr) \
            RwaObjectGetParamData(_object, \
                rwaSPU2OUTIDXOUT_LISTENERPOS, rwaIOPARAM_OUTPUT, _ptr)
/*TGenSectionFinish_SPU2OutGet1Macro*/
/*TGenSectionStart_SPU2OutSet2Macro*/
#define RwaSPU2OutSetListenerVel(_object, _ptr) \
            RwaObjectSetParamData(_object, \
                rwaSPU2OUTIDXIN_LISTENERVEL, rwaIOPARAM_INPUT, _ptr)
/*TGenSectionFinish_SPU2OutSet2Macro*/
/*TGenSectionStart_SPU2OutGet2Macro*/
#define RwaSPU2OutGetListenerVel(_object, _ptr) \
            RwaObjectGetParamData(_object, \
                rwaSPU2OUTIDXOUT_LISTENERVEL, rwaIOPARAM_OUTPUT, _ptr)
/*TGenSectionFinish_SPU2OutGet2Macro*/
/*TGenSectionStart_SPU2OutSet3Macro*/
#define RwaSPU2OutSetListenerUp(_object, _ptr) \
            RwaObjectSetParamData(_object, \
                rwaSPU2OUTIDXIN_LISTENERUP, rwaIOPARAM_INPUT, _ptr)
/*TGenSectionFinish_SPU2OutSet3Macro*/
/*TGenSectionStart_SPU2OutGet3Macro*/
#define RwaSPU2OutGetListenerUp(_object, _ptr) \
            RwaObjectGetParamData(_object, \
                rwaSPU2OUTIDXOUT_LISTENERUP, rwaIOPARAM_OUTPUT, _ptr)
/*TGenSectionFinish_SPU2OutGet3Macro*/
/*TGenSectionStart_SPU2OutSet4Macro*/
#define RwaSPU2OutSetListenerAt(_object, _ptr) \
            RwaObjectSetParamData(_object, \
                rwaSPU2OUTIDXIN_LISTENERAT, rwaIOPARAM_INPUT, _ptr)
/*TGenSectionFinish_SPU2OutSet4Macro*/
/*TGenSectionStart_SPU2OutGet4Macro*/
#define RwaSPU2OutGetListenerAt(_object, _ptr) \
            RwaObjectGetParamData(_object, \
                rwaSPU2OUTIDXOUT_LISTENERAT, rwaIOPARAM_OUTPUT, _ptr)
/*TGenSectionFinish_SPU2OutGet4Macro*/
/*TGenSectionStart_SPU2OutGet5Macro*/
#define RwaSPU2OutGetListenerRight(_object, _ptr) \
            RwaObjectGetParamData(_object, \
                rwaSPU2OUTIDXOUT_LISTENERRIGHT, rwaIOPARAM_OUTPUT, _ptr)
/*TGenSectionFinish_SPU2OutGet5Macro*/
/*TGenSectionStart_SPU2OutSet5Macro*/
#define RwaSPU2OutSetDopplerScale(_object, _value) \
            RwaObjectSetParamReal(_object, \
                rwaSPU2OUTIDXIN_DOPPLERSCALE, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_SPU2OutSet5Macro*/
/*TGenSectionStart_SPU2OutGet6Macro*/
#define RwaSPU2OutGetDopplerScale(_object) \
            RwaObjectGetParamReal(_object, \
                rwaSPU2OUTIDXOUT_DOPPLERSCALE, rwaIOPARAM_OUTPUT, (RwBool*)NULL)
/*TGenSectionFinish_SPU2OutGet6Macro*/
/*TGenSectionStart_SPU2OutSet6Macro*/
#define RwaSPU2OutSetDistanceFactor(_object, _value) \
            RwaObjectSetParamReal(_object, \
                rwaSPU2OUTIDXIN_DISTANCEFACTOR, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_SPU2OutSet6Macro*/
/*TGenSectionStart_SPU2OutGet7Macro*/
#define RwaSPU2OutGetDistanceFactor(_object) \
            RwaObjectGetParamReal(_object, \
                rwaSPU2OUTIDXOUT_DISTANCEFACTOR, rwaIOPARAM_OUTPUT, (RwBool*)NULL)
/*TGenSectionFinish_SPU2OutGet7Macro*/
/*TGenSectionStart_SPU2OutSet7Macro*/
#define RwaSPU2OutSetRolloffFactor(_object, _value) \
            RwaObjectSetParamReal(_object, \
                rwaSPU2OUTIDXIN_ROLLOFFFACTOR, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_SPU2OutSet7Macro*/
/*TGenSectionStart_SPU2OutGet8Macro*/
#define RwaSPU2OutGetRolloffFactor(_object) \
            RwaObjectGetParamReal(_object, \
                rwaSPU2OUTIDXOUT_ROLLOFFFACTOR, rwaIOPARAM_OUTPUT, (RwBool*)NULL)
/*TGenSectionFinish_SPU2OutGet8Macro*/
/*TGenSectionStart_SPU2OutSet8Macro*/
#define RwaSPU2OutSetReverbType(_object, _value) \
            RwaObjectSetParamInt32(_object, \
                rwaSPU2OUTIDXIN_REVERBTYPE, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_SPU2OutSet8Macro*/
/*TGenSectionStart_SPU2OutGet9Macro*/
#define RwaSPU2OutGetReverbType(_object) \
            RwaObjectGetParamInt32(_object, \
                rwaSPU2OUTIDXOUT_REVERBTYPE, rwaIOPARAM_OUTPUT, (RwBool*)NULL)
/*TGenSectionFinish_SPU2OutGet9Macro*/
/*TGenSectionStart_SPU2OutSet9Macro*/
#define RwaSPU2OutSetReverbGain(_object, _value) \
            RwaObjectSetParamReal(_object, \
                rwaSPU2OUTIDXIN_REVERBGAIN, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_SPU2OutSet9Macro*/
/*TGenSectionStart_SPU2OutGet10Macro*/
#define RwaSPU2OutGetReverbGain(_object) \
            RwaObjectGetParamReal(_object, \
                rwaSPU2OUTIDXOUT_REVERBGAIN, rwaIOPARAM_OUTPUT, (RwBool*)NULL)
/*TGenSectionFinish_SPU2OutGet10Macro*/
/*TGenSectionStart_SPU2OutSet10Macro*/
#define RwaSPU2OutSetSpeakerConfig(_object, _value) \
            RwaObjectSetParamInt32(_object, \
                rwaSPU2OUTIDXIN_SPEAKERCONFIG, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_SPU2OutSet10Macro*/
/*TGenSectionStart_SPU2OutGet11Macro*/
#define RwaSPU2OutGetSpeakerConfig(_object) \
            RwaObjectGetParamInt32(_object, \
                rwaSPU2OUTIDXOUT_SPEAKERCONFIG, rwaIOPARAM_OUTPUT, (RwBool*)NULL)
/*TGenSectionFinish_SPU2OutGet11Macro*/
#endif /* RWADEBUG */


#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */

/* register SPU2Out object interface definition */
/*TGenSectionStart_SPU2OutInterfaceRegister*/
RwaObjInterfaceDef* RwaSPU2OutInterfaceRegister(void);
/*TGenSectionFinish_SPU2OutInterfaceRegister*/

#ifdef    __cplusplus
}
#endif /* __cplusplus */


/*--- Automatically derived from: d:/dev/rwa/source/ps2/spu2/ee/src/rwaspu2out.h ---*/

/******************************************************************************
 * Defines/Macros & Constants
 *****************************************************************************/
#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */

/*TGenSectionStart_SPU2OutUUID*/
extern const RwaUUID rwaSPU2OUTID;
/*TGenSectionFinish_SPU2OutUUID*/

#ifdef    __cplusplus
}
#endif /* __cplusplus */

/*TGenSectionStart_SPU2OutDestroyMacro*/
#ifndef RWADEBUG
#define RwaSPU2OutDestroy(_handle) \
    RwaObjectRelease(_handle)
#endif /* !RWADEBUG */
/*TGenSectionFinish_SPU2OutDestroyMacro*/

typedef struct RwaSPU2OutCreationParamsTag
{
    RwUInt32 maximumSPU2Voices;
    RwBool   reverbEnableCore0;
    RwBool   reverbEnableCore1;
} RwaSPU2OutCreationParams;

typedef signed short *(*RwaOutputSPU2Callback)(RwUInt32 length, RwUInt32 user);


/******************************************************************************
 * Functions
 *****************************************************************************/

#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */


/*TGenSectionStart_SPU2OutCreate*/
/* create SPU2Out */
RwaObjHandle *RwaSPU2OutCreate(void *creationParams);
/*TGenSectionFinish_SPU2OutCreate*/

/*TGenSectionStart_SPU2OutDestroy*/
#ifdef RWADEBUG
/* destroy SPU2Out */
void RwaSPU2OutDestroy(RwaObjHandle *objHandle);
#endif /* RWADEBUG */
/*TGenSectionFinish_SPU2OutDestroy*/

/*TGenSectionStart_SPU2OutRegister*/
/* register SPU2Out object definition */
RwaObjDef* RwaSPU2OutRegister(void);
/*TGenSectionFinish_SPU2OutRegister*/

RwaObj *_RwaSPU2OutGetVoiceState(RwaObj *object, RwInt32 voiceindex, void **stateblock);
void    _RwaSPU2OutSetIRQCallback(RwaOutputSPU2Callback callback, RwUInt32 user);

#ifdef    __cplusplus
}
#endif /* __cplusplus */


/*--- Automatically derived from: d:/dev/rwa/source/ps2/spu2/ee/src/rwaspu2.h ---*/

/******************************************************************************
 * Functions
 *****************************************************************************/

#if __cplusplus
extern "C"
{
#endif

/* register all rwaspu2 objects and wave interfaces */
RwBool RwaSPU2Register(void);

#if __cplusplus
}
#endif

#endif /* RWASPU2_H */
