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
 * Filename: <d:/dev/rwa/include/ps2/rwacore.h>
 * Automatically Generated on: Thu Dec 06 11:59:20 2001
 *
 ************************************************************************/

#ifndef RWACORE_H
#define RWACORE_H

/*--- System Header Files ---*/
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>


/*--- Automatically derived from: d:/dev/rwa/source/ps2/core/src/ostypes.h ---*/
#if defined(RWANOPLATFORM) || defined(RWADOXYGEN)
#ifndef SKY_OSTYPES_H
#define SKY_OSTYPES_H

#define rwLITTLEENDIAN         /* This is a little endian machine */

#ifdef R5900
    #include <eetypes.h>
    #include <../gcc/ee/include/string.h>  /* prototypes for memcpy etc */
#else
/*    #include "rwaps2iop.h" */  /* IOP compatibility code */
#endif

typedef int RwFixed;
typedef int RwInt32;
typedef unsigned int RwUInt32;
typedef short RwInt16;
typedef unsigned short RwUInt16;
typedef unsigned char RwUInt8;
typedef signed char RwInt8;

#ifdef RWUNICODE
typedef wchar_t RwChar;
#else /* RWUNICODE */
typedef char RwChar;
#endif /* RWUNICODE */
#ifdef __R5900__
    typedef float RwReal;
#else
    typedef RwInt32 RwReal;
#endif
typedef RwInt32 RwBool;

/*
 * Fix for GCC 2.95.3
 * From README_SN2953.txt:
 * Version 1.00 - March '01
 * ------------
 * CAUTION - With this patch the GNU 'long long' type should not be used - 
 * use 'long' instead (it is also 64bits).
 */

#if (defined(__GNUC__) && defined (__LONG_MAX__))
#if ( 2147483647L < __LONG_MAX__)
typedef long RwInt64;
typedef unsigned long RwUInt64;
#else  /* ( 2147483647L < __LONG_MAX__ ) */
typedef long long RwInt64;
typedef unsigned long long RwUInt64;
#endif /* ( 2147483647L < __LONG_MAX__ ) */
#else  /* (defined(__GNUC__) && defined (__LONG_MAX__)) */
typedef long long RwInt64;
typedef unsigned long long RwUInt64;
#endif /* (defined(__GNUC__) && defined (__LONG_MAX__)) */
#define RWZERO64 ((RwUInt64)0)

#ifdef __R5900__
    typedef long128 RwInt128;
    typedef u_long128 RwUInt128;
    #define RWZERO128 ((RwUInt128)0)
#else /* __R5900__ */
    /* Fake 128 bit type for IOP */
    typedef struct _RwUInt128 RwUInt128;
    typedef struct _RwInt128 RwInt128;

    /* We'll do it with structures
     * (can't do maths on these, but OK for allocation): */
    #ifdef rwBIGENDIAN
    struct _RwUInt128
    {
        RwUInt64 top;
        RwUInt64 bottom;
    };

    struct _RwInt128
    {
        RwInt64 top;
        RwUInt64 bottom;
    };

    #else /* rwBIGENDIAN */
    #ifdef rwLITTLEENDIAN
    struct _RwUInt128
    {
        RwUInt64 bottom;
        RwUInt64 top;
    };

    struct _RwInt128
    {
        RwUInt64 bottom;
        RwInt64 top;
    };

    #else /* rwLITTLEENDIAN */
    #error "ENDIAN-ness undefined!"
    #endif /* rwLITTLEENDIAN */
    #endif /* rwBIGENDIAN */
#endif /* __R5900__ */


/* Limits of types */
#define RwInt32MAXVAL       0x7FFFFFFF
#define RwInt32MINVAL       0x80000000
#define RwUInt32MAXVAL      0xFFFFFFFF
#define RwUInt32MINVAL      0x00000000
#define RwRealMAXVAL        (RwReal)(3.40282347e+38)
#define RwRealMINVAL        (RwReal)(1.17549435e-38)
#define RwInt16MAXVAL       0x7FFF
#define RwInt16MINVAL       0x8000
#define RwUInt16MAXVAL      0xFFFF
#define RwUInt16MINVAL      0x0000

/* Structure alignment */

#define RWALIGN(type, x)   type __attribute__((aligned(x)))

/* Stringification */

#define _SKY_STRINGIFY(_x) #_x
#define _SKY_EXPAND(_x) _SKY_STRINGIFY(_x)

#if defined (__MWERKS__)

#if (defined(RWVERBOSE))
#pragma message (__FILE__ "/" _SKY_EXPAND(__LINE__) ": __MWERKS__ == " _SKY_EXPAND(__MWERKS__))
#endif /* (defined (__MWERKS__)) */

#if ((!defined(RWSUPPRESSOPTIMIZATIONPRAGMAS)) && __option(global_optimizer))

/* #pragma inline_instrinsics on */
/* #pragma always_inline on */ /* seems to hang the compiler sometimes  */

#pragma auto_inline on
#pragma dont_inline off
#pragma inline_depth(smart)
#pragma opt_common_subs on
#pragma opt_dead_assignments on
#pragma opt_dead_code on
#pragma opt_lifetimes on
#pragma opt_loop_invariants on
#pragma opt_propagation on
#pragma opt_strength_reduction on
#pragma opt_unroll_loops on
#pragma opt_vectorize_loops on
#pragma peephole on

#if (0x2401 <= __MWERKS__)
#pragma fast_fptosi on
/* #pragma irocseglobaladdresses on */
#endif /* (0x2401 <= __MWERKS__) */

#endif /* ((!defined(RWSUPPRESSOPTIMIZATIONPRAGMAS)) && __option(global_optimizer)) */

#if (defined(RW_USE_SPF))
#pragma float_constants on
#endif /* (defined(RW_USE_SPF)) */

#pragma extended_errorcheck on

#define rwMATRIXALIGNMENT 16
#define rwFRAMEALIGNMENT 16
#define rwV4DALIGNMENT 16

#endif /*  defined (__MWERKS__) */

#if (!defined(rwMATRIXALIGNMENT))
#define rwMATRIXALIGNMENT sizeof(RwUInt128)
#endif /* (!defined(rwMATRIXALIGNMENT)) */

#if (!defined(rwFRAMEALIGNMENT))
#define rwFRAMEALIGNMENT sizeof(RwUInt128)
#endif /* (!defined(rwFRAMEALIGNMENT)) */

#if (!defined(rwV4DALIGNMENT))
#define rwV4DALIGNMENT sizeof(RwUInt128)
#endif /* (!defined(rwV4DALIGNMENT)) */

#endif /* SKY_OSTYPES_H */
#endif /* defined(RWANOPLATFORM) || defined(RWADOXYGEN) */

#ifndef RWASKY_OSTYPES_H
#define RWASKY_OSTYPES_H

/* Malloc alignment */
#define rwMALLOCALIGNMENT sizeof(RwUInt128)

#if (defined(R5900) && !defined(RWANOPLATFORM))
    #include "rwplcore.h" /* renderware platform */
#endif /* defined(R5900) && (!defined(RWANOPLATFORM)) */

#endif /* RWASKY_OSTYPES_H */


/*--- Automatically derived from: d:/dev/rwa/source/core/src/rwatypes.h ---*/
#if defined(DEBUG) || defined(_DEBUG)
    #ifndef RWADEBUG
        #define RWADEBUG
    #endif /* RWADEBUG */
    #ifndef RWDEBUG
        #define RWDEBUG
    #endif /* RWDEBUG */
#endif /* defined(DEBUG) || defined(_DEBUG) */

#if defined(RWANOPLATFORM) || defined(RWADOXYGEN)
#ifndef RWTYPES_H
#define RWTYPES_H


#if (!defined(RWFORCEENUMSIZEINT))
#define RWFORCEENUMSIZEINT ((~((RwUInt32)0))>>1)
#endif /* (!defined(RWFORCEENUMSIZEINT)) */

/*
 * See
 * http://www.eskimo.com/~scs/C-faq/q11.17.html
 */

#define RW_STRINGIFY(X) #X
#define RW_STRINGIFY_EXPANDED(X) RW_STRINGIFY(X)

/****************************************************************************
 Attributes
 */

#if (defined(__GNUC__))

/* See http://www.gnu.org/software/gcc/onlinedocs/gcc_4.html#SEC91 */

#if (!(defined(__cplusplus) || defined(__MWERKS__) || defined(__RWUNUSED__)))
#define __RWUNUSED__ __attribute__ ((unused))
#endif /* (!(defined(__cplusplus) || defined(__MWERKS__) || defined(__RWUNUSED__))) */

#if (!(defined(__RWUNUSEDRELEASE__) || defined(RWVALIDATEPARAM)))
#if (!( defined(__cplusplus) || defined(__MWERKS__) || defined(RWADEBUG)))
#define __RWUNUSEDRELEASE__ __attribute__ ((unused))
#endif /* (!(defined(__cplusplus) || defined(__MWERKS__) || defined(RWADEBUG))) */
#endif /* (!(defined(__RWUNUSEDRELEASE__) || defined(RWVALIDATEPARAM))) */

#if (!defined(__RWFORMAT__))
#define __RWFORMAT__(_archetype, _string_index, _first_to_check)        \
    __attribute__ ((format (_archetype, _string_index, _first_to_check)))
#endif /* (!defined(__RWFORMAT__)) */

#endif /* (defined(__GNUC__)) */

#if (!defined(__RWUNUSED__))
#define __RWUNUSED__           /* No op */
#endif /* (!defined(__RWUNUSED__)) */

#if (!defined(__RWUNUSEDRELEASE__))
#define __RWUNUSEDRELEASE__           /* No op */
#endif /* (!defined(__RWUNUSEDRELEASE__)) */

#if (!defined(__RWFORMAT__))
#define __RWFORMAT__(_archetype, _string_index, _first_to_check)  /* No op */
#endif /* (!defined(__RWFORMAT__)) */

/****************************************************************************
 Calling conventions
 */

#if (defined(WIN32))
#define RWASMCALL   __cdecl
#define RWASMAPI(TYPE) TYPE RWASMCALL
#endif /* (defined(WIN32)) */

#if (!defined(RWASMCALL))
#define RWASMCALL              /* No op */
#endif /* (!defined(RWASMCALL)) */

#if (!defined(RWASMAPI))
#define RWASMAPI(TYPE) TYPE
#endif /* (!defined(RWASMAPI)) */


/* Maximum number of nested contexts */
#define rwMAXPIPECONTEXT 10


/****************************************************************************
 Macro wrappers. These are needed everywhere.
 */

#ifndef MACRO_START
#define MACRO_START do
#endif /* MACRO_START */

#ifndef MACRO_STOP
#define MACRO_STOP while(0)
#endif /* MACRO_STOP */

/****************************************************************************
 Types needed everywhere
 */

#ifdef FALSE
#undef FALSE
#endif
#define FALSE 0

#ifdef TRUE
#undef TRUE
#endif
#define TRUE !FALSE

/****************************************************************************
 MS VC/C++ Specific
 */

#if (defined(_MSC_VER))
#if (_MSC_VER>=1000)


/*
 * Check for correct compiler version
 */
#define RW_MSC_VER 1200

#if (0 && !defined(RW_NO_COMPILER_CHECK))
#if (_MSC_VER != RW_MSC_VER )
# pragma message (__FILE__ "(" RW_STRINGIFY_EXPANDED(__LINE__) "):" "\n  This compiler is a different version (" RW_STRINGIFY_EXPANDED(_MSC_VER) ")\n  to the compiler used to build the RenderWare product libraries (" RW_STRINGIFY_EXPANDED(RW_MSC_VER) ") \n  To turn off this warning please define RW_NO_COMPILER_CHECK " )
# pragma comment ( user, "comment:" __FILE__ "(" RW_STRINGIFY_EXPANDED(__LINE__) "):" "\n  This compiler is a different version (" RW_STRINGIFY_EXPANDED(_MSC_VER) ")\n  to the compiler used to build the RenderWare product libraries (" RW_STRINGIFY_EXPANDED(RW_MSC_VER) ") \n  To turn off this warning please define RW_NO_COMPILER_CHECK " )
#endif /* (_MSC_VER != RW_MSC_VER ) */
#endif /* (0 && !defined(RW_NO_COMPILER_CHECK)) */

/*
 * Output some compiler messages and object file comments
 */

#pragma comment ( compiler )

#pragma comment ( user, "comment:" __DATE__" "  __TIME__ " - " __FILE__ "(" RW_STRINGIFY_EXPANDED(__LINE__) ")")
#pragma comment ( user, "comment:" " _MSC_VER==" RW_STRINGIFY_EXPANDED(_MSC_VER) "; _M_IX86==" RW_STRINGIFY_EXPANDED(_M_IX86))
#if (defined(rwLIBRARYCURRENTVERSION))
#pragma comment ( user, "comment:" "rwLIBRARYCURRENTVERSION:" RW_STRINGIFY_EXPANDED(rwLIBRARYCURRENTVERSION) )
#endif /* (defined(rwLIBRARYCURRENTVERSION)) */

#if (defined(RWADEBUG) && defined(RWVERBOSE))

/* #include <windows.h> */
#if (defined(RWMEMDEBUG) && !defined(_CRTDBG_MAP_ALLOC))
#define _CRTDBG_MAP_ALLOC
#endif /* defined(RWMEMDEBUG) && !defined(_CRTDBG_MAP_ALLOC)) */
#include <crtdbg.h>

#pragma message (__DATE__" "  __TIME__ " - " __FILE__ "(" RW_STRINGIFY_EXPANDED(__LINE__) ")" )
#pragma message ("_MSC_VER==" RW_STRINGIFY_EXPANDED(_MSC_VER) "; _M_IX86==" RW_STRINGIFY_EXPANDED(_M_IX86))

#if (defined(rwLIBRARYCURRENTVERSION))
#pragma message ( "rwLIBRARYCURRENTVERSION:" RW_STRINGIFY_EXPANDED(rwLIBRARYCURRENTVERSION) )
#endif /* (defined(rwLIBRARYCURRENTVERSION)) */

#endif /* (defined(RWADEBUG) && defined(RWVERBOSE) ) */

#endif /* (_MSC_VER>=1000) */
#endif /* (defined(_MSC_VER)) */

/*******************/
/* Primitive types */
/*******************/

/* String construction stuff (gets us UNICODE support) */
#ifdef RWUNICODE
#define _RWSTRING(x) L ## x
#else /* RWUNICODE */
#define _RWSTRING(x) x
#endif /* RWUNICODE */
#define RWSTRING(x) _RWSTRING(x)

/* NB volatile keyword required for VC5.0 to ensure a reload - AMB */
typedef union RwSplitBits RwSplitBits;
union RwSplitBits
{
    RwReal nReal;
    volatile RwInt32 nInt;
    volatile RwUInt32 nUInt;
};

typedef struct RwSplitFixed RwSplitFixed;

#ifdef rwBIGENDIAN
struct RwSplitFixed
{
    RwInt16 integral;
    RwUInt16 fractional;
};

#else /* rwBIGENDIAN */
#ifdef rwLITTLEENDIAN
struct RwSplitFixed
{
    RwUInt16 fractional;
    RwInt16 integral;
};

#else /* rwLITTLEENDIAN */
#error "ENDIAN-ness undefined!"
#endif /* rwLITTLEENDIAN */
#endif /* rwBIGENDIAN */

typedef union RwUnionReal RwUnionReal;
union RwUnionReal /* MSB is sign bit in any circumstance */
{
    RwReal real; /* 4 bytes interpreted as RwReal */
    float floating; /* 4 bytes interpreted as float */
    RwFixed fixed; /* 4 bytes interpreted as 16:16 fixed */
    RwSplitFixed splitfixed; /* 4 bytes interpreted as 16:16 fixed */
};

/*****************/

/* Complex types */

/*****************/

/**
 * \ingroup datatypes
 * \typedef RwV2d
 * typedef for struct RwV2d
 */
typedef struct RwV2d RwV2d;
/**
 * \ingroup datatypes
 * \struct RwV2d
 * This type represents points in a 2D space, such as device
 * space, specified by the (x, y) coordinates of the point.
 */
struct RwV2d
{
    RwReal x;   /**< X value*/
    RwReal y;   /**< Y vlaue */
};

/**
 * \ingroup datatypes
 * \typedef RwV3d
 * typedef for struct RwV3d
 */
typedef struct RwV3d RwV3d;
/**
 * \ingroup datatypes
 * \struct RwV3d
 *  This type represents 3D points and vectors specified by
 * the (x, y, z) coordinates of a 3D point or the (x, y, z) components of a
 * 3D vector.
 */
struct RwV3d
{
    RwReal x;   /**< X value */
    RwReal y;   /**< Y value */
    RwReal z;   /**< Z value */
};



#ifndef rwMATRIXALIGNMENT
#define rwMATRIXALIGNMENT 16
#endif
/**
 * \ingroup datatypes
 * \typedef RwMatrix 
 * Matrix to define transformations. 
 * This should be considered an opaque type.
 * Use the RwMatrix API functions to access.
 */
typedef struct RwMatrix RWALIGN(RwMatrix, rwMATRIXALIGNMENT);

#if (!defined(DOXYGEN))
struct RwMatrix
{
    /* These are padded to be 16 byte quantities per line */
    RwV3d               right;
    RwUInt32            flags;
    RwV3d               up;
    RwUInt32            pad1;
    RwV3d               at;
    RwUInt32            pad2;
    RwV3d               pos;
    RwUInt32            pad3;
};
#endif /* (!defined(DOXYGEN)) */

/* matrix handling macros */
#define RwMatrixGetRight(m)    (&(m)->right)
#define RwMatrixGetUp(m)       (&(m)->up)
#define RwMatrixGetAt(m)       (&(m)->at)
#define RwMatrixGetPos(m)      (&(m)->pos)


/* Singley linked list macros. End marked as NULL */

typedef struct RwSLLink RwSLLink;    /*** RwSLLink ***/
struct RwSLLink
{
    RwSLLink  *next;
};

#define rwSLLinkGetData(link,type,entry)                                \
    ((type *)(((RwUInt8 *)(link))-offsetof(type,entry)))
#define rwSLLinkInitialize(linkvar)                                     \
    (linkvar)->next = NULL;
#define rwSLLinkGetNext(linkvar)                                        \
    ((linkvar)->next)

typedef struct RwSingleList RwSingleList;
struct RwSingleList
{
    RwSLLink link;
};

#define rwSingleListInitialize(list)                                    \
    (list)->link.next= NULL;
#define rwSingleListEmpty(list)                                         \
    (((list)->link.next)==NULL)
#define rwSingleListAddSLLink(list,linkvar)                             \
    MACRO_START                                                         \
    {                                                                   \
        (linkvar)->next = (list)->link.next;                            \
        (list)->link.next = (linkvar);                                  \
    }                                                                   \
    MACRO_STOP
#define rwSingleListGetFirstSLLink(list)                                \
    ((list)->link.next)
#define rwSingleListGetTerminator(list) (NULL)

/* Doubly linked list. End marked as start (its a ring) */

typedef struct RwLLLink  RwLLLink;                     /*** RwLLLink ***/
struct RwLLLink
{
    RwLLLink *next;
    RwLLLink *prev;
};

#define rwLLLinkGetData(linkvar,type,entry)                             \
    ((type *)(((RwUInt8 *)(linkvar))-offsetof(type,entry)))
#define rwLLLinkGetNext(linkvar)                                        \
    ((linkvar)->next)
#define rwLLLinkGetPrevious(linkvar)                                    \
    ((linkvar)->prev)
#define rwLLLinkInitialize(linkvar)                                     \
    MACRO_START                                                         \
    {                                                                   \
        (linkvar)->prev = (RwLLLink *)NULL;                             \
        (linkvar)->next = (RwLLLink *)NULL;                             \
    }                                                                   \
    MACRO_STOP
#define rwLLLinkAttached(linkvar)                                       \
    ((linkvar)->next)

typedef struct RwLinkList RwLinkList;
struct RwLinkList
{
    RwLLLink link;
};

#define rwLinkListInitialize(list)                                      \
    MACRO_START                                                         \
    {                                                                   \
        (list)->link.next = ((RwLLLink *)(list));                       \
        (list)->link.prev = ((RwLLLink *)(list));                       \
    }                                                                   \
    MACRO_STOP
#define rwLinkListEmpty(list)                                           \
    (((list)->link.next) == (&(list)->link))
#define rwLinkListAddLLLink(list, linkvar)                              \
    MACRO_START                                                         \
    {                                                                   \
        (linkvar)->next = (list)->link.next;                            \
        (linkvar)->prev = (&(list)->link);                              \
        ((list)->link.next)->prev = (linkvar);                          \
        (list)->link.next = (linkvar);                                  \
    }                                                                   \
    MACRO_STOP
    
#define rwLinkListRemoveLLLink(linkvar)                                 \
    MACRO_START                                                         \
    {                                                                   \
        ((linkvar)->prev)->next = (linkvar)->next;                      \
        ((linkvar)->next)->prev = (linkvar)->prev;                      \
    }                                                                   \
    MACRO_STOP
#define rwLinkListGetFirstLLLink(list)                                  \
    ((list)->link.next)
#define rwLinkListGetLastLLLink(list)                                   \
    ((list)->link.prev)
#define rwLinkListGetTerminator(list)                                   \
    (&((list)->link))

/**********
 * Macros *
 **********/

/* ANSI C defines the offsetof(type,member) macro; should be in <stddef.h> */

/* If not, fall back to this: */
#ifndef offsetof
#define offsetof(type, member)                                          \
    ((size_t)((RwUInt8 *)&((type *) 0)->member - (RwUInt8 *)((type *) 0)))
#endif /* offsetof */

/*
 *
 * Numeric Macros to handle Fixed/Floating point versions of RenderWare
 *
 */
#define RWFIX_MIN     (1)
#define RWFIX_MAX     (0x7fffffff)
#define RwFixedCast(A)     ((RwFixed)((A) * 65536.0f))
#define RwFixedToInt(A)    ((A) >> 16)
#define RwFixedToFloat(A)  ((float)(((float)(A)) * (1.0f / 65536.0f)))
#define RwFixedToReal(a)    ((RwReal)(((RwReal)(a)) * (1.0f / 65536.0f)))
#define RwRealToFixed(a)    ((RwFixed)((a) * 65536.0f))
#define RwRealAbs(a)       ((RwReal)((a) >= (RwReal)(0.0) ? (a) : (-(a))))
#define RwRealMin2(a,b)    ((RwReal)( ((a) <= (b)) ?  (a) : (b)))
#define RwRealMax2(a,b)    ((RwReal)( ((a) >= (b)) ?  (a) : (b)))
#define RwRealMin3(a,b,c)  RwRealMin2(a,RwRealMin2(b,c))
#define RwRealMax3(a,b,c)  RwRealMax2(a,RwRealMax2(b,c))

#ifndef NORWREALSHORTCUT
#define RToFixed RwRealToFixed
#define RAbs     RwRealAbs
#define FxCast    RwFixedCast
#define FxToInt   RwFixedToInt
#define FxToFloat RwFixedToFloat
#define FxToReal  RwFixedToFloat

#endif

#ifndef rwPI
#define rwPI ((RwReal)(3.1415926535f))
#define rwPIOVER2 (rwPI / (RwReal)(2.0f))
#endif


/****************************************************************************
 Defines
 */

/**
 * \ingroup rwcore
 * \page inttypes Integer Types
 *
 * RenderWare supports a number of integer types:
 *
 * RwInt8 8-bit signed integer.
 *    \li RwUInt8 8-bit unsigned integer.
 *    \li RwChar Character type.
 *    \li RwInt16 16-bit signed integer.
 *    \li RwUInt16 16-bit unsigned integer.
 *    \li RwInt32 32-bit signed integer.
 *    \li RwUInt32 32-bit unsigned integer.
 *    \li RwInt64 64-bit signed integer.
 *    \li RwUInt64 64-bit unsigned integer.
 *    \li RwInt128 128-bit signed integer.
 *    \li RwUInt128 128-bit unsigned integer.
 *    \li RwBool Boolean type (in 32 bits).
 *
 * These types should be used in applications in preference to the underlying
 * native types. 
 * 
 * The following constants indicate the maximum and minimum values possible
 * for the various RenderWare integer types:
 *
 *    \li RwInt32MAXVAL   Maximum RwInt32 value.
 *    \li RwInt32MINVAL   Minimum RwInt32 value.
 *    \li RwUInt32MAXVAL   Maximum RwUInt32 value.
 *    \li RwUInt32MINVAL   Minimum RwUInt32 value.
 *    \li RwInt16MAXVAL   Maximum RwInt16 value.
 *    \li RwInt16MINVAL   Minimum RwInt16 value.
 *    \li RwUInt16MAXVAL   Maximum RwUInt16 value.
 *    \li RwUInt16MINVAL   Minimum RwUInt16 value.
 *
 * \see RwReal
 */

/**
 * \ingroup datatypes
 * \typedef RwReal 
 *
 * RenderWare supports a single RwReal floating-point type to aid portability
 * across platforms. This type should be used in applications in preference to
 * the underlying native type.
 *
 * The constants RwRealMAXVAL and RwRealMINVAL are provided for determining
 * the maximum and minimum values possible using the RwReal type.
 *
 * In addition, the following macros are available for operations on RwReal
 * types:
 *      \li RwRealMin2(a, b)    Find the minimum of two RwReal values.
 *      \li RwRealMax2(a, b)    Find the maximum of two RwReal values.
 *      \li RwRealMin3(a, b, c)    Find the minimum of three RwReal values.
 *      \li RwRealMax3(a, b, c)    Find the maximum of three RwReal values.
 *      \li RwRealAbs(x)    Find the absolute value of a RwReal value.
 *
 * \see \ref inttypes
 */

/** 
 * \ingroup datatypes
 * \typedef RwFixed
 * 
 * RenderWare Graphics supports a single RwFixed fixed-point type.
 *
 * Although popular in the days when integer math was much faster than floating point math, 
 * fixed-point math is now rarely used. It is provided because it is still useful for some
 * processes.
 *
 * The maximum and minimum size of an RwFixed value are defined by the constants
 * RWFIX_MAX and RWFIX_MIN respectively.
 *
 * The following macros are provided to help you work with RwFixed datatypes:
 *      \li RwFixedCast(x)		Cast the integer portion of an RwFixed to another type.
 *      \li RwFixedToInt(x)		Convert an RwFixed to an integer. (The fractional portion is lost.)
 *      \li RwFixedToFloat(x)	Convert an RwFixed to a float.
 *      \li RwFixedToReal(x)		Convert an RwFixed to an RwReal.
 *      \li RwRealToFixed(x)		Convert an RwReal to an RwFixed. (Some precision may be lost.)
 */

/** 
 * \ingroup datatypes
 * \typedef RwInt8    
 * 
 * Signed 8 bit integer type.
 * \see \ref inttypes
 */

/** 
 * \ingroup datatypes
 * \typedef RwUInt8   
 *
 * Unsigned 8bit integer type.
 * \see \ref inttypes
 */

/** 
 * \ingroup datatypes
 * \typedef RwChar    
 *
 * Character type.
 * \see \ref inttypes
 */

/** 
 * \ingroup datatypes
 * \typedef RwInt16   
 *
 * Signed 16 bit integer type.
 * \see \ref inttypes
 */

/** 
 * \ingroup datatypes
 * \typedef RwUInt16  
 *
 * Unsigned 16 bit integer type.
 * \see \ref inttypes
 */

/** 
 * \ingroup datatypes
 * \typedef RwInt32   
 *
 * Signed 32 bit integer type.
 * \see \ref inttypes
 */

/** 
 * \ingroup datatypes
 * \typedef RwUInt32  
 *
 * Unsigned 32 bit integer type.
 * \see \ref inttypes
 */

/** 
 * \ingroup datatypes
 * \typedef RwInt64   
 *
 * Signed 64 bit integer type.
 * \see \ref inttypes
 */

/** 
 * \ingroup datatypes
 * \typedef RwUInt64  
 *
 * Unsigned 64 bit integer type.
 * \see \ref inttypes
 */

