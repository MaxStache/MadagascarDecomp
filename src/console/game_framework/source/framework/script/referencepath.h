#ifndef __REFERENCEPATH__
#define __REFERENCEPATH__

#include "scriptreference.h"
#include "opcode.h"

namespace Script
{
    // GLOBAL: GAME 0x00621f10
    ScriptReference *gSenderRef;
    // GLOBAL: GAME 0x00621f14
    ScriptReference *gSelfRef;
    // GLOBAL: GAME 0x00621f1c
    ScriptReference *gEachRef;
    // GLOBAL: GAME 0x00621f20
    ScriptReference *gFoundRef;
    // GLOBAL: GAME 0x00621f2c
    ScriptReference *gControllerRef;
    // GLOBAL: GAME 0x00622004
    ScriptReference *gSubsetRef;

    class ReferencePath
    {
    public:
        RwUInt32 raw;

        // FUNCTION: GAME 0x0043c5a0
        void Resolve(void **ppOwner, ScriptReference **ppSet, bool flag)
        {
            void **ppvVar1;
            ReferencePath *pRVar2;
            RwUInt32 symbol;
            int *userReferenceProto;
            ScriptReference *pCur;
            ScriptReference *pValue;
            ScriptReference *pSVar3;
            int iVar4;
            RwUInt32 scope;
            int local_8;
            ReferencePath *self_copy;
            ScriptReference_vtbl *curVtable;

            pCur = gControllerRef;
            symbol = this->raw >> 0xe;
            scope = this->raw >> 6 & 3;
            self_copy = this;
            switch (symbol)
            {
            case 0x3fffa:
                pCur = gFoundRef;
                goto LAB_0043c66a;
            case 0x3fffb:
                pCur = gSenderRef;
            LAB_0043c66a:
                if ((pCur != (ScriptReference *)0x0) &&
                    (curVtable = pCur->vtable, userReferenceProto = (int *)tfb_getUserReferenceProto(),
                        curVtable == (ScriptReference_vtbl *)*userReferenceProto))
                {
                    if (((this->raw & 0x3f00) == 0) && (scope != 0))
                    {
                        local_8 = CONCAT31(local_8._1_3_, 1);
                        scope = 0;
                    }
                    else
                    {
                        local_8 = (uint)local_8._1_3_ << 8;
                    }
                    pCur = (ScriptReference *)(*pCur->vtable->getObject)(0, local_8);
                }
            LAB_0043c6a3:
                *ppOwner = pCur;
                break;
            case 0x3fffc:
                *ppOwner = gSubsetRef;
                pCur = gSubsetRef;
                break;
            case 0x3fffd:
                *ppOwner = gEachRef;
                pCur = gEachRef;
                break;
            case 0x3fffe:
                *ppOwner = tfb_controllerOwner;
                break;
            case 0x3ffff:
                *ppOwner = tfb_selfOwner;
                pCur = gSelfRef;
                break;
            default:
                if (0x3fc0c < symbol)
                {
                    pCur = tfb_currentScript->locals[symbol - 0x3fc0d];
                    goto LAB_0043c66a;
                }
                symbol = tfb_globalSymbols->begin[symbol].objAndFlag;
                if ((symbol & 1) == 0)
                {
                    pCur = (ScriptReference *)(symbol & 0xfffffffe);
                    goto LAB_0043c66a;
                }
                pCur = (ScriptReference *)0x0;
                goto LAB_0043c6a3;
            }
            ppvVar1 = ppOwner;
            *ppSet = (ScriptReference *)0x0;
            if (pCur != (ScriptReference *)0x0)
            {
                symbol = this->raw >> 8 & 0x3f;
                if (symbol != 0)
                {
                    pValue = (*pCur->vtable->getExposedMembers)(pCur, (int *)&ppOwner);
                    pCur = pValue + (symbol - 1);
                    pValue = (ScriptReference *)(*(pValue[symbol - 1].vtable)->getObject)(*ppvVar1, 0);
                    if ((pValue != pCur) && (((flag != false || (scope != 0)) || ((self_copy->raw & 0x3f) != 0))))
                    {
                        *ppvVar1 = pValue;
                        pCur = pValue;
                    }
                }
                if (pCur != (ScriptReference *)0x0)
                {
                    pValue = (*pCur->vtable->getType)(pCur);
                    pSVar3 = (ScriptReference *)tfb_getReferenceSetProto();
                    if (pValue == pSVar3)
                    {
                        *ppSet = pCur;
                        if (scope == 0)
                        {
                            *ppvVar1 = pCur;
                            return pCur;
                        }
                        pCur = (ScriptReference *)FUN_0043cd00(pCur, scope, &local_8);
                        *ppvVar1 = pCur;
                    }
                    pRVar2 = self_copy;
                    ppSet = (ScriptReference **)(self_copy->raw & 0x3f);
                    if ((ppSet != (ScriptReference **)0x0) && (pCur != (ScriptReference *)0x0))
                    {
                        if ((scope == 0) && (pCur == *ppvVar1))
                        {
                            curVtable = pCur->vtable;
                            userReferenceProto = (int *)tfb_getUserReferenceProto();
                            if (curVtable == (ScriptReference_vtbl *)*userReferenceProto)
                            {
                                userReferenceProto = (int *)FUN_00430300();
                                symbol = pRVar2->raw;
                                iVar4 = (**(code **)(*userReferenceProto + 0x1c))(&ppOwner);
                                pCur = (ScriptReference *)(iVar4 + -4 + (symbol & 0x3f) * 4);
                            }
                            else
                            {
                                pCur = (*pCur->vtable->getBaseType)(pCur);
                                symbol = pRVar2->raw;
                                iVar4 = (*pCur->vtable->getExposedMembers)(&ppOwner);
                                pCur = (ScriptReference *)(iVar4 + -4 + (symbol & 0x3f) * 4);
                            }
                        }
                        else
                        {
                            pCur = (*pCur->vtable->getExposedMembers)(pCur, (int *)&ppOwner);
                            pCur = pCur + (int)ppSet + -1;
                        }
                        pValue = (ScriptReference *)(*pCur->vtable->getObject)(*ppvVar1, 0);
                        if ((pValue != pCur) && ((char)ppOwner != '\0'))
                        {
                            *ppvVar1 = pValue;
                            pCur = pValue;
                        }
                    }
                }
            }
            return pCur;
        }
    };
}

#endif