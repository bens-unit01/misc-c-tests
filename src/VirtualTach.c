/*
 * VirtualTach.c
 *
 *  Created on: 26 févr. 2021
 *      Author: Utilisateur
 */

#include "VirtualTach.h"


#define VT_DEBUG_DATA_SIZE            73

void VirtualTachTask(uint32_t initial_data)
{
   //WatchdogsCreate();

   // Define context
 /*  poORCATy this;

   // Task variables
   bool bKey = false;
   bool bConvertOverflow;
   uint32_t u16Vbatt = 0, u16VbattAverage;
   float fVbattSlope = 0;
   DataBlockTy DataBlock;
   MQX_TICK_STRUCT CurrentTicks;
   MQX_TICK_STRUCT runQualifTickCount;
   pointer appManagerEvent = NULL;

   uint8_t  uVBattOnStartCount=0;
   uint8_t  uVBattRunCount=0;
   uint8_t  uTimeCount=0;
   uint8_t  uDebugDataToSend[VT_DEBUG_DATA_SIZE] = {0};
   bool     bStartVoltageSent    = false;
   bool     bRunVoltageSent      = false;

   oVirtualTachTy oVirtualTach;

#ifdef DEBUG_TRACE_TASK_DESCRIPTOR_ADDRESSES
    WatchdogsClear(VIRTUAL_TACH_WDT_MS);
    printf("[VT] TDADDRESS FOR %s is 0x%P\n\r", __FUNCTION__, _task_get_td(_task_get_id()));
#endif

   oVirtualTach.app.status = RUNNING;
*/
   while(1)
   {
 //     WatchdogsClear(VIRTUAL_TACH_WDT_MS);

/*      const VT_SMTy eInitialState = oVirtualTach.VTState;

      ORCAIOReadInstantInput(this->poORCAIO, KEY, &bKey);
      if(ORCAIOGetVBatt(this->poORCAIO, &u16Vbatt) == true)
      {
         VirtualTachVBattInfoUpdate(u16Vbatt);
      }
      else
      {
         printf("[VT] ORCAIOGetVBatt FAILED!!!\n");
      }

      switch(oVirtualTach.VTState)
      {
         case VT_OFF:
         {
            ORCAIORegCallback(this->poORCAIO, KEY, (PFuncTy)VirtualTachKeyOnIrq, &oVirtualTach);

            if(oVirtualTach.bQualifDone == false || (ORCAIOReadInstantInput(this->poORCAIO, KEY, &bKey) == true && bKey == false))
            {
               oVirtualTach.app.status = STOPPED;

               WatchdogsStop();

               printf("[VT] sleep zzz...\n");

               if (_lwevent_wait_ticks(&oVirtualTach.lwevent, VT_EVENT_KEY_ON, false, 0) != MQX_OK)
               {
                  _mqx_exit(0);
               }

               WatchdogsClear(ANTITHEFT_WDT_MS);

               VirtualTachVBattInfoReset();

               if(ORCAIOReadInstantInput(this->poORCAIO, KEY, &bKey) == true &&
                     bKey == true &&
                     ORCAIOGetVBatt(this->poORCAIO, &u16Vbatt) == true &&
                     oVirtualTach.bQualifDone == false)
               {
                  oVirtualTach.app.status = RUNNING;

                  oVirtualTach.u16VbattON = u16Vbatt;
                  printf("[VT] Qualified VBatt ON (%.1fV)\n", ((FLOAT)oVirtualTach.u16VbattON)/10);
                  oVirtualTach.VTState = VT_START_QUALIF;

                  _time_get_elapsed_ticks(&runQualifTickCount);
               }
            }
            if(oVirtualTach.bQualifDone && bKey == true && u16Vbatt)
            {
               oVirtualTach.app.status = RUNNING;

               if(u16Vbatt < ((oVirtualTach.u16VbattRUN + oVirtualTach.u16VbattON)/2))
               {
                  VirtualTachSetState(VT_ON);
               }
               else
               {
                  VirtualTachSetState(VT_RUN);
                  printf("[VT] Error Failed to detect ON State\n");
               }
            }

            ORCAIOUnregCallback(this->poORCAIO, KEY, (PFuncTy)VirtualTachKeyOnIrq);

            if (_lwevent_clear(&oVirtualTach.lwevent, VT_EVENT_KEY_ON) != MQX_OK)
            {
               _mqx_exit(0);
            }
         }break;
         case VT_ON:
         {
            uTimeCount= uTimeCount+1;
            // Get Battery Voltage and add it to array every 0.1s until frame payload reached
            if (uVBattOnStartCount < VT_DEBUG_DATA_SIZE-1 &&  uTimeCount == 10 && bStartVoltageSent == false)
            {
               uDebugDataToSend[uVBattOnStartCount] = (uint8_t) u16Vbatt;
               uTimeCount = 0;
               uVBattOnStartCount+=1;
            }
            if(bKey == false)
            {
               VirtualTachSetState(VT_OFF);
            }
            else if(u16Vbatt < ((oVirtualTach.u16VbattON + oVirtualTach.u16VbattSTART)/2))
            {
               _time_get_elapsed_ticks(&runQualifTickCount);
               VirtualTachSetState(VT_START);
               // 0 is the delimiter in frame's data between ON values and START values
               if (uVBattOnStartCount <= 71)
               {
                  uDebugDataToSend[uVBattOnStartCount] = 0;
                  uVBattOnStartCount+=1;
               }
               else
               {
                  uDebugDataToSend[0] = 0;
                  uVBattOnStartCount=1;
               }
            }
            else if(u16Vbatt > ((oVirtualTach.u16VbattRUN + oVirtualTach.u16VbattON)/2))
            {
               VirtualTachSetState(VT_RUN);
               printf("[VT] Error Failed to detect Start State\n");
            }

            if (uVBattOnStartCount == VT_DEBUG_DATA_SIZE-1)
            {
               uVBattOnStartCount =0;
            }
         }break;
         case VT_START:
         {
            uTimeCount= uTimeCount+1;
            // Get Battery Voltage and add it to array every 0.1s until frame payload reached
            if (uVBattOnStartCount < VT_DEBUG_DATA_SIZE-1 &&  uTimeCount == 10 && bStartVoltageSent == false)
            {
               uDebugDataToSend[uVBattOnStartCount] = (uint8_t) u16Vbatt;
               uTimeCount = 0;
               uVBattOnStartCount+=1;
            }

            if(bKey == false)
            {
               VirtualTachSetState(VT_OFF);
            }
            else if(ToolsIsDueMS(&runQualifTickCount, VT_RUN_QUALIF_TIMEOUT_MS))
            {
               printf("[VT] Error Failed to detect Run State\n");
               VirtualTachSetState(VT_ON);
            }
            else if(VirtualTachGetVBattAverage(&u16VbattAverage) == true &&
                  u16VbattAverage  > ((oVirtualTach.u16VbattRUN + oVirtualTach.u16VbattON)/2))
            {
               VirtualTachSetState(VT_RUN);

               //put Last voltage index in last element of buffer
               uDebugDataToSend[VT_DEBUG_DATA_SIZE-1] = uVBattOnStartCount-1;
               ToolsAddDebugInfoBinaryAutoTaskDataBlock(eDEBUGINFOLEVEL_DEBUG, uDebugDataToSend, sizeof(uDebugDataToSend));
               for (int i=0; i < VT_DEBUG_DATA_SIZE ; i++)
               {
                   printf("[VT] Start_Batt_Voltage[%u] = %u\n", i,uDebugDataToSend[i]);
               }
               bStartVoltageSent = true;
               uTimeCount=0;
               uVBattOnStartCount=0;
            }
            if (uVBattOnStartCount == VT_DEBUG_DATA_SIZE-1)
            {
               uVBattOnStartCount =0;
            }
         }break;
         case VT_RUN:
         {
            // Get Battery voltage every 0.1s for 3s after Run state detected and add it to array
            if (uVBattRunCount < VT_DEBUG_DATA_SIZE && bRunVoltageSent == false)
            {
               uDebugDataToSend[uVBattRunCount] = (uint8_t) u16Vbatt;
               uVBattRunCount+=1;
            }
            if (uVBattRunCount == VT_DEBUG_DATA_SIZE)
            {
               // Send 0xEE frame
               ToolsAddDebugInfoBinaryAutoTaskDataBlock(eDEBUGINFOLEVEL_DEBUG, uDebugDataToSend, sizeof(uDebugDataToSend));
               for (int j=0; j < VT_DEBUG_DATA_SIZE ; j++)
               {
                   printf("[VT] Run_Batt_Voltage[%u] = %u\n", j,uDebugDataToSend[j]);
               }
               memset(uDebugDataToSend,0,sizeof(uDebugDataToSend));
               bRunVoltageSent = true;
               uVBattRunCount=0;
            }

            if(bKey == false)
            {
               VirtualTachSetState(VT_OFF);
               bStartVoltageSent = false;
               bRunVoltageSent   = false;
            }
            else if(VirtualTachGetVBattAverage(&u16VbattAverage) == true &&
                    u16VbattAverage < ((oVirtualTach.u16VbattRUN + oVirtualTach.u16VbattON)/2))
            {
               VirtualTachSetState(VT_ON);
            }
         }break;
         case VT_START_QUALIF:
         {
            if(bKey == true && !ToolsIsDueMS(&runQualifTickCount, VT_RUN_QUALIF_TIMEOUT_MS))
            {
               if(oVirtualTach.u16VbattSTART == 0)
               {
                  if(u16Vbatt < (oVirtualTach.u16VbattON - VT_KEY_ON_THREASHOLD))
                  {
                     oVirtualTach.u16VbattSTART = u16Vbatt;
                  }
                  // Start timeout only when crank is detected
                  _time_get_elapsed_ticks(&runQualifTickCount);
               }
               else if(u16Vbatt < oVirtualTach.u16VbattSTART)
               {
                  oVirtualTach.u16VbattSTART = u16Vbatt;
               }
               else if(u16Vbatt > (oVirtualTach.u16VbattON + VT_KEY_ON_THREASHOLD))
               {
                  oVirtualTach.VTState = VT_RUN_QUALIF;
                  printf("[VT] Qualified VBatt START (%.1fV)\n", ((FLOAT)oVirtualTach.u16VbattSTART)/10);

                  _time_get_elapsed_ticks(&CurrentTicks);
                  oVirtualTach.u8Cranktime = _time_diff_seconds(&CurrentTicks, &runQualifTickCount, &bConvertOverflow);
                  _time_get_elapsed_ticks(&runQualifTickCount);
               }
            }
            else
            {
               oVirtualTach.u16VbattON = 0;
               oVirtualTach.u16VbattSTART = 0;
               VirtualTachSetState(VT_OFF);
            }
         }break;
         case VT_RUN_QUALIF:
         {
            if(bKey == true && !ToolsIsDueMS(&runQualifTickCount, VT_RUN_QUALIF_TIMEOUT_MS))
            {
               // Wait for stable VBatt to consider valid
               if(VirtualTachGetVBattSlope(&fVbattSlope) == true && fVbattSlope < VT_RUN_MAX_V_BATT_SLOP)
               {
                  VirtualTachGetVBattAverage(&oVirtualTach.u16VbattRUN);

                  if(oVirtualTach.u16VbattRUN > (oVirtualTach.u16VbattON + VT_KEY_ON_THREASHOLD))
                  {
                     oVirtualTach.bQualifDone = true;

                     _time_get_elapsed_ticks(&CurrentTicks);
                     oVirtualTach.u8Cranktime += _time_diff_seconds(&CurrentTicks, &runQualifTickCount, &bConvertOverflow);

                     VirtualTachSetState(VT_RUN);
                     printf("[VT] Qualified VBatt RUN (%.1fV)\n", ((FLOAT)oVirtualTach.u16VbattRUN)/10);

                     // Send qualified voltage to server
                     VirtualTachAddDataBlock(&DataBlock);
                     MemoryPoolAddBlock(this->poMemoryPool, &DataBlock);

                     VirtualTachSave();

                     if(_event_set(appManagerEvent, CRITICAL_PARAMETERS_CHANGED) != MQX_OK)
                     {
                        _mqx_exit(0);
                     }
                  }
               }
            }
            else
            {
               oVirtualTach.u16VbattON = 0;
               oVirtualTach.u16VbattSTART = 0;
               oVirtualTach.u16VbattRUN = 0;
               VirtualTachSetState(VT_OFF);
            }
         }break;
         default:
         {
            VirtualTachSetState(VT_OFF);
         }break;
      }

      if (oVirtualTach.VTState != eInitialState)
      {
         printf("[VT] State changed from %i to %i (\"%s\")(%udV)\r\n",
                eInitialState,
                oVirtualTach.VTState,
                apszVtAppState[oVirtualTach.VTState],
                u16Vbatt);
      }

      if(oVirtualTach.VTState == VT_RUN)
      {
         // Acquisition time base
         _time_delay(VT_100MS_TIME_BASE);
      }
      else
      {
         // Acquisition time base
         _time_delay(VT_10MS_TIME_BASE);
      }

   */
   }
}