/** 
 * \ingroup datatypes
 * \typedef RwInt128  
 *
 * Signed 128 bit integer type.
 * \see \ref inttypes
 */

/** 
 * \ingroup datatypes
 * \typedef RwUInt128 
 *
 * Unsigned 128 bit integer type.
 * \see \ref inttypes
 */

/** 
 * \ingroup datatypes
 * \typedef RwBool    
 *
 * Boolean type.
 * \see \ref inttypes
 */
 

#endif /* RWTYPES_H */
#endif /* defined(RWANOPLATFORM) || defined(RWADOXYGEN) */


/*--- Automatically derived from: d:/dev/rwa/source/core/src/rwatimer.h ---*/

#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */

#if !defined (RWADOXYGEN)

/* open module */
extern RwBool   _rwaTimerModuleOpen( void );

/* close module */
extern void     _rwaTimerModuleClose( void );

/* start timer */
extern void     RwaTimerStart( void );

/* stop timer */
extern RwUInt32 RwaTimerStop( void );

/* get the timer value */
extern RwUInt32 RwaTimerGetValue( void );

/* get the timer's frequency */
extern RwUInt32 RwaTimerGetFrequency( void );

#ifdef    __cplusplus
}
#endif /* __cplusplus */

#endif /* RWADOXYGEN */


/*--- Automatically derived from: d:/dev/rwa/source/core/src/rwauuid.h ---*/
/******************************************************************************
 * Defines & Macros
 *****************************************************************************/

/* length of a UUID string */
#define RWAUUIDSTRINGLEN 37 

#if !defined(EXTERN_C)
#if !defined(RWAINITUUID)
#if defined(__cplusplus)
#define EXTERN_C extern "C"
#else
#define EXTERN_C extern
#endif /* __cplusplus */
#else
#define EXTERN_C
#endif /* !defined(RWAINITUUID) */
#endif /* !defined(EXTERN_C) */

#ifndef RWAINITUUID
#define RWADEFINE_UUID(_name, _time_low, _time_mid, _time_hi_and_version, \
                       b1, b2, b3, b4, b5, b6, b7, b8) \
    EXTERN_C const RwaUUID _name
#else

#define RWADEFINE_UUID(_name, _time_low, _time_mid, _time_hi_and_version, \
                               b1, b2, b3, b4, b5, b6, b7, b8) \
    EXTERN_C const RwaUUID _name \
                = { _time_low, _time_mid, _time_hi_and_version, \
                  { b1, b2,  b3,  b4,  b5,  b6,  b7,  b8 } }
#endif /* RWAINITGUID */

/******************************************************************************
 * Type Defintions
 *****************************************************************************/
#if !defined(RWADOXYGENINTERNAL)
typedef struct RwaUUID RwaUUID;
/**
 * \ingroup rwauuid
 * UUID type.  Uniquely identifies objects within RenderWare Audio
 */
struct RwaUUID
{
    RwUInt32    time_low;            /**<low field of the timestamp*/
    RwUInt16    time_mid;            /**<mid field of the timestamp*/
    RwUInt16    time_hi_and_version; /**<high field of the timestamp 
                                        multiplexed with the version number */
    RwUInt8     node[8];             /**<node[0] is the high field of the clock
                                         sequence muliplexed with the variant.
                                         node[1] is the low filed of the clock
                                         sequence.  nodes 2-7 comprise the 
                                         spatially unique node identifier. */
};
#endif /* !defined(RWADOXYGENINTERNAL) */

/* flags for uniqueID structure */
#define rwaUNIQUEIDFLAGS_COPIEDUUID 0x0001
#define rwaUNIQUEIDFLAGS_COPIEDNAME 0x0002

#if !defined(RWADOXYGENINTERNAL)
typedef struct RwaUniqueID RwaUniqueID;
/**
 * \ingroup rwacore
 * Unique ID
 */
struct RwaUniqueID
{
    union
    {
        const RwaUUID *uuid;       /**<Statically allocated Universially Unique Identifier */
        RwaUUID       *copyUUID;   /**<Dynamically allocated Universially Unique Identifier */
    } uuid;
    union
    {
        const RwChar  *uniqueName; /**<Staticlly allocated human readable name */
        RwChar        *copyName;   /**<Dynamically allocated human readable name */
    } name;
    RwUInt32      flags;
};
#endif /* !defined(RWADOXYGENINTERNAL) */

#ifndef RWADEBUG

#define _rwaUniqueIDGetUUID(_uniqueIDPtr) \
    (_uniqueIDPtr)->uuid.uuid

#define _rwaUniqueIDGetName(_uniqueIDPtr) \
    (_uniqueIDPtr)->name.uniqueName

#endif /* RWADEBUG */


/******************************************************************************
 * Function Prototypes
 *****************************************************************************/

#if !defined (RWADOXYGEN)

#ifdef __cplusplus
extern "C"
{
#endif

/* generate a UUID */
void RwaUUIDGenerate( RwaUUID *uuid );

/* generate a UUID string */
void RwaUUIDStringGenerate ( RwChar *uuidString );

/* convert UUID to a string */
void RwaUUIDToString ( const RwaUUID *uuid, RwChar *uuidString );

/* convert a string to a UUID */
void RwaStringToUUID ( const RwChar *uuidString, RwaUUID *uuid );

/* compare two UUIDs */
RwInt32 RwaUUIDCompare ( const RwaUUID *uuid1, const RwaUUID *uuid2 );

/* compare two string IDs */
RwInt32 RwaStringCompare ( const RwChar *textID1, const RwChar *textID2 );


#ifdef RWADEBUG
/* get a name from a uniqueID */
const RwChar*  _rwaUniqueIDGetName( const RwaUniqueID *uniqueID );

/* get a uuid from a uniqueID */
const RwaUUID* _rwaUniqueIDGetUUID( const RwaUniqueID *uniqueID );
#endif /* RWADEBUG */

#ifdef __cplusplus
}
#endif

#endif /* RWADOXYGEN */


/*--- Automatically derived from: d:/dev/rwa/source/core/src/rwadebug.h ---*/

#include <stdio.h>
#include <string.h>

/******************************************************************************
 * Defines
 *****************************************************************************/

#if defined(RWADEBUG)
    #define RWAUSEASSERTS
#endif

#define RWAUSEERRORCHECKING

/* assertion */
#ifdef RWAUSEASSERTS
    #ifdef WIN32
        #define RWAASSERTE(x,s) \
            if (!(x)) {printf("RWAASSERT : %s %d %s\n", __FILE__, __LINE__, s); \
                _asm { int 3h}; }
    #endif

    /* PS2 EE  & IOP */
    #if (defined(mips) && defined(MIPSEL))
        #ifdef	__MWERKS__
            #define RWAASSERTE(_x,_s) \
                if (!(_x)) {printf("RWAASSERT : %s %d %s\n", __FILE__, __LINE__, _s);   \
                    asm volatile ("breakc 0x0");}
        #endif
        
        #if (defined(__GNUC__)) && (!defined(__MINGW32__)) && (!defined(__MWERKS__))
            #define RWAASSERTE(_x,_s) \
                if (!(_x)) {printf("RWAASSERT : %s %d %s\n", __FILE__, __LINE__, _s);   \
                    asm volatile ("break");}
        #endif
    #endif
    
#else
    #define RWAASSERTE(_x,_s)
#endif


#define RwaMemClr(_ptr, _size) memset(_ptr, 0x00, _size)


#if defined(RWADEBUG)
    #define RwaStructInit(_ptr) memset(_ptr, 0xCD, sizeof(*_ptr))
    #define RwaMemInit(_ptr, _size) memset(_ptr, 0xCD, _size)
#else /* RWADEBUG */
    #define RwaStructInit(_ptr) memset(_ptr, 0x00, sizeof(*_ptr))
    #define RwaMemInit(_ptr, _size) memset(_ptr, 0x00, _size)
#endif /* RWADEBUG */


#ifdef  RWAUSEASSERTS
    #define RWAVERIFY(expr)  if (!expr) RWAASSERTE(1,#expr)
#else   /*_DEBUG*/ 
    #define RWAVERIFY(expr)  expr
#endif  /*_DEBUG*/ 


/* debug output */
#if defined(RWADEBUG)

    /* standard printf */
    #define RWAPRINTF(c) printf c

    /* warning output */
    #define RWAPRINTWARNING(c) \
        RWAPRINTF(("WARNING: %s %d", __FILE__, __LINE__)); \
        RWAPRINTF(c)

    /* error output */
    #define RWAPRINTERROR(c) \
        RWAPRINTF(("ERROR: %s %d", __FILE__, __LINE__)); \
        RWAPRINTF(c)

#else /* RWADEBUG */

    #define RWAPRINTF(c)
    #define RWAPRINTWARNING(c)
    #define RWAPRINTERROR(c)

#endif /* RWADEBUG */


#ifdef RWAUSEASSERTS
#define RWAASSERT(_x) RWAASSERTE(_x, #_x)
#else
#define RWAASSERT(_x)
#endif

/******************************************************************************
 * Type Defintions
 *****************************************************************************/

/**
 * \ingroup datatypes
 * RwaDebugType 
 * This type represents the different types of debug and 
 * trace messages that can be sent to the currently installed debug handler 
 * (see API function \ref RwaDebugSendMessage)*/
enum RwaDebugType
{
    rwaNADEBUGTYPE = 0, /**<Invalid*/
    rwaDEBUGASSERT,      /**<Send an assert message*/
    rwaDEBUGERROR,       /**<Send an error message*/
    rwaDEBUGMESSAGE,     /**<Send an informational message*/
    rwaDEBUGTRACE,       /**<Send a trace message*/
    rwaDEBUGTYPEFORCEENUMSIZEINT
};
typedef enum RwaDebugType RwaDebugType;

/**
 * \ingroup datatypes
 * \ref RwaDebugHandler
 * This type represents the
 * function called from \ref RwaDebugSendMessage for sending a message to the
 * RenderWare Audio debug stream.
 *
 * \param  type   Type of debug message (assert, error, etc.).
 *
 * \param  string   Pointer to a string containing the error
 * message.
 * 
 * \return Nothing
 *
 * \remarks
 * This function requires the application to be linked against the following 
 * libraries...<BR>
 * <B>rwacore.lib</B> <BR><BR>
 * This function also requires the following headers to be included...<BR>
 * <B>rwacore.h</B><BR><BR>
 *
 * \see RwaDebugSetHandler
 */
typedef void(* RwaDebugHandler)(RwaDebugType type, const RwChar *string) ;

/******************************************************************************
 * Function Prototypes & Some function like macros
 *****************************************************************************/

/* print a debug message */
void _rwaprintf(const RwChar * format, ...);

#ifdef RWADEBUG

#define RwaDebugSendMessage(type, funcName, message)    \
    _rwaDebugSendMessage(type, __FILE__, __LINE__, funcName, message)

#if RWAVERBOSE
#define RWNOTIFY(_func, _message)                            \
    _rwDebugSendMessage(rwDEBUGTRACE, __FILE__,  __LINE__, _func, _message)
#endif /* RWAVERBOSE */

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/* setup a debug handler */
RwaDebugHandler RwaDebugSetHandler ( RwaDebugHandler handler );

/* send and debug message */
void _rwaDebugSendMessage ( 
    RwaDebugType  type,  
    const RwChar *fileName,  
    const RwInt32 line,  
    const RwChar *funcName,  
    const RwChar *message );

/* set the debug trace state */
void RwaDebugSetTraceState ( RwBool state );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#else

#define RWNOTIFY(_func, _message)

/* all functions calls are preprocessed out of the code in release build */
#define RwaDebugSetHandler(handler)
#define RwaDebugSetTraceState(state)
#define RwaDebugSendMessage(type, funcName, message)

#endif /* RWADEBUG */


/*--- Automatically derived from: d:/dev/rwa/source/core/src/rwamemory.h ---*/

/******************************************************************************
 * Macros
 *****************************************************************************/

#if defined(RWADOXYGEN)
/**
 * \ingroup rwmem
 * \def RwMalloc
 * RwMalloc(_s) is a macro for malloc(_s).
 */
#define RwMalloc(_s) ((memoryFuncs.rwmalloc)((_s)))

/**
 * \ingroup rwmem
 * \def RwFree
 * RwFree(_p) is a macro for free(_p).
 */
#define RwFree(_p) ((memoryFuncs.rwfree)((_p)))

/**
 * \ingroup rwmem
 * \def RwCalloc
 * RwCalloc(_n, _s) is a macro for calloc(_n, _s).
 */
#define RwCalloc(_n, _s) ((memoryFuncs.rwcalloc)((_n), (_s)))

/**
 * \ingroup rwmem
 * \def RwRealloc
 * RwRealloc(_p, _s) is a macro for realloc(_p, _s).
 */
#define RwRealloc(_p, _s) ((memoryFuncs.rwrealloc)((_p),(_s)))

#endif /* defined(RWADOXYGEN) */

#if (!defined(RwaMalloc))
#define RwaMalloc(_s) _rwaMalloc((_s))
#endif /* (!defined(RwaMalloc)) */

#if (!defined(RwaFree))
#define RwaFree(_p) _rwaFree((_p))
#endif /* (!defined(RwaFree)) */

#if (!defined(RwaCalloc))
#define RwaCalloc(_n, _s) _rwaCalloc((_n), (_s))
#endif /* (!defined(RwaCalloc)) */

#if (!defined(RwaRealloc))
#define RwaRealloc(_p, _s) _rwaRealloc((_p), (_s))
#endif /* (!defined(RwaRealloc)) */

/******************************************************************************
 * Types
 *****************************************************************************/

#if defined(RWANOPLATFORM) || defined(RWADOXYGEN)
typedef struct RwMemoryFunctions RwMemoryFunctions;
/**
 * \ingroup datatypes
 * \struct RwMemoryFunctions
 * This type represents the memory functions used
 * by RenderWare Audio. By default, the standard ANSI functions are used. The
 * application may install an alternative interface providing that it is ANSI
 * compliant
 */
struct RwMemoryFunctions
{
    /* c.f.
     * Program Files/Microsoft Visual Studio/VC98/Include/MALLOC.H
     */
    void *(*rwmalloc)(size_t size);                   /**<rwmalloc  malloc */
    void  (*rwfree)(void *mem);                       /**<rwfree    free */
    void *(*rwrealloc)(void *mem, size_t newSize);    /**<rwrealloc realloc */
    void *(*rwcalloc)(size_t numObj, size_t sizeObj); /**<rwcalloc  calloc */
};
#endif /* defined(RWANOPLATFORM)  || defined(RWADOXYGEN) */

/******************************************************************************
 * Globals
 *****************************************************************************/

#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */

/* memory function pointers */
extern RwMemoryFunctions *_rwMemFuncs;

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

/* returns the memory interface */
extern RwMemoryFunctions *RwOsGetMemoryInterface(void);

/* returns the memory interface for renderware audio */
RwMemoryFunctions* RwaOsGetMemoryInterface(void);


/* RenderWare Audio's Memory functions */
void* _rwaMalloc(size_t size);
void  _rwaFree(void *block);
void* _rwaRealloc(void *block, size_t size);
void* _rwaCalloc(size_t numObj, size_t sizeObj);

#ifdef    __cplusplus
}
#endif /* __cplusplus */


/*--- Automatically derived from: d:/dev/rwa/source/core/src/rwafile.h ---*/

/******************************************************************************
 * Non-conditional defines
 *****************************************************************************/
/**  
 * \ingroup rwfile
 * \def RwFexist
 * RwFexist(_name) determines whether a file exists using the installed 
 * RenderWare file system.
 * 
 * \see RwOsGetFileInterface
 */
#define RwFexist(_name) \
    _rwFileFuncs->rwfexist(_name)

/**
 * \ingroup rwfile
 * \def RwFopen
 * RwFopen(_name, _access) opens a file using the installed RenderWare file
 * system.
 * 
 * \see RwOsGetFileInterface
 */
#define RwFopen(_name, _access) \
    _rwFileFuncs->rwfopen(_name, _access)

/**
 * \ingroup rwfile
 * \def RwFclose
 * RwFclose(_fptr) closes a file using the installed RenderWare file
 * system.
 * 
 * \see RwOsGetFileInterface
 */
#define RwFclose(_fptr) \
    _rwFileFuncs->rwfclose(_fptr)

/**
 * \ingroup rwfile
 * \def RwFread
 * RwFread(_addr, _size, _count, _fptr) reads from a file using the installed 
 * RenderWare file system.
 * 
 * \see RwOsGetFileInterface
 */
#define RwFread(_addr, _size, _count, _fptr) \
    _rwFileFuncs->rwfread(_addr, _size, _count, _fptr)

/**
 * \ingroup rwfile
 * \def RwFwrite
 * RwFwrite(_addr, _size, _count, _fptr) write to a file using the installed 
 * RenderWare file system.
 * 
 * \see RwOsGetFileInterface
 */
#define RwFwrite(_addr, _size, _count, _fptr) \
    _rwFileFuncs->rwfwrite(_addr, _size, _count, _fptr)

/**
 * \ingroup rwfile
 * \def RwFgets
 * RwFgets(_buffer, _maxLen, _fptr) gets a string from a file using the 
 * installed RenderWare file system.
 * 
 * \see RwOsGetFileInterface
 */
#define RwFgets(_buffer, _maxLen, _fptr) \
     _rwFileFuncs->rwfgets(_buffer, _maxLen, _fptr)

/**
 * \ingroup rwfile
 * \def RwFputs
 * RwFputs(_buffer, _fptr) puts a string to a file using the installed 
 * RenderWare file system.
 * 
 * \see RwOsGetFileInterface
 */
#define RwFputs(_buffer, _fptr) \
      _rwFileFuncs->rwfputs(_buffer, _fptr)

/**
 * \ingroup rwfile
 * \def RwFeof
 * RwFeof(_fptr) determine whether this file pointer is at the end of a file 
 * using the installed RenderWare file system.
 * 
 * \see RwOsGetFileInterface
 */
#define RwFeof(_fptr) \
    _rwFileFuncs->rwfeof(_fptr)

/**
 * \ingroup rwfile
 * \def RwFseek
 * RwFseek(_fptr, _offset, _origin) seeks to a position within a file
 * using the installed RenderWare file system.
 * 
 * \see RwOsGetFileInterface
 */
#define RwFseek(_fptr, _offset, _origin) \
    _rwFileFuncs->rwfseek(_fptr, _offset, _origin)

/**
 * \ingroup rwfile
 * \def RwFflush
 * RwFflush(_fptr) flushes the contents of the buffer associated with the file
 * stream using the installed RenderWare file system.
 * 
 * \see RwOsGetFileInterface
 */
#define RwFflush(_fptr) \
    _rwFileFuncs->rwfflush(_fptr)

/**
 * \ingroup rwfile
 * \def RwFtell
 * RwFtell(_fptr) returns the position within a file using the installed 
 * RenderWare file system.
 * 
 * \see RwOsGetFileInterface
 */
#define RwFtell(_fptr) \
    _rwFileFuncs->rwftell(_fptr)

#if defined(RWANOPLATFORM) || defined(RWADOXYGEN)

/* size of a RwStream header */
#define RWSTREAMHEADERSIZE 12

/****************************************************************************
 Global Types
 */

/**
 * \ingroup datatypes
 * \typedef rwFnFexist
 * Returns true if file with given name exists, false if it doesn't.
 */
typedef RwBool  (*rwFnFexist)(const RwChar *name);

/**
 * \ingroup datatypes
 * \typedef rwFnFopen
 * Mimics ANSI C Standard Library fopen.
 */
typedef void   *(*rwFnFopen)(const RwChar *name, const RwChar *access);

/**
 * \ingroup datatypes
 * \typedef rwFnFclose
 * Mimics ANSI C Standard Library fclose.
 */
typedef int     (*rwFnFclose)(void *fptr);

/**
 * \ingroup datatypes
 * \typedef rwFnFread
 * Mimics ANSI C Standard Library fread.
 */
typedef size_t  (*rwFnFread)(void *addr, size_t size, size_t count, void *fptr);

/**
 * \ingroup datatypes
 * \typedef rwFnFwrite
 * Mimics ANSI C Standard Library fwrite.
 */
typedef size_t  (*rwFnFwrite)(const void *addr, size_t size, size_t count, void *fptr);

/**
 * \ingroup datatypes
 * \typedef rwFnFgets
 * Mimics ANSI C Standard Library fgets.
 */
typedef RwChar *(*rwFnFgets)(RwChar *buffer, int maxLen, void *fptr);

/**
 * \ingroup datatypes
 * \typedef rwFnFputs
 * Mimics ANSI C Standard Library fputs.
 */
typedef int     (*rwFnFputs)(const RwChar *buffer, void *fptr);

/**
 * \ingroup datatypes
 * \typedef rwFnFeof
 * Mimics ANSI C Standard Library feof.
 */
typedef int     (*rwFnFeof)(void *fptr);

/**
 * \ingroup datatypes
 * \typedef rwFnFseek
 * Mimics ANSI C Standard Library fseek.
 */
typedef int     (*rwFnFseek)(void *fptr, long offset, int origin);

/**
 * \ingroup datatypes
 * \typedef rwFnFflush
 * Mimics ANSI C Standard Library fflush.
 */
typedef int     (*rwFnFflush)(void *fptr);

/**
 * \ingroup datatypes
 * \typedef rwFnFtell
 * Mimics ANSI C Standard Library ftell.
 */
typedef int     (*rwFnFtell)(void *fptr);


/**
 * \ingroup datatypes
 * \typedef RwFileFunctions
 * typedef for struct RwFileFunctions
 */
typedef struct RwFileFunctions RwFileFunctions;
/**
 * \ingroup datatypes
 * \struct RwFileFunctions
 * This type is used to specify the file access
 * functions used by RenderWare Audio. The default file system uses the standard
 * ANSI functions. The application may install an alternative file system
 * providing it complies with the ANSI interface -- see API 
 * function \ref RwOsGetFileInterface.
 *
 * The function types associated with this type are defined as follows 
 *
 * \verbatim
   RwBool (*rwFnFexist)(const RwChar *name)
       void *(*rwFnFopen)(const RwChar *name, const RwChar *access) 
       int (*rwFnFclose)(void *fptr)
       size_t (*rwFnFread)(void *addr, size_t size, size_t count, void *fptr)                        
       size_t (*rwFnFwrite)(const void *addr, size_t size, size_t count,
                 void *fptr)
   RwChar *(*rwFnFgets)(RwChar *buffer, int maxLen, void *fptr)
       int (*rwFnFputs)(const RwChar *buffer, void *fptr)
       int (*rwFnFeof)(void *fptr)
       int (*rwFnFseek)(void *fptr, long offset, int origin)
       int (*rwFnFflush)(void *fptr)
       int (*rwFnFtell)(void *fptr)
 \endverbatim
 * Note the function argument lists are consistent with the ANSI
 * standard file access interface:
 */
struct RwFileFunctions
{
    rwFnFexist  rwfexist; /**< Pointer to fexist function */
    rwFnFopen   rwfopen;  /**< Pointer to fopen function */
    rwFnFclose  rwfclose; /**< Pointer to fclose function */
    rwFnFread   rwfread;  /**< Pointer to fread function */
    rwFnFwrite  rwfwrite; /**< Pointer to fwrite function */
    rwFnFgets   rwfgets;  /**< Pointer to fgets function */
    rwFnFputs   rwfputs;  /**< Pointer to puts function */
    rwFnFeof    rwfeof;   /**< Pointer to feof function */
    rwFnFseek   rwfseek;  /**< Pointer to fseek function */
    rwFnFflush  rwfflush; /**< Pointer to fflush function */
    rwFnFtell   rwftell;  /**< Pointer to ftell function */  
};


#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

extern RwFileFunctions *RwOsGetFileInterface(void);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

#else /* defined(RWANOPLATFORM) || defined(RWADOXYGEN) */

#ifdef    __cplusplus
extern "C"
{
#endif
extern RwFileFunctions  *_rwFileFuncs;
#ifdef    __cplusplus
}
#endif


#endif /* RWANOPLATFORM */

#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

extern RwBool RwaInstallFileSystem(RwChar *subdir);
extern void   RwaUnInstallFileSystem(void);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */


/*--- Automatically derived from: d:/dev/rwa/source/core/src/rwabase.h ---*/
/******************************************************************************
 * Defines
 *****************************************************************************/

#define USEFREELISTS

/* ranges not defined by RenderWare Graphics */
#define RwInt8MINVAL   0x80
#define RwInt8MAXVAL   0x7F
#define RwUInt8MAXVAL  0xFF
#define RwInt16MINVAL  0x8000
#define RwInt16MAXVAL  0x7FFF
#define RwUInt16MAXVAL 0xFFFF
#define RwInt64MINVAL  0x8000000000000000
#define RwInt64MAXVAL  0x7FFFFFFFFFFFFFFF
#define RwUInt64MAXVAL 0xFFFFFFFFFFFFFFFF

/* defines the name space for all global variables in Rwa */
#define RWASRCGLOBAL(_name) _rwaG##_name

/* used with stream chunk IDs */
#define RWAMAKECHUNKID(vendorID, chunkID) (((vendorID & 0xFFFFFF) << 8) | (chunkID & 0xFF))
#define RWAGETVENDORID(chunkID) ((chunkID >> 8) & 0xFFFFFF)

/******************************************************************************
 * Macros
 *****************************************************************************/

/* initialise a linked list node */
#define RWALLNODEINIT(node) \
    MACRO_START \
    { \
        (node)->prev = NULL; \
        (node)->next = NULL; \
        (node)->data = NULL; \
    } \
    MACRO_STOP

/*-----------------------------------------------------------------------------
 - define RWANOPLATFORM for no RenderWare Platform 
 ----------------------------------------------------------------------------*/
#if defined(RWANOPLATFORM)

/* no stream functionality */
typedef void RwStream;

#endif /* defined(RWANOPLATFORM) */

/******************************************************************************
 * Type Defintions
 *****************************************************************************/

#if !defined(RWADOXYGENINTERNAL)
/**
 * \ingroup rwacore
 * Atomic Parameter Types
 */
typedef enum RwaType
{
    rwaTYPE_UINT8   = 0x0001, /**<8 bit unsigned int */
    rwaTYPE_INT8    = 0x0002, /**<8 bit signed int */
    rwaTYPE_UINT16  = 0x0004, /**<16 bit unsigned int */
    rwaTYPE_INT16   = 0x0008, /**<16 bit signed int */
    rwaTYPE_UINT32  = 0x0010, /**<32 bit unsigned int */
    rwaTYPE_INT32   = 0x0020, /**<32 bit signed int */
    rwaTYPE_UINT64  = 0x0040, /**<64 bit unsigned int */
    rwaTYPE_INT64   = 0x0080, /**<64 bit signed int */
    rwaTYPE_UINT128 = 0x0100, /**<128 bit unsigned int */
    rwaTYPE_INT128  = 0x0200, /**<128 bit signed int */
    rwaTYPE_FLOAT   = 0x0400, /**<4 byte floating point */
    rwaTYPE_DOUBLE  = 0x0800, /**<8 byte floating point */
    rwaTYPE_POINTER = 0x1000, /**<pointer */
    rwaTYPE_ARRAY   = 0x2000, /**<array */
    rwaTYPE_ALIAS   = 0x4000  /**<alias */
} RwaType;


typedef struct RwaLLNode RwaLLNode;
/**
 * \ingroup rwacore
 * Node of a doubly linked list
 */
struct RwaLLNode
{
    struct RwaLLNode *prev;  /**<previous node in list */
    struct RwaLLNode *next;  /**<next node in list */
    void             *data;  /**<data in list */
};

typedef struct RwaFreeList RwaFreeList;
/**
 * \ingroup rwacore
 * Free list
 */
struct RwaFreeList
{
    RwUInt32   entrySize;       /**<size of an entry in the free list */
#ifdef RWADEBUG
    RwUInt32   nonAlignedEntrySize;
#endif /* RWADEBUG */
    RwUInt32   entriesPerBlock; /**<number of entries per free list block */
    RwUInt32   alignment;       /**<alignment of a free list entry */
    RwUInt32   blocks;          /**<total number of blocks */
    RwLinkList blockList;       /**<list of data blocks */
    RwBool     staticAlloc;     /**<TRUE if the structure was statically allocated */
    RwLLLink   link;            /**<link to the free list linked list */
};

