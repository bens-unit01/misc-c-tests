/*
 * VirtualTach.h
 *
 *  Created on: 26 févr. 2021
 *      Author: Utilisateur
 */

#ifndef VIRTUALTACH_H_
#define VIRTUALTACH_H_

#include "stdbool.h"
#include "GenericTypes.h"
#include "stddef.h"



typedef struct
{
 //  AppModuleTy                  app;
   bool bUpdated;
   bool                         bQualifDone;
 //  VT_SMTy                      VTState;
   UINT16                       u16VbattON;
   UINT16                       u16VbattSTART;
   UINT16                       u16VbattRUN;
   UINT8                        u8Cranktime;
 //  oVT_VbattInfoTy              VbattInfo;
 //  LWEVENT_STRUCT               lwevent;
}oVirtualTachTy,*poVirtualTachTy;


typedef enum
{
   VT_OFF = 0,
   VT_ON,
   VT_START,
   VT_RUN,
   VT_START_QUALIF,
   VT_RUN_QUALIF,
   // This value is only used to know how many previous values exist. It must
   // stay last.
   eVT_APPLICATIONSTATE_ENUM_VALUE_COUNT
}VT_SMTy;
#endif /* VIRTUALTACH_H_ */
