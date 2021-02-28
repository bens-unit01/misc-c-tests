/*
 * ORCA.h
 *
 *  Created on: 26 févr. 2021
 *      Author: Utilisateur
 */

#ifndef ORCA_H_
#define ORCA_H_



typedef enum
{
   STOPPED,
   RUNNING,
   // This value is only used to know how many previous values exist. It must
   // stay last.
   eAM_APPSTATUS_ENUM_VALUE_COUNT
}AppStatusTy;

typedef struct
{
   oORCATy* poORCA;
/*   _task_id task_id;
   ActivationStateTy activation;
   EnabledStateTy enabledState;
   InstallationStateTy installationState;
   */
   AppStatusTy status;
}AppModuleTy;

#include "GenericTypes.h"

typedef enum
{
   ORCA_INIT = 0,
   ORCA_BOOT,
   ORCA_RUN,
}ORCA_SMTy;


typedef struct
{
	int value;
}oORCAIOTy,*poORCAIOTy;

typedef struct SOrcaInstance_struct
{
  // PeripheralModuleTy   peripheral;
   ORCA_SMTy            ORCAState;
   poORCAIOTy           poORCAIO;
  // poModemTy            poModem;
#ifdef ORCA4_HW
   poWifiTy         	poWifi;
#endif
#ifdef FIRMWARE_BUILD_BLUETOOTH_ENABLE
   poBluetoothTy        poBluetooth;
#endif
  /* poSystemTy           poSystem;
   poSettingsTy         poSettings;
   poMemoryPoolTy       poMemoryPool;
   poBootloaderTy       poBootloader;
   poAccelerometerTy    poAccelerometer;
   poCardReaderTy       poCardReader;
   poECUScannerTy       poECUScanner;
   poEngineInterfaceTy  poEngineInterface;
   */
#ifdef FIRMWARE_BUILD_VIMS_ENABLE
   poVimsTy					poVims;
#endif
  /* poRs232Ty            poRs232;
   UINT8                u8SerialNumber[SERIAL_NUMBER_LENGTH];
   bool                 bShutdownDone;
   bool                 bIsNewlyProgrammed;
   EnabledStateTy       garageModeEnabledState;
   EnabledStateTy       auxModeEnabledState;
   EnabledStateTy       lowPowerModeEnabledState;
   UINT16               u16WakeUpPeriodMn;
   oCardDatabaseTy*     poCardDatabase;
   ORCAWakeUpTypeTy     wakeUpType;
   ActivationStateTy    powerSwitch;
   bool                 bIsShuttingDown;
   */
#ifdef ORCA4_HW
   poGpsTy			poGps;
#endif
}oORCATy,*poORCATy;


typedef struct
{
   UINT8                u8FrameCode;
   UINT8                u8ExpectedFrameCode;
 //  DataBlockSourceTy	DataBlockSource;
   // uIsDataShared is declared as uint8_t to make sure that the size is constant, known and minimal regardless of the architecture
   uint8_t              uIsDataShared;
   UINT32		u32SessionNumber;
 //  UINT16		u16SequenceNumber;
   UINT32		u32Timestamp;
   UINT8		u8PayloadLength;
  // UINT8		u8Payload[DATABLOCK_PAYLOAD_MAX_LENGTH];
   // Checksum of the previous data (used to verify that data block is read
   // correctly from memory).
   UINT8		u8Checksum;
}DataBlockTy,*pDataBlockTy;
#endif /* ORCA_H_ */


typedef uint32_t  _mqx_uint, * _mqx_uint_ptr;
#define MQX_MIN_BITS_IN_TICK_STRUCT (64)
#define MQX_INT_SIZE_IN_BITS (32)

#define MQX_NUM_TICK_FIELDS  ((MQX_MIN_BITS_IN_TICK_STRUCT+ \
   MQX_INT_SIZE_IN_BITS-1) / MQX_INT_SIZE_IN_BITS)
typedef struct mqx_tick_struct
{
   _mqx_uint TICKS[MQX_NUM_TICK_FIELDS];
   uint32_t   HW_TICKS;
} MQX_TICK_STRUCT, * MQX_TICK_STRUCT_PTR