/* RWAPUBLICEND */

/**
 * \ingroup rwacore 
 * Stream vendor IDs for RenderWare Audio
 * Check enumeration found in rwsdk/src/batype.h
 */
enum RwaPluginVendor
{
    rwaVENDORID_CRITERIONRWA        = 0x000008L,
    rwaPLUGINVENDORFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RwaPluginVendor RwaPluginVendor;


/**
 * \ingroup rwacore
 * Custom chunk IDs for RenderWare Audio stream chunks. 
 */
enum RwaCoreChunkID
{
    /* single object definition alias */
    rwaID_OBJDEFALIAS            = RWAMAKECHUNKID(rwaVENDORID_CRITERIONRWA, 0x00),
    rwaID_OBJDEFALIAS_DATA       = RWAMAKECHUNKID(rwaVENDORID_CRITERIONRWA, 0x01),
    /* single wave */
    rwaID_WAVE                   = RWAMAKECHUNKID(rwaVENDORID_CRITERIONRWA, 0x02),
    rwaID_WAVESTRUCT             = RWAMAKECHUNKID(rwaVENDORID_CRITERIONRWA, 0x03),
    rwaID_WAVEDATA               = RWAMAKECHUNKID(rwaVENDORID_CRITERIONRWA, 0x04),
    /* object dictionary */
    rwaID_OBJDICT                = RWAMAKECHUNKID(rwaVENDORID_CRITERIONRWA, 0x05),
    rwaID_OBJDICTOBJDEFALIAS     = RWAMAKECHUNKID(rwaVENDORID_CRITERIONRWA, 0x06),
    rwaID_OBJDICTOBJDEFALIAS_HDR = RWAMAKECHUNKID(rwaVENDORID_CRITERIONRWA, 0x07),
    rwaID_OBJDICTOBJDEFALIAS_DAT = RWAMAKECHUNKID(rwaVENDORID_CRITERIONRWA, 0x08),
    /* wave dictionary */
    rwaID_WAVEDICT               = RWAMAKECHUNKID(rwaVENDORID_CRITERIONRWA, 0x09),
    rwaID_WAVEDICT_DICT          = RWAMAKECHUNKID(rwaVENDORID_CRITERIONRWA, 0x0A),
    rwaID_WAVEDICT_WAVE_HDR      = RWAMAKECHUNKID(rwaVENDORID_CRITERIONRWA, 0x0B),
    rwaID_WAVEDICT_WAVE          = RWAMAKECHUNKID(rwaVENDORID_CRITERIONRWA, 0x0C),
    rwaID_WAVEDICT_WAVEDATA_HDR  = RWAMAKECHUNKID(rwaVENDORID_CRITERIONRWA, 0x0D),
    rwaID_WAVEDICT_WAVEDATA      = RWAMAKECHUNKID(rwaVENDORID_CRITERIONRWA, 0x0E),
    rwaCORECHUNKIDFORCEENUMSIZEINT  = RWFORCEENUMSIZEINT
};
typedef enum RwaCoreChunkID RwaCoreChunkID;

/* RWAPUBLIC */

#endif /* !defined(RWADOXYGENINTERNAL) */

#if defined(RWAMETRICS) || defined(RWADOXYGEN)
typedef struct RwaMetrics RwaMetrics;
/**
 * \ingroup rwacore
 * Global Metrics information
 *
 * \note This metrics information is only available in METRICS builds.
 * METRICS builds require metrics libraries for RenderWare Audio to be used and 
 * RWAMETRICS to be defined by the application.
 * For more information about build types see the section on 
 * \ref buildtypes "RenderWare Audio Build Types".
 */
struct RwaMetrics
{
    RwUInt32 noObjects;            /**<total number of objects */
    RwUInt32 noDefinitions;        /**<number of object definitions */
    RwUInt32 noAllocs;             /**<number of allocations */
    RwUInt32 totalStartUpdateTime; /**<total time within RwaCoreUpdateStart*/
    RwUInt32 totalFinishUpdateTime;/**<total time within RwaCoreUpdateFinish*/
    RwUInt32 usedMemory;
};
#endif /* RWAMETRICS */

/******************************************************************************
 * Globals
 *****************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif

/* debug */
extern RwInt32    RWASRCGLOBAL(debugStackDepth); /* stack depth */
extern RwBool     RWASRCGLOBAL(debugTrace);      /* TRUE turns tracing on */

#ifdef RWAMETRICS
extern RwaMetrics RWASRCGLOBAL(metrics);         /* global metrics */
#endif /* RWAMETRICS */

/* block alignment */
extern RwUInt32   RWASRCGLOBAL(blockAlign);      /* min block alignment size */

#ifdef __cplusplus
}
#endif

/******************************************************************************
 * Function Prototypes
 *****************************************************************************/

/* Do NOT remove this line or Doxygen will make a mess of the hyperlinking. */
#if !defined (RWADOXYGEN)


#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */

/*-----------------------------------------------------------------------------
 - Core Functions
 ----------------------------------------------------------------------------*/

/* open and initalise RenderWare Audio core */
RwBool RwaCoreOpen ( RwMemoryFunctions *memFuncs, RwBool usingRwGraphics );

/* whether the core is open */
RwBool RwaCoreIsOpen ( void );

/* start RenderWare Audio update */
void RwaCoreUpdateStart ( void );

/* finish RenderWare Audio update */
void RwaCoreUpdateFinish ( void );

/* update RenderWare Audio */
void RwaCoreUpdate ( void );

/* whether the core is updating */
RwBool RwaCoreIsUpdating ( void );

/* close RenderWare Audio core */
void RwaCoreClose  ( void );

/* Register default object definitions for the os */
extern RwBool RwaOsRegisterDefaults ( void );

/* get the current tick time */
RwUInt32 RwaCoreGetTickTime ( void );

/* determines the size of a type */
RwUInt32 RwaSizeOf ( RwaType type );

/* returns metrics information from the core */
#ifdef RWAMETRICS
RwaMetrics* RwaCoreGetMetrics( void );
#endif /* RWAMETRICS */

/* setup the pointer alignment */
RwUInt32 RwaSetBlockAlign( RwUInt32 size );

/*-----------------------------------------------------------------------------
 - RWA Free List Functions 
 ----------------------------------------------------------------------------*/
/* open the free list module */
RwBool _rwaFreeListModuleOpen( void );

/* close the free list module */
void _rwaFreeListModuleClose ( void );

/* create a free list */
RwaFreeList *RwaFreeListCreate(
    RwUInt32    entrySize, 
    RwUInt32    entriesPerBlock, /* must be multiple of 8 */
    RwUInt32    alignment,
    RwaFreeList *freeList);

/* destroy a free list */
void RwaFreeListDestroy( RwaFreeList *freeList );

/* allocate an entry in a free list */
void *RwaFreeListAlloc( RwaFreeList *freeList );

/* free an entry in a free list */
void RwaFreeListFree ( RwaFreeList *freeList, void *block );

/*-----------------------------------------------------------------------------
 - RWA Linked List Functions
 ----------------------------------------------------------------------------*/

/* add an item to a linked list */
RwaLLNode* RwaLListAdd(RwaLLNode *head, void *data);

/* remove an data item from a linked list */
RwaLLNode* RwaLListRemoveData(RwaLLNode *head, void *data);

/* remove an item from a linked list */
void RwaLListRemoveNode(RwaLLNode *head, RwaLLNode *node);

/* remove an item from a specified list index */
void RwaLListRemoveIndex(RwaLLNode *head, RwUInt32 index);

/* find the index of the data in the linked list */
RwUInt32 RwaLListFindDataIndex(RwaLLNode *head, void *data);

/* get the data at a specified index in the linked list */
void* RwaLListFindDataByIndex(RwaLLNode *head, RwUInt32 index);

/* get the next node from a linked list */
RwaLLNode* RwaLListGetNext(RwaLLNode *node);

/* get the previous node from a linked list */
RwaLLNode* RwaLListGetPrevious(RwaLLNode *node);

/* initialize the linked list */
RwaLLNode* RwaLListInitialize(RwaLLNode *head);

/* empty a linked list */
void RwaLListEmpty(RwaLLNode *head);

/* get the size of the linked list */
RwUInt32 RwaLListGetCount(RwaLLNode *head);

/* get the end of the linked list */
RwaLLNode* RwaLListGetEnd(RwaLLNode *head);


#ifdef    __cplusplus
}
#endif /* __cplusplus */

#endif /* RWADOXYGEN */


/*--- Automatically derived from: d:/dev/rwa/source/core/src/rwawave.h ---*/

/******************************************************************************
 * Macros
 *****************************************************************************/
 
/* Metrics members for RwaWave */
#ifdef RWAMETRICS
    #define RWAWAVEMETRICS
#else
    #define RWAWAVEMETRICS
#endif

/* Metrics members for RwaWaveDef */
#ifdef RWAMETRICS
    #define RWAWAVEDEFMETRICS \
        RwUInt32 metricsNoInstances; /**<Number of instances of the wave definition*/
#else
    #define RWAWAVEDEFMETRICS
#endif

/******************************************************************************
 * Constants
 *****************************************************************************/


#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */

extern const RwaUUID rwaWAVE_NULL;
extern const RwaUUID rwaWAVEFORMAT_VAG;
extern const RwaUUID rwaWAVEFORMAT_PCM;
extern const RwaUUID rwaWAVEFORMAT_FLOAT;
extern const RwaUUID rwaWAVEFORMAT_DOLBY;
extern const RwaUUID rwaWAVEFORMAT_AC3;

extern const RwaUUID rwaWAVEDICT_WORK;

/******************************************************************************
 * Type Defintions
 *****************************************************************************/


/**
 * \ingroup rwawavefuncptr
 * Wave creation function
 *
 * \see RwaWaveDefSetCreateFunc
 */
typedef struct RwaWave* (*RwaWaveDefCreateFunc) (struct RwaWave *wave);

/**
 * \ingroup rwawavefuncptr
 * Wave destruction function
 *
 * \see RwaWaveDefSetDestroyFunc
 */
typedef void (*RwaWaveDefDestroyFunc) (struct RwaWave *wave);

/**
 * \ingroup rwawavefuncptr
 * This function uploads new data to 
 * a hardware audio device or external sample memory.
 *
 * \see RwaWaveDefSetUploadFunc
 */
typedef struct RwaWave* (*RwaWaveDefUploadFunc) 
    (struct RwaWave *wave, RwUInt32 offset, void *block, RwUInt32 blockLength);

/**
 * \ingroup rwawavefuncptr
 * This function downloads data from a hardware audio device or external 
 * sample memory.
 *
 * \see RwaWaveDefSetDownloadFunc
 */
typedef struct RwaWave* (*RwaWaveDefDownloadFunc)
    (struct RwaWave *wave, RwUInt32 offset, void *block, RwUInt32 blockLength);

/**
 * \ingroup rwawavefuncptr
 * This function returns if the uploading device is busy or not.
 *
 * \see RwaWaveDefSetUploadBusyFunc
 */
typedef RwBool (*RwaWaveDefUploadBusyFunc)  (void);

#ifdef    __cplusplus
}
#endif /* __cplusplus */


#if !defined(RWADOXYGENINTERNAL)
typedef struct RwaWaveDef RwaWaveDef;
/**
 * \ingroup rwawavedefinition
 * Wave definition.
 *
 * \see RwaWaveDefCreate
 */
struct RwaWaveDef
{
    RwaUniqueID              uniqueID;
    RwaWaveDefCreateFunc     createFunction;     /**<creates a wave */
    RwaWaveDefDestroyFunc    destroyFunction;    /**<destroys a wave */
    RwaWaveDefUploadFunc     uploadFunction;     /**<uploads a wave's data*/
    RwaWaveDefDownloadFunc   downloadFunction;   /**<downloads a wave's data */
    RwaWaveDefUploadBusyFunc uploadBusyFunction; /**<checks if upload is active or not*/
    RwLLLink                 link;               /**<link to other definitions*/
    RWAWAVEDEFMETRICS
};
#endif /* !defined(RWADOXYGENINTERNAL) */

typedef struct RwaWaveFormat RwaWaveFormat;
/**
 * \ingroup rwawaveinst
 * When creating a wave using \ref RwaWaveCreate , the format of the source 
 * audio data to be uploaded to the wave must be specified using this 
 * structure.<BR>
 * 
 * The data type member can be set to any of the following formats...<BR>
 * &\ref rwaWAVEFORMAT_VAG <BR>
 * &\ref rwaWAVEFORMAT_FLOAT <BR>
 * &\ref rwaWAVEFORMAT_PCM <BR>
 *
 * \note Some waves do not support uploads all of these formats.  Check the 
 * documentation relating to each specific wave.
 */
struct RwaWaveFormat
{
    RwUInt32      sampleRate;           /**<rate of the wave */
    const RwaUUID *dataType;            /**<data format*/
    RwUInt32      length;               /**<length of the data*/
    RwUInt32      lengthUncompressed;   /**<uncompressed length of data */
    RwUInt8       bitDepth;             /**<number of bits per sample*/
    RwUInt8       noChannels;           /**<number of channels*/
    RwUInt8       is3D;                 /**<specifies whether it is a 3d buffer or not*/
    RwUInt8       pad[1];               /**<pad for 32 bit alignment*/
};


#if !defined(RWADOXYGENINTERNAL)
typedef struct RwaWave RwaWave;
/**
 * \ingroup rwawaveinst
 * Wave
 * \see RwaWaveCreate
 */
struct RwaWave
{
    RwaUniqueID      uniqueID;       /**<Unique Identifier for the wave instance */
    RwaWaveDef       *waveDef;       /**<definition of this wave instance */
    RwaWaveFormat    format;         /**<format of the wave*/
    void             *data;          /**<pointer to raw data if it has any*/
    void             *state;         /**<state of the wave*/
    RwBool           packed;         /**<whether this wave is packed */
    RWAWAVEMETRICS
};
#else
typedef struct RwaWave RwaWave;
/**
 * \ingroup rwawaveinst
 * A wave instance structure which should be considered as an opaque type.
 * For more information see the section \ref waveinstancing "Wave Instancing".
 */
struct RwaWave
{
};
#endif /* !defined(RWADOXYGENINTERNAL) */

#if !defined(RWADOXYGENINTERNAL)
typedef struct RwaWaveDict RwaWaveDict;
/**
 * \ingroup rwawavedict
 * Wave dictionary
 * \see RwaWaveDictCreate
 */
struct RwaWaveDict
{
    RwaUniqueID uniqueID;     /**<unique ID for the dictionary */
    RwaLLNode   waveListHead; /**<list of waves */
    RwBool      packed;       /**<whether the dictionary is packed */
    RwLLLink    link;         /**<link to list wave dictionaries */
};
#else
typedef struct RwaWaveDict RwaWaveDict;
/**
 * \ingroup rwawaveinst
 * A wave dictionary structure which should be considered as an opaque type.
 * For more information see the section \ref wavedictionary "Wave Dictionaries".
 */
struct RwaWaveDict
{
};
#endif /* !defined(RWADOXYGENINTERNAL)


/******************************************************************************
 * Function Prototypes
 *****************************************************************************/

/* Do NOT remove this line or Doxygen will make a mess of the hyperlinking. */
#if !defined (RWADOXYGEN)

#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */

/*-----------------------------------------------------------------------------
 - Wave Definition Functions
 ----------------------------------------------------------------------------*/

/* Assign an ID to a wave defintion */
RwaWaveDef* RwaWaveDefAssignID(
    RwaWaveDef    *waveDef,
    const RwaUUID *uuid, 
    const RwChar  *name);

/* Copy an ID to a wave definition */
RwaWaveDef* RwaWaveDefSetID(
    RwaWaveDef    *waveDef, 
    const RwaUUID *uuid, 
    const RwChar  *name);

#ifdef RWAMETRICS
RwUInt32 RwaWaveDefMetricsGetWaves(RwaWaveDef *waveDef);
#endif /* RWAMETRICS */

/* create a wave definition */
RwaWaveDef* RwaWaveDefCreate( void );

/* destroy a wave definition */
void RwaWaveDefDestroy(RwaWaveDef *waveDef);

/* destroy a wave definition by UUID */
void RwaWaveDefDestroyByUUID(const RwaUUID *uuid);

/* find a wave definition by UUID */
RwaWaveDef* RwaWaveDefFindByUUID(const RwaUUID *uuid);

/* set the create function of a wave definition */
RwaWaveDef* RwaWaveDefSetCreateFunc(
    RwaWaveDef           *waveDef,
    RwaWaveDefCreateFunc createFunction);

/* set the destroy function of a wave definition */
RwaWaveDef* RwaWaveDefSetDestroyFunc(
    RwaWaveDef            *waveDef,
    RwaWaveDefDestroyFunc destroyFunction);

/* set the upload function of a wave definition */
RwaWaveDef* RwaWaveDefSetUploadFunc(
    RwaWaveDef           *waveDef,
    RwaWaveDefUploadFunc uploadFunction);

/* set the upload function of a wave definition */
RwaWaveDef* RwaWaveDefSetUploadBusyFunc(
    RwaWaveDef           *waveDef,
    RwaWaveDefUploadBusyFunc uploadBusyFunction);

/* set the download function of a wave definition */
RwaWaveDef* RwaWaveDefSetDownloadFunc(
    RwaWaveDef             *waveDef,
    RwaWaveDefDownloadFunc downloadFunction);

/*-----------------------------------------------------------------------------
 - Wave Functions
 ----------------------------------------------------------------------------*/

/* initialize the wave format */
RwaWaveFormat* RwaWaveFormatInitialize(RwaWaveFormat *waveFormat);

/* find a wave using its UUID */
RwaWave* RwaWaveFindByUUID(const RwaUUID *uuid);

/* assign an ID to a wave */
RwaWave* RwaWaveAssignID(
    RwaWave       *wave,
    const RwaUUID *uuid, 
    const RwChar  *name);

/* copy an ID to a wave */
RwaWave* RwaWaveSetID(
    RwaWave       *wave, 
    const RwaUUID *uuid, 
    const RwChar  *name);

/* create a wave */
RwaWave* RwaWaveCreate(
    RwaWaveFormat *format,
    RwaWaveDef    *waveDefinition);

/* create a wave using the definition's UUID */
RwaWave* RwaWaveCreateByUUID(
    RwaWaveFormat *format,
    const RwaUUID *waveDefUUID);

/* duplicate a wave */
RwaWave* RwaWaveCopy(RwaWave *sourceWave);

/* destroy a wave */
void RwaWaveDestroy( RwaWave *wave );

/* upload a wave */
RwaWave* RwaWaveUpload( 
    RwaWave  *wave,
    RwUInt32 offset,
    void     *block, 
    RwUInt32 blockLength);

/* download a wave */
RwaWave* RwaWaveDownload(
    RwaWave  *wave,
    RwUInt32 offset,
    void     *block,
    RwUInt32 blockLength);

/* get status of if the wave is busy uploading or not */
RwBool RwaWaveUploadBusy( RwaWave *wave );

/* get the wave's format */
void RwaWaveGetFormat ( RwaWave *wave, RwaWaveFormat *waveFormat );

/* write the wave object to a stream */
RwaWave* RwaWaveStreamWrite ( RwaWave *wave, RwStream *stream );

/* read a wave object from a stream */
RwaWave* RwaWaveStreamRead ( RwStream *stream);

/*-----------------------------------------------------------------------------
 - Wave Dictionary Functions
 ----------------------------------------------------------------------------*/

/* create a wave dictionary */
RwaWaveDict* RwaWaveDictCreate ( void );

/* destroy a wave dictionary */
void RwaWaveDictDestroy( RwaWaveDict *waveDict );

/* get a the wave dictionary by an index into the dictionaries list */
RwaWaveDict* RwaWaveDictFindByIndex ( RwUInt32 index );

/* get the number of wave dictionaries */
RwUInt32 RwaWaveDictGetCount ( void );

/* assign an ID to a wave dictionary */
RwaWaveDict* RwaWaveDictAssignID (
    RwaWaveDict   *waveDict, 
    const RwaUUID *uuid,
    const RwChar  *name);

/* copy an ID to a wave dictionary */
RwaWaveDict* RwaWaveDictSetID (
    RwaWaveDict   *waveDict, 
    const RwaUUID *uuid,
    const RwChar  *name);

/* Determine whether a wave definition is in use by any wave contained within
 * any wave dictionary */
RwaWaveDef* RwaWaveDictUsingAllWaveDef( RwaWaveDef *waveDef );

/* find a wave dictionary by name */
RwaWaveDict* RwaWaveDictFindByName(const RwChar *name);

/* find a wave dictionary by uuid */
RwaWaveDict* RwaWaveDictFindByUUID(const RwaUUID *uuid);

/* check a wave dictionary for a wave */
RwaWaveDict* RwaWaveDictContainsWave( RwaWaveDict *waveDict, RwaWave *wave );

/* search a wave dictionary for a wave using the wave's name */
RwaWave* RwaWaveDictFindWaveByName(RwaWaveDict *waveDict, const RwChar *name);

/* search a wave dictionary for a wave using the wave's UUID */
RwaWave* RwaWaveDictFindWaveByUUID(RwaWaveDict *waveDict, const RwaUUID *uuid);

/* search a wave dictionary for a wave at a particular index */
RwaWave* RwaWaveDictFindWaveByIndex(RwaWaveDict *waveDict, RwUInt32 index);

/* returns the number of waves within a wave dictionary */
RwUInt32 RwaWaveDictGetWaveCount(RwaWaveDict *waveDict);

/* add a wave to a wave dictionary */
RwaWaveDict* RwaWaveDictAddWave( RwaWaveDict *waveDict, RwaWave *wave );

/* remove a wave from a wave dictionary */
RwaWaveDict* RwaWaveDictRemoveWave( RwaWaveDict *waveDict, RwaWave *wave );

/* remove wave from all dictionaries */
void RwaWaveDictRemoveAllWave( RwaWave *wave );

/* get the working dictionary */
RwaWaveDict* RwaWaveDictGetWorking( void );

/* write a wave dictionary to a stream */
RwaWaveDict* RwaWaveDictStreamWrite( RwaWaveDict *waveDict, RwStream *stream );

/* read a wave dictionary from a stream */
RwaWaveDict* RwaWaveDictStreamRead( RwaWaveDict *waveDict, RwStream *stream );

#ifdef    __cplusplus
}
#endif /* __cplusplus */

#endif /* RWADOXYGEN */


/*--- Automatically derived from: d:/dev/rwa/source/core/src/rwaparam.h ---*/

/******************************************************************************
 * UUIDs of built in parameter types
 *****************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif
extern const RwaUUID rwaPARAMTYPE_UINT8;
extern const RwaUUID rwaPARAMTYPE_INT8;
extern const RwaUUID rwaPARAMTYPE_UINT16;
extern const RwaUUID rwaPARAMTYPE_INT16;
extern const RwaUUID rwaPARAMTYPE_UINT32;
extern const RwaUUID rwaPARAMTYPE_INT32;
extern const RwaUUID rwaPARAMTYPE_UINT64;
extern const RwaUUID rwaPARAMTYPE_INT64;
extern const RwaUUID rwaPARAMTYPE_REAL;
extern const RwaUUID rwaPARAMTYPE_RWV2D;
extern const RwaUUID rwaPARAMTYPE_RWV3D;
extern const RwaUUID rwaPARAMTYPE_RWBOOL;
extern const RwaUUID rwaPARAMTYPE_POINTER;
extern const RwaUUID rwaPARAMTYPE_RWMATRIX;
extern const RwaUUID rwaPARAMTYPE_RWAWAVE;
extern const RwaUUID rwaPARAMTYPE_RWAWAVEPTR;
#ifdef __cplusplus
}
#endif

/* build in parameter types aliases */
#define rwaPARAMTYPE_VOID rwaPARAMTYPE_POINTER
#define rwaPARAMTYPE_BOOL rwaPARAMTYPE_RWBOOL

/******************************************************************************
 * Type Defintions
 *****************************************************************************/

#if !defined(RWADOXYGENINTERNAL)
typedef struct RwaParamType RwaParamType;
/**
 * \ingroup rwaparam
 * Supports definition of a parameter type.
 */
struct RwaParamType
{
    RwaUniqueID  uniqueID;       /**<unique ID of the parameter type */
    void         *rangeMin;      /**<minimum value of parameter type */
    void         *rangeMax;      /**<maximum value of parameter type */
    RwaType      type;           /**<type of parameter type */
    RwaParamType *paramType; /**<parent of parameter type */
    RwLLLink     link;           /**<link to the symbol table */
};

typedef struct RwaParamTypeHandle RwaParamTypeHandle;
/**
 * \ingroup rwaparam
 * Handle to a parameter type
 */
struct RwaParamTypeHandle
{
    union
    {
        const RwaUUID *paramTypeUUID;
        RwaParamType  *paramType;
    } u;
    RwBool isUUID;
};

typedef struct _rwaParamTypeDef _rwaParamTypeDef;
/**
 * \ingroup rwaparam
 * Definition for a generating parameter types from a table
 */
struct _rwaParamTypeDef
{
    const RwChar   *name;
    RwaType        type;
    RwUInt32       size;
    void           *range;
    const RwaUUID  *typeUUID;
    const RwaUUID  *sourceTypeUUID;
};
#endif /* !defined(RWADOXYGENINTERNAL) */

/******************************************************************************
 * Function Prototypes
 *****************************************************************************/

/* Do NOT remove this line or Doxygen will make a mess of the hyperlinking. */
#if !defined (RWADOXYGEN)


#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */

/* atomic C type allocation & deallocation */
void* RwaAtomicAlloc ( RwaType type );
void  RwaAtomicFree  ( void *block, RwaType type );
    
/* returns the total size of a parameter type */
RwUInt32 RwaParamTypeGetSize(RwaParamType *paramType);

/* create an atomic parameter type */
RwaParamType* RwaParamTypeCreateAtomic(
    RwaType       type,
    const void    *rangeMin,
    const void    *rangeMax);

/* create an array parameter type */
RwaParamType* RwaParamTypeCreateArray(
    RwaType       type,
    RwaParamType  *arrayType,
    RwUInt32      size);

/* create a pointer type */
RwaParamType* RwaParamTypeCreatePointer(RwaParamType *arrayType);

/* create a parameter type alias using the source type's uuid */
RwaParamType* RwaParamTypeCreateAliasByUUID(
    const void    *rangeMin,
    const void    *rangeMax,
    RwaUUID       *sourceTypeUuid);

/* create a parameter type alias */
RwaParamType* RwaParamTypeCreateAlias(
    const void    *rangeMin,
    const void    *rangeMax,
    RwaParamType  *sourceType);

/* get the base type */
RwaType RwaParamTypeGetAtomic( const RwaParamType *paramType );

/* get the size of an array */
RwUInt32 RwaParamTypeGetArraySize( const RwaParamType *paramType );

/* get the total size of param type (the abstract type not the structure) */
RwUInt32 RwaParamTypeGetTypeSize( const RwaParamType *paramType );

/* destroy a parameter */
void RwaParamTypeDestroy(
    RwaParamType *paramType, 
    RwBool       recursive);

/* set the parameter's uuid */
RwaParamType* RwaParamTypeSetUUID(
    RwaParamType  *paramType,
    const RwaUUID *uuid);

/* assign the parameter's uuid */
RwaParamType* RwaParamTypeAssignUUID(
    RwaParamType  *paramType,
    const RwaUUID *uuid);

/* set the parameter's name */
RwaParamType* RwaParamTypeSetName(
    RwaParamType *paramType,
    const RwChar *uuid);

/* assign the parameter's name */
RwaParamType* RwaParamTypeAssignName(
    RwaParamType *paramType,
    const RwChar *uuid);

/* destroy a parameter using its name */
void RwaParamTypeDestroyByName(
    const RwChar *name, 
    RwBool       recursive);

/* destroy a parameter using its UUID */
void RwaParamTypeDestroyByUUID(
    const RwaUUID *uuid, 
    RwBool        recursive);

/* get a parameter type using it's name */
RwaParamType* RwaParamTypeFindByName( const RwChar *name);

/* get a parameter type using it's UUID */
RwaParamType* RwaParamTypeFindByUUID( const RwaUUID *uuid);

/* create a set of parameter types using a table of parameter type 
   definition structures */
_rwaParamTypeDef* _rwaParamTypeCreateByTypeDefs(
    _rwaParamTypeDef *paramTypeDefs,
    RwUInt32         noParamTypeDefs);

/*-----------------------------------------------------------------------------
 - Function aliases enabling some compile time type checking
 ----------------------------------------------------------------------------*/

/* create an UINT8 parameter type */
RwaParamType* RwaParamTypeCreateUInt8(
    const RwaUUID *uuid,
    const RwChar  *name,
    RwUInt8       rangeMin,
    RwUInt8       rangeMax);

/* create an INT8 parameter type */
RwaParamType* RwaParamTypeCreateInt8(
    const RwaUUID *uuid,
    const RwChar  *name,
    RwInt8        rangeMin,
    RwInt8        rangeMax);

/* create an UINT16 parameter type */
RwaParamType* RwaParamTypeCreateUInt16(
    const RwaUUID *uuid,
    const RwChar  *name,
    RwUInt16      rangeMin,
    RwUInt16      rangeMax);

/* create an INT16 parameter type */
RwaParamType* RwaParamTypeCreateInt16(
    const RwaUUID *uuid,
    const RwChar *name,
    RwInt16      rangeMin,
    RwInt16      rangeMax);

/* create an UINT32 parameter type */
RwaParamType* RwaParamTypeCreateUInt32(
    const RwaUUID *uuid,
    const RwChar  *name,
    RwUInt32      rangeMin,
    RwUInt32      rangeMax);

/* create an INT32 parameter type */
RwaParamType* RwaParamTypeCreateInt32(
    const RwaUUID *uuid,
    const RwChar  *name,
    RwInt32       rangeMin,
    RwInt32       rangeMax);

/* create an UINT64 parameter type */
RwaParamType* RwaParamTypeCreateUInt64(
    const RwaUUID *uuid,
    const RwChar  *name,
    RwUInt64      rangeMin,
    RwUInt64      rangeMax);

/* create an INT64 parameter type */
RwaParamType* RwaParamTypeCreateInt64(
    const RwaUUID *uuid,
    const RwChar  *name,
    RwInt64       rangeMin,
    RwInt64       rangeMax);

/* create an UINT128 parameter type */
RwaParamType* RwaParamTypeCreateUInt128(
    const RwaUUID *uuid,
    const RwChar  *name,
    RwUInt128     rangeMin,
    RwUInt128     rangeMax);

/* create an INT128 parameter type */
RwaParamType* RwaParamTypeCreateInt128(
    const RwaUUID *uuid,
    const RwChar  *name,
    RwInt128      rangeMin,
    RwInt128      rangeMax);

/* create an FLOAT parameter type */
RwaParamType* RwaParamTypeCreateReal(
    const RwaUUID *uuid,
    const RwChar  *name,
    RwReal        rangeMin,
    RwReal        rangeMax);

#ifdef    __cplusplus
}
#endif /* __cplusplus */


#endif /* RWADOXYGEN */


/*--- Automatically derived from: d:/dev/rwa/source/core/src/rwasymboltable.h ---*/
/******************************************************************************
 * Type Defintions
 *****************************************************************************/
#if !defined(RWADOXYGENINTERNAL)
typedef struct RwaSymbolTable RwaSymbolTable;
/**
 * \ingroup rwasymboltable 
 * Symbol table type
 */
struct RwaSymbolTable
{
    RwInt32          noParamTypes; /**<number of parameter types in symbol table */
    RwLinkList       list;             /**<list of parameter types */
};
#endif /* !defined(RWADOXYGENINTERNAL) */

/******************************************************************************
 * Function Prototypes
 *****************************************************************************/

/* Do NOT remove this line or Doxygen will make a mess of the hyperlinking. */
#if !defined (RWADOXYGEN)


#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */

/* initialise a symbol table */
void _rwaSymbolTableInit    ( RwaSymbolTable *symbolTable );

/* destroy a symbol table */
void _rwaSymbolTableDestroy ( RwaSymbolTable *symbolTable );

/* add a parameter type to the symbol table */
RwaSymbolTable* _rwaSymbolTableAddParamType ( 
    RwaSymbolTable *symbolTable, 
    RwaParamType   *parameterType);

/* remove a parameter type from the symbol table */
RwaSymbolTable* _rwaSymbolTableRemoveParamType( 
    RwaSymbolTable *symbolTable, 
    RwaParamType   *parameterType);

/* find a parameter type in the symbol table using its UUID */
RwaParamType* _rwaSymbolTableFindParamTypeByUUID(
    RwaSymbolTable *symbolTable,
    const RwaUUID  *uuid);

/* get a parameter Type from the symbol table using its name */
RwaParamType* _rwaSymbolTableFindParamTypeByName(
    RwaSymbolTable *symbolTable,
    const RwChar   *name);

/* get the first parameter type from 
   the symbol table which is dependant on the passed parameter */
RwaParamType* _rwaSymbolTableFindParamTypeFirstDepend(
    RwaSymbolTable *symbolTable,
    RwaParamType   *parentParamType);

/* get the an indexed parameter type from the symbol table */
RwaParamType* _rwaSymbolTableFindParamTypeByIndex(
    RwaSymbolTable *symbolTable,
    RwUInt32       parameterIndex);

#ifdef    __cplusplus
}
#endif /* __cplusplus */

#endif /* RWADOXYGEN */


/*--- Automatically derived from: d:/dev/rwa/source/core/src/rwaparamqueue.h ---*/
#if !defined(RWADOXYGENINTERNAL)
typedef struct RwaEvent RwaEvent;
/**
 * \ingroup rwaparameterqueue
 * event
 */
struct RwaEvent
{
    void     *eventData; /**<event data */
    RwUInt32 timeStamp;  /**<time stamp for this event*/
    RwBool   used;       /**<TRUE when used */
};

typedef struct RwaParamQueue RwaParamQueue;
/**
 * \ingroup rwaparameterqueue
 * parameter queue
 */
struct RwaParamQueue
{
    RwUInt32      size;           /**<size of the parameter queue */
    RwaEvent      *queue;         /**<the queue data*/
    RwUInt32      writePosition;  /**<write position of the queue */
    RwUInt32      readPosition;   /**<read position of the queue */
    RwUInt32      eventDataSize;  /**<quick ref size of the event data */
    RwaParamType  *eventDataType; /**<data type of the event data */
};
#endif /* !defined(RWADOXYGENINTERNAL) */

/*--- Automatically derived from: d:/dev/rwa/source/core/src/rwaobjinterfacetypes.h ---*/
#if !defined(RWADOXYGENINTERNAL)
typedef struct RwaObjInterfaceDef RwaObjInterfaceDef;
/**
 * \ingroup rwaobjinterfacedef
 * Defines an object's interface
 */
struct RwaObjInterfaceDef
{
    RwaUniqueID uniqueID;        /**<Unique ID for this object interface*/
    RwUInt32    noInputParams;   /**<Number of inputs within this interface*/
    RwaUniqueID *inputParamIDs;  /**<Array of inputs within this interface*/
    RwUInt32    noOutputParams;  /**<Number of outputs within this interface*/
    RwaUniqueID *outputParamIDs; /**<Array of outputs within this interface*/
    RwBool      freeListAlloc;   /**<TRUE if this was allocated from a free list */
    RwLLLink    link;            /**<link within list of object interfaces */
};
#endif /* !defined(RWADOXYGENINTERNAL) */


/*--- Automatically derived from: d:/dev/rwa/source/core/src/rwaobjdef.h ---*/

/* Metrics members for RwaObjDef */
#if defined(RWAMETRICS) && !defined(RWADOXYGENINTERNAL)

typedef struct RwaObjDefMetrics RwaObjDefMetrics;
/**
 * \ingroup rwaobjectdef
 * Metrics information for an object definition.
 */
struct RwaObjDefMetrics
{
    RwUInt32 memoryUsage;              /**<Memory usage of this object definition */
    RwUInt32 instanceUpdateStartTime;  /**<CPU time taken by all instances of this 
                                           object definition to run the object's
                                           start execute function*/
    RwUInt32 instanceUpdateFinishTime; /**<CPU time taken by all instances of this 
                                           object definition to run the object's
                                           finish execute function*/
    RwUInt32 instanceExternalStartTime; /**<CPU time taken by all instances of this 
                                           object definition to call the object's
                                           external functions during a start update */
    RwUInt32 instanceExternalFinishTime;/**<CPU time taken by all instances of this 
                                           object definition to call the object's
                                           external functions during a finish update */
    RwUInt32 instanceMemoryUsage;      /**<Memory usage of all instances of this
                                           object definition */
    RwUInt32 numInstances;             /**<Number of instances of this definition */
};


#define RWAOBJDEFMETRICS(_x) RwaObjDefMetrics _x ;
#else
#define RWAOBJDEFMETRICS(_x)
#endif /* defined(RWAMETRICS) && !defined(RWADOXYGENINTERNAL) */

/* set the maximum number of instances for this object definition */
#define RwaObjDefSetMaxInstances(_objDef, _maxNoInstances) \
    (_objDef)->maxInstances = _maxNoInstances

/* get the maximum number of instances for this object definition */
#define RwaObjDefGetMaxInstances(_objDef) \
    (_objDef)->maxInstances

/* set the size of an object's state */
#define RwaObjDefSetStateSize(_objDef, _stateSize) \
    (_objDef)->stateSize  = _stateSize; 

/* set the alignment of an object's state */
#define RwaObjDefSetStateAlignment(_objDef, _alignment) \
    (_objDef)->stateAlign = _alignment

/* get the size of an object's state */
#define RwaObjDefGetStateSize(_objDef) \
    (_objDef)->stateSize

/* get the alignment of an object's state */
#define RwaObjDefGetStateAlignment(_objDef) \
    (_objDef)->stateAlign

/* get the number of inputs on an object definition */
#define RwaObjDefGetNoInputs(_objDef) \
    (_objDef)->noInputs

/* get the number of outputs on an object definition */
#define RwaObjDefGetNoOutputs(_objDef) \
    (_objDef)->noOutputs

/******************************************************************************
 * Type Defintions
 *****************************************************************************/

#if !defined(RWADOXYGENINTERNAL)
/**
 * \ingroup rwaobjtypes
 * Selects either the input or output parameter set on an audio object
 */
enum RwaIOParam
{
    rwaNAIOPARAM = 0,
    rwaIOPARAM_INPUT,  /**<selects the an AudioObject's input parameters */
    rwaIOPARAM_OUTPUT, /**<selects the an AudioObject's output parameters */
    rwaIOPARAM_FORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RwaIOParam RwaIOParam;


/**
 * \ingroup rwaobjectdef
 * AudioObject creator function.
 */
typedef struct RwaObj* (*RwaObjCreateFunc) 
    (struct RwaObj *object, void *creationParams);

/**
 * \ingroup rwaobjectdef
 * AudioObject execution function.
 */
typedef struct RwaObj* (*RwaObjExecuteFunc) (struct RwaObj *obj);

/**
 * \ingroup rwaobjectdef
 * AudioObject destructor function.
 */
typedef void (*RwaObjDestroyFunc) (struct RwaObj *obj);

/**
 * \ingroup rwaobjectdef
 * AudioObject signal function. 
 * This function is a generic message passing function between AudioObjects.
 */
typedef struct RwaObj* (*RwaObjSignalFunc)
    (struct RwaObj *obj, void *signalParams);

/** 
 * \ingroup rwaobjectdef
 * AudioObject property setting / retrieval function.
 * If the object has set this function pointer for an input or output, this
 * function is called when either \ref RwaObjGetParamData or 
 * \ref RwaObjSetParamData are called.
 */
typedef struct RwaObj* (*RwaObjParamFunc) 
    (struct RwaObj *obj, RwUInt32 paramIndex, void *data);

/** 
 * \ingroup rwaobjectdef
 * AudioObject get creation parameters function.
 * This function is called by the core when serializing an object.  The object
 * should return a pointer to the set of creation parameters used to create
 * the object and the size of the creation parameters.
 */
typedef struct RwaObj* (*RwaObjGetCreationParamsFunc)
    (struct RwaObj *obj, void **creationParams, RwUInt32 *size);


/**
 * \ingroup rwaobjectdef
 * AudioObject unregister function.  This function is called when an 
 * object is unregistered when the core is closing.
 */
typedef struct RwaObjDef* (*RwaObjDefUnregisterFunc)(struct RwaObjDef *objDef);


typedef struct RwaDefaultValue RwaDefaultValue;
/**
 * \ingroup rwaobjectdef
 * Default value
 */
struct RwaDefaultValue
{
    void   *value; /**<pointer to the default value of the parameter */
    RwBool copied; /**<whether the value was allocated by the object */
};


typedef struct RwaInputParamDef RwaInputParamDef;
/**
 * \ingroup rwaobjectdef
 * Input parameter definition for an audio object definition
 */
struct RwaInputParamDef
{
    RwaUniqueID        uniqueID;         /**<unique ID for the input parameter */
    RwaParamTypeHandle paramHandle;      /**<handle to a parameter type */
    RwaDefaultValue    defaultValue;     /**<default value for the input 
                                             parameter*/
    RwUInt32           defaultQueueSize; /**<default queue size of the input 
                                             parameter */
    RwaObjParamFunc    getFunc;          /**<parameter get function */
    RwaObjParamFunc    setFunc;          /**<parameter set function */
    RwBool             copy;             /**<TRUE if the audio object requires 
                                             a copy of the parameter */
};


typedef struct RwaOutputParamDef RwaOutputParamDef;
/**
 * \ingroup rwaobjectdef
 * Output parameter definition for an audio object definition
 */
struct RwaOutputParamDef
{
    RwaUniqueID        uniqueID;         /**<unique ID for the output parameter */
    RwaParamTypeHandle paramHandle;      /**<handle to a parameter type */
    RwaDefaultValue    defaultValue;     /**<default value for the output 
                                          parameter */
    RwUInt32           defaultQueueSize; /**<default queue size of the output 
                                          parameter */
    RwaObjParamFunc    getFunc;          /**<parameter get function */
    RwaObjParamFunc    setFunc;          /**<parameter set function */
};


/**
 * \ingroup rwaobjectdef 
 * \def rwaOBJDEFFLAGS_STATICOUTPUTS
 * Flag for the flags member of \ref RwaObjDef
 */
#define rwaOBJDEFFLAGS_STATICOUTPUTS 0x1

/**
 * \ingroup rwaobjectdef 
 * \def rwaOBJDEFFLAGS_STATICINPUTS
 * Flag for the flags member of \ref RwaObjDef
 */
#define rwaOBJDEFFLAGS_STATICINPUTS  0x2

/**
 * \ingroup rwaobjectdef
 * \def rwaOBJDEFFLAGS_CLOCKMASTER
 * Flag for the flags member of \ref RwaObjDef
 */
#define rwaOBJDEFFLAGS_CLOCKMASTER  0x4


typedef struct RwaObjDef RwaObjDef;
/**
 * \ingroup rwaobjectdef
 * AudioObject definition.
 */
struct RwaObjDef
{
    RwaUniqueID        uniqueID;             /**<ID of the definition */
    RwUInt32           maxInstances;         /**<maximum number of instances 
                                                 of this object*/
    RwaObjInterfaceDef *defaultInterface;    /**<This object's default 
                                                 interface*/
    RwaLLNode          subObjects;           /**<sub-objects list within this 
                                                 object */
    RwLinkList         subObjectConns;      /**<connections list between sub 
                                                objects */
    RwLinkList         instances;           /**<list of instances of this 
                                                object definition*/
    RwUInt32           noInputs;            /**<number of inputs to this 
                                                object */
    RwaInputParamDef   *inputParams;        /**<input parameters */
    RwUInt32           noOutputs;           /**<number of outputs from this 
                                                object */
    RwaOutputParamDef  *outputParams;       /**<output parameters */
    RwUInt32           noSignals;           /**<number of signals this object 
                                                calls*/
    RwLinkList         aliasList;           /**<list of aliases for this object 
                                                definition */

    /* audio objects this object broadcasts data to */
    RwaObjSignalFunc  *signalFunctions;     /**<pointers to signal functions*/
    struct RwaObjDef  **signalObjects;      /**<objects this object calls*/

    RwaObjCreateFunc  createFunction;       /**<create object function */
    RwaObjExecuteFunc startExecuteFunction; /**<start execute object function*/
    RwaObjExecuteFunc finishExecuteFunction;/**<finish execute object function*/
    RwaObjExecuteFunc interruptFunction;    /**<interrupt object function */
    RwaObjDestroyFunc destroyFunction;      /**<destroy object function */
    RwaObjSignalFunc  signalFunction;       /**<signal object function */
    
    RwaObjGetCreationParamsFunc getCreationParamsFunction;
        /**<Should be implemented by the object to return it's creation parameters */

    RwaObjDefUnregisterFunc     unregisterFunction; 
        /**Called when object definition is destroyed */

    RwLinkList        interfaceList;        /**<list of interfaces for this object */
    RwaFreeList       *instanceFreeList;    /**<free list to create instances from */
    RwUInt32          stateSize;            /**<size of the object's state */
    RwUInt32          stateAlign;           /**<alignment of the object's state */
    RwaLLNode         dependencyList;       /**<list of definitions this 
                                                definition is dependent upon */
    RwaLLNode         dependList;           /**<list of dependent definitions */
    RwUInt32          flags;           
        /**<Flags for the object definition.
            The following bits can be set...
            <UL>
                <LI>rwaOBJDEFFLAGS_CLOCKMASTER - 
                    This object is a clock master therefore it has it's own
                    execution list.</LI>
                <LI>rwaOBJDEFFLAGS_STATICOUTPUTS - 
                     Outputs for this object where statically allocated,</LI>
                <LI>rwaOBJDEFFLAGS_STATICINPUTS< -
                     Inputs for this object where statically allocated./LI>
            </UL>*/
    RwaLLNode       associatedObjs;         /**<objects associated with this one */
    RwaLLNode       associatedWaves;        /**<waves associated with this one */
    RWAOBJDEFMETRICS(metrics)               /**<metrics information for the object 
                                                definition*/
};


typedef struct RwaSubObjDefConn RwaSubObjDefConn;
/**
 * \ingroup rwaobjectdef
 * subObject definition connection.
 */
struct RwaSubObjDefConn
{
    RwUInt32       sourceObjDefIndex;         /**<index of the source object 
                                            definition in sub models list */
    const RwaUUID  *sourceParameterUUID;      /**<UUID of the source parameter */
    RwUInt32       destinationObjDefIndex;    /**<index of the destination object 
                                                  definition in sub models list */
    const RwaUUID  *destinationParameterUUID; /**<UUID of the destination parameter*/
    RwLLLink       link;                      /**<link in the connection list */
};
#endif /* !defined(RWADOXYGENINTERNAL) */

#if !defined(RWADOXYGEN)

/*-----------------------------------------------------------------------------
 - Object Definition Functions
 ----------------------------------------------------------------------------*/

#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */

/* create an audio object definition */
RwaObjDef* RwaObjDefCreate(
    RwUInt32 noInputs, 
    RwUInt32 noOutputs, 
    RwUInt32 noSignals);

/* set an audio object's default interface */
RwaObjDef* RwaObjDefSetInterface(
    RwaObjDef          *objDef,
    RwaObjInterfaceDef *objInterfaceDef);

/* set an audio object's default interface by UUID*/
RwaObjDef* RwaObjDefSetInterfaceByUUID(RwaObjDef *objDef, const RwaUUID *uuid);

/* set whether this object is a clock master */
RwaObjDef* RwaObjDefSetClockMaster(RwaObjDef *objDef, RwBool clockMaster);

/* make one object definition dependent upon another object definition */
RwaObjDef* RwaObjDefAddDependency(RwaObjDef *objDef, RwaObjDef *dependentObjDef);

/* remove all dependencies from an object definition */
RwaObjDef* RwaObjDefRemoveDependency(RwaObjDef *objDef);

/* setup an object definitions inputs and outputs from static data arrays */
RwaObjDef* _rwaObjDefSetupParams(
    RwaObjDef         *objDef,
    RwaInputParamDef  *inputParamDefs,
    RwUInt32          noInputs,
    RwaOutputParamDef *outputParamDefs,
    RwUInt32          noOutputs);

/* create a copy of an audio object definition */
RwaObjDef* RwaObjDefCopy( RwaObjDef *sourceObjDef);

/* destroy an audio object definition */
void RwaObjDefDestroy( RwaObjDef *objDef );

/* assign an ID to an audio object definition */
RwaObjDef* RwaObjDefAssignID(
    RwaObjDef     *objDef,
    const RwaUUID *uuid,
    const RwChar  *textID);

/* copy the ID to an audio object definition */
RwaObjDef* RwaObjDefSetID(
    RwaObjDef     *objDef,
    const RwaUUID *uuid,
    const RwChar  *textID);

/* get the number of associated object definitions */
RwUInt32 RwaObjDefGetAssociatedObjDefCount(RwaObjDef *objDef);

/* get the associated object definitions */
RwUInt32 RwaObjDefGetAssociatedObjDefs(
    RwaObjDef *objDef, 
    RwaObjDef **associatedObjDefs,
    RwUInt32  noAssociatedObjDefs);

/* get the number of associated wave definitions */
RwUInt32 RwaObjDefGetAssociatedWaveDefCount(RwaObjDef *objDef);

/* get the associated wave definitions */
RwUInt32 RwaObjDefGetAssociatedWaveDefs(
    RwaObjDef  *objDef, 
    RwaWaveDef **associatedWaveDefs,
    RwUInt32   noAssociatedWaveDefs);

/* add an associated object definition UUID to this definition */
RwaObjDef* RwaObjDefAddAssociatedObjDef(
    RwaObjDef *objDef, 
    RwaUUID   *associatedObjDefUUID);

/* remove an associated object definition UUID from this definition */
RwaObjDef* RwaObjDefRemoveAssociatedObjDef(
    RwaObjDef *objDef,
    RwaUUID   *associatedObjDefUUID);

/* add an associated wave definition UUID to this definition */
RwaObjDef* RwaObjDefAddAssociatedWaveDef(
    RwaObjDef *objDef,
    RwaUUID   *associatedWaveDefUUID);

/* remove an associated wave definition UUID from this definition */
RwaObjDef* RwaObjDefRemoveAssociatedWaveDef(
    RwaObjDef *objDef,
    RwaUUID   *associatedWaveDefUUID);

/* set up the start execute function */
RwaObjDef* RwaObjDefSetStartExecuteFunc(
    RwaObjDef         *objDef,
    RwaObjExecuteFunc executeFunction);

/* set up the finish execute function */
RwaObjDef* RwaObjDefSetFinishExecuteFunc(
    RwaObjDef         *objDef,
    RwaObjExecuteFunc executeFunction);

/* set up the create function */
RwaObjDef* RwaObjDefSetCreateFunc(
    RwaObjDef        *objDef,
    RwaObjCreateFunc createFunction);

/* set up the destroy function */
RwaObjDef* RwaObjDefSetDestroyFunc(
    RwaObjDef         *objDef,
    RwaObjDestroyFunc destroyFunction);

/* set up this object's signal function */
RwaObjDef* RwaObjDefSetRecieveSignalFunc(
    RwaObjDef        *objDef,
    RwaObjSignalFunc signalFunction);

/* set up the object's this object signals */
RwaObjDef* RwaObjDefSetTransmitSignalFunc(
    RwaObjDef *objDef,
    RwaObjDef *signalObjDef,
    RwUInt32  signalIndex);

/* set up the object's get creation parameters function */
RwaObjDef* RwaObjDefSetCreateParamsFunc(
    RwaObjDef                   *objDef,
    RwaObjGetCreationParamsFunc creationParamsFunction );

/* set up the object's unregister function */
RwaObjDef* RwaObjDefSetUnregisterFunc(
    RwaObjDef               *objDef,
    RwaObjDefUnregisterFunc unregisterFunction);

#ifdef RWAMETRICS 
/* get the metrics information from an object definition */
RwaObjDefMetrics* RwaObjDefGetMetrics( RwaObjDef *objDef );

#endif /* RWAMETRICS */

/*-Parameter Functions-------------------------------------------------------*/
/* set a parameter's attributes */
RwaObjDef* RwaObjDefSetParam(
    RwaObjDef     *objDef,
    RwUInt32      paramIndex,
    RwaIOParam    inputOutput,
    const RwaUUID *parameterUUID,
    const RwChar  *parameterName,
    const RwaUUID *parameterTypeUUID,
    void          *defaultValue,
    RwUInt32      queueSize);

/* assign a parameter's attributes */
RwaObjDef* RwaObjDefAssignParam(
    RwaObjDef     *objDef,
    RwUInt32      paramIndex,
    RwaIOParam    inputOutput,
    const RwaUUID *parameterUUID,
    const RwChar  *parameterName,
    const RwaUUID *parameterTypeUUID,
    void          *defaultValue,
    RwUInt32      queueSize);

/* set a parameter's type */
RwaObjDef* RwaObjDefSetParamType(
    RwaObjDef    *objDef,
    RwUInt32     paramIndex,
    RwaIOParam   inputOutput,
    RwaParamType *paramType,
    void         *defaultValue,
    RwUInt32     queueSize);

/* assign a parameter's type */
RwaObjDef* RwaObjDefAssignParamType(
    RwaObjDef    *objDef,
    RwUInt32     paramIndex,
    RwaIOParam   inputOutput,
    RwaParamType *paramType,
    void         *defaultValue,
    RwUInt32     queueSize);

/* get a parameter's type */
RwaParamType* RwaObjDefGetParamType(
    RwaObjDef  *objDef,
    RwUInt32   paramIndex,
    RwaIOParam inputOutput);

/* set an input parameter's set function */
RwaObjDef* RwaObjDefSetParamSetFunc(
    RwaObjDef       *objDef,
    RwUInt32        paramIndex,
    RwaObjParamFunc function);

/* set a parameter's get function */
RwaObjDef* RwaObjDefSetParamGetFunc(
    RwaObjDef       *objDef,
    RwUInt32        paramIndex,
    RwaIOParam      inputOutput,
    RwaObjParamFunc function);

/* copy to a parameter's ID */
RwaObjDef* RwaObjDefSetParamID(
    RwaObjDef     *objDef,
    RwUInt32      paramIndex,
    RwaIOParam    inputOutput,
    const RwaUUID *uuid,
    const RwChar  *parameterName);

/* assign a parameter's ID */
RwaObjDef* RwaObjDefAssignParamID(
    RwaObjDef     *objDef,
    RwUInt32      paramIndex,
    RwaIOParam    inputOutput,
    const RwaUUID *uuid,
    const RwChar  *parameterName);

/* get a parameter's ID using a parameter index */
RwaObjDef *RwaObjDefGetParamID(
    RwaObjDef   *objDef,
    RwUInt32    paramIndex,
    RwaIOParam  inputOutput,
    RwaUniqueID *uniqueID);

/* get a parameter's index using a text ID */
RwUInt32 RwaObjDefParamNameGetIndex(
    RwaObjDef    *objDef,
    RwaIOParam   inputOutput,
    const RwChar *textID);

/* get a parameter's index using a uuid */
RwUInt32 RwaObjDefParamUUIDGetIndex(
    RwaObjDef     *objDef,
    RwaIOParam    inputOutput,
    const RwaUUID *uuid);

/* determine whether the object definition is using a parameter type */
RwaObjDef* RwaObjDefUsingParamType(
    RwaObjDef    *objDef,
    RwaParamType *paramType);

/* add a parameter to the definition */
RwaObjDef* RwaObjDefAddParam(RwaObjDef *objDef, RwaIOParam inputOutput);

/* insert a parameter onto the definition */
RwaObjDef* RwaObjDefInsertParam(
    RwaObjDef     *objDef,
    RwUInt32      paramIndex,
    RwaIOParam    inputOutput);

/* remove a parameter from the definition */
RwaObjDef* RwaObjDefRemoveParam(
    RwaObjDef  *objDef,
    RwUInt32   paramIndex,
    RwaIOParam inputOutput);

#ifdef    __cplusplus
}
#endif /* __cplusplus */

#endif /* !defined(RWADOXYGEN) */


/*--- Automatically derived from: d:/dev/rwa/source/core/src/rwaobj.h ---*/

/* Metrics members for RwaObj */
#if defined(RWAMETRICS) || defined(RWADOXYGEN)

typedef struct RwaObjMetrics RwaObjMetrics;
/**
 * \ingroup rwaobject
 * Low-level AudioObject (Obj) metrics information
 *
 * \note This metrics information is only available in METRICS builds.
 * METRICS builds require metrics libraries for RenderWare Audio to be used and 
 * RWAMETRICS to be defined by the application.
 * For more information about build types see the section on 
 * \ref buildtypes "RenderWare Audio Build Types".
 */
struct RwaObjMetrics
{
    RwUInt32 updateStartTime;   /**<CPU time taken by start execute function*/
    RwUInt32 updateFinishTime;  /**<CPU time taken by finish execute function */
    RwUInt32 externalStartTime; /**<This is Optionally set by object and is the
                                    CPU time taken to execute external functions 
                                    in the start execute function*/
    RwUInt32 externalFinishTime;/**<This is Optionally set by object and is the
                                    CPU time taken to execute external functions 
                                    in the finish execute function*/
    RwUInt32 objectMemoryUsage; /**<Memory usage of the object*/
    RwUInt32 stateMemoryUsage;  /**<Size of the object's state */
};

#define RWAOBJMETRICS(_x) RwaObjMetrics _x ;
#else
#define RWAOBJMETRICS(_x)
#endif /* defined(RWAMETRICS) || defined(RWADOXYGEN) */

/* get the definition of an object */
#define RwaObjGetObjDef(_obj) (_obj)->definition

/* get the parent object of an object */
#define RwaObjGetParentObj(_obj) (_obj)->parentObject

/* set the active flag of an object */
#define RwaObjSetActive(_obj, _flag) (_obj)->active = _flag

/* get the active flag of an object */
#define RwaObjGetActive(_obj) (_obj)->active

#ifdef RWAMETRICS

/* set / get the external update time for an object */
#define RwaObjSetExternalStartTime(_obj, _val) \
    (_obj)->metrics.externalStartTime = _val
#define RwaObjGetExternalStartTime(_obj) (_obj)->metrics.externalStartTime

#define RwaObjSetExternalFinishTime(_obj, _val) \
    (_obj)->metrics.externalFinishTime = _val

#define RwaObjGetExternalFinishTime(_obj) (_obj)->metrics.externalFinishTime
#endif /*RWAMETRICS */

/******************************************************************************
 * Type Defintions
 *****************************************************************************/

#if !defined(RWADOXYGENINTERNAL)

typedef struct RwaObjConn RwaObjConn;
/**
 * \ingroup rwaobjectinst
 * Connection between two object instances
 */
struct RwaObjConn
{
    struct RwaObj   *srcObj;   /**<source object for the connection*/
    RwUInt32        srcIndex;  /**<index of output parameter on src object */
    RwaObjParamFunc getFunc;   /**<get function on the source object */
    struct RwaObj   *destObj;  /**<destination object for the connection */
    RwUInt32        destIndex; /**<index of input parameter on dest object */
    RwaObjParamFunc setFunc;   /**<set function on destination object */
    RwaParamQueue   *queue;    /**<queue used between objects */
    RwLLLink        srcLink;   /**<link in list of connections on the source object */
    RwLLLink        destLink;  /**<link in list of connections on the destination object */
};

typedef struct RwaParam RwaParam;
/**
 * \ingroup rwaobjectinst
 * Parameter for an object instance
 */
struct RwaParam
{
    RwUInt16        noConnections; /**<number of connections from this parameter */
    RwUInt16        connIndex;     /**<selected connection's index */
    RwLLLink        *connLink;     /**<currently selected connection */
    RwLinkList      conns;         /**<list of connections */
    RwaParamQueue   *queue;        /**<pointer to queue */
    RwaObjParamFunc setFunc;       /**<set parameter function */
    RwaObjParamFunc getFunc;       /**<get parameter function */
};


typedef struct RwaObj RwaObj;
/**
 * \ingroup rwaobjectinst
 * Represents an AudioObject instance
 */
struct RwaObj
{
    struct RwaObjDef *definition;    /**<definition of instance */
    RwUInt32         subObjectIndex; /**<index of this object's 
                                         definition in the parent 
                                         definition's subobjects list */
    struct RwaObj    *parentObject;  /**<container object of this 
                                         object */
    RwLinkList       subObjList;     /**<list of sub objects */
    RwLLLink         subObjLink;     /**<link to list of sub objects */
    RwLLLink         instanceLink;   /**<link in list of instances for 
                                         this object's definition */
    RwaParam         *inputParams;   /**<input parameters*/
    RwaParam         *outputParams;  /**<output parameters*/
    struct RwaObj    *nextObject;    /**<next object in execution list */
    void             *state;         /**<state data */
    RwUInt32         routeDepth;     /**<depth within the network route */
    RwLLLink         routeDepthLink; /**<link in the route depth list */
    RwLLLink         link;           /**<link to global instance list */
    RwaLLNode        dependantObjs;  /**<list of dependant objects */
    RwaLLNode        depUponObjs;    /**<list of objects this object is 
                                         dependant on */
    RwLinkList       interfaceList;  /**<list of interfaces to this object */
    RwUInt32         refCount;       /**<number of RwaObject references 
                                         to this obj. */
    RwBool           active;         /**<whether the object is active and 
                                         should be executed */
    RWAOBJMETRICS(metrics)           /**<metrics information */
};
#endif /* !defined(RWADOXYGENINTERNAL) */

/******************************************************************************
 * Function Prototypes
 *****************************************************************************/

#if !defined (RWADOXYGEN)

#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */

/*-----------------------------------------------------------------------------
 - Object Instance Functions
 ----------------------------------------------------------------------------*/


/* create an instance of an object */
RwaObj* RwaObjCreate( RwaObjDef *objDef, void *creationParams);

/* create an instance of an object by UUID */
RwaObj* RwaObjCreateByUUID( const RwaUUID *uuid, void *creationParams);

/* destroy an instance of an object */
void RwaObjDestroy ( RwaObj *object);

/* get the number of instances of a particular object definition */
RwUInt32 RwaObjGetCount ( RwaObjDef *objDef );

#ifdef RWAMETRICS

/* returns metrics information for this object */
RwaObjMetrics* RwaObjGetMetrics( RwaObj *object );

#endif /* RWAMETRICS */

/* create a connection between an output parameter of a source object to the 
   input parameter of a destination object */
RwaObj* RwaObjConnectParamIndex(
    RwaObj    *sourceObj,
    RwUInt32  outputIndex,
    RwaObj    *destinationObj,
    RwUInt32  inputIndex);

/* disconnect a parameter */
RwaObj* RwaObjDisconnectParamIndex(
    RwaObj     *object,
    RwUInt32   paramIndex,
    RwaIOParam inputOutput);

/* move to a particular connection index */
RwaObj* RwaObjParamMoveConnectionIndex(
    RwaObj     *object,
    RwUInt32   paramIndex,
    RwaIOParam inputOutput,
    RwUInt32   connectionIndex);

/* get the number of connections to a parameter */
RwUInt32 RwaObjParamGetConnectionCount(
    RwaObj     *object,
    RwUInt32   paramIndex,
    RwaIOParam inputOutput);

/* create a dependency between an two objects. This makes RwaCoreUpdate(XXXXX) 
   execute the dependentObject before the object */
RwaObj* RwaObjAddDependency(
    RwaObj *object, 
    RwaObj *dependentObject);

/* remove a dependency between two objects either object in the dependancy 
   can be specified */
RwaObj* RwaObjRemoveDependency( RwaObj *object );

/* move a subobject to the definition */
RwaObj* RwaObjMoveSubObject(
    RwaObj *object,
    RwaObj *subObject);

/* returns a pointer to the renderware audio object */
RwaObj* RwaObjGetTopLevelObject( void );

/* get the state of an object */
#ifdef RWADEBUG
void* RwaObjGetState(RwaObj *obj);
#else
#define RwaObjGetState(_obj) (_obj)->state;
#endif /* RWADEBUG */

/* set the state of an object */
#ifdef RWADEBUG
void* RwaObjSetState(RwaObj *obj, void *state);
#else
#define RwaObjSetState(_obj, _state) ((_obj)->state = _state);
#endif /* RWADEBUG */

/* set a parameter on an object */
RwaObj* RwaObjSetParamData(
    RwaObj     *obj,
    RwUInt32   paramIndex,
    RwaIOParam inputOutput,
    void       *data);

/* get a parameter from the first attached object */
RwaObj* RwaObjGetParamData(
    RwaObj     *obj,
    RwUInt32   paramIndex,
    RwaIOParam inputOutput,
    void       *data);

/* set a RwUInt8 parameter on an object */
RwaObj* RwaObjSetParamUInt8(
    RwaObj     *obj,
    RwUInt32   paramIndex,
    RwaIOParam inputOutput,
    RwUInt8    value);

/* set a RwInt8 parameter on an object */
RwaObj* RwaObjSetParamInt8(
    RwaObj     *obj,
    RwUInt32   paramIndex,
    RwaIOParam inputOutput,
    RwInt8     value);

/* set a RwUInt16 parameter on an object */
RwaObj* RwaObjSetParamUInt16(
    RwaObj     *object,
    RwUInt32   paramIndex,
    RwaIOParam inputOutput,
    RwUInt16   value);

/* set a RwInt16 parameter on an object */
RwaObj* RwaObjSetParamInt16(
    RwaObj     *object,
    RwUInt32   paramIndex,
    RwaIOParam inputOutput,
    RwInt16    value); 

/* set a RwUInt32 parameter on an object */
RwaObj* RwaObjSetParamUInt32(
    RwaObj     *object,
    RwUInt32   paramIndex,
    RwaIOParam inputOutput,
    RwUInt32   value);

/* set a RwInt32 parameter on an object */
RwaObj* RwaObjSetParamInt32(
    RwaObj     *object,
    RwUInt32   paramIndex,
    RwaIOParam inputOutput,
    RwInt32    value);

/* set a RwUInt64 parameter on an object */
RwaObj* RwaObjSetParamUInt64(
    RwaObj     *object,
    RwUInt32   paramIndex,
    RwaIOParam inputOutput,
    RwUInt64   value);

/* set a RwInt64 parameter on an object */
RwaObj* RwaObjSetParamInt64(
    RwaObj     *object,
    RwUInt32   paramIndex,
    RwaIOParam inputOutput,
    RwInt64    value);

/* set a RwUInt128 parameter on an object */
RwaObj* RwaObjSetParamUInt128(
    RwaObj     *object,
    RwUInt32   paramIndex,
    RwaIOParam inputOutput,
    RwUInt128  value);

/* set a RwInt128 parameter on an object */
RwaObj* RwaObjSetParamInt128(
    RwaObj     *object,
    RwUInt32   paramIndex,
    RwaIOParam inputOutput,
    RwInt128   value);

/* set a RwReal parameter on an object */
RwaObj* RwaObjSetParamReal(
    RwaObj     *object,
    RwUInt32   paramIndex,
    RwaIOParam inputOutput,
    RwReal      value);

/* get a RwUInt8 parameter from an object */
RwUInt8 RwaObjGetParamUInt8(
    RwaObj     *object,
    RwUInt32   paramIndex,
    RwaIOParam inputOutput,
    RwBool     *newValue);

/* get a RwInt8 parameter from an object */
RwInt8 RwaObjGetParamInt8(
    RwaObj     *object,
    RwUInt32   paramIndex,
    RwaIOParam inputOutput,
    RwBool     *newValue);

/* get a RwUInt16 parameter from an object */
RwUInt16 RwaObjGetParamUInt16(
    RwaObj     *object,
    RwUInt32   paramIndex,
    RwaIOParam inputOutput,
    RwBool     *newValue);

/* get a RwInt16 parameter from an object */
RwInt16 RwaObjGetParamInt16(
    RwaObj     *object,
    RwUInt32   paramIndex,
    RwaIOParam inputOutput,
    RwBool     *newValue);

/* get a RwUInt32 parameter from an object */
RwUInt32 RwaObjGetParamUInt32(
    RwaObj     *object,
    RwUInt32   paramIndex,
    RwaIOParam inputOutput,
    RwBool     *newValue);

/* get a RwInt32 parameter from an object */
RwInt32 RwaObjGetParamInt32(
    RwaObj     *object,
    RwUInt32   paramIndex,
    RwaIOParam inputOutput,
    RwBool     *newValue);

/* get a RwUInt64 parameter from an object */
RwUInt64 RwaObjGetParamUInt64(
    RwaObj     *object,
    RwUInt32   paramIndex,
    RwaIOParam inputOutput,
    RwBool     *newValue);

/* get a RwInt64 parameter from an object */
RwInt64 RwaObjGetParamInt64(
    RwaObj     *object,
    RwUInt32   paramIndex,
    RwaIOParam inputOutput,
    RwBool     *newValue);

/* get a RwReal parameter from an object */
RwReal RwaObjGetParamReal(
    RwaObj     *object,
    RwUInt32   paramIndex,
    RwaIOParam inputOutput,
    RwBool     *newValue);

#ifdef    __cplusplus
}
#endif /* __cplusplus */

#endif /* RWADOXYGEN */


/*--- Automatically derived from: d:/dev/rwa/source/core/src/rwaobjinterface.h ---*/
/******************************************************************************
 * Defines, Constants and Macros
 *****************************************************************************/
#define RWAOBJINTERFACEASSERT( _uuidptr, _objptr ) \
    RWAASSERT( _objptr ); \
    RWAASSERT( _objptr->objInterface ); \
    RWAASSERT( _objptr->objInterface->interfaceDef ); \
    RWAASSERT( RwaUUIDCompare ( _uuidptr, \
        _rwaUniqueIDGetUUID(&_objptr->objInterface->interfaceDef->uniqueID) ) \
        == 0 )

/******************************************************************************
 * Types
 *****************************************************************************/

#if !defined(RWADOXYGENINTERNAL)
typedef struct RwaInputParamMap RwaInputParamMap;
/**
 * \ingroup rwaobjinterface
 * Input parameter mapping used by the object interface.
 */
struct RwaInputParamMap
{
    RwaObjParamFunc setFunc;    /**<set function for the object input parameter*/
    RwaObjParamFunc getFunc;    /**<get function for the object input parameter*/
    RwUInt32        paramIndex; /**<index of the object's parameter 
                                    (for accessing queues)*/
};


typedef struct RwaOutputParamMap RwaOutputParamMap;
/**
 * \ingroup rwaobjinterface
 * Output parameter mapping used by the object interface.
 */
struct RwaOutputParamMap
{
    RwaObjParamFunc getFunc;    /**<get function for the object output parameter*/
    RwUInt32        paramIndex; /**<index of the object's parameter 
                                    (for accessing queues)*/
};


typedef struct RwaObjInterface RwaObjInterface;
/**
 * \ingroup rwaobjinterface
 * Instance of an object's interface.  
 * This is shared between object's of the same object definition.
 */
struct RwaObjInterface
{
    RwaObjInterfaceDef  *interfaceDef;   /**<This interface's definition */
    RwaInputParamMap    *inputParamMaps; /**<Mappings to the object's input 
                                             parameters */
    RwaOutputParamMap   *outputParamMaps;/**<Mappings to the object's output 
                                             parameters */
    RwUInt32            refCount;        /**<Number of reference to this 
                                             interface from the application */
    RwLLLink            link;            /**<Link to the list of interfaces for 
                                             an object definition */
};
#endif /* !defined(RWADOXYGENINTERNAL) */

/******************************************************************************
 * Function Prototypes
 *****************************************************************************/

#if !defined (RWADOXYGEN)
#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */


/* assign an ID to an object interface definition */
RwaObjInterfaceDef* RwaObjInterfaceDefAssignID(
    RwaObjInterfaceDef *objInterfaceDef,
    const RwaUUID      *uuid, 
    const RwChar       *name);

/* set an ID on an object interface defintiion */
RwaObjInterfaceDef* RwaObjInterfaceDefSetID(
    RwaObjInterfaceDef *objInterfaceDef,
    const RwaUUID      *uuid, 
    const RwChar       *name);

/* create an object interface definition */
RwaObjInterfaceDef* RwaObjInterfaceDefCreate( 
    RwUInt32      noInputParams,
    RwUInt32      noOutputParams);

/* destroy an object interface definition */
void RwaObjInterfaceDefDestroy(RwaObjInterfaceDef *objInterfaceDef);

/* destroy an object interface definition by UUID */
void RwaObjInterfaceDefDestroyByUUID(const RwaUUID *uuid);

/* destroy an object interface definition by name */
void RwaObjInterfaceDefDestroyByName(const RwChar *name);

/* find an object interface definition by UUID */
RwaObjInterfaceDef* RwaObjInterfaceDefFindByUUID(const RwaUUID *uuid);

/* find an object interface definition by name */
RwaObjInterfaceDef* RwaObjInterfaceDefFindByName(const RwChar *name);

/* set the ID of a parameter on an object interface definition.*/
RwaObjInterfaceDef* RwaObjInterfaceDefSetParamID(
    RwaObjInterfaceDef *objInterfaceDef,
    const RwaUUID      *uuid, 
    const RwChar       *name,
    RwUInt32           paramIndex,
    RwaIOParam         inputOutput);

/* assign the ID of a parameter on an object interface definition */
RwaObjInterfaceDef* RwaObjInterfaceDefAssignParamID(
    RwaObjInterfaceDef *objInterfaceDef,
    const RwaUUID      *uuid, 
    const RwChar       *name,
    RwUInt32           paramIndex,
    RwaIOParam         inputOutput);

/* pack the object interface definition into a single block of memory */
RwaObjInterfaceDef* RwaObjInterfaceDefPack(RwaObjInterfaceDef *objInterfaceDef);

/* create an object interface definition from a packed block of memory */
RwaObjInterfaceDef* RwaObjInterfaceDefCreateFromPack(RwaObjInterfaceDef *objInterfaceDef);

/* returns the total size of the object interface definition */
RwUInt32 RwaObjInterfaceDefGetSize(RwaObjInterfaceDef *objInterfaceDef);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* RWADOXYGEN */


/*--- Automatically derived from: d:/dev/rwa/source/core/src/rwaintf.h ---*/

/******************************************************************************
 * Macros
 *****************************************************************************/
#define RwaObjectSetParamBool(_objHandle, _paramIndex, _inputOutput, _value) \
    RwaObjectSetParamInt32(_objHandle, _paramIndex, _inputOutput, _value)

#define RwaObjectGetParamBool(_objHandle, _paramIndex, _inputOutput, _newValue) \
    RwaObjectGetParamInt32(_objHandle, _paramIndex, _inputOutput, _newValue)

#if defined(RWAMETRICS) || defined(RWADOXYGEN)

typedef struct RwaObjHandleMetrics RwaObjHandleMetrics;
/**
 * \ingroup rwaobject
 * Metrics information for an object handle
 *
 * \note This metrics information is only available in METRICS builds.
 * METRICS builds require metrics libraries for RenderWare Audio to be used and 
 * RWAMETRICS to be defined by the application.
 * For more information about build types see the section on 
 * \ref buildtypes "RenderWare Audio Build Types".
 *
 * \see RwaObjectGetMetrics
 */
struct RwaObjHandleMetrics
{
    RwUInt32      numInterfaces; /**<Number of interfaces in use for this object */
    RwaObjMetrics *objMetrics;   /**<Metrics information for the underlying 
                                     object the handle refers to. */
};

#define RWAOBJHANDLEMETRICS(_x) RwaObjHandleMetrics _x ;

#else

#define RWAOBJHANDLEMETRICS(_x)

#endif /* defined(RWAMETRICS) || defined(RWADOXYGEN) */

/******************************************************************************
 * Type Defintions
 *****************************************************************************/
#if !defined(RWADOXYGENINTERNAL)
typedef struct RwaObjHandle RwaObjHandle;
/**
 * \ingroup rwaobject
 * Audio object handle
 *
 * \see RwaObjectCreate
 */
struct RwaObjHandle
{
    RwaObj          *obj;          /**<The Object */
    RwaObjInterface *objInterface; /**<Object's interface */
    RwLLLink        link;          /**<Link to the global interface list */
    RwLLLink        objLink;       /**<Link to interface list on object instance */
    RwUInt32        refCount;      /**<reference count for this interface */
    RWAOBJHANDLEMETRICS(metrics)   /**<metrics information for this object handle */
};
#else
typedef struct RwaObjHandle RwaObjHandle;
/**
 * \ingroup rwaobject
 * An AudioObject handle structure which should be considered as an opaque type.
 * For more information see the section \ref intf "Instances & Handles".
 */
struct RwaObjHandle
{
};
#endif /* !defined(RWADOXYGENINTERNAL) */

/******************************************************************************
 * Function Prototypes
 *****************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/* open module */
RwBool _rwaObjectOpenModule( void );

/* close module */
void _rwaObjectCloseModule( void );

/* create an object */
RwaObjHandle* RwaObjectCreate(RwaObjDef *objDef, void *creationParams);

/* create an object using the object definition's UUID */
RwaObjHandle* RwaObjectCreateByUUID(const RwaUUID *uuid, void *creationParams);

/* create a connection between two objects */
RwaObjHandle* RwaObjectConnectParam(
    RwaObjHandle  *srcObjHandle, 
    const RwaUUID *srcParamUUID,
    RwaObjHandle  *destObjHandle, 
    const RwaUUID *destParamUUID);

/* disconnect a parameter */
RwaObjHandle* RwaObjectDisconnectParam(
    RwaObjHandle  *objHandle,
    const RwaUUID *paramUUID);

/* add a dependency */
RwaObjHandle* RwaObjectAddDependency(
    RwaObjHandle *objHandle,
    RwaObjHandle *dependantObjHandle);

/* remove a dependency */
RwaObjHandle* RwaObjectRemoveDependency(
    RwaObjHandle *objHandle);

/* release an object */
void RwaObjectRelease(RwaObjHandle *objHandle);

#ifdef RWAMETRICS
RwaObjHandleMetrics* RwaObjectGetMetrics(RwaObjHandle *objHandle);

#endif /* RWAMETRICS */

/* Get an interface object handle from an existing object. */
RwaObjHandle* RwaObjectGetInterface(
    RwaObjHandle       *objHandle, 
    RwaObjInterfaceDef *objInterfaceDef);

/* Get an interface object handle from an existing object using the 
   interface's UUID */
RwaObjHandle* RwaObjectGetInterfaceByUUID(
    RwaObjHandle  *objHandle, 
    const RwaUUID *uuid);

/* set a parameter on an object */
RwaObjHandle* RwaObjectSetParamData(
    RwaObjHandle *objHandle, 
    RwUInt32     paramIndex,
    RwaIOParam   inputOutput,
    void         *data);

/* get a parameter from an object */
RwaObjHandle* RwaObjectGetParamData(
    RwaObjHandle *objHandle, 
    RwUInt32     paramIndex,
    RwaIOParam   inputOutput,
    void         *data);

/* set an RwInt8 parameter on an object */
RwaObjHandle* RwaObjectSetParamInt8(
    RwaObjHandle *objHandle,
    RwUInt32     paramIndex,
    RwaIOParam   inputOutput,
    RwInt8       value);

/* set an RwUInt8 parameter on an object */
RwaObjHandle* RwaObjectSetParamUInt8(
    RwaObjHandle *objHandle,
    RwUInt32     paramIndex,
    RwaIOParam   inputOutput,
    RwUInt8      value);

/* set an RwInt16 parameter on an object */
RwaObjHandle* RwaObjectSetParamInt16(
    RwaObjHandle *objHandle,
    RwUInt32     paramIndex,
    RwaIOParam   inputOutput,
    RwInt16      value);

/* set an RwUInt16 parameter on an object */
RwaObjHandle* RwaObjectSetParamUInt16(
    RwaObjHandle *objHandle,
    RwUInt32     paramIndex,
    RwaIOParam   inputOutput,
    RwUInt16     value);

/* set an RwInt32 parameter on an object */
RwaObjHandle* RwaObjectSetParamInt32(
    RwaObjHandle *objHandle,
    RwUInt32     paramIndex,
    RwaIOParam   inputOutput,
    RwInt32      value);

/* set an RwUInt32 parameter on an object */
RwaObjHandle* RwaObjectSetParamUInt32(
    RwaObjHandle *objHandle,
    RwUInt32     paramIndex,
    RwaIOParam   inputOutput,
    RwUInt32     value);

/* set an RwInt64 parameter on an object */
RwaObjHandle* RwaObjectSetParamInt64(
    RwaObjHandle *objHandle,
    RwUInt32     paramIndex,
    RwaIOParam   inputOutput,
    RwInt64      value);

/* set an RwUInt64 parameter on an object */
RwaObjHandle* RwaObjectSetParamUInt64(
    RwaObjHandle *intf,
    RwUInt32     paramIndex,
    RwaIOParam   inputOutput,
    RwUInt64     value);

/* set an RwUInt64 parameter on an object */
RwaObjHandle* RwaObjectSetParamReal(
    RwaObjHandle *intf,
    RwUInt32     paramIndex,
    RwaIOParam   inputOutput,
    RwReal       value);

/* get an RwInt8 parameter on an object */
RwInt8 RwaObjectGetParamInt8(
    RwaObjHandle *objHandle,
    RwUInt32     paramIndex,
    RwaIOParam   inputOutput,
    RwBool       *newValue);

/* get an RwUInt8 parameter on an object */
RwUInt8 RwaObjectGetParamUInt8(
    RwaObjHandle *objHandle,
    RwUInt32     paramIndex,
    RwaIOParam   inputOutput,
    RwBool       *newValue);

/* get an RwInt16 parameter on an object */
RwInt16 RwaObjectGetParamInt16(
    RwaObjHandle *objHandle,
    RwUInt32     paramIndex,
    RwaIOParam   inputOutput,
    RwBool       *newValue);

/* get an RwUInt16 parameter on an object */
RwUInt16 RwaObjectGetParamUInt16(
    RwaObjHandle *objHandle,
    RwUInt32     paramIndex,
    RwaIOParam   inputOutput,
    RwBool       *newValue);

/* get an RwInt32 parameter on an object */
RwInt32 RwaObjectGetParamInt32(
    RwaObjHandle *objHandle,
    RwUInt32     paramIndex,
    RwaIOParam   inputOutput,
    RwBool       *newValue);

/* get an RwUInt32 parameter on an object */
RwUInt32 RwaObjectGetParamUInt32(
    RwaObjHandle *objHandle,
    RwUInt32     paramIndex,
    RwaIOParam   inputOutput,
    RwBool       *newValue);

/* get an RwInt64 parameter on an object */
RwInt64 RwaObjectGetParamInt64(
    RwaObjHandle *objHandle,
    RwUInt32     paramIndex,
    RwaIOParam   inputOutput,
    RwBool       *newValue);

/* get an RwUInt64 parameter on an object */
RwUInt64 RwaObjectGetParamUInt64(
    RwaObjHandle *objHandle,
    RwUInt32     paramIndex,
    RwaIOParam   inputOutput,
    RwBool       *newValue);

/* get an RwReal parameter on an object */
RwReal RwaObjectGetParamReal(
    RwaObjHandle *objHandle,
    RwUInt32     paramIndex,
    RwaIOParam   inputOutput,
    RwBool       *newValue);

#ifdef __cplusplus
}
#endif /* __cplusplus */


/*--- Automatically derived from: d:/dev/rwa/source/core/src/rwaobjdefalias.h ---*/
/******************************************************************************
 * Type Defintions
 *****************************************************************************/

#if !defined(RWADOXYGEN)

typedef struct RwaDefaultValueMask RwaDefaultValueMask;
/**
 * \ingroup rwaobjectalias
 * Default Value mask for an object definition alias.
 * Typically many parameters of object definitions are left at their default 
 * values.  This structure allows the default values of an object 
 * definition to be masked by ones defined in the object definition alias.
 * The index field of this structure corresponds to a parameter index on the
 * object definition.
 */
struct RwaDefaultValueMask
{
    void     *value; /**<Default value for a parameter */
    RwUInt32 index;  /**<Index of the default value */
};


typedef struct RwaObjDefAlias RwaObjDefAlias;
/**
 * \ingroup rwaobjectalias
 * AudioObject definition alias.
 * An alias of an object definition simply defines the default values for the
 * input parameters of an object definition.
 */
struct RwaObjDefAlias 
{
    RwaUniqueID         uniqueID;          /**<Unique ID for the alias */
    RwUInt32            noDefaults;        /**<Number of default value */
    RwaDefaultValueMask *defaults;         /**<Default input values */
    RwaObjDef           *objDef;           /**<Object definition this is an alias of */
    void                *creationParams;   /**<Object's creation parameters */
    RwUInt32            creationParamsSize;/**<Size of the creation parameters */
    RwLLLink            link;              /**<Link to the default list on the object
                                               definition this is an alias of */
    RwBool              packed;            /**<whether the structure is packed */
};

#endif /* !defined(RWADOXYGEN) */

/******************************************************************************
 * Function Prototypes
 *****************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/* create an object definition alias from an object instance */
RwaObjDefAlias* RwaObjDefAliasCreateByObject(RwaObjHandle *obj);

/* destroy an object definition alias */
void RwaObjDefAliasDestroy(RwaObjDefAlias *objDefAlias);

/* assign an ID to an object definition alias */
RwaObjDefAlias* RwaObjDefAliasAssignID(
    RwaObjDefAlias *objDefAlias, 
    const RwaUUID  *uuid,
    const RwChar   *name);

/* copy an ID to an object definition alias */
RwaObjDefAlias* RwaObjDefAliasSetID(
    RwaObjDefAlias *objDefAlias,
    const RwaUUID  *uuid,
    const RwChar   *name);

/* create an object using an object definition alias' UUID */
RwaObjHandle* RwaObjectCreateByObjDefAliasUUID(const RwaUUID *uuid);

/* create an object using an object definition alias */
RwaObjHandle* RwaObjectCreateByObjDefAlias(const RwaObjDefAlias *objDefAlias);

/* write an object definition alias to a stream */
RwaObjDefAlias* RwaObjDefAliasStreamWrite(
    RwaObjDefAlias *objDefAlias, 
    RwStream       *stream);

/* read an object definition alias from a stream */
RwaObjDefAlias* RwaObjDefAliasStreamRead(RwStream *stream);


#ifdef __cplusplus
}
#endif /* __cplusplus */


/*--- Automatically derived from: d:/dev/rwa/source/core/src/rwadictionary.h ---*/

/******************************************************************************
 * Defines
 *****************************************************************************/
/* Metrics members for RwaObjDict */
#ifdef RWAMETRICS
#define RWAOBJDICTMETRICS
#else
#define RWAOBJDICTMETRICS
#endif

/******************************************************************************
 * Globals
 *****************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */
extern const RwaUUID rwaOBJDICT_WORK; /*UUID of the working dictionary */
#ifdef __cplusplus
}
#endif /* __cplusplus */

/******************************************************************************
 * Type Defintions
 *****************************************************************************/

#if !defined(RWADOXYGENINTERNAL)
typedef struct RwaObjDict RwaObjDict;
/**
 * \ingroup rwaobjectdictionary
 * Object Dictionary
 */
struct RwaObjDict
{
    RwaUniqueID uniqueID;         /**<unique identifier for the dictionary */
    RwInt32     noObjDefinitions; /**<number of object definitions in the dictionary */
    RwaLLNode   head;             /**<list holding all of the object definitions */
    RwBool      packed;           /**<TRUE if the structure is packed */
    RwLLLink    link;             /**<link to dictionary list */
    RWAOBJDICTMETRICS
};
#endif /*!defined(RWADOXYGENINTERNAL)*/

/******************************************************************************
 * Function Prototypes
 *****************************************************************************/

/* Do NOT remove this line or Doxygen will make a mess of the hyperlinking. */
#if !defined (RWADOXYGEN)

#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */

/* create an object dictionary */
RwaObjDict* RwaObjDictCreate ( void );

/* destroy an object dictionary */
void RwaObjDictDestroy ( RwaObjDict *dictionary );

/* assign an ID to an object dictionary */
RwaObjDict* RwaObjDictAssignID (
    RwaObjDict    *objDict, 
    const RwaUUID *uuid, 
    const RwChar  *name);

/* set an ID of an object dictionary */
RwaObjDict* RwaObjDictSetID (
    RwaObjDict    *objDict, 
    const RwaUUID *uuid, 
    const RwChar  *name);

/* destroy an object dictionary using it's UUID */
void RwaObjDictDestroyByUUID ( const RwaUUID *uuid );

/* destroy an object dictionary using it's name */
void RwaObjDictDestroyByName ( const RwChar *name );

/* find a dictionary using it's name */
RwaObjDict* RwaObjDictFindByName( const RwChar *name );

/* find a dictionary using it's UUID */
RwaObjDict* RwaObjDictFindByUUID( const RwaUUID *uuid );

/* find a dictionary using it's list index */
RwaObjDict* RwaObjDictFindByIndex(RwUInt32 index);

/* get the working dictionary */
RwaObjDict* RwaObjDictGetWorking( void );

/* get the number of dictionaries */
RwUInt32 RwaObjDictGetCount( void );

/* add an object definition to a dictionary */
RwaObjDict* RwaObjDictAddObjDef(
    RwaObjDict *dictionary, 
    RwaObjDef  *objectDefinition);

/* remove an object definition from a dictionary */
RwaObjDict* RwaObjDictRemoveObjDef(
    RwaObjDict *dictionary,
    RwaObjDef  *objectDefinition);

/* get the number of object definitions which support a particular interface */
RwUInt32 RwaObjDictGetSupportedObjDefCount(
    RwaObjDict         *dictionary, 
    RwaObjInterfaceDef *objInterfaceDef);

/* get the object definitions which support a particular interface */
RwUInt32 RwaObjDictFindSupportedObjDefs(
    RwaObjDict         *dictionary,
    RwaObjInterfaceDef *objInterfaceDef,
    RwaObjDef          **objDefArray,
    RwUInt32           objDefArraySize);

/* remove an object definition from all dictionaries */
void RwaObjDictRemoveAllObjDefs(RwaObjDef *objectDefinition);

/* find an object definition alias from a dictionary using its name */
RwaObjDefAlias* RwaObjDictFindObjDefAliasByName(
    RwaObjDict   *dictionary,
    const RwChar *name);

/* find an object definition alias searching all dictionaries using it's UUID*/
RwaObjDefAlias* RwaObjDictAllFindObjDefAliasByUUID(
    const RwaUUID *uuid, 
    RwaObjDict    **dictionary);

/* find an object definition alias from a dictionary using its UUID */
RwaObjDefAlias* RwaObjDictFindObjDefAliasByUUID(
    RwaObjDict    *dictionary,
    const RwaUUID *uuid);

/* find an object definition from a dictionary using the object's name */
RwaObjDef* RwaObjDictFindObjDefByName(
    RwaObjDict   *dictionary,
    const RwChar *name);

/* find an object definition searching all dictionaries using it's UUID*/
RwaObjDef* RwaObjDictAllFindObjDefByUUID(
    const RwaUUID *uuid, 
    RwaObjDict    **dictionary);

/* find an object definition from a dictionary using the object's UUID */
RwaObjDef* RwaObjDictFindObjDefByUUID(
    RwaObjDict    *dictionary,
    const RwaUUID *uuid);

/* get an object definition from a specific index in the dictionary */
RwaObjDef* RwaObjDictFindObjDefByIndex(
    RwaObjDict *dictionary,
    RwUInt32   index);

/* search a dictionary for an object definition */
RwaObjDict* RwaObjDictContainsObjDef(
    RwaObjDict *dictionary,
    RwaObjDef  *objectDefinition);

/* remove an object definition from a dictionary using the object's name */
RwaObjDict* RwaObjDictRemoveObjDefByName(
    RwaObjDict   *dictionary,
    const RwChar *name);

/* remove an object definition from a dictionary using the object's UUID */
RwaObjDict* RwaObjDictRemoveObjDefByUUID(
    RwaObjDict    *dictionary,
    const RwaUUID *uniqueID);

/* search dictionary for objects using a parameter type */
RwaObjDict* RwaObjDictContainsParamType(
    RwaObjDict   *dictionary,
    RwaParamType *parameterType);

/* search all dictionaries for objects using a parameter type */
RwaParamType* RwaObjDictExistsParamType(
    RwaParamType *parameterType);

/* write the object definition aliases within a dictionary to a stream */
RwaObjDict* RwaObjDictObjDefAliasStreamWrite(
    RwaObjDict *dictionary,
    RwStream   *stream);

/* read a dictionary containing object definition aliases */
RwaObjDict* RwaObjDictObjDefAliasStreamRead(
    RwaObjDict *dictionary, 
    RwStream   *stream);

#ifdef    __cplusplus
}
#endif /* __cplusplus */

#endif /* RWADOXYGEN */


/*--- Automatically derived from: d:/dev/rwa/source/core/src/rwastream.h ---*/

/******************************************************************************
 * Defines/Macros & Constants
 *****************************************************************************/
typedef struct RwaStream RwaStream;

/******************************************************************************
 * Stream functions to be overriden
 *****************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */


/* 
    Stream engine intialization functions
*/
RwBool      RwaStreamSystemInit(RwInt32 maxstreams, RwReal buffersizescale);
void        RwaStreamSystemClose(void);

/* 
    Stream Manipulation functions
*/
RwaStream  *RwaStreamOpen(const RwChar *filename, RwaWaveFormat *format, RwBool block);
RwaStream  *RwaStreamStart(RwaStream *stream, RwaObjHandle *voice, RwaObjHandle *voicestereo, RwBool loop);
void        RwaStreamStop (RwaStream *stream);
void        RwaStreamClose(RwaStream *stream);
RwBool      RwaStreamFlush(RwaStream *stream);
void        RwaStreamSetPosition(RwaStream *stream, RwUInt32 pos);
void        RwaStreamSetTime(RwaStream *stream, RwUInt32 ms);

/* 
    Information functions
*/
RwBool      RwaStreamGetFormat(RwaStream *stream, RwaWaveFormat *format);
RwUInt32    RwaStreamGetPosition(RwaStream *stream);
RwUInt32    RwaStreamGetTime(RwaStream *stream);
RwUInt32    RwaStreamGetLength(RwaStream *stream);
RwUInt32    RwaStreamGetLengthMs(RwaStream *stream);
RwUInt32    RwaStreamGetMemUsage(void);
RwUInt32    RwaStreamGetThroughput(void);

#ifdef    __cplusplus
}
#endif /* __cplusplus */


/*--- Automatically derived from: d:/dev/rwa/source/core/src/rwavoicemanager.h ---*/

#ifdef    __cplusplus
extern "C"{
#endif /* __cplusplus */

RwBool  RwaVoiceManagerRegister( RwaObjHandle *output, RwaObjHandle **realvoices, RwInt32 numrealvoices );

#ifdef    __cplusplus
}
#endif /* __cplusplus */


/*--- Automatically derived from: d:/dev/rwa/source/objects/src/rwavirtualvoiceobj.h ---*/

/******************************************************************************
 * Defines/Macros & Constants
 *****************************************************************************/
#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */

/*TGenSectionStart_VirtualVoiceUUID*/
extern const RwaUUID rwaVIRTUALVOICEID;
/*TGenSectionFinish_VirtualVoiceUUID*/

#ifdef    __cplusplus
}
#endif /* __cplusplus */

/******************************************************************************
 * Types
 *****************************************************************************/

/*TGenSectionStart_VirtualVoiceDestroyMacro*/
#ifndef RWADEBUG
#define RwaVirtualVoiceDestroy(_handle) \
    RwaObjectRelease(_handle)
#endif /* !RWADEBUG */
/*TGenSectionFinish_VirtualVoiceDestroyMacro*/

typedef struct RwaVirtualVoiceState RwaVirtualVoiceState;

struct RwaVirtualVoiceState
{
    RwLLLink        link;
    RwaObjHandle   *RealVoice;    /* valid if active, NULL if swapped out */
    RwaObjHandle   *RealVoice3D;  /* valid if active, NULL if swapped out */  
    RwBool          Used;
    RwInt32         NumRealVoices;  /* stores the number of voices a realvoice is using */
    
    /* State of the virtual voice */
    RwBool          Trigger;
    RwUInt32        Frequency;
    RwReal          Gain;
    RwReal          Pan;
    RwBool          Looping;
    RwUInt32        WavePosition;
    RwaWave        *Wave;
    
    RwUInt32        LastPosTime;
    
    RwV3d           Position;
    RwV3d           Velocity;
    RwReal          MinDistance;
    RwReal          MaxDistance;
    
    RwReal          Priority;
    RwReal          Bias;
    RwReal          Weight;
};

/******************************************************************************
 * Functions
 *****************************************************************************/

#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */

/*TGenSectionStart_VirtualVoiceCreate*/
/* create VirtualVoice */
RwaObjHandle *RwaVirtualVoiceCreate(void *creationParams);
/*TGenSectionFinish_VirtualVoiceCreate*/

/*TGenSectionStart_VirtualVoiceDestroy*/
#ifdef RWADEBUG
/* destroy VirtualVoice */
void RwaVirtualVoiceDestroy(RwaObjHandle *objHandle);
#endif /* RWADEBUG */
/*TGenSectionFinish_VirtualVoiceDestroy*/

/*TGenSectionStart_VirtualVoiceRegister*/
/* register VirtualVoice object definition */
RwaObjDef* RwaVirtualVoiceRegister(void);
/*TGenSectionFinish_VirtualVoiceRegister*/

#ifdef    __cplusplus
}
#endif /* __cplusplus */


/*--- Automatically derived from: d:/dev/rwa/source/interfaces/src/rwavirtualvoice.h ---*/


/******************************************************************************
 * Defines/Macros & Constants
 *****************************************************************************/

/*TGenSectionStart_VirtualVoiceInterfaceName*/
/* object interface's name */
#ifdef RWADEBUG
#define rwaVIRTUALVOICEINTERFACENAME "VirtualVoice Interface"
#else
#define rwaVIRTUALVOICEINTERFACENAME ""
#endif /* RWADEBUG */
/*TGenSectionFinish_VirtualVoiceInterfaceName*/

/*TGenSectionStart_VirtualVoiceParameterNames*/
/* object interface's parameter names */
#ifdef RWADEBUG
#define rwaVIRTUALVOICENAMEI_FREQ        rwaVOICENAMEI_FREQ
#define rwaVIRTUALVOICENAMEO_FREQ        rwaVOICENAMEO_FREQ
#define rwaVIRTUALVOICENAMEI_GAIN        rwaVOICENAMEI_GAIN
#define rwaVIRTUALVOICENAMEO_GAIN        rwaVOICENAMEO_GAIN
#define rwaVIRTUALVOICENAMEI_TRIGGER     rwaVOICENAMEI_TRIGGER
#define rwaVIRTUALVOICENAMEO_PLAYING     rwaVOICENAMEO_PLAYING
#define rwaVIRTUALVOICENAMEI_WAVEPOS     rwaVOICENAMEI_WAVEPOS
#define rwaVIRTUALVOICENAMEO_WAVEPOS     rwaVOICENAMEO_WAVEPOS
#define rwaVIRTUALVOICENAMEI_LOOP        rwaVOICENAMEI_LOOP
#define rwaVIRTUALVOICENAMEO_LOOP        rwaVOICENAMEO_LOOP
#define rwaVIRTUALVOICENAMEI_WAVE        rwaVOICENAMEI_WAVE
#define rwaVIRTUALVOICENAMEO_WAVE        rwaVOICENAMEO_WAVE
#define rwaVIRTUALVOICENAMEI_PAN         rwaVOICENAMEI_PAN
#define rwaVIRTUALVOICENAMEO_PAN         rwaVOICENAMEO_PAN
#define rwaVIRTUALVOICENAMEI_PRIORITY    "PriorityI" 
#define rwaVIRTUALVOICENAMEO_PRIORITY    "PriorityO" 
#define rwaVIRTUALVOICENAMEI_BIAS        "BiasI" 
#define rwaVIRTUALVOICENAMEO_BIAS        "BiasO" 
#define rwaVIRTUALVOICENAMEO_ISSTEREO    rwaVOICENAMEO_ISSTEREO
#define rwaVIRTUALVOICENAMEI_POS         rwaVOICE3DNAMEI_POS 
#define rwaVIRTUALVOICENAMEO_POS         rwaVOICE3DNAMEO_POS
#define rwaVIRTUALVOICENAMEI_VEL         rwaVOICE3DNAMEI_VEL
#define rwaVIRTUALVOICENAMEO_VEL         rwaVOICE3DNAMEO_VEL
#define rwaVIRTUALVOICENAMEI_MINDISTANCE rwaVOICE3DNAMEI_MINDISTANCE
#define rwaVIRTUALVOICENAMEO_MINDISTANCE rwaVOICE3DNAMEO_MINDISTANCE
#define rwaVIRTUALVOICENAMEI_MAXDISTANCE rwaVOICE3DNAMEI_MAXDISTANCE
#define rwaVIRTUALVOICENAMEO_MAXDISTANCE rwaVOICE3DNAMEO_MAXDISTANCE
#else

#define rwaVIRTUALVOICENAMEI_FREQ "" 
#define rwaVIRTUALVOICENAMEO_FREQ "" 
#define rwaVIRTUALVOICENAMEI_GAIN "" 
#define rwaVIRTUALVOICENAMEO_GAIN "" 
#define rwaVIRTUALVOICENAMEI_TRIGGER "" 
#define rwaVIRTUALVOICENAMEO_PLAYING "" 
#define rwaVIRTUALVOICENAMEI_WAVEPOS "" 
#define rwaVIRTUALVOICENAMEO_WAVEPOS "" 
#define rwaVIRTUALVOICENAMEI_LOOP "" 
#define rwaVIRTUALVOICENAMEO_LOOP "" 
#define rwaVIRTUALVOICENAMEI_WAVE "" 
#define rwaVIRTUALVOICENAMEO_WAVE "" 
#define rwaVIRTUALVOICENAMEI_PAN "" 
#define rwaVIRTUALVOICENAMEO_PAN "" 
#define rwaVIRTUALVOICENAMEI_PRIORITY "" 
#define rwaVIRTUALVOICENAMEO_PRIORITY "" 
#define rwaVIRTUALVOICENAMEI_BIAS "" 
#define rwaVIRTUALVOICENAMEO_BIAS "" 
#define rwaVIRTUALVOICENAMEO_ISSTEREO "" 
#define rwaVIRTUALVOICENAMEI_POS "" 
#define rwaVIRTUALVOICENAMEO_POS "" 
#define rwaVIRTUALVOICENAMEI_VEL "" 
#define rwaVIRTUALVOICENAMEO_VEL "" 
#define rwaVIRTUALVOICENAMEI_MINDISTANCE "" 
#define rwaVIRTUALVOICENAMEO_MINDISTANCE "" 
#define rwaVIRTUALVOICENAMEI_MAXDISTANCE "" 
#define rwaVIRTUALVOICENAMEO_MAXDISTANCE "" 
#endif /* RWADEBUG */
/*TGenSectionFinish_VirtualVoiceParameterNames*/

#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */

/*TGenSectionStart_VirtualVoiceInterfaceUUID*/
extern const RwaUUID rwaVIRTUALVOICEINTERFACEID;  /* object interface's UUID */
/*TGenSectionFinish_VirtualVoiceInterfaceUUID*/

/*----------------------------------------------------------------------------
 - object interface's input and output UUIDs
 ---------------------------------------------------------------------------*/
/*TGenSectionStart_VirtualVoiceParameterUUIDs*/
#define rwaVIRTUALVOICEIDI_FREQ         rwaVOICEIDI_FREQ
#define rwaVIRTUALVOICEIDO_FREQ         rwaVOICEIDO_FREQ
#define rwaVIRTUALVOICEIDI_GAIN         rwaVOICEIDI_GAIN
#define rwaVIRTUALVOICEIDO_GAIN         rwaVOICEIDO_GAIN
#define rwaVIRTUALVOICEIDI_TRIGGER      rwaVOICEIDI_TRIGGER
#define rwaVIRTUALVOICEIDO_PLAYING      rwaVOICEIDO_PLAYING
#define rwaVIRTUALVOICEIDI_WAVEPOS      rwaVOICEIDI_WAVEPOS
#define rwaVIRTUALVOICEIDO_WAVEPOS      rwaVOICEIDO_WAVEPOS
#define rwaVIRTUALVOICEIDI_LOOP         rwaVOICEIDI_LOOP
#define rwaVIRTUALVOICEIDO_LOOP         rwaVOICEIDO_LOOP
#define rwaVIRTUALVOICEIDI_WAVE         rwaVOICEIDI_WAVE
#define rwaVIRTUALVOICEIDO_WAVE         rwaVOICEIDO_WAVE
#define rwaVIRTUALVOICEIDI_PAN          rwaVOICEIDI_PAN
#define rwaVIRTUALVOICEIDO_PAN          rwaVOICEIDO_PAN
extern const RwaUUID rwaVIRTUALVOICEIDI_PRIORITY;
extern const RwaUUID rwaVIRTUALVOICEIDO_PRIORITY;
extern const RwaUUID rwaVIRTUALVOICEIDI_BIAS;
extern const RwaUUID rwaVIRTUALVOICEIDO_BIAS;
#define rwaVIRTUALVOICEIDO_ISSTEREO     rwaVOICEIDO_ISSTEREO
#define rwaVIRTUALVOICEIDI_POS          rwaVOICE3DIDI_POS
#define rwaVIRTUALVOICEIDO_POS          rwaVOICE3DIDO_POS
#define rwaVIRTUALVOICEIDI_VEL          rwaVOICE3DIDI_VEL
#define rwaVIRTUALVOICEIDO_VEL          rwaVOICE3DIDO_VEL
#define rwaVIRTUALVOICEIDI_MINDISTANCE  rwaVOICE3DIDI_MINDISTANCE
#define rwaVIRTUALVOICEIDO_MINDISTANCE  rwaVOICE3DIDO_MINDISTANCE
#define rwaVIRTUALVOICEIDI_MAXDISTANCE  rwaVOICE3DIDI_MAXDISTANCE
#define rwaVIRTUALVOICEIDO_MAXDISTANCE  rwaVOICE3DIDO_MAXDISTANCE

/*TGenSectionFinish_VirtualVoiceParameterUUIDs*/

#ifdef    __cplusplus
}
#endif /* __cplusplus */


/******************************************************************************
 * Types
 *****************************************************************************/

/* object input and output indexes */
/*TGenSectionStart_VirtualVoiceIndexes*/
typedef enum
{   

    rwaVIRTUALVOICEIDXIN_FREQ = 0,
    rwaVIRTUALVOICEIDXIN_GAIN = 1,
    rwaVIRTUALVOICEIDXIN_TRIGGER = 2,
    rwaVIRTUALVOICEIDXIN_WAVEPOS = 3,
    rwaVIRTUALVOICEIDXIN_LOOP = 4,
    rwaVIRTUALVOICEIDXIN_WAVE = 5,
    rwaVIRTUALVOICEIDXIN_PAN = 6,
    rwaVIRTUALVOICEIDXIN_PRIORITY = 7,
    rwaVIRTUALVOICEIDXIN_BIAS = 8,
    rwaVIRTUALVOICEIDXIN_POS = 9,
    rwaVIRTUALVOICEIDXIN_VEL = 10,
    rwaVIRTUALVOICEIDXIN_MINDISTANCE = 11,
    rwaVIRTUALVOICEIDXIN_MAXDISTANCE = 12,
    rwaVIRTUALVOICEIDXIN_FORCEENUMSIZEINT = RWFORCEENUMSIZEINT
} rwaVIRTUALVOICEIDXIN;

typedef enum
{

    rwaVIRTUALVOICEIDXOUT_FREQ = 0,
    rwaVIRTUALVOICEIDXOUT_GAIN = 1,
    rwaVIRTUALVOICEIDXOUT_PLAYING = 2,
    rwaVIRTUALVOICEIDXOUT_WAVEPOS = 3,
    rwaVIRTUALVOICEIDXOUT_LOOP = 4,
    rwaVIRTUALVOICEIDXOUT_WAVE = 5,
    rwaVIRTUALVOICEIDXOUT_PAN = 6,
    rwaVIRTUALVOICEIDXOUT_PRIORITY = 7,
    rwaVIRTUALVOICEIDXOUT_BIAS = 8,
    rwaVIRTUALVOICEIDXOUT_ISSTEREO = 9,
    rwaVIRTUALVOICEIDXOUT_POS = 10,
    rwaVIRTUALVOICEIDXOUT_VEL = 11,
    rwaVIRTUALVOICEIDXOUT_MINDISTANCE = 12,
    rwaVIRTUALVOICEIDXOUT_MAXDISTANCE = 13,
    rwaVIRTUALVOICEIDXOUT_FORCEENUMSIZEINT = RWFORCEENUMSIZEINT
} rwaVIRTUALVOICEIDXOUT;
/*TGenSectionFinish_VirtualVoiceIndexes*/

/******************************************************************************
 * Functions
 *****************************************************************************/

#ifdef RWADEBUG
#if !defined (RWADOXYGEN)
#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */

/*TGenSectionStart_VirtualVoiceSet0*/
RwaObjHandle* RwaVirtualVoiceSetFreq( RwaObjHandle *objHandle, RwInt32 value);
/*TGenSectionFinish_VirtualVoiceSet0*/
/*TGenSectionStart_VirtualVoiceGet0*/
RwInt32 RwaVirtualVoiceGetFreq( RwaObjHandle *object );
/*TGenSectionFinish_VirtualVoiceGet0*/
/*TGenSectionStart_VirtualVoiceSet1*/
RwaObjHandle* RwaVirtualVoiceSetGain( RwaObjHandle *objHandle, RwReal value);
/*TGenSectionFinish_VirtualVoiceSet1*/
/*TGenSectionStart_VirtualVoiceGet1*/
RwReal RwaVirtualVoiceGetGain( RwaObjHandle *object );
/*TGenSectionFinish_VirtualVoiceGet1*/
/*TGenSectionStart_VirtualVoiceSet2*/
RwaObjHandle* RwaVirtualVoiceSetTrigger( RwaObjHandle *objHandle, RwBool value);
/*TGenSectionFinish_VirtualVoiceSet2*/
/*TGenSectionStart_VirtualVoiceGet2*/
RwBool RwaVirtualVoiceGetPlaying( RwaObjHandle *object );
/*TGenSectionFinish_VirtualVoiceGet2*/
/*TGenSectionStart_VirtualVoiceSet3*/
RwaObjHandle* RwaVirtualVoiceSetWavePos( RwaObjHandle *objHandle, RwUInt32 value);
/*TGenSectionFinish_VirtualVoiceSet3*/
/*TGenSectionStart_VirtualVoiceGet3*/
RwUInt32 RwaVirtualVoiceGetWavePos( RwaObjHandle *object );
/*TGenSectionFinish_VirtualVoiceGet3*/
/*TGenSectionStart_VirtualVoiceSet4*/
RwaObjHandle* RwaVirtualVoiceSetLoop( RwaObjHandle *objHandle, RwBool value);
/*TGenSectionFinish_VirtualVoiceSet4*/
/*TGenSectionStart_VirtualVoiceGet4*/
RwBool RwaVirtualVoiceGetLoop( RwaObjHandle *object );
/*TGenSectionFinish_VirtualVoiceGet4*/
/*TGenSectionStart_VirtualVoiceSet5*/
RwaObjHandle* RwaVirtualVoiceSetWave( RwaObjHandle *objHandle, RwaWave *data );
/*TGenSectionFinish_VirtualVoiceSet5*/
/*TGenSectionStart_VirtualVoiceGet5*/
RwaObjHandle* RwaVirtualVoiceGetWave( RwaObjHandle *object, RwaWave *data );
/*TGenSectionFinish_VirtualVoiceGet5*/
/*TGenSectionStart_VirtualVoiceSet6*/
RwaObjHandle* RwaVirtualVoiceSetPan( RwaObjHandle *objHandle, RwReal value);
/*TGenSectionFinish_VirtualVoiceSet6*/
/*TGenSectionStart_VirtualVoiceGet6*/
RwReal RwaVirtualVoiceGetPan( RwaObjHandle *object );
/*TGenSectionFinish_VirtualVoiceGet6*/
/*TGenSectionStart_VirtualVoiceSet7*/
RwaObjHandle* RwaVirtualVoiceSetPriority( RwaObjHandle *objHandle, RwReal value);
/*TGenSectionFinish_VirtualVoiceSet7*/
/*TGenSectionStart_VirtualVoiceGet7*/
RwReal RwaVirtualVoiceGetPriority( RwaObjHandle *object );
/*TGenSectionFinish_VirtualVoiceGet7*/
/*TGenSectionStart_VirtualVoiceSet8*/
RwaObjHandle* RwaVirtualVoiceSetBias( RwaObjHandle *objHandle, RwReal value);
/*TGenSectionFinish_VirtualVoiceSet8*/
/*TGenSectionStart_VirtualVoiceGet8*/
RwReal RwaVirtualVoiceGetBias( RwaObjHandle *object );
/*TGenSectionFinish_VirtualVoiceGet8*/
/*TGenSectionStart_VirtualVoiceGet9*/
RwBool RwaVirtualVoiceGetIsStereo( RwaObjHandle *object );
/*TGenSectionFinish_VirtualVoiceGet9*/
/*TGenSectionStart_VirtualVoiceSet9*/
RwaObjHandle* RwaVirtualVoiceSetPos( RwaObjHandle *objHandle, RwV3d *data );
/*TGenSectionFinish_VirtualVoiceSet9*/
/*TGenSectionStart_VirtualVoiceGet10*/
RwaObjHandle* RwaVirtualVoiceGetPos( RwaObjHandle *object, RwV3d *data );
/*TGenSectionFinish_VirtualVoiceGet10*/
/*TGenSectionStart_VirtualVoiceSet10*/
RwaObjHandle* RwaVirtualVoiceSetVel( RwaObjHandle *objHandle, RwV3d *data );
/*TGenSectionFinish_VirtualVoiceSet10*/
/*TGenSectionStart_VirtualVoiceGet11*/
RwaObjHandle* RwaVirtualVoiceGetVel( RwaObjHandle *object, RwV3d *data );
/*TGenSectionFinish_VirtualVoiceGet11*/
/*TGenSectionStart_VirtualVoiceSet11*/
RwaObjHandle* RwaVirtualVoiceSetMinDistance( RwaObjHandle *objHandle, RwReal value);
/*TGenSectionFinish_VirtualVoiceSet11*/
/*TGenSectionStart_VirtualVoiceGet12*/
RwReal RwaVirtualVoiceGetMinDistance( RwaObjHandle *object );
/*TGenSectionFinish_VirtualVoiceGet12*/
/*TGenSectionStart_VirtualVoiceSet12*/
RwaObjHandle* RwaVirtualVoiceSetMaxDistance( RwaObjHandle *objHandle, RwReal value);
/*TGenSectionFinish_VirtualVoiceSet12*/
/*TGenSectionStart_VirtualVoiceGet13*/
RwReal RwaVirtualVoiceGetMaxDistance( RwaObjHandle *object );
/*TGenSectionFinish_VirtualVoiceGet13*/
#ifdef    __cplusplus
}
#endif /* __cplusplus */
#endif /* RWADOXYGEN */
#else
/*-----------------------------------------------------------------------------
 - Set parameter and get parameter functions and macros
 ----------------------------------------------------------------------------*/

/*TGenSectionStart_VirtualVoiceSet0Macro*/
#define RwaVirtualVoiceSetFreq(_object, _value) \
            RwaObjectSetParamInt32(_object, \
                rwaVIRTUALVOICEIDXIN_FREQ, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_VirtualVoiceSet0Macro*/
/*TGenSectionStart_VirtualVoiceGet0Macro*/
#define RwaVirtualVoiceGetFreq(_object) \
            RwaObjectGetParamInt32(_object, \
                rwaVIRTUALVOICEIDXOUT_FREQ, rwaIOPARAM_OUTPUT, (RwBool*)NULL)
/*TGenSectionFinish_VirtualVoiceGet0Macro*/
/*TGenSectionStart_VirtualVoiceSet1Macro*/
#define RwaVirtualVoiceSetGain(_object, _value) \
            RwaObjectSetParamReal(_object, \
                rwaVIRTUALVOICEIDXIN_GAIN, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_VirtualVoiceSet1Macro*/
/*TGenSectionStart_VirtualVoiceGet1Macro*/
#define RwaVirtualVoiceGetGain(_object) \
            RwaObjectGetParamReal(_object, \
                rwaVIRTUALVOICEIDXOUT_GAIN, rwaIOPARAM_OUTPUT, (RwBool*)NULL)
/*TGenSectionFinish_VirtualVoiceGet1Macro*/
/*TGenSectionStart_VirtualVoiceSet2Macro*/
#define RwaVirtualVoiceSetTrigger(_object, _value) \
            RwaObjectSetParamBool(_object, \
                rwaVIRTUALVOICEIDXIN_TRIGGER, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_VirtualVoiceSet2Macro*/
/*TGenSectionStart_VirtualVoiceGet2Macro*/
#define RwaVirtualVoiceGetPlaying(_object) \
            RwaObjectGetParamBool(_object, \
                rwaVIRTUALVOICEIDXOUT_PLAYING, rwaIOPARAM_OUTPUT, (RwBool*)NULL)
/*TGenSectionFinish_VirtualVoiceGet2Macro*/
/*TGenSectionStart_VirtualVoiceSet3Macro*/
#define RwaVirtualVoiceSetWavePos(_object, _value) \
            RwaObjectSetParamUInt32(_object, \
                rwaVIRTUALVOICEIDXIN_WAVEPOS, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_VirtualVoiceSet3Macro*/
/*TGenSectionStart_VirtualVoiceGet3Macro*/
#define RwaVirtualVoiceGetWavePos(_object) \
            RwaObjectGetParamUInt32(_object, \
                rwaVIRTUALVOICEIDXOUT_WAVEPOS, rwaIOPARAM_OUTPUT, (RwBool*)NULL)
/*TGenSectionFinish_VirtualVoiceGet3Macro*/
/*TGenSectionStart_VirtualVoiceSet4Macro*/
#define RwaVirtualVoiceSetLoop(_object, _value) \
            RwaObjectSetParamBool(_object, \
                rwaVIRTUALVOICEIDXIN_LOOP, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_VirtualVoiceSet4Macro*/
/*TGenSectionStart_VirtualVoiceGet4Macro*/
#define RwaVirtualVoiceGetLoop(_object) \
            RwaObjectGetParamBool(_object, \
                rwaVIRTUALVOICEIDXOUT_LOOP, rwaIOPARAM_OUTPUT, (RwBool*)NULL)
/*TGenSectionFinish_VirtualVoiceGet4Macro*/
/*TGenSectionStart_VirtualVoiceSet5Macro*/
#define RwaVirtualVoiceSetWave(_object, _ptr) \
            RwaObjectSetParamData(_object, \
                rwaVIRTUALVOICEIDXIN_WAVE, rwaIOPARAM_INPUT, &_ptr)
/*TGenSectionFinish_VirtualVoiceSet5Macro*/
/*TGenSectionStart_VirtualVoiceGet5Macro*/
#define RwaVirtualVoiceGetWave(_object, _ptr) \
            RwaObjectGetParamData(_object, \
                rwaVIRTUALVOICEIDXOUT_WAVE, rwaIOPARAM_OUTPUT, _ptr)
/*TGenSectionFinish_VirtualVoiceGet5Macro*/
/*TGenSectionStart_VirtualVoiceSet6Macro*/
#define RwaVirtualVoiceSetPan(_object, _value) \
            RwaObjectSetParamReal(_object, \
                rwaVIRTUALVOICEIDXIN_PAN, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_VirtualVoiceSet6Macro*/
/*TGenSectionStart_VirtualVoiceGet6Macro*/
#define RwaVirtualVoiceGetPan(_object) \
            RwaObjectGetParamReal(_object, \
                rwaVIRTUALVOICEIDXOUT_PAN, rwaIOPARAM_OUTPUT, (RwBool*)NULL)
/*TGenSectionFinish_VirtualVoiceGet6Macro*/
/*TGenSectionStart_VirtualVoiceSet7Macro*/
#define RwaVirtualVoiceSetPriority(_object, _value) \
            RwaObjectSetParamReal(_object, \
                rwaVIRTUALVOICEIDXIN_PRIORITY, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_VirtualVoiceSet7Macro*/
/*TGenSectionStart_VirtualVoiceGet7Macro*/
#define RwaVirtualVoiceGetPriority(_object) \
            RwaObjectGetParamReal(_object, \
                rwaVIRTUALVOICEIDXOUT_PRIORITY, rwaIOPARAM_OUTPUT, (RwBool*)NULL)
/*TGenSectionFinish_VirtualVoiceGet7Macro*/
/*TGenSectionStart_VirtualVoiceSet8Macro*/
#define RwaVirtualVoiceSetBias(_object, _value) \
            RwaObjectSetParamReal(_object, \
                rwaVIRTUALVOICEIDXIN_BIAS, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_VirtualVoiceSet8Macro*/
/*TGenSectionStart_VirtualVoiceGet8Macro*/
#define RwaVirtualVoiceGetBias(_object) \
            RwaObjectGetParamReal(_object, \
                rwaVIRTUALVOICEIDXOUT_BIAS, rwaIOPARAM_OUTPUT, (RwBool*)NULL)
/*TGenSectionFinish_VirtualVoiceGet8Macro*/
/*TGenSectionStart_VirtualVoiceGet9Macro*/
#define RwaVirtualVoiceGetIsStereo(_object) \
            RwaObjectGetParamBool(_object, \
                rwaVIRTUALVOICEIDXOUT_ISSTEREO, rwaIOPARAM_OUTPUT, (RwBool*)NULL)
/*TGenSectionFinish_VirtualVoiceGet9Macro*/
/*TGenSectionStart_VirtualVoiceSet9Macro*/
#define RwaVirtualVoiceSetPos(_object, _ptr) \
            RwaObjectSetParamData(_object, \
                rwaVIRTUALVOICEIDXIN_POS, rwaIOPARAM_INPUT, _ptr)
/*TGenSectionFinish_VirtualVoiceSet9Macro*/
/*TGenSectionStart_VirtualVoiceGet10Macro*/
#define RwaVirtualVoiceGetPos(_object, _ptr) \
            RwaObjectGetParamData(_object, \
                rwaVIRTUALVOICEIDXOUT_POS, rwaIOPARAM_OUTPUT, _ptr)
/*TGenSectionFinish_VirtualVoiceGet10Macro*/
/*TGenSectionStart_VirtualVoiceSet10Macro*/
#define RwaVirtualVoiceSetVel(_object, _ptr) \
            RwaObjectSetParamData(_object, \
                rwaVIRTUALVOICEIDXIN_VEL, rwaIOPARAM_INPUT, _ptr)
/*TGenSectionFinish_VirtualVoiceSet10Macro*/
/*TGenSectionStart_VirtualVoiceGet11Macro*/
#define RwaVirtualVoiceGetVel(_object, _ptr) \
            RwaObjectGetParamData(_object, \
                rwaVIRTUALVOICEIDXOUT_VEL, rwaIOPARAM_OUTPUT, _ptr)
/*TGenSectionFinish_VirtualVoiceGet11Macro*/
/*TGenSectionStart_VirtualVoiceSet11Macro*/
#define RwaVirtualVoiceSetMinDistance(_object, _value) \
            RwaObjectSetParamReal(_object, \
                rwaVIRTUALVOICEIDXIN_MINDISTANCE, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_VirtualVoiceSet11Macro*/
/*TGenSectionStart_VirtualVoiceGet12Macro*/
#define RwaVirtualVoiceGetMinDistance(_object) \
            RwaObjectGetParamReal(_object, \
                rwaVIRTUALVOICEIDXOUT_MINDISTANCE, rwaIOPARAM_OUTPUT, (RwBool*)NULL)
/*TGenSectionFinish_VirtualVoiceGet12Macro*/
/*TGenSectionStart_VirtualVoiceSet12Macro*/
#define RwaVirtualVoiceSetMaxDistance(_object, _value) \
            RwaObjectSetParamReal(_object, \
                rwaVIRTUALVOICEIDXIN_MAXDISTANCE, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_VirtualVoiceSet12Macro*/
/*TGenSectionStart_VirtualVoiceGet13Macro*/
#define RwaVirtualVoiceGetMaxDistance(_object) \
            RwaObjectGetParamReal(_object, \
                rwaVIRTUALVOICEIDXOUT_MAXDISTANCE, rwaIOPARAM_OUTPUT, (RwBool*)NULL)
/*TGenSectionFinish_VirtualVoiceGet13Macro*/
#endif /* RWADEBUG */


#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */

/* register VirtualVoice object interface definition */
/*TGenSectionStart_VirtualVoiceInterfaceRegister*/
RwaObjInterfaceDef* RwaVirtualVoiceInterfaceRegister(void);
/*TGenSectionFinish_VirtualVoiceInterfaceRegister*/

#ifdef    __cplusplus
}
#endif /* __cplusplus */


/*--- Automatically derived from: d:/dev/rwa/source/interfaces/src/rwavoice.h ---*/


/******************************************************************************
 * Defines/Macros & Constants
 *****************************************************************************/

/*TGenSectionStart_VoiceInterfaceName*/
/* object interface's name */
#ifdef RWADEBUG
#define rwaVOICEINTERFACENAME "Voice Interface"
#else
#define rwaVOICEINTERFACENAME ""
#endif /* RWADEBUG */
/*TGenSectionFinish_VoiceInterfaceName*/

/*TGenSectionStart_VoiceParameterNames*/
/* object interface's parameter names */
#ifdef RWADEBUG

#define rwaVOICENAMEI_FREQ "FreqI" 
#define rwaVOICENAMEO_FREQ "FreqO" 
#define rwaVOICENAMEI_GAIN "GainI" 
#define rwaVOICENAMEO_GAIN "GainO" 
#define rwaVOICENAMEI_TRIGGER "TriggerI" 
#define rwaVOICENAMEO_PLAYING "PlayingO" 
#define rwaVOICENAMEI_WAVEPOS "WavePosI" 
#define rwaVOICENAMEO_WAVEPOS "WavePosO" 
#define rwaVOICENAMEI_LOOP "LoopI" 
#define rwaVOICENAMEO_LOOP "LoopO" 
#define rwaVOICENAMEI_WAVE "WaveI" 
#define rwaVOICENAMEO_WAVE "WaveO" 
#define rwaVOICENAMEI_PAN "PanI" 
#define rwaVOICENAMEO_PAN "PanO" 
#define rwaVOICENAMEO_ISSTEREO "IsStereoO" 
#else

#define rwaVOICENAMEI_FREQ "" 
#define rwaVOICENAMEO_FREQ "" 
#define rwaVOICENAMEI_GAIN "" 
#define rwaVOICENAMEO_GAIN "" 
#define rwaVOICENAMEI_TRIGGER "" 
#define rwaVOICENAMEO_PLAYING "" 
#define rwaVOICENAMEI_WAVEPOS "" 
#define rwaVOICENAMEO_WAVEPOS "" 
#define rwaVOICENAMEI_LOOP "" 
#define rwaVOICENAMEO_LOOP "" 
#define rwaVOICENAMEI_WAVE "" 
#define rwaVOICENAMEO_WAVE "" 
#define rwaVOICENAMEI_PAN "" 
#define rwaVOICENAMEO_PAN "" 
#define rwaVOICENAMEO_ISSTEREO "" 
#endif /* RWADEBUG */
/*TGenSectionFinish_VoiceParameterNames*/

#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */

/*TGenSectionStart_VoiceInterfaceUUID*/
extern const RwaUUID rwaVOICEINTERFACEID;  /* object interface's UUID */
/*TGenSectionFinish_VoiceInterfaceUUID*/

/*----------------------------------------------------------------------------
 - object interface's input and output UUIDs
 ---------------------------------------------------------------------------*/
/*TGenSectionStart_VoiceParameterUUIDs*/
extern const RwaUUID rwaVOICEIDI_FREQ;
extern const RwaUUID rwaVOICEIDO_FREQ;
extern const RwaUUID rwaVOICEIDI_GAIN;
extern const RwaUUID rwaVOICEIDO_GAIN;
extern const RwaUUID rwaVOICEIDI_TRIGGER;
extern const RwaUUID rwaVOICEIDO_PLAYING;
extern const RwaUUID rwaVOICEIDI_WAVEPOS;
extern const RwaUUID rwaVOICEIDO_WAVEPOS;
extern const RwaUUID rwaVOICEIDI_LOOP;
extern const RwaUUID rwaVOICEIDO_LOOP;
extern const RwaUUID rwaVOICEIDI_WAVE;
extern const RwaUUID rwaVOICEIDO_WAVE;
extern const RwaUUID rwaVOICEIDI_PAN;
extern const RwaUUID rwaVOICEIDO_PAN;
extern const RwaUUID rwaVOICEIDO_ISSTEREO;

/*TGenSectionFinish_VoiceParameterUUIDs*/

#ifdef    __cplusplus
}
#endif /* __cplusplus */


/******************************************************************************
 * Types
 *****************************************************************************/

/* object input and output indexes */
/*TGenSectionStart_VoiceIndexes*/
typedef enum
{   

    rwaVOICEIDXIN_FREQ = 0,
    rwaVOICEIDXIN_GAIN = 1,
    rwaVOICEIDXIN_TRIGGER = 2,
    rwaVOICEIDXIN_WAVEPOS = 3,
    rwaVOICEIDXIN_LOOP = 4,
    rwaVOICEIDXIN_WAVE = 5,
    rwaVOICEIDXIN_PAN = 6,
    rwaVOICEIDXIN_FORCEENUMSIZEINT = RWFORCEENUMSIZEINT
} rwaVOICEIDXIN;

typedef enum
{

    rwaVOICEIDXOUT_FREQ = 0,
    rwaVOICEIDXOUT_GAIN = 1,
    rwaVOICEIDXOUT_PLAYING = 2,
    rwaVOICEIDXOUT_WAVEPOS = 3,
    rwaVOICEIDXOUT_LOOP = 4,
    rwaVOICEIDXOUT_WAVE = 5,
    rwaVOICEIDXOUT_PAN = 6,
    rwaVOICEIDXOUT_ISSTEREO = 7,
    rwaVOICEIDXOUT_FORCEENUMSIZEINT = RWFORCEENUMSIZEINT
} rwaVOICEIDXOUT;
/*TGenSectionFinish_VoiceIndexes*/

/******************************************************************************
 * Functions
 *****************************************************************************/

#ifdef RWADEBUG
#if !defined (RWADOXYGEN)
#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */

/*TGenSectionStart_VoiceSet0*/
RwaObjHandle* RwaVoiceSetFreq( RwaObjHandle *objHandle, RwInt32 value);
/*TGenSectionFinish_VoiceSet0*/
/*TGenSectionStart_VoiceGet0*/
RwInt32 RwaVoiceGetFreq( RwaObjHandle *object );
/*TGenSectionFinish_VoiceGet0*/
/*TGenSectionStart_VoiceSet1*/
RwaObjHandle* RwaVoiceSetGain( RwaObjHandle *objHandle, RwReal value);
/*TGenSectionFinish_VoiceSet1*/
/*TGenSectionStart_VoiceGet1*/
RwReal RwaVoiceGetGain( RwaObjHandle *object );
/*TGenSectionFinish_VoiceGet1*/
/*TGenSectionStart_VoiceSet2*/
RwaObjHandle* RwaVoiceSetTrigger( RwaObjHandle *objHandle, RwBool value);
/*TGenSectionFinish_VoiceSet2*/
/*TGenSectionStart_VoiceGet2*/
RwBool RwaVoiceGetPlaying( RwaObjHandle *object );
/*TGenSectionFinish_VoiceGet2*/
/*TGenSectionStart_VoiceSet3*/
RwaObjHandle* RwaVoiceSetWavePos( RwaObjHandle *objHandle, RwUInt32 value);
/*TGenSectionFinish_VoiceSet3*/
/*TGenSectionStart_VoiceGet3*/
RwUInt32 RwaVoiceGetWavePos( RwaObjHandle *object );
/*TGenSectionFinish_VoiceGet3*/
/*TGenSectionStart_VoiceSet4*/
RwaObjHandle* RwaVoiceSetLoop( RwaObjHandle *objHandle, RwBool value);
/*TGenSectionFinish_VoiceSet4*/
/*TGenSectionStart_VoiceGet4*/
RwBool RwaVoiceGetLoop( RwaObjHandle *object );
/*TGenSectionFinish_VoiceGet4*/
/*TGenSectionStart_VoiceSet5*/
RwaObjHandle* RwaVoiceSetWave( RwaObjHandle *objHandle, RwaWave *data );
/*TGenSectionFinish_VoiceSet5*/
/*TGenSectionStart_VoiceGet5*/
RwaObjHandle* RwaVoiceGetWave( RwaObjHandle *object, RwaWave *data );
/*TGenSectionFinish_VoiceGet5*/
/*TGenSectionStart_VoiceSet6*/
RwaObjHandle* RwaVoiceSetPan( RwaObjHandle *objHandle, RwReal value);
/*TGenSectionFinish_VoiceSet6*/
/*TGenSectionStart_VoiceGet6*/
RwReal RwaVoiceGetPan( RwaObjHandle *object );
/*TGenSectionFinish_VoiceGet6*/
/*TGenSectionStart_VoiceGet7*/
RwaObjHandle* RwaVoiceGetIsStereo( RwaObjHandle *object, RwBool *data );
/*TGenSectionFinish_VoiceGet7*/
#ifdef    __cplusplus
}
#endif /* __cplusplus */
#endif /* RWADOXYGEN */
#else
/*-----------------------------------------------------------------------------
 - Set parameter and get parameter functions and macros
 ----------------------------------------------------------------------------*/

/*TGenSectionStart_VoiceSet0Macro*/
#define RwaVoiceSetFreq(_object, _value) \
            RwaObjectSetParamInt32(_object, \
                rwaVOICEIDXIN_FREQ, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_VoiceSet0Macro*/
/*TGenSectionStart_VoiceGet0Macro*/
#define RwaVoiceGetFreq(_object) \
            RwaObjectGetParamInt32(_object, \
                rwaVOICEIDXOUT_FREQ, rwaIOPARAM_OUTPUT, (RwBool*)NULL)
/*TGenSectionFinish_VoiceGet0Macro*/
/*TGenSectionStart_VoiceSet1Macro*/
#define RwaVoiceSetGain(_object, _value) \
            RwaObjectSetParamReal(_object, \
                rwaVOICEIDXIN_GAIN, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_VoiceSet1Macro*/
/*TGenSectionStart_VoiceGet1Macro*/
#define RwaVoiceGetGain(_object) \
            RwaObjectGetParamReal(_object, \
                rwaVOICEIDXOUT_GAIN, rwaIOPARAM_OUTPUT, (RwBool*)NULL)
/*TGenSectionFinish_VoiceGet1Macro*/
/*TGenSectionStart_VoiceSet2Macro*/
#define RwaVoiceSetTrigger(_object, _value) \
            RwaObjectSetParamBool(_object, \
                rwaVOICEIDXIN_TRIGGER, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_VoiceSet2Macro*/
/*TGenSectionStart_VoiceGet2Macro*/
#define RwaVoiceGetPlaying(_object) \
            RwaObjectGetParamBool(_object, \
                rwaVOICEIDXOUT_PLAYING, rwaIOPARAM_OUTPUT, (RwBool*)NULL)
/*TGenSectionFinish_VoiceGet2Macro*/
/*TGenSectionStart_VoiceSet3Macro*/
#define RwaVoiceSetWavePos(_object, _value) \
            RwaObjectSetParamUInt32(_object, \
                rwaVOICEIDXIN_WAVEPOS, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_VoiceSet3Macro*/
/*TGenSectionStart_VoiceGet3Macro*/
#define RwaVoiceGetWavePos(_object) \
            RwaObjectGetParamUInt32(_object, \
                rwaVOICEIDXOUT_WAVEPOS, rwaIOPARAM_OUTPUT, (RwBool*)NULL)
/*TGenSectionFinish_VoiceGet3Macro*/
/*TGenSectionStart_VoiceSet4Macro*/
#define RwaVoiceSetLoop(_object, _value) \
            RwaObjectSetParamBool(_object, \
                rwaVOICEIDXIN_LOOP, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_VoiceSet4Macro*/
/*TGenSectionStart_VoiceGet4Macro*/
#define RwaVoiceGetLoop(_object) \
            RwaObjectGetParamBool(_object, \
                rwaVOICEIDXOUT_LOOP, rwaIOPARAM_OUTPUT, (RwBool*)NULL)
/*TGenSectionFinish_VoiceGet4Macro*/
/*TGenSectionStart_VoiceSet5Macro*/
#define RwaVoiceSetWave(_object, _ptr) \
            RwaObjectSetParamData(_object, \
                rwaVOICEIDXIN_WAVE, rwaIOPARAM_INPUT, &_ptr)
/*TGenSectionFinish_VoiceSet5Macro*/
/*TGenSectionStart_VoiceGet5Macro*/
#define RwaVoiceGetWave(_object, _ptr) \
            RwaObjectGetParamData(_object, \
                rwaVOICEIDXOUT_WAVE, rwaIOPARAM_OUTPUT, _ptr)
/*TGenSectionFinish_VoiceGet5Macro*/
/*TGenSectionStart_VoiceSet6Macro*/
#define RwaVoiceSetPan(_object, _value) \
            RwaObjectSetParamReal(_object, \
                rwaVOICEIDXIN_PAN, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_VoiceSet6Macro*/
/*TGenSectionStart_VoiceGet6Macro*/
#define RwaVoiceGetPan(_object) \
            RwaObjectGetParamReal(_object, \
                rwaVOICEIDXOUT_PAN, rwaIOPARAM_OUTPUT, (RwBool*)NULL)
/*TGenSectionFinish_VoiceGet6Macro*/
/*TGenSectionStart_VoiceGet7Macro*/
#define RwaVoiceGetIsStereo(_object, _ptr) \
            RwaObjectGetParamData(_object, \
                rwaVOICEIDXOUT_ISSTEREO, rwaIOPARAM_OUTPUT, _ptr)
/*TGenSectionFinish_VoiceGet7Macro*/
#endif /* RWADEBUG */


#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */

/* register Voice object interface definition */
/*TGenSectionStart_VoiceInterfaceRegister*/
RwaObjInterfaceDef* RwaVoiceInterfaceRegister(void);
/*TGenSectionFinish_VoiceInterfaceRegister*/

#ifdef    __cplusplus
}
#endif /* __cplusplus */


/*--- Automatically derived from: d:/dev/rwa/source/interfaces/src/rwavoice3d.h ---*/


/******************************************************************************
 * Defines/Macros & Constants
 *****************************************************************************/

/*TGenSectionStart_Voice3DInterfaceName*/
/* object interface's name */
#ifdef RWADEBUG
#define rwaVOICE3DINTERFACENAME "Voice3D Interface"
#else
#define rwaVOICE3DINTERFACENAME ""
#endif /* RWADEBUG */
/*TGenSectionFinish_Voice3DInterfaceName*/

/*TGenSectionStart_Voice3DParameterNames*/
/* object interface's parameter names */
#ifdef RWADEBUG

#define rwaVOICE3DNAMEI_POS "PosI" 
#define rwaVOICE3DNAMEO_POS "PosO" 
#define rwaVOICE3DNAMEI_VEL "VelI" 
#define rwaVOICE3DNAMEO_VEL "VelO" 
#define rwaVOICE3DNAMEI_MINDISTANCE "MinDistanceI" 
#define rwaVOICE3DNAMEO_MINDISTANCE "MinDistanceO" 
#define rwaVOICE3DNAMEI_MAXDISTANCE "MaxDistanceI" 
#define rwaVOICE3DNAMEO_MAXDISTANCE "MaxDistanceO" 
#else

#define rwaVOICE3DNAMEI_POS "" 
#define rwaVOICE3DNAMEO_POS "" 
#define rwaVOICE3DNAMEI_VEL "" 
#define rwaVOICE3DNAMEO_VEL "" 
#define rwaVOICE3DNAMEI_MINDISTANCE "" 
#define rwaVOICE3DNAMEO_MINDISTANCE "" 
#define rwaVOICE3DNAMEI_MAXDISTANCE "" 
#define rwaVOICE3DNAMEO_MAXDISTANCE "" 
#endif /* RWADEBUG */
/*TGenSectionFinish_Voice3DParameterNames*/

#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */

/*TGenSectionStart_Voice3DInterfaceUUID*/
extern const RwaUUID rwaVOICE3DINTERFACEID;  /* object interface's UUID */
/*TGenSectionFinish_Voice3DInterfaceUUID*/

/*----------------------------------------------------------------------------
 - object interface's input and output UUIDs
 ---------------------------------------------------------------------------*/
/*TGenSectionStart_Voice3DParameterUUIDs*/
extern const RwaUUID rwaVOICE3DIDI_POS;
extern const RwaUUID rwaVOICE3DIDO_POS;
extern const RwaUUID rwaVOICE3DIDI_VEL;
extern const RwaUUID rwaVOICE3DIDO_VEL;
extern const RwaUUID rwaVOICE3DIDI_MINDISTANCE;
extern const RwaUUID rwaVOICE3DIDO_MINDISTANCE;
extern const RwaUUID rwaVOICE3DIDI_MAXDISTANCE;
extern const RwaUUID rwaVOICE3DIDO_MAXDISTANCE;

/*TGenSectionFinish_Voice3DParameterUUIDs*/

#ifdef    __cplusplus
}
#endif /* __cplusplus */


/******************************************************************************
 * Types
 *****************************************************************************/

/* object input and output indexes */
/*TGenSectionStart_Voice3DIndexes*/
typedef enum
{   

    rwaVOICE3DIDXIN_POS = 0,
    rwaVOICE3DIDXIN_VEL = 1,
    rwaVOICE3DIDXIN_MINDISTANCE = 2,
    rwaVOICE3DIDXIN_MAXDISTANCE = 3,
    rwaVOICE3DIDXIN_FORCEENUMSIZEINT = RWFORCEENUMSIZEINT
} rwaVOICE3DIDXIN;

typedef enum
{

    rwaVOICE3DIDXOUT_POS = 0,
    rwaVOICE3DIDXOUT_VEL = 1,
    rwaVOICE3DIDXOUT_MINDISTANCE = 2,
    rwaVOICE3DIDXOUT_MAXDISTANCE = 3,
    rwaVOICE3DIDXOUT_FORCEENUMSIZEINT = RWFORCEENUMSIZEINT
} rwaVOICE3DIDXOUT;
/*TGenSectionFinish_Voice3DIndexes*/

/******************************************************************************
 * Functions
 *****************************************************************************/

#ifdef RWADEBUG
#if !defined (RWADOXYGEN)
#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */

/*TGenSectionStart_Voice3DSet0*/
RwaObjHandle* RwaVoice3DSetPos( RwaObjHandle *objHandle, RwV3d *data );
/*TGenSectionFinish_Voice3DSet0*/
/*TGenSectionStart_Voice3DGet0*/
RwaObjHandle* RwaVoice3DGetPos( RwaObjHandle *object, RwV3d *data );
/*TGenSectionFinish_Voice3DGet0*/
/*TGenSectionStart_Voice3DSet1*/
RwaObjHandle* RwaVoice3DSetVel( RwaObjHandle *objHandle, RwV3d *data );
/*TGenSectionFinish_Voice3DSet1*/
/*TGenSectionStart_Voice3DGet1*/
RwaObjHandle* RwaVoice3DGetVel( RwaObjHandle *object, RwV3d *data );
/*TGenSectionFinish_Voice3DGet1*/
/*TGenSectionStart_Voice3DSet2*/
RwaObjHandle* RwaVoice3DSetMinDistance( RwaObjHandle *objHandle, RwReal value);
/*TGenSectionFinish_Voice3DSet2*/
/*TGenSectionStart_Voice3DGet2*/
RwReal RwaVoice3DGetMinDistance( RwaObjHandle *object );
/*TGenSectionFinish_Voice3DGet2*/
/*TGenSectionStart_Voice3DSet3*/
RwaObjHandle* RwaVoice3DSetMaxDistance( RwaObjHandle *objHandle, RwReal value);
/*TGenSectionFinish_Voice3DSet3*/
/*TGenSectionStart_Voice3DGet3*/
RwReal RwaVoice3DGetMaxDistance( RwaObjHandle *object );
/*TGenSectionFinish_Voice3DGet3*/
#ifdef    __cplusplus
}
#endif /* __cplusplus */
#endif /* RWADOXYGEN */
#else
/*-----------------------------------------------------------------------------
 - Set parameter and get parameter functions and macros
 ----------------------------------------------------------------------------*/

/*TGenSectionStart_Voice3DSet0Macro*/
#define RwaVoice3DSetPos(_object, _ptr) \
            RwaObjectSetParamData(_object, \
                rwaVOICE3DIDXIN_POS, rwaIOPARAM_INPUT, _ptr)
/*TGenSectionFinish_Voice3DSet0Macro*/
/*TGenSectionStart_Voice3DGet0Macro*/
#define RwaVoice3DGetPos(_object, _ptr) \
            RwaObjectGetParamData(_object, \
                rwaVOICE3DIDXOUT_POS, rwaIOPARAM_OUTPUT, _ptr)
/*TGenSectionFinish_Voice3DGet0Macro*/
/*TGenSectionStart_Voice3DSet1Macro*/
#define RwaVoice3DSetVel(_object, _ptr) \
            RwaObjectSetParamData(_object, \
                rwaVOICE3DIDXIN_VEL, rwaIOPARAM_INPUT, _ptr)
/*TGenSectionFinish_Voice3DSet1Macro*/
/*TGenSectionStart_Voice3DGet1Macro*/
#define RwaVoice3DGetVel(_object, _ptr) \
            RwaObjectGetParamData(_object, \
                rwaVOICE3DIDXOUT_VEL, rwaIOPARAM_OUTPUT, _ptr)
/*TGenSectionFinish_Voice3DGet1Macro*/
/*TGenSectionStart_Voice3DSet2Macro*/
#define RwaVoice3DSetMinDistance(_object, _value) \
            RwaObjectSetParamReal(_object, \
                rwaVOICE3DIDXIN_MINDISTANCE, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_Voice3DSet2Macro*/
/*TGenSectionStart_Voice3DGet2Macro*/
#define RwaVoice3DGetMinDistance(_object) \
            RwaObjectGetParamReal(_object, \
                rwaVOICE3DIDXOUT_MINDISTANCE, rwaIOPARAM_OUTPUT, (RwBool*)NULL)
/*TGenSectionFinish_Voice3DGet2Macro*/
/*TGenSectionStart_Voice3DSet3Macro*/
#define RwaVoice3DSetMaxDistance(_object, _value) \
            RwaObjectSetParamReal(_object, \
                rwaVOICE3DIDXIN_MAXDISTANCE, rwaIOPARAM_INPUT, _value)
/*TGenSectionFinish_Voice3DSet3Macro*/
/*TGenSectionStart_Voice3DGet3Macro*/
#define RwaVoice3DGetMaxDistance(_object) \
            RwaObjectGetParamReal(_object, \
                rwaVOICE3DIDXOUT_MAXDISTANCE, rwaIOPARAM_OUTPUT, (RwBool*)NULL)
/*TGenSectionFinish_Voice3DGet3Macro*/
#endif /* RWADEBUG */


#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */

/* register Voice3D object interface definition */
/*TGenSectionStart_Voice3DInterfaceRegister*/
RwaObjInterfaceDef* RwaVoice3DInterfaceRegister(void);
/*TGenSectionFinish_Voice3DInterfaceRegister*/

#ifdef    __cplusplus
}
#endif /* __cplusplus */


/*--- Automatically derived from: d:/dev/rwa/source/interfaces/src/rwaoutput.h ---*/

/******************************************************************************
 * Defines/Macros & Constants
 *****************************************************************************/

/* object interface's name */
#ifdef RWADEBUG
#define rwaOUTPUTINTERFACENAME "Output Interface"
#else
#define rwaOUTPUTINTERFACENAME ""
#endif /* RWADEBUG */

/* object interface's parameter names */
#ifdef RWADEBUG

#define rwaOUTPUTNAMEI_GAIN "GainI" 
#define rwaOUTPUTNAMEO_GAIN "GainO" 
#define rwaOUTPUTNAMEI_LISTENERPOS "ListenerPosI" 
#define rwaOUTPUTNAMEO_LISTENERPOS "ListenerPosO" 
#define rwaOUTPUTNAMEI_LISTENERVEL "ListenerVelI" 
#define rwaOUTPUTNAMEO_LISTENERVEL "ListenerVelO" 
#define rwaOUTPUTNAMEI_LISTENERUP "ListenerUpI" 
#define rwaOUTPUTNAMEO_LISTENERUP "ListenerUpO" 
#define rwaOUTPUTNAMEI_LISTENERAT "ListenerAtI" 
#define rwaOUTPUTNAMEO_LISTENERAT "ListenerAtO" 
#define rwaOUTPUTNAMEI_DOPPLERSCALE "DopplerScaleI" 
#define rwaOUTPUTNAMEO_DOPPLERSCALE "DopplerScaleO" 
#define rwaOUTPUTNAMEI_DISTANCEFACTOR "DistanceFactorI" 
#define rwaOUTPUTNAMEO_DISTANCEFACTOR "DistanceFactorO" 
#define rwaOUTPUTNAMEI_ROLLOFFFACTOR "RolloffFactorI" 
#define rwaOUTPUTNAMEO_ROLLOFFFACTOR "RolloffFactorO" 
#define rwaOUTPUTNAMEI_REVERBTYPE "ReverbTypeI" 
#define rwaOUTPUTNAMEO_REVERBTYPE "ReverbTypeO" 
#define rwaOUTPUTNAMEI_REVERBGAIN "ReverbGainI" 
#define rwaOUTPUTNAMEO_REVERBGAIN "ReverbGainO" 
#define rwaOUTPUTNAMEI_SPEAKERCONFIG "SpeakerConfigI" 
#define rwaOUTPUTNAMEO_SPEAKERCONFIG "SpeakerConfigO" 
#else

#define rwaOUTPUTNAMEI_GAIN "" 
#define rwaOUTPUTNAMEO_GAIN "" 
#define rwaOUTPUTNAMEI_LISTENERPOS "" 
#define rwaOUTPUTNAMEO_LISTENERPOS "" 
#define rwaOUTPUTNAMEI_LISTENERVEL "" 
#define rwaOUTPUTNAMEO_LISTENERVEL "" 
#define rwaOUTPUTNAMEI_LISTENERUP "" 
#define rwaOUTPUTNAMEO_LISTENERUP "" 
#define rwaOUTPUTNAMEI_LISTENERAT "" 
#define rwaOUTPUTNAMEO_LISTENERAT "" 
#define rwaOUTPUTNAMEI_DOPPLERSCALE "" 
#define rwaOUTPUTNAMEO_DOPPLERSCALE "" 
#define rwaOUTPUTNAMEI_DISTANCEFACTOR "" 
#define rwaOUTPUTNAMEO_DISTANCEFACTOR "" 
#define rwaOUTPUTNAMEI_ROLLOFFFACTOR "" 
#define rwaOUTPUTNAMEO_ROLLOFFFACTOR "" 
#define rwaOUTPUTNAMEI_REVERBTYPE "" 
#define rwaOUTPUTNAMEO_REVERBTYPE "" 
#define rwaOUTPUTNAMEI_REVERBGAIN "" 
#define rwaOUTPUTNAMEO_REVERBGAIN "" 
#define rwaOUTPUTNAMEI_SPEAKERCONFIG "" 
#define rwaOUTPUTNAMEO_SPEAKERCONFIG "" 
#endif /* RWADEBUG */

#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */

extern const RwaUUID rwaOUTPUTINTERFACEID;  /* object interface's UUID */
 
/*----------------------------------------------------------------------------
 - object interface's input and output UUIDs
 ---------------------------------------------------------------------------*/
extern const RwaUUID rwaOUTPUTIDI_GAIN;
extern const RwaUUID rwaOUTPUTIDO_GAIN;
extern const RwaUUID rwaOUTPUTIDI_LISTENERPOS;
extern const RwaUUID rwaOUTPUTIDO_LISTENERPOS;
extern const RwaUUID rwaOUTPUTIDI_LISTENERVEL;
extern const RwaUUID rwaOUTPUTIDO_LISTENERVEL;
extern const RwaUUID rwaOUTPUTIDI_LISTENERUP;
extern const RwaUUID rwaOUTPUTIDO_LISTENERUP;
extern const RwaUUID rwaOUTPUTIDI_LISTENERAT;
extern const RwaUUID rwaOUTPUTIDO_LISTENERAT;
extern const RwaUUID rwaOUTPUTIDI_DOPPLERSCALE;
extern const RwaUUID rwaOUTPUTIDO_DOPPLERSCALE;
extern const RwaUUID rwaOUTPUTIDI_DISTANCEFACTOR;
extern const RwaUUID rwaOUTPUTIDO_DISTANCEFACTOR;
extern const RwaUUID rwaOUTPUTIDI_ROLLOFFFACTOR;
extern const RwaUUID rwaOUTPUTIDO_ROLLOFFFACTOR;
extern const RwaUUID rwaOUTPUTIDI_REVERBTYPE;
extern const RwaUUID rwaOUTPUTIDO_REVERBTYPE;
extern const RwaUUID rwaOUTPUTIDI_REVERBGAIN;
extern const RwaUUID rwaOUTPUTIDO_REVERBGAIN;
extern const RwaUUID rwaOUTPUTIDI_SPEAKERCONFIG;
extern const RwaUUID rwaOUTPUTIDO_SPEAKERCONFIG;


#ifdef    __cplusplus
}
#endif /* __cplusplus */


/******************************************************************************
 * Types
 *****************************************************************************/

/** 
 * \ingroup rwaoutputinterface
 * Reverb enviornment setting.
 */
enum RwaEnvironment
{
    rwaNAENVIRONMENT = 0,              /**<Invalid           */
    rwaENVIRONMENT_OFF,                /**<off*/
    rwaENVIRONMENT_GENERIC,            /**<Generic           */
    rwaENVIRONMENT_PADDEDCELL,         /**<Padded cell       */
    rwaENVIRONMENT_ROOM,               /**<Room              */
    rwaENVIRONMENT_BATHROOM,           /**<Bathroom          */
    rwaENVIRONMENT_LIVINGROOM,         /**<Living Room       */
    rwaENVIRONMENT_STONEROOM,          /**<Stone Room        */
    rwaENVIRONMENT_AUDITORIUM,         /**<Auditorium        */
    rwaENVIRONMENT_CONCERTHALL,        /**<Concert Hall      */
    rwaENVIRONMENT_CAVE,               /**<Cave              */
    rwaENVIRONMENT_ARENA,              /**<Arena             */
    rwaENVIRONMENT_HANGAR,             /**<Hanger            */
    rwaENVIRONMENT_CARPETEDHALLWAY,    /**<Carpeted Hallway  */
    rwaENVIRONMENT_HALLWAY,            /**<Hallway           */
    rwaENVIRONMENT_STONECORRIDOR,      /**<Stone Corridor    */
    rwaENVIRONMENT_ALLEY,              /**<Alley             */
    rwaENVIRONMENT_FOREST,             /**<Forest            */
    rwaENVIRONMENT_CITY,               /**<City              */
    rwaENVIRONMENT_MOUNTAINS,          /**<Mountains         */
    rwaENVIRONMENT_QUARRY,             /**<Quarry            */
    rwaENVIRONMENT_PLAIN,              /**<Plain             */
    rwaENVIRONMENT_PARKINGLOT,         /**<Parking lot       */
    rwaENVIRONMENT_SEWERPIPE,          /**<Sewer Pipe        */
    rwaENVIRONMENT_UNDERWATER,         /**<Underwater        */
    rwaENVIRONMENT_SILENT,             /**<Silent            */
    rwaENVIRONMENT_SMALLROOM,          /**<Small Room        */
    rwaENVIRONMENT_MEDIUMROOM,         /**<Medium Room       */
    rwaENVIRONMENT_LARGEROOM,          /**<Large Room        */
    rwaENVIRONMENT_MEDIUMHALL,         /**<Medium Hall       */
    rwaENVIRONMENT_LARGEHALL,          /**<Large Hall        */
    rwaENVIRONMENT_PLATE,              /**<Plate             */
    rwaENVIRONMENT_MAX,
    rwaENVIRONMENT_FORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RwaEnvironment RwaEnvironment;


/** 
 * \ingroup rwaoutputinterface
 * Speaker configurations.
 */
enum RwaSpeakerConfig
{
    rwaNASPEAKERCONFIG = 0,              
    rwaSPEAKERCONFIG_STEREO,             /**<Stereo*/
    rwaSPEAKERCONFIG_MONO,               /**<Mono */
    rwaSPEAKERCONFIG_HEADPHONES,         /**<Headphones */
    rwaSPEAKERCONFIG_5POINT1,            /**<5 Point 1 Digital out */
    rwaSPEAKERCONFIG_FORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RwaSpeakerConfig RwaSpeakerConfig;


/* object input and output indexes */
typedef enum
{   

    rwaOUTPUTIDXIN_GAIN = 0,
    rwaOUTPUTIDXIN_LISTENERPOS = 1,
    rwaOUTPUTIDXIN_LISTENERVEL = 2,
    rwaOUTPUTIDXIN_LISTENERUP = 3,
    rwaOUTPUTIDXIN_LISTENERAT = 4,
    rwaOUTPUTIDXIN_DOPPLERSCALE = 5,
    rwaOUTPUTIDXIN_DISTANCEFACTOR = 6,
    rwaOUTPUTIDXIN_ROLLOFFFACTOR = 7,
    rwaOUTPUTIDXIN_REVERBTYPE = 8,
    rwaOUTPUTIDXIN_REVERBGAIN = 9,
    rwaOUTPUTIDXIN_SPEAKERCONFIG = 10,
    rwaOUTPUTIDXIN_FORCEENUMSIZEINT = RWFORCEENUMSIZEINT
} rwaOUTPUTIDXIN;

typedef enum
{

    rwaOUTPUTIDXOUT_GAIN = 0,
    rwaOUTPUTIDXOUT_LISTENERPOS = 1,
    rwaOUTPUTIDXOUT_LISTENERVEL = 2,
    rwaOUTPUTIDXOUT_LISTENERUP = 3,
    rwaOUTPUTIDXOUT_LISTENERAT = 4,
    rwaOUTPUTIDXOUT_DOPPLERSCALE = 5,
    rwaOUTPUTIDXOUT_DISTANCEFACTOR = 6,
    rwaOUTPUTIDXOUT_ROLLOFFFACTOR = 7,
    rwaOUTPUTIDXOUT_REVERBTYPE = 8,
    rwaOUTPUTIDXOUT_REVERBGAIN = 9,
    rwaOUTPUTIDXOUT_SPEAKERCONFIG = 10,
    rwaOUTPUTIDXOUT_FORCEENUMSIZEINT = RWFORCEENUMSIZEINT
} rwaOUTPUTIDXOUT;



#ifdef RWADEBUG
#if !defined (RWADOXYGEN)
#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */

RwaObjHandle   *RwaOutputSetGain           ( RwaObjHandle *objHandle, RwReal value);
RwReal          RwaOutputGetGain           ( RwaObjHandle *object );
RwaObjHandle   *RwaOutputSetListenerPos    ( RwaObjHandle *objHandle, RwV3d *data );
RwaObjHandle   *RwaOutputGetListenerPos    ( RwaObjHandle *object,    RwV3d *data );
RwaObjHandle   *RwaOutputSetListenerVel    ( RwaObjHandle *objHandle, RwV3d *data );
RwaObjHandle   *RwaOutputGetListenerVel    ( RwaObjHandle *object,    RwV3d *data );
RwaObjHandle   *RwaOutputSetListenerUp     ( RwaObjHandle *objHandle, RwV3d *data );
RwaObjHandle   *RwaOutputGetListenerUp     ( RwaObjHandle *object,    RwV3d *data );
RwaObjHandle   *RwaOutputSetListenerAt     ( RwaObjHandle *objHandle, RwV3d *data );
RwaObjHandle   *RwaOutputGetListenerAt     ( RwaObjHandle *object,    RwV3d *data );
RwaObjHandle   *RwaOutputSetDopplerScale   ( RwaObjHandle *objHandle, RwReal value);
RwReal          RwaOutputGetDopplerScale   ( RwaObjHandle *object );
RwaObjHandle   *RwaOutputSetDistanceFactor ( RwaObjHandle *objHandle, RwReal value);
RwReal          RwaOutputGetDistanceFactor ( RwaObjHandle *object );
RwaObjHandle   *RwaOutputSetRolloffFactor  ( RwaObjHandle *objHandle, RwReal value);
RwReal          RwaOutputGetRolloffFactor  ( RwaObjHandle *object );
RwaObjHandle   *RwaOutputSetReverbType     ( RwaObjHandle *objHandle, RwaEnvironment value);
RwaEnvironment  RwaOutputGetReverbType     ( RwaObjHandle *object );
RwaObjHandle   *RwaOutputSetReverbGain     ( RwaObjHandle *objHandle, RwReal value);
RwReal          RwaOutputGetReverbGain     ( RwaObjHandle *object );
RwaObjHandle   *RwaOutputSetSpeakerConfig  ( RwaObjHandle *objHandle, RwaSpeakerConfig value);
RwaSpeakerConfig RwaOutputGetSpeakerConfig ( RwaObjHandle *object );

#ifdef    __cplusplus
}
#endif /* __cplusplus */
#endif /* RWADOXYGEN */
#else
/*-----------------------------------------------------------------------------
 - Set parameter and get parameter functions and macros
 ----------------------------------------------------------------------------*/

#define RwaOutputSetGain(_object, _value) \
            RwaObjectSetParamReal(_object, \
                rwaOUTPUTIDXIN_GAIN, rwaIOPARAM_INPUT, _value)
#define RwaOutputGetGain(_object) \
            RwaObjectGetParamReal(_object, \
                rwaOUTPUTIDXOUT_GAIN, rwaIOPARAM_OUTPUT, (RwBool*)NULL)
#define RwaOutputSetListenerPos(_object, _ptr) \
            RwaObjectSetParamData(_object, \
                rwaOUTPUTIDXIN_LISTENERPOS, rwaIOPARAM_INPUT, _ptr)
#define RwaOutputGetListenerPos(_object, _ptr) \
            RwaObjectGetParamData(_object, \
                rwaOUTPUTIDXOUT_LISTENERPOS, rwaIOPARAM_OUTPUT, _ptr)
#define RwaOutputSetListenerVel(_object, _ptr) \
            RwaObjectSetParamData(_object, \
                rwaOUTPUTIDXIN_LISTENERVEL, rwaIOPARAM_INPUT, _ptr)
#define RwaOutputGetListenerVel(_object, _ptr) \
            RwaObjectGetParamData(_object, \
                rwaOUTPUTIDXOUT_LISTENERVEL, rwaIOPARAM_OUTPUT, _ptr)
#define RwaOutputSetListenerUp(_object, _ptr) \
            RwaObjectSetParamData(_object, \
                rwaOUTPUTIDXIN_LISTENERUP, rwaIOPARAM_INPUT, _ptr)
#define RwaOutputGetListenerUp(_object, _ptr) \
            RwaObjectGetParamData(_object, \
                rwaOUTPUTIDXOUT_LISTENERUP, rwaIOPARAM_OUTPUT, _ptr)
#define RwaOutputSetListenerAt(_object, _ptr) \
            RwaObjectSetParamData(_object, \
                rwaOUTPUTIDXIN_LISTENERAT, rwaIOPARAM_INPUT, _ptr)
#define RwaOutputGetListenerAt(_object, _ptr) \
            RwaObjectGetParamData(_object, \
                rwaOUTPUTIDXOUT_LISTENERAT, rwaIOPARAM_OUTPUT, _ptr)
#define RwaOutputSetDopplerScale(_object, _value) \
            RwaObjectSetParamReal(_object, \
                rwaOUTPUTIDXIN_DOPPLERSCALE, rwaIOPARAM_INPUT, _value)
#define RwaOutputGetDopplerScale(_object) \
            RwaObjectGetParamReal(_object, \
                rwaOUTPUTIDXOUT_DOPPLERSCALE, rwaIOPARAM_OUTPUT, (RwBool*)NULL)
#define RwaOutputSetDistanceFactor(_object, _value) \
            RwaObjectSetParamReal(_object, \
                rwaOUTPUTIDXIN_DISTANCEFACTOR, rwaIOPARAM_INPUT, _value)
#define RwaOutputGetDistanceFactor(_object) \
            RwaObjectGetParamReal(_object, \
                rwaOUTPUTIDXOUT_DISTANCEFACTOR, rwaIOPARAM_OUTPUT, (RwBool*)NULL)
#define RwaOutputSetRolloffFactor(_object, _value) \
            RwaObjectSetParamReal(_object, \
                rwaOUTPUTIDXIN_ROLLOFFFACTOR, rwaIOPARAM_INPUT, _value)
#define RwaOutputGetRolloffFactor(_object) \
            RwaObjectGetParamReal(_object, \
                rwaOUTPUTIDXOUT_ROLLOFFFACTOR, rwaIOPARAM_OUTPUT, (RwBool*)NULL)
#define RwaOutputSetReverbType(_object, _value) \
            RwaObjectSetParamInt32(_object, \
                rwaOUTPUTIDXIN_REVERBTYPE, rwaIOPARAM_INPUT, (RwInt32)_value)
#define RwaOutputGetReverbType(_object) \
            (RwaEnvironment)RwaObjectGetParamInt32(_object, \
                rwaOUTPUTIDXOUT_REVERBTYPE, rwaIOPARAM_OUTPUT, (RwBool*)NULL)
#define RwaOutputSetReverbGain(_object, _value) \
            RwaObjectSetParamReal(_object, \
                rwaOUTPUTIDXIN_REVERBGAIN, rwaIOPARAM_INPUT, _value)
#define RwaOutputGetReverbGain(_object) \
            RwaObjectGetParamReal(_object, \
                rwaOUTPUTIDXOUT_REVERBGAIN, rwaIOPARAM_OUTPUT, (RwBool*)NULL)
#define RwaOutputSetSpeakerConfig(_object, _value) \
            RwaObjectSetParamInt32(_object, \
                rwaOUTPUTIDXIN_SPEAKERCONFIG, rwaIOPARAM_INPUT, (RwInt32)_value)
#define RwaOutputGetSpeakerConfig(_object) \
            (RwaSpeakerConfig)RwaObjectGetParamInt32(_object, \
                rwaOUTPUTIDXOUT_SPEAKERCONFIG, rwaIOPARAM_OUTPUT, (RwBool*)NULL)
#endif /* RWADEBUG */

/******************************************************************************
 * Functions
 *****************************************************************************/

#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */

/* register Output object interface definition */
RwaObjInterfaceDef* RwaOutputInterfaceRegister(void);

#ifdef    __cplusplus
}
#endif /* __cplusplus */

#endif /* RWACORE_H */
