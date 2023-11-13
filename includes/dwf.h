/************************************************************************/
/*                                                                      */
/*    dwf.h  --    Public Interface Declarations for DWF.DLL            */
/*                                                                      */
/************************************************************************/
/*    Author: Laszlo Attila Kovacs                                      */
/*    Copyright 2013-2022 Digilent Inc.                                 */
/************************************************************************/
/*  File Description:                                                   */
/*                                                                      */
/*    This header file contains the public interface declarations for   */
/*    the DWF.DLL.  This interface consists of  hardware device         */
/*    enumeration, connection (open/close), and hardware instrument     */
/*    control.  This spans all 4 main instruments  supported by the     */
/*    WaveForms system:                                                 */
/*      Analog In, Analog Out, Analog I/O, and Digital I/O              */
/*                                                                      */
/*    For details on using this interface, refer to:                    */
/*    The WaveForms SDK User's Manual (available in the WaveForms SDK)  */
/*                                                                      */
/************************************************************************/
/*  Revision History:                                                   */
/*                                                                      */
/*  06/6/2009(KovacsLA) : Created                                       */
/*                                                                      */
/************************************************************************/


#pragma once

#ifndef DWFINC 
#define DWFINC TRUE

#ifndef DWFAPI
    #if defined(WIN32)
        #if defined(__cplusplus)
            #define    DWFAPI extern "C" __declspec(dllimport)
        #else
            #define    DWFAPI __declspec(dllimport)
        #endif
    #else        
        #if defined(__cplusplus)
            #define DWFAPI extern "C"
        #else
            #define DWFAPI
        #endif
    #endif
#endif

// device handle
typedef int HDWF;
const HDWF hdwfNone = 0;

// device enumeration filters
typedef int ENUMFILTER;
const ENUMFILTER enumfilterAll      = 0;
const ENUMFILTER enumfilterType     = 0x8000000;
const ENUMFILTER enumfilterUSB      = 0x0000001;
const ENUMFILTER enumfilterNetwork  = 0x0000002;
const ENUMFILTER enumfilterAXI      = 0x0000004;
const ENUMFILTER enumfilterRemote   = 0x1000000;
const ENUMFILTER enumfilterAudio    = 0x2000000;
const ENUMFILTER enumfilterDemo     = 0x4000000;

// device ID
typedef int DEVID;
const DEVID devidEExplorer  = 1;
const DEVID devidDiscovery  = 2;
const DEVID devidDiscovery2 = 3;
const DEVID devidDDiscovery = 4;
const DEVID devidADP3X50    = 6;
const DEVID devidEclypse    = 7;
const DEVID devidADP5250    = 8;
const DEVID devidDPS3340    = 9;

// device version
typedef int DEVVER;
const DEVVER devverEExplorerC   = 2;
const DEVVER devverEExplorerE   = 4;
const DEVVER devverEExplorerF   = 5;
const DEVVER devverDiscoveryA   = 1;
const DEVVER devverDiscoveryB   = 2;
const DEVVER devverDiscoveryC   = 3;

// trigger source
typedef unsigned char TRIGSRC;
const TRIGSRC trigsrcNone               = 0;
const TRIGSRC trigsrcPC                 = 1;
const TRIGSRC trigsrcDetectorAnalogIn   = 2;
const TRIGSRC trigsrcDetectorDigitalIn  = 3;
const TRIGSRC trigsrcAnalogIn           = 4;
const TRIGSRC trigsrcDigitalIn          = 5;
const TRIGSRC trigsrcDigitalOut         = 6;
const TRIGSRC trigsrcAnalogOut1         = 7;
const TRIGSRC trigsrcAnalogOut2         = 8;
const TRIGSRC trigsrcAnalogOut3         = 9;
const TRIGSRC trigsrcAnalogOut4         = 10;
const TRIGSRC trigsrcExternal1          = 11;
const TRIGSRC trigsrcExternal2          = 12;
const TRIGSRC trigsrcExternal3          = 13;
const TRIGSRC trigsrcExternal4          = 14;
const TRIGSRC trigsrcHigh               = 15;
const TRIGSRC trigsrcLow                = 16;
const TRIGSRC trigsrcClock              = 17;

// instrument states:
typedef unsigned char DwfState;
const DwfState DwfStateReady        = 0;
const DwfState DwfStateConfig       = 4;
const DwfState DwfStatePrefill      = 5;
const DwfState DwfStateArmed        = 1;
const DwfState DwfStateWait         = 7;
const DwfState DwfStateTriggered    = 3;
const DwfState DwfStateRunning      = 3;
const DwfState DwfStateDone         = 2;

//
typedef int DwfEnumConfigInfo;
const DwfEnumConfigInfo DECIAnalogInChannelCount = 1;
const DwfEnumConfigInfo DECIAnalogOutChannelCount = 2;
const DwfEnumConfigInfo DECIAnalogIOChannelCount = 3;
const DwfEnumConfigInfo DECIDigitalInChannelCount = 4;
const DwfEnumConfigInfo DECIDigitalOutChannelCount = 5;
const DwfEnumConfigInfo DECIDigitalIOChannelCount = 6;
const DwfEnumConfigInfo DECIAnalogInBufferSize = 7;
const DwfEnumConfigInfo DECIAnalogOutBufferSize = 8;
const DwfEnumConfigInfo DECIDigitalInBufferSize = 9;
const DwfEnumConfigInfo DECIDigitalOutBufferSize = 10;

// acquisition modes:
typedef int ACQMODE;
const ACQMODE acqmodeSingle     = 0;
const ACQMODE acqmodeScanShift  = 1;
const ACQMODE acqmodeScanScreen = 2;
const ACQMODE acqmodeRecord     = 3;
const ACQMODE acqmodeOvers      = 4;
const ACQMODE acqmodeSingle1    = 5;

// analog acquisition filter:
typedef int FILTER;
const FILTER filterDecimate = 0;
const FILTER filterAverage  = 1;
const FILTER filterMinMax   = 2;
const FILTER filterAverageFit  = 3;

// analog in trigger mode:
typedef int TRIGTYPE;
const TRIGTYPE trigtypeEdge         = 0;
const TRIGTYPE trigtypePulse        = 1;
const TRIGTYPE trigtypeTransition   = 2;
const TRIGTYPE trigtypeWindow       = 3;

// trigger slope:
typedef int DwfTriggerSlope;
const DwfTriggerSlope DwfTriggerSlopeRise   = 0;
const DwfTriggerSlope DwfTriggerSlopeFall   = 1;
const DwfTriggerSlope DwfTriggerSlopeEither = 2;

// trigger length condition
typedef int TRIGLEN;
const TRIGLEN triglenLess       = 0;
const TRIGLEN triglenTimeout    = 1;
const TRIGLEN triglenMore       = 2;

// error codes for the functions:
typedef int DWFERC;                           
const   DWFERC dwfercNoErc                  = 0;        //  No error occurred
const   DWFERC dwfercUnknownError           = 1;        //  API waiting on pending API timed out
const   DWFERC dwfercApiLockTimeout         = 2;        //  API waiting on pending API timed out
const   DWFERC dwfercAlreadyOpened          = 3;        //  Device already opened
const   DWFERC dwfercNotSupported           = 4;        //  Device not supported
const   DWFERC dwfercInvalidParameter0      = 0x10;     //  Invalid parameter sent in API call
const   DWFERC dwfercInvalidParameter1      = 0x11;     //  Invalid parameter sent in API call
const   DWFERC dwfercInvalidParameter2      = 0x12;     //  Invalid parameter sent in API call
const   DWFERC dwfercInvalidParameter3      = 0x13;     //  Invalid parameter sent in API call
const   DWFERC dwfercInvalidParameter4      = 0x14;     //  Invalid parameter sent in API call

// analog out signal types
typedef unsigned char FUNC;
const FUNC funcDC       = 0;
const FUNC funcSine     = 1;
const FUNC funcSquare   = 2;
const FUNC funcTriangle = 3;
const FUNC funcRampUp   = 4;
const FUNC funcRampDown = 5;
const FUNC funcNoise    = 6;
const FUNC funcPulse    = 7;
const FUNC funcTrapezium= 8;
const FUNC funcSinePower= 9;
const FUNC funcCustomPattern = 28;
const FUNC funcPlayPattern = 29;
const FUNC funcCustom   = 30;
const FUNC funcPlay     = 31;

const FUNC funcAnalogIn1= 64;
const FUNC funcAnalogIn2= 65;
const FUNC funcAnalogIn3= 66;
const FUNC funcAnalogIn4= 67;
const FUNC funcAnalogIn5= 68;
const FUNC funcAnalogIn6= 69;
const FUNC funcAnalogIn7= 70;
const FUNC funcAnalogIn8= 71;
const FUNC funcAnalogIn9= 72;
const FUNC funcAnalogIn10= 73;
const FUNC funcAnalogIn11= 74;
const FUNC funcAnalogIn12= 75;
const FUNC funcAnalogIn13= 76;
const FUNC funcAnalogIn14= 77;
const FUNC funcAnalogIn15= 78;
const FUNC funcAnalogIn16= 79;

// analog io channel node types
typedef unsigned char ANALOGIO;
const ANALOGIO analogioEnable       = 1;
const ANALOGIO analogioVoltage      = 2;
const ANALOGIO analogioCurrent      = 3;
const ANALOGIO analogioPower        = 4;
const ANALOGIO analogioTemperature  = 5;
const ANALOGIO analogioDmm          = 6;
const ANALOGIO analogioRange        = 7;
const ANALOGIO analogioMeasure      = 8;
const ANALOGIO analogioTime         = 9;
const ANALOGIO analogioFrequency    = 10;
const ANALOGIO analogioResistance   = 11;
const ANALOGIO analogioSlew         = 12;

typedef int DwfDmm;
const DwfDmm DwfDmmResistance     = 1;
const DwfDmm DwfDmmContinuity     = 2;
const DwfDmm DwfDmmDiode          = 3;
const DwfDmm DwfDmmDCVoltage      = 4;
const DwfDmm DwfDmmACVoltage      = 5;
const DwfDmm DwfDmmDCCurrent      = 6;
const DwfDmm DwfDmmACCurrent      = 7;
const DwfDmm DwfDmmDCLowCurrent   = 8;
const DwfDmm DwfDmmACLowCurrent   = 9;
const DwfDmm DwfDmmTemperature    = 10;

typedef int AnalogOutNode;
const AnalogOutNode AnalogOutNodeCarrier  = 0;
const AnalogOutNode AnalogOutNodeFM       = 1;
const AnalogOutNode AnalogOutNodeAM       = 2;

typedef int DwfAnalogOutMode;
const DwfAnalogOutMode DwfAnalogOutModeVoltage  = 0;
const DwfAnalogOutMode DwfAnalogOutModeCurrent  = 1;

typedef int DwfAnalogOutIdle;
const DwfAnalogOutIdle DwfAnalogOutIdleDisable  = 0;
const DwfAnalogOutIdle DwfAnalogOutIdleOffset   = 1;
const DwfAnalogOutIdle DwfAnalogOutIdleInitial  = 2;

typedef int DwfDigitalInClockSource;
const DwfDigitalInClockSource DwfDigitalInClockSourceInternal = 0;
const DwfDigitalInClockSource DwfDigitalInClockSourceExternal = 1;
const DwfDigitalInClockSource DwfDigitalInClockSourceExternal2 = 2;

typedef int DwfDigitalInSampleMode;
const DwfDigitalInSampleMode DwfDigitalInSampleModeSimple   = 0;
// alternate samples: noise|sample|noise|sample|...  
// where noise is more than 1 transition between 2 samples
const DwfDigitalInSampleMode DwfDigitalInSampleModeNoise    = 1; 

typedef int DwfDigitalOutOutput;
const DwfDigitalOutOutput DwfDigitalOutOutputPushPull   = 0;
const DwfDigitalOutOutput DwfDigitalOutOutputOpenDrain  = 1;
const DwfDigitalOutOutput DwfDigitalOutOutputOpenSource = 2;
const DwfDigitalOutOutput DwfDigitalOutOutputThreeState = 3; // for custom and random

typedef int DwfDigitalOutType;
const DwfDigitalOutType DwfDigitalOutTypePulse      = 0;
const DwfDigitalOutType DwfDigitalOutTypeCustom     = 1;
const DwfDigitalOutType DwfDigitalOutTypeRandom     = 2;
const DwfDigitalOutType DwfDigitalOutTypeROM        = 3;
const DwfDigitalOutType DwfDigitalOutTypeState      = 4;
const DwfDigitalOutType DwfDigitalOutTypePlay       = 5;

typedef int DwfDigitalOutIdle;
const DwfDigitalOutIdle DwfDigitalOutIdleInit     = 0;
const DwfDigitalOutIdle DwfDigitalOutIdleLow      = 1;
const DwfDigitalOutIdle DwfDigitalOutIdleHigh     = 2;
const DwfDigitalOutIdle DwfDigitalOutIdleZet      = 3;

typedef int DwfAnalogImpedance;
const DwfAnalogImpedance DwfAnalogImpedanceImpedance = 0; // Ohms
const DwfAnalogImpedance DwfAnalogImpedanceImpedancePhase = 1; // Radians
const DwfAnalogImpedance DwfAnalogImpedanceResistance = 2; // Ohms
const DwfAnalogImpedance DwfAnalogImpedanceReactance = 3; // Ohms
const DwfAnalogImpedance DwfAnalogImpedanceAdmittance = 4; // Siemen
const DwfAnalogImpedance DwfAnalogImpedanceAdmittancePhase = 5; // Radians
const DwfAnalogImpedance DwfAnalogImpedanceConductance = 6; // Siemen
const DwfAnalogImpedance DwfAnalogImpedanceSusceptance = 7; // Siemen
const DwfAnalogImpedance DwfAnalogImpedanceSeriesCapacitance = 8; // Farad
const DwfAnalogImpedance DwfAnalogImpedanceParallelCapacitance = 9; // Farad
const DwfAnalogImpedance DwfAnalogImpedanceSeriesInductance = 10; // Henry
const DwfAnalogImpedance DwfAnalogImpedanceParallelInductance = 11; // Henry
const DwfAnalogImpedance DwfAnalogImpedanceDissipation = 12; // factor
const DwfAnalogImpedance DwfAnalogImpedanceQuality = 13; // factor
const DwfAnalogImpedance DwfAnalogImpedanceVrms = 14; // Vrms
const DwfAnalogImpedance DwfAnalogImpedanceVreal = 15; // V real
const DwfAnalogImpedance DwfAnalogImpedanceVimag = 16; // V imag
const DwfAnalogImpedance DwfAnalogImpedanceIrms = 17; // Irms
const DwfAnalogImpedance DwfAnalogImpedanceIreal = 18; // I real
const DwfAnalogImpedance DwfAnalogImpedanceIimag = 19; // I imag

typedef int DwfParam;
const DwfParam DwfParamUsbPower        = 2; // 1 keep the USB power enabled even when AUX is connected, Analog Discovery 2
const DwfParam DwfParamLedBrightness   = 3; // LED brightness 0 ... 100%, Digital Discovery
const DwfParam DwfParamOnClose         = 4; // 0 continue, 1 stop, 2 shutdown
const DwfParam DwfParamAudioOut        = 5; // 0 disable / 1 enable audio output, Analog Discovery 1, 2
const DwfParam DwfParamUsbLimit        = 6; // 0..1000 mA USB power limit, -1 no limit, Analog Discovery 1, 2
const DwfParam DwfParamAnalogOut       = 7; // 0 disable / 1 enable
const DwfParam DwfParamFrequency       = 8; // Hz
const DwfParam DwfParamExtFreq         = 9; // Hz
const DwfParam DwfParamClockMode       = 10; // 0 internal, 1 output, 2 input, 3 IO
const DwfParam DwfParamTempLimit       = 11;
const DwfParam DwfParamFreqPhase       = 12;

typedef int DwfWindow;
const DwfWindow DwfWindowRectangular    = 0;
const DwfWindow DwfWindowTriangular     = 1;
const DwfWindow DwfWindowHamming        = 2;
const DwfWindow DwfWindowHann           = 3;
const DwfWindow DwfWindowCosine         = 4;
const DwfWindow DwfWindowBlackmanHarris = 5;
const DwfWindow DwfWindowFlatTop        = 6;
const DwfWindow DwfWindowKaiser         = 7;

// analog input coupling:
typedef int DwfAnalogCoupling;
const DwfAnalogCoupling DwfAnalogCouplingDC = 0;
const DwfAnalogCoupling DwfAnalogCouplingAC = 1;


// Macro used to verify if bit is 1 or 0 in given bit field
#define IsBitSet(fs, bit) ((fs & (1<<bit)) != 0)

// Error and version APIs:
DWFAPI int FDwfGetLastError(DWFERC *pdwferc);
DWFAPI int FDwfGetLastErrorMsg(char szError[512]);
DWFAPI int FDwfGetVersion(char szVersion[32]);  // Returns DLL version, for instance: "3.8.5"

DWFAPI int FDwfParamSet(DwfParam param, int value);
DWFAPI int FDwfParamGet(DwfParam param, int *pvalue);

// DEVICE MANAGMENT FUNCTIONS
// Enumeration:
DWFAPI int FDwfEnum(ENUMFILTER enumfilter, int *pcDevice);
DWFAPI int FDwfEnumStart(ENUMFILTER enumfilter);
DWFAPI int FDwfEnumStop(int *pcDevice);
DWFAPI int FDwfEnumInfo(int idxDevice, const char *szOpt);
DWFAPI int FDwfEnumDeviceType(int idxDevice, DEVID *pDeviceId, DEVVER *pDeviceRevision);
DWFAPI int FDwfEnumDeviceIsOpened(int idxDevice, int *pfIsUsed);
DWFAPI int FDwfEnumUserName(int idxDevice, char szUserName[32]);
DWFAPI int FDwfEnumDeviceName(int idxDevice, char szDeviceName[32]);
DWFAPI int FDwfEnumSN(int idxDevice, char szSN[32]);
DWFAPI int FDwfEnumConfig(int idxDevice, int *pcConfig);
DWFAPI int FDwfEnumConfigInfo(int idxConfig, DwfEnumConfigInfo info, int *pv);

// Open/Close:
DWFAPI int FDwfDeviceOpen(int idxDevice, HDWF *phdwf);
DWFAPI int FDwfDeviceOpenEx(const char *szOpt, HDWF *phdwf);
DWFAPI int FDwfDeviceConfigOpen(int idxDev, int idxCfg, HDWF *phdwf);
DWFAPI int FDwfDeviceClose(HDWF hdwf);
DWFAPI int FDwfDeviceCloseAll();
DWFAPI int FDwfDeviceAutoConfigureSet(HDWF hdwf, int fAutoConfigure);
DWFAPI int FDwfDeviceAutoConfigureGet(HDWF hdwf, int *pfAutoConfigure);
DWFAPI int FDwfDeviceReset(HDWF hdwf);
DWFAPI int FDwfDeviceEnableSet(HDWF hdwf, int fEnable);
DWFAPI int FDwfDeviceTriggerInfo(HDWF hdwf, int *pfstrigsrc); // use IsBitSet
DWFAPI int FDwfDeviceTriggerSet(HDWF hdwf, int idxPin, TRIGSRC trigsrc);
DWFAPI int FDwfDeviceTriggerGet(HDWF hdwf, int idxPin, TRIGSRC *ptrigsrc);
DWFAPI int FDwfDeviceTriggerPC(HDWF hdwf);
DWFAPI int FDwfDeviceTriggerSlopeInfo(HDWF hdwf, int *pfsslope); // use IsBitSet
DWFAPI int FDwfDeviceParamSet(HDWF hdwf, DwfParam param, int value);
DWFAPI int FDwfDeviceParamGet(HDWF hdwf, DwfParam param, int *pvalue);


// ANALOG IN INSTRUMENT FUNCTIONS
// Control and status: 
DWFAPI int FDwfAnalogInReset(HDWF hdwf);
DWFAPI int FDwfAnalogInConfigure(HDWF hdwf, int fReconfigure, int fStart);
DWFAPI int FDwfAnalogInTriggerForce(HDWF hdwf);
DWFAPI int FDwfAnalogInStatus(HDWF hdwf, int fReadData, DwfState *psts);
DWFAPI int FDwfAnalogInStatusSamplesLeft(HDWF hdwf, int *pcSamplesLeft);
DWFAPI int FDwfAnalogInStatusSamplesValid(HDWF hdwf, int *pcSamplesValid);
DWFAPI int FDwfAnalogInStatusIndexWrite(HDWF hdwf, int *pidxWrite);
DWFAPI int FDwfAnalogInStatusAutoTriggered(HDWF hdwf, int *pfAuto);
DWFAPI int FDwfAnalogInStatusData(HDWF hdwf, int idxChannel, double *rgdVoltData, int cdData);
DWFAPI int FDwfAnalogInStatusData2(HDWF hdwf, int idxChannel, double *rgdVoltData, int idxData, int cdData);
DWFAPI int FDwfAnalogInStatusData16(HDWF hdwf, int idxChannel, short *rgu16Data, int idxData, int cdData);
DWFAPI int FDwfAnalogInStatusNoise(HDWF hdwf, int idxChannel, double *rgdMin, double *rgdMax, int cdData);
DWFAPI int FDwfAnalogInStatusNoise2(HDWF hdwf, int idxChannel, double *rgdMin, double *rgdMax, int idxData, int cdData);
DWFAPI int FDwfAnalogInStatusSample(HDWF hdwf, int idxChannel, double *pdVoltSample);
DWFAPI int FDwfAnalogInStatusTime(HDWF hdwf, unsigned int *psecUtc, unsigned int *ptick, unsigned int *pticksPerSecond);

DWFAPI int FDwfAnalogInStatusRecord(HDWF hdwf, int *pcdDataAvailable, int *pcdDataLost, int *pcdDataCorrupt);
DWFAPI int FDwfAnalogInRecordLengthSet(HDWF hdwf, double sLength);
DWFAPI int FDwfAnalogInRecordLengthGet(HDWF hdwf, double *psLength);

DWFAPI int FDwfAnalogInCounterInfo(HDWF hdwf, double *pcntMax, double *psecMax);
DWFAPI int FDwfAnalogInCounterSet(HDWF hdwf, double sec);
DWFAPI int FDwfAnalogInCounterGet(HDWF hdwf, double *psec);
DWFAPI int FDwfAnalogInCounterStatus(HDWF hdwf, double *pcnt, double *pfreq, int *ptick);

// Acquisition configuration:
DWFAPI int FDwfAnalogInFrequencyInfo(HDWF hdwf, double *phzMin, double *phzMax);
DWFAPI int FDwfAnalogInFrequencySet(HDWF hdwf, double hzFrequency);
DWFAPI int FDwfAnalogInFrequencyGet(HDWF hdwf, double *phzFrequency);

DWFAPI int FDwfAnalogInBitsInfo(HDWF hdwf, int *pnBits); // Returns the number of ADC bits

DWFAPI int FDwfAnalogInBufferSizeInfo(HDWF hdwf, int *pnSizeMin, int *pnSizeMax);
DWFAPI int FDwfAnalogInBufferSizeSet(HDWF hdwf, int nSize);
DWFAPI int FDwfAnalogInBufferSizeGet(HDWF hdwf, int *pnSize);

DWFAPI int FDwfAnalogInNoiseSizeInfo(HDWF hdwf, int *pnSizeMax);
DWFAPI int FDwfAnalogInNoiseSizeSet(HDWF hdwf, int nSize);
DWFAPI int FDwfAnalogInNoiseSizeGet(HDWF hdwf, int *pnSize);

DWFAPI int FDwfAnalogInAcquisitionModeInfo(HDWF hdwf, int *pfsacqmode); // use IsBitSet
DWFAPI int FDwfAnalogInAcquisitionModeSet(HDWF hdwf, ACQMODE acqmode);
DWFAPI int FDwfAnalogInAcquisitionModeGet(HDWF hdwf, ACQMODE *pacqmode);

// Channel configuration:
DWFAPI int FDwfAnalogInChannelCount(HDWF hdwf, int *pcChannel);
DWFAPI int FDwfAnalogInChannelCounts(HDWF hdwf, int* pcReal, int* pcFilter, int* pcTotal);
DWFAPI int FDwfAnalogInChannelEnableSet(HDWF hdwf, int idxChannel, int fEnable);
DWFAPI int FDwfAnalogInChannelEnableGet(HDWF hdwf, int idxChannel, int *pfEnable);
DWFAPI int FDwfAnalogInChannelFilterInfo(HDWF hdwf, int *pfsfilter); // use IsBitSet
DWFAPI int FDwfAnalogInChannelFilterSet(HDWF hdwf, int idxChannel, FILTER filter);
DWFAPI int FDwfAnalogInChannelFilterGet(HDWF hdwf, int idxChannel, FILTER *pfilter);
DWFAPI int FDwfAnalogInChannelRangeInfo(HDWF hdwf, double *pvoltsMin, double *pvoltsMax, double *pnSteps);
DWFAPI int FDwfAnalogInChannelRangeSteps(HDWF hdwf, double rgVoltsStep[32], int *pnSteps);
DWFAPI int FDwfAnalogInChannelRangeSet(HDWF hdwf, int idxChannel, double voltsRange);
DWFAPI int FDwfAnalogInChannelRangeGet(HDWF hdwf, int idxChannel, double *pvoltsRange);
DWFAPI int FDwfAnalogInChannelOffsetInfo(HDWF hdwf, double *pvoltsMin, double *pvoltsMax, double *pnSteps);
DWFAPI int FDwfAnalogInChannelOffsetSet(HDWF hdwf, int idxChannel, double voltOffset);
DWFAPI int FDwfAnalogInChannelOffsetGet(HDWF hdwf, int idxChannel, double *pvoltOffset);
DWFAPI int FDwfAnalogInChannelAttenuationSet(HDWF hdwf, int idxChannel, double xAttenuation);
DWFAPI int FDwfAnalogInChannelAttenuationGet(HDWF hdwf, int idxChannel, double *pxAttenuation);
DWFAPI int FDwfAnalogInChannelBandwidthSet(HDWF hdwf, int idxChannel, double hz);
DWFAPI int FDwfAnalogInChannelBandwidthGet(HDWF hdwf, int idxChannel, double *phz);
DWFAPI int FDwfAnalogInChannelImpedanceSet(HDWF hdwf, int idxChannel, double ohms);
DWFAPI int FDwfAnalogInChannelImpedanceGet(HDWF hdwf, int idxChannel, double *pOhms);
DWFAPI int FDwfAnalogInChannelCouplingInfo(HDWF hdwf, int *pfscoupling); // use IsBitSet
DWFAPI int FDwfAnalogInChannelCouplingSet(HDWF hdwf, int idxChannel, DwfAnalogCoupling coupling);
DWFAPI int FDwfAnalogInChannelCouplingGet(HDWF hdwf, int idxChannel, DwfAnalogCoupling *pcoupling);

// Trigger configuration:
DWFAPI int FDwfAnalogInTriggerSourceSet(HDWF hdwf, TRIGSRC trigsrc);
DWFAPI int FDwfAnalogInTriggerSourceGet(HDWF hdwf, TRIGSRC *ptrigsrc);

DWFAPI int FDwfAnalogInTriggerPositionInfo(HDWF hdwf, double *psecMin, double *psecMax, double *pnSteps);
DWFAPI int FDwfAnalogInTriggerPositionSet(HDWF hdwf, double secPosition);
DWFAPI int FDwfAnalogInTriggerPositionGet(HDWF hdwf, double *psecPosition);
DWFAPI int FDwfAnalogInTriggerPositionStatus(HDWF hdwf, double *psecPosition);

DWFAPI int FDwfAnalogInTriggerAutoTimeoutInfo(HDWF hdwf, double *psecMin, double *psecMax, double *pnSteps);
DWFAPI int FDwfAnalogInTriggerAutoTimeoutSet(HDWF hdwf, double secTimeout);
DWFAPI int FDwfAnalogInTriggerAutoTimeoutGet(HDWF hdwf, double *psecTimeout);

DWFAPI int FDwfAnalogInTriggerHoldOffInfo(HDWF hdwf, double *psecMin, double *psecMax, double *pnStep);
DWFAPI int FDwfAnalogInTriggerHoldOffSet(HDWF hdwf, double secHoldOff);
DWFAPI int FDwfAnalogInTriggerHoldOffGet(HDWF hdwf, double *psecHoldOff);

DWFAPI int FDwfAnalogInTriggerTypeInfo(HDWF hdwf, int *pfstrigtype); // use IsBitSet
DWFAPI int FDwfAnalogInTriggerTypeSet(HDWF hdwf, TRIGTYPE trigtype);
DWFAPI int FDwfAnalogInTriggerTypeGet(HDWF hdwf, TRIGTYPE *ptrigtype);

DWFAPI int FDwfAnalogInTriggerChannelInfo(HDWF hdwf, int *pidxMin, int *pidxMax);
DWFAPI int FDwfAnalogInTriggerChannelSet(HDWF hdwf, int idxChannel);
DWFAPI int FDwfAnalogInTriggerChannelGet(HDWF hdwf, int *pidxChannel);

DWFAPI int FDwfAnalogInTriggerFilterInfo(HDWF hdwf, int *pfsfilter); // use IsBitSet
DWFAPI int FDwfAnalogInTriggerFilterSet(HDWF hdwf, FILTER filter);
DWFAPI int FDwfAnalogInTriggerFilterGet(HDWF hdwf, FILTER *pfilter);

DWFAPI int FDwfAnalogInTriggerLevelInfo(HDWF hdwf, double *pvoltsMin, double *pvoltsMax, double *pnSteps);
DWFAPI int FDwfAnalogInTriggerLevelSet(HDWF hdwf, double voltsLevel);
DWFAPI int FDwfAnalogInTriggerLevelGet(HDWF hdwf, double *pvoltsLevel);

DWFAPI int FDwfAnalogInTriggerHysteresisInfo(HDWF hdwf, double *pvoltsMin, double *pvoltsMax, double *pnSteps);
DWFAPI int FDwfAnalogInTriggerHysteresisSet(HDWF hdwf, double voltsLevel);
DWFAPI int FDwfAnalogInTriggerHysteresisGet(HDWF hdwf, double *pvoltsHysteresis);

DWFAPI int FDwfAnalogInTriggerConditionInfo(HDWF hdwf, int *pfstrigcond); // use IsBitSet
DWFAPI int FDwfAnalogInTriggerConditionSet(HDWF hdwf, DwfTriggerSlope trigcond);
DWFAPI int FDwfAnalogInTriggerConditionGet(HDWF hdwf, DwfTriggerSlope *ptrigcond);

DWFAPI int FDwfAnalogInTriggerLengthInfo(HDWF hdwf, double *psecMin, double *psecMax, double *pnSteps);
DWFAPI int FDwfAnalogInTriggerLengthSet(HDWF hdwf, double secLength);
DWFAPI int FDwfAnalogInTriggerLengthGet(HDWF hdwf, double *psecLength);

DWFAPI int FDwfAnalogInTriggerLengthConditionInfo(HDWF hdwf, int *pfstriglen); // use IsBitSet
DWFAPI int FDwfAnalogInTriggerLengthConditionSet(HDWF hdwf, TRIGLEN triglen);
DWFAPI int FDwfAnalogInTriggerLengthConditionGet(HDWF hdwf, TRIGLEN *ptriglen);

DWFAPI int FDwfAnalogInSamplingSourceSet(HDWF hdwf, TRIGSRC trigsrc);
DWFAPI int FDwfAnalogInSamplingSourceGet(HDWF hdwf, TRIGSRC *ptrigsrc);

DWFAPI int FDwfAnalogInSamplingSlopeSet(HDWF hdwf, DwfTriggerSlope slope);
DWFAPI int FDwfAnalogInSamplingSlopeGet(HDWF hdwf, DwfTriggerSlope *pslope);

DWFAPI int FDwfAnalogInSamplingDelaySet(HDWF hdwf, double sec);
DWFAPI int FDwfAnalogInSamplingDelayGet(HDWF hdwf, double *psec);


// ANALOG OUT INSTRUMENT FUNCTIONS
// Configuration:
DWFAPI int FDwfAnalogOutCount(HDWF hdwf, int *pcChannel);

DWFAPI int FDwfAnalogOutMasterSet(HDWF hdwf, int idxChannel, int idxMaster);
DWFAPI int FDwfAnalogOutMasterGet(HDWF hdwf, int idxChannel, int *pidxMaster);

DWFAPI int FDwfAnalogOutTriggerSourceSet(HDWF hdwf, int idxChannel, TRIGSRC trigsrc);
DWFAPI int FDwfAnalogOutTriggerSourceGet(HDWF hdwf, int idxChannel, TRIGSRC *ptrigsrc);

DWFAPI int FDwfAnalogOutTriggerSlopeSet(HDWF hdwf, int idxChannel, DwfTriggerSlope slope);
DWFAPI int FDwfAnalogOutTriggerSlopeGet(HDWF hdwf, int idxChannel, DwfTriggerSlope *pslope);

DWFAPI int FDwfAnalogOutRunInfo(HDWF hdwf, int idxChannel, double *psecMin, double *psecMax);
DWFAPI int FDwfAnalogOutRunSet(HDWF hdwf, int idxChannel, double secRun);
DWFAPI int FDwfAnalogOutRunGet(HDWF hdwf, int idxChannel, double *psecRun);
DWFAPI int FDwfAnalogOutRunStatus(HDWF hdwf, int idxChannel, double *psecRun);

DWFAPI int FDwfAnalogOutWaitInfo(HDWF hdwf, int idxChannel, double *psecMin, double *psecMax);
DWFAPI int FDwfAnalogOutWaitSet(HDWF hdwf, int idxChannel, double secWait);
DWFAPI int FDwfAnalogOutWaitGet(HDWF hdwf, int idxChannel, double *psecWait);

DWFAPI int FDwfAnalogOutRepeatInfo(HDWF hdwf, int idxChannel, int *pnMin, int *pnMax);
DWFAPI int FDwfAnalogOutRepeatSet(HDWF hdwf, int idxChannel, int cRepeat);
DWFAPI int FDwfAnalogOutRepeatGet(HDWF hdwf, int idxChannel, int *pcRepeat);
DWFAPI int FDwfAnalogOutRepeatStatus(HDWF hdwf, int idxChannel, int *pcRepeat);

DWFAPI int FDwfAnalogOutRepeatTriggerSet(HDWF hdwf, int idxChannel, int fRepeatTrigger);
DWFAPI int FDwfAnalogOutRepeatTriggerGet(HDWF hdwf, int idxChannel, int *pfRepeatTrigger);

// EExplorer, DPS3340 channel 3&4 current/voltage limitation
DWFAPI int FDwfAnalogOutLimitationInfo(HDWF hdwf, int idxChannel, double *pMin, double *pMax);
DWFAPI int FDwfAnalogOutLimitationSet(HDWF hdwf, int idxChannel, double limit);
DWFAPI int FDwfAnalogOutLimitationGet(HDWF hdwf, int idxChannel, double *plimit);

DWFAPI int FDwfAnalogOutModeSet(HDWF hdwf, int idxChannel, DwfAnalogOutMode mode);
DWFAPI int FDwfAnalogOutModeGet(HDWF hdwf, int idxChannel, DwfAnalogOutMode *pmode);

DWFAPI int FDwfAnalogOutIdleInfo(HDWF hdwf, int idxChannel, int *pfsidle);
DWFAPI int FDwfAnalogOutIdleSet(HDWF hdwf, int idxChannel, DwfAnalogOutIdle idle);
DWFAPI int FDwfAnalogOutIdleGet(HDWF hdwf, int idxChannel, DwfAnalogOutIdle *pidle);

DWFAPI int FDwfAnalogOutNodeInfo(HDWF hdwf, int idxChannel, int *pfsnode); // use IsBitSet

// Mode: 0 Disable, 1 Enable
// for FM node: 1 is Frequenc Modulation (+-200%), 2 is Phase Modulation (+-100%), 3 is PMD with degree (+-180%) amplitude/offset units
// for AM node: 1 is Amplitude Modulation (+-200%), 2 is SUM (+-400%), 3 is SUM with Volts amplitude/offset units (+-4X CarrierAmplitude)
// PID output: 4
DWFAPI int FDwfAnalogOutNodeEnableSet(HDWF hdwf, int idxChannel, AnalogOutNode node, int fMode);
DWFAPI int FDwfAnalogOutNodeEnableGet(HDWF hdwf, int idxChannel, AnalogOutNode node, int *pfMode);

DWFAPI int FDwfAnalogOutNodeFunctionInfo(HDWF hdwf, int idxChannel, AnalogOutNode node, unsigned int *pfsfunc); // use IsBitSet
DWFAPI int FDwfAnalogOutNodeFunctionSet(HDWF hdwf, int idxChannel, AnalogOutNode node, FUNC func);
DWFAPI int FDwfAnalogOutNodeFunctionGet(HDWF hdwf, int idxChannel, AnalogOutNode node, FUNC *pfunc);

DWFAPI int FDwfAnalogOutNodeFrequencyInfo(HDWF hdwf, int idxChannel, AnalogOutNode node, double *phzMin, double *phzMax);
DWFAPI int FDwfAnalogOutNodeFrequencySet(HDWF hdwf, int idxChannel, AnalogOutNode node, double hzFrequency);
DWFAPI int FDwfAnalogOutNodeFrequencyGet(HDWF hdwf, int idxChannel, AnalogOutNode node, double *phzFrequency);
// Carrier Amplitude or Modulation Index 
DWFAPI int FDwfAnalogOutNodeAmplitudeInfo(HDWF hdwf, int idxChannel, AnalogOutNode node, double *pMin, double *pMax);
DWFAPI int FDwfAnalogOutNodeAmplitudeSet(HDWF hdwf, int idxChannel, AnalogOutNode node, double vAmplitude);
DWFAPI int FDwfAnalogOutNodeAmplitudeGet(HDWF hdwf, int idxChannel, AnalogOutNode node, double *pvAmplitude);

DWFAPI int FDwfAnalogOutNodeOffsetInfo(HDWF hdwf, int idxChannel, AnalogOutNode node, double *pMin, double *pMax);
DWFAPI int FDwfAnalogOutNodeOffsetSet(HDWF hdwf, int idxChannel, AnalogOutNode node, double vOffset);
DWFAPI int FDwfAnalogOutNodeOffsetGet(HDWF hdwf, int idxChannel, AnalogOutNode node, double *pvOffset);

DWFAPI int FDwfAnalogOutNodeSymmetryInfo(HDWF hdwf, int idxChannel, AnalogOutNode node, double *ppercentageMin, double *ppercentageMax);
DWFAPI int FDwfAnalogOutNodeSymmetrySet(HDWF hdwf, int idxChannel, AnalogOutNode node, double percentageSymmetry);
DWFAPI int FDwfAnalogOutNodeSymmetryGet(HDWF hdwf, int idxChannel, AnalogOutNode node, double *ppercentageSymmetry);

DWFAPI int FDwfAnalogOutNodePhaseInfo(HDWF hdwf, int idxChannel, AnalogOutNode node, double *pdegreeMin, double *pdegreeMax);
DWFAPI int FDwfAnalogOutNodePhaseSet(HDWF hdwf, int idxChannel, AnalogOutNode node, double degreePhase);
DWFAPI int FDwfAnalogOutNodePhaseGet(HDWF hdwf, int idxChannel, AnalogOutNode node, double *pdegreePhase);

DWFAPI int FDwfAnalogOutNodeDataInfo(HDWF hdwf, int idxChannel, AnalogOutNode node, int *pnSamplesMin, int *pnSamplesMax);
DWFAPI int FDwfAnalogOutNodeDataSet(HDWF hdwf, int idxChannel, AnalogOutNode node, double *rgdData, int cdData);

// needed for EExplorer, not used for Analog Discovery
DWFAPI int FDwfAnalogOutCustomAMFMEnableSet(HDWF hdwf, int idxChannel, int fEnable);
DWFAPI int FDwfAnalogOutCustomAMFMEnableGet(HDWF hdwf, int idxChannel, int *pfEnable);

// Control:
DWFAPI int FDwfAnalogOutReset(HDWF hdwf, int idxChannel);
DWFAPI int FDwfAnalogOutConfigure(HDWF hdwf, int idxChannel, int fStart);
DWFAPI int FDwfAnalogOutStatus(HDWF hdwf, int idxChannel, DwfState *psts);
DWFAPI int FDwfAnalogOutNodePlayStatus(HDWF hdwf, int idxChannel, AnalogOutNode node, int *cdDataFree, int *cdDataLost, int *cdDataCorrupted);
DWFAPI int FDwfAnalogOutNodePlayData(HDWF hdwf, int idxChannel, AnalogOutNode node, double *rgdData, int cdData);


// ANALOG IO INSTRUMENT FUNCTIONS
// Control:
DWFAPI int FDwfAnalogIOReset(HDWF hdwf);
DWFAPI int FDwfAnalogIOConfigure(HDWF hdwf);
DWFAPI int FDwfAnalogIOStatus(HDWF hdwf);

// Configure:
DWFAPI int FDwfAnalogIOEnableInfo(HDWF hdwf, int *pfSet, int *pfStatus);
DWFAPI int FDwfAnalogIOEnableSet(HDWF hdwf, int fMasterEnable);
DWFAPI int FDwfAnalogIOEnableGet(HDWF hdwf, int *pfMasterEnable);
DWFAPI int FDwfAnalogIOEnableStatus(HDWF hdwf, int *pfMasterEnable);
DWFAPI int FDwfAnalogIOChannelCount(HDWF hdwf, int *pnChannel);
DWFAPI int FDwfAnalogIOChannelName(HDWF hdwf, int idxChannel, char szName[32], char szLabel[16]);
DWFAPI int FDwfAnalogIOChannelInfo(HDWF hdwf, int idxChannel, int *pnNodes);
DWFAPI int FDwfAnalogIOChannelNodeName(HDWF hdwf, int idxChannel, int idxNode, char szNodeName[32], char szNodeUnits[16]);
DWFAPI int FDwfAnalogIOChannelNodeInfo(HDWF hdwf, int idxChannel, int idxNode, ANALOGIO *panalogio);
DWFAPI int FDwfAnalogIOChannelNodeSetInfo(HDWF hdwf, int idxChannel, int idxNode, double *pmin, double *pmax, int *pnSteps);
DWFAPI int FDwfAnalogIOChannelNodeSet(HDWF hdwf, int idxChannel, int idxNode, double value);
DWFAPI int FDwfAnalogIOChannelNodeGet(HDWF hdwf, int idxChannel, int idxNode, double *pvalue);
DWFAPI int FDwfAnalogIOChannelNodeStatusInfo(HDWF hdwf, int idxChannel, int idxNode, double *pmin, double *pmax, int *pnSteps);
DWFAPI int FDwfAnalogIOChannelNodeStatus(HDWF hdwf, int idxChannel, int idxNode, double *pvalue);


// DIGITAL IO INSTRUMENT FUNCTIONS
// Control:
DWFAPI int FDwfDigitalIOReset(HDWF hdwf);
DWFAPI int FDwfDigitalIOConfigure(HDWF hdwf);
DWFAPI int FDwfDigitalIOStatus(HDWF hdwf);

// Configure:
DWFAPI int FDwfDigitalIOOutputEnableInfo(HDWF hdwf, unsigned int *pfsOutputEnableMask);
DWFAPI int FDwfDigitalIOOutputEnableSet(HDWF hdwf, unsigned int fsOutputEnable);
DWFAPI int FDwfDigitalIOOutputEnableGet(HDWF hdwf, unsigned int *pfsOutputEnable);
DWFAPI int FDwfDigitalIOOutputInfo(HDWF hdwf, unsigned int *pfsOutputMask);
DWFAPI int FDwfDigitalIOOutputSet(HDWF hdwf, unsigned int fsOutput);
DWFAPI int FDwfDigitalIOOutputGet(HDWF hdwf, unsigned int *pfsOutput);
DWFAPI int FDwfDigitalIOPullInfo(HDWF hdwf, unsigned int *pfsUp, unsigned int *pfsDown);
DWFAPI int FDwfDigitalIOPullSet(HDWF hdwf, unsigned int fsUp, unsigned int fsDown);
DWFAPI int FDwfDigitalIOPullGet(HDWF hdwf, unsigned int *pfsUp, unsigned int *pfsDown);
DWFAPI int FDwfDigitalIODriveInfo(HDWF hdwf, int channel, double *ampMin, double *ampMax, int *ampSteps, int *pslewSteps);
DWFAPI int FDwfDigitalIODriveSet(HDWF hdwf, int channel, double amp, int slew);
DWFAPI int FDwfDigitalIODriveGet(HDWF hdwf, int channel, double *pamp, int *pslew);
DWFAPI int FDwfDigitalIOInputInfo(HDWF hdwf, unsigned int *pfsInputMask);
DWFAPI int FDwfDigitalIOInputStatus(HDWF hdwf, unsigned int *pfsInput);
DWFAPI int FDwfDigitalIOOutputEnableInfo64(HDWF hdwf, unsigned long long *pfsOutputEnableMask);
DWFAPI int FDwfDigitalIOOutputEnableSet64(HDWF hdwf, unsigned long long fsOutputEnable);
DWFAPI int FDwfDigitalIOOutputEnableGet64(HDWF hdwf, unsigned long long *pfsOutputEnable);
DWFAPI int FDwfDigitalIOOutputInfo64(HDWF hdwf, unsigned long long *pfsOutputMask);
DWFAPI int FDwfDigitalIOOutputSet64(HDWF hdwf, unsigned long long fsOutput);
DWFAPI int FDwfDigitalIOOutputGet64(HDWF hdwf, unsigned long long *pfsOutput);
DWFAPI int FDwfDigitalIOInputInfo64(HDWF hdwf, unsigned long long *pfsInputMask);
DWFAPI int FDwfDigitalIOInputStatus64(HDWF hdwf, unsigned long long *pfsInput);


// DIGITAL IN INSTRUMENT FUNCTIONS
// Control and status: 
DWFAPI int FDwfDigitalInReset(HDWF hdwf);
DWFAPI int FDwfDigitalInConfigure(HDWF hdwf, int fReconfigure, int fStart);
DWFAPI int FDwfDigitalInStatus(HDWF hdwf, int fReadData, DwfState *psts);
DWFAPI int FDwfDigitalInStatusSamplesLeft(HDWF hdwf, int *pcSamplesLeft);
DWFAPI int FDwfDigitalInStatusSamplesValid(HDWF hdwf, int *pcSamplesValid);
DWFAPI int FDwfDigitalInStatusIndexWrite(HDWF hdwf, int *pidxWrite);
DWFAPI int FDwfDigitalInStatusAutoTriggered(HDWF hdwf, int *pfAuto);
DWFAPI int FDwfDigitalInStatusData(HDWF hdwf, void *rgData, int countOfDataBytes);
DWFAPI int FDwfDigitalInStatusData2(HDWF hdwf, void *rgData, int idxSample, int countOfDataBytes);
DWFAPI int FDwfDigitalInStatusNoise2(HDWF hdwf, void *rgData, int idxSample, int countOfDataBytes);
DWFAPI int FDwfDigitalInStatusRecord(HDWF hdwf, int *pcdDataAvailable, int *pcdDataLost, int *pcdDataCorrupt);
DWFAPI int FDwfDigitalInStatusCompress(HDWF hdwf, int *pcdDataAvailable, int *pcdDataLost, int *pcdDataCorrupt);
DWFAPI int FDwfDigitalInStatusCompressed(HDWF hdwf, void *rgData, int countOfBytes); // value1,span1,value2,span2...
DWFAPI int FDwfDigitalInStatusCompressed2(HDWF hdwf, void *rgData, int idxSample, int countOfBytes);
DWFAPI int FDwfDigitalInStatusTime(HDWF hdwf, unsigned int *psecUtc, unsigned int *ptick, unsigned int *pticksPerSecond);

DWFAPI int FDwfDigitalInCounterInfo(HDWF hdwf, double *pcntMax, double *psecMax);
DWFAPI int FDwfDigitalInCounterSet(HDWF hdwf, double sec);
DWFAPI int FDwfDigitalInCounterGet(HDWF hdwf, double *psec);
DWFAPI int FDwfDigitalInCounterStatus(HDWF hdwf, double *pcnt, double *pfreq, int *ptick);

// Acquisition configuration:
DWFAPI int FDwfDigitalInInternalClockInfo(HDWF hdwf, double *phzFreq);

DWFAPI int FDwfDigitalInClockSourceInfo(HDWF hdwf, int *pfsDwfDigitalInClockSource); // use IsBitSet
DWFAPI int FDwfDigitalInClockSourceSet(HDWF hdwf, DwfDigitalInClockSource v);
DWFAPI int FDwfDigitalInClockSourceGet(HDWF hdwf, DwfDigitalInClockSource *pv);

DWFAPI int FDwfDigitalInDividerInfo(HDWF hdwf, unsigned int *pdivMax);
DWFAPI int FDwfDigitalInDividerSet(HDWF hdwf, unsigned int div);
DWFAPI int FDwfDigitalInDividerGet(HDWF hdwf, unsigned int *pdiv);

DWFAPI int FDwfDigitalInBitsInfo(HDWF hdwf, int *pnBits); // Returns the number of Digital In bits
DWFAPI int FDwfDigitalInSampleFormatSet(HDWF hdwf, int nBits);  // valid options 8/16/32
DWFAPI int FDwfDigitalInSampleFormatGet(HDWF hdwf, int *pnBits);

DWFAPI int FDwfDigitalInInputOrderSet(HDWF hdwf, int fDioFirst); // for Digital Discovery

DWFAPI int FDwfDigitalInBufferSizeInfo(HDWF hdwf, int *pnSizeMax);
DWFAPI int FDwfDigitalInBufferSizeSet(HDWF hdwf, int nSize);
DWFAPI int FDwfDigitalInBufferSizeGet(HDWF hdwf, int *pnSize);

DWFAPI int FDwfDigitalInSampleModeInfo(HDWF hdwf, int *pfsDwfDigitalInSampleMode); // use IsBitSet
DWFAPI int FDwfDigitalInSampleModeSet(HDWF hdwf, DwfDigitalInSampleMode v);
DWFAPI int FDwfDigitalInSampleModeGet(HDWF hdwf, DwfDigitalInSampleMode *pv);

DWFAPI int FDwfDigitalInSampleSensibleSet(HDWF hdwf, unsigned int fs);
DWFAPI int FDwfDigitalInSampleSensibleGet(HDWF hdwf, unsigned int *pfs);

DWFAPI int FDwfDigitalInAcquisitionModeInfo(HDWF hdwf, int *pfsacqmode); // use IsBitSet
DWFAPI int FDwfDigitalInAcquisitionModeSet(HDWF hdwf, ACQMODE acqmode);
DWFAPI int FDwfDigitalInAcquisitionModeGet(HDWF hdwf, ACQMODE *pacqmode);

// Trigger configuration:
DWFAPI int FDwfDigitalInTriggerSourceSet(HDWF hdwf, TRIGSRC trigsrc);
DWFAPI int FDwfDigitalInTriggerSourceGet(HDWF hdwf, TRIGSRC *ptrigsrc);

DWFAPI int FDwfDigitalInTriggerSlopeSet(HDWF hdwf, DwfTriggerSlope slope);
DWFAPI int FDwfDigitalInTriggerSlopeGet(HDWF hdwf, DwfTriggerSlope *pslope);

DWFAPI int FDwfDigitalInTriggerPositionInfo(HDWF hdwf, unsigned int *pnSamplesAfterTriggerMax);
DWFAPI int FDwfDigitalInTriggerPositionSet(HDWF hdwf, unsigned int cSamplesAfterTrigger);
DWFAPI int FDwfDigitalInTriggerPositionGet(HDWF hdwf, unsigned int *pcSamplesAfterTrigger);

DWFAPI int FDwfDigitalInTriggerPrefillSet(HDWF hdwf, unsigned int cSamplesBeforeTrigger);
DWFAPI int FDwfDigitalInTriggerPrefillGet(HDWF hdwf, unsigned int *pcSamplesBeforeTrigger);

DWFAPI int FDwfDigitalInTriggerAutoTimeoutInfo(HDWF hdwf, double *psecMin, double *psecMax, double *pnSteps);
DWFAPI int FDwfDigitalInTriggerAutoTimeoutSet(HDWF hdwf, double secTimeout);
DWFAPI int FDwfDigitalInTriggerAutoTimeoutGet(HDWF hdwf, double *psecTimeout);

DWFAPI int FDwfDigitalInTriggerInfo(HDWF hdwf, unsigned int *pfsLevelLow, unsigned int *pfsLevelHigh, unsigned int *pfsEdgeRise, unsigned int *pfsEdgeFall);
DWFAPI int FDwfDigitalInTriggerSet(HDWF hdwf, unsigned int fsLevelLow, unsigned int fsLevelHigh, unsigned int fsEdgeRise, unsigned int fsEdgeFall);
DWFAPI int FDwfDigitalInTriggerGet(HDWF hdwf, unsigned int *pfsLevelLow, unsigned int *pfsLevelHigh, unsigned int *pfsEdgeRise, unsigned int *pfsEdgeFall);
// the logic for trigger bits: Low and High and (Rise or Fall)
// bits set in Rise and Fall means any edge

DWFAPI int FDwfDigitalInTriggerResetSet(HDWF hdwf, unsigned int fsLevelLow, unsigned int fsLevelHigh, unsigned int fsEdgeRise, unsigned int fsEdgeFall);
DWFAPI int FDwfDigitalInTriggerCountSet(HDWF hdwf, int cCount, int fRestart);
DWFAPI int FDwfDigitalInTriggerLengthSet(HDWF hdwf, double secMin, double secMax, int idxSync);
DWFAPI int FDwfDigitalInTriggerMatchSet(HDWF hdwf, int iPin, unsigned int fsMask, unsigned int fsValue, int cBitStuffing);


// DIGITAL OUT INSTRUMENT FUNCTIONS
// Control:
DWFAPI int FDwfDigitalOutReset(HDWF hdwf);
DWFAPI int FDwfDigitalOutConfigure(HDWF hdwf, int fStart);
DWFAPI int FDwfDigitalOutStatus(HDWF hdwf, DwfState *psts);
DWFAPI int FDwfDigitalOutStatusOutput(HDWF hdwf, unsigned int *pfsValue, unsigned int *pfsEnable);

// Configuration:
DWFAPI int FDwfDigitalOutInternalClockInfo(HDWF hdwf, double *phzFreq);

DWFAPI int FDwfDigitalOutTriggerSourceSet(HDWF hdwf, TRIGSRC trigsrc);
DWFAPI int FDwfDigitalOutTriggerSourceGet(HDWF hdwf, TRIGSRC *ptrigsrc);

DWFAPI int FDwfDigitalOutRunInfo(HDWF hdwf, double *psecMin, double *psecMax);
DWFAPI int FDwfDigitalOutRunSet(HDWF hdwf, double secRun);
DWFAPI int FDwfDigitalOutRunGet(HDWF hdwf, double *psecRun);
DWFAPI int FDwfDigitalOutRunStatus(HDWF hdwf, double *psecRun);

DWFAPI int FDwfDigitalOutWaitInfo(HDWF hdwf, double *psecMin, double *psecMax);
DWFAPI int FDwfDigitalOutWaitSet(HDWF hdwf, double secWait);
DWFAPI int FDwfDigitalOutWaitGet(HDWF hdwf, double *psecWait);

DWFAPI int FDwfDigitalOutRepeatInfo(HDWF hdwf, unsigned int *pnMin, unsigned int *pnMax);
DWFAPI int FDwfDigitalOutRepeatSet(HDWF hdwf, unsigned int cRepeat);
DWFAPI int FDwfDigitalOutRepeatGet(HDWF hdwf, unsigned int *pcRepeat);
DWFAPI int FDwfDigitalOutRepeatStatus(HDWF hdwf, unsigned int *pcRepeat);

DWFAPI int FDwfDigitalOutTriggerSlopeSet(HDWF hdwf, DwfTriggerSlope slope);
DWFAPI int FDwfDigitalOutTriggerSlopeGet(HDWF hdwf, DwfTriggerSlope *pslope);

DWFAPI int FDwfDigitalOutRepeatTriggerSet(HDWF hdwf, int fRepeatTrigger);
DWFAPI int FDwfDigitalOutRepeatTriggerGet(HDWF hdwf, int *pfRepeatTrigger);

DWFAPI int FDwfDigitalOutCount(HDWF hdwf, int *pcChannel);
DWFAPI int FDwfDigitalOutEnableSet(HDWF hdwf, int idxChannel, int fEnable);
DWFAPI int FDwfDigitalOutEnableGet(HDWF hdwf, int idxChannel, int *pfEnable);

DWFAPI int FDwfDigitalOutOutputInfo(HDWF hdwf, int idxChannel, int *pfsDwfDigitalOutOutput); // use IsBitSet
DWFAPI int FDwfDigitalOutOutputSet(HDWF hdwf, int idxChannel, DwfDigitalOutOutput v);
DWFAPI int FDwfDigitalOutOutputGet(HDWF hdwf, int idxChannel, DwfDigitalOutOutput *pv);

DWFAPI int FDwfDigitalOutTypeInfo(HDWF hdwf, int idxChannel, int *pfsDwfDigitalOutType); // use IsBitSet
DWFAPI int FDwfDigitalOutTypeSet(HDWF hdwf, int idxChannel, DwfDigitalOutType v);
DWFAPI int FDwfDigitalOutTypeGet(HDWF hdwf, int idxChannel, DwfDigitalOutType *pv);

DWFAPI int FDwfDigitalOutIdleInfo(HDWF hdwf, int idxChannel, int *pfsDwfDigitalOutIdle); // use IsBitSet
DWFAPI int FDwfDigitalOutIdleSet(HDWF hdwf, int idxChannel, DwfDigitalOutIdle v);
DWFAPI int FDwfDigitalOutIdleGet(HDWF hdwf, int idxChannel, DwfDigitalOutIdle *pv);

DWFAPI int FDwfDigitalOutDividerInfo(HDWF hdwf, int idxChannel, unsigned int *vMin, unsigned int *vMax);
DWFAPI int FDwfDigitalOutDividerInitSet(HDWF hdwf, int idxChannel, unsigned int v);
DWFAPI int FDwfDigitalOutDividerInitGet(HDWF hdwf, int idxChannel, unsigned int *pv);
DWFAPI int FDwfDigitalOutDividerSet(HDWF hdwf, int idxChannel, unsigned int v);
DWFAPI int FDwfDigitalOutDividerGet(HDWF hdwf, int idxChannel, unsigned int *pv);

DWFAPI int FDwfDigitalOutCounterInfo(HDWF hdwf, int idxChannel, unsigned int *vMin, unsigned int *vMax);
DWFAPI int FDwfDigitalOutCounterInitSet(HDWF hdwf, int idxChannel, int fHigh, unsigned int v);
DWFAPI int FDwfDigitalOutCounterInitGet(HDWF hdwf, int idxChannel, int *pfHigh, unsigned int *pv);
DWFAPI int FDwfDigitalOutCounterSet(HDWF hdwf, int idxChannel, unsigned int vLow, unsigned int vHigh);
DWFAPI int FDwfDigitalOutCounterGet(HDWF hdwf, int idxChannel, unsigned int *pvLow, unsigned int *pvHigh);

// ADP3X50
DWFAPI int FDwfDigitalOutRepetitionInfo(HDWF hdwf, int idxChannel, unsigned int *pnMax);
DWFAPI int FDwfDigitalOutRepetitionSet(HDWF hdwf, int idxChannel, unsigned int cRepeat);
DWFAPI int FDwfDigitalOutRepetitionGet(HDWF hdwf, int idxChannel, unsigned int *pcRepeat);

DWFAPI int FDwfDigitalOutDataInfo(HDWF hdwf, int idxChannel, unsigned int *pcountOfBitsMax);
DWFAPI int FDwfDigitalOutDataSet(HDWF hdwf, int idxChannel, void *rgBits, unsigned int countOfBits);
// bits order is lsb first
// for TS output the count of bits its the total number of IO|OE bits, it should be an even number
// BYTE:   0                 |1     ...
// bit:    0 |1 |2 |3 |...|7 |0 |1 |...
// sample: IO|OE|IO|OE|...|OE|IO|OE|...

DWFAPI int FDwfDigitalOutPlayDataSet(HDWF hdwf, unsigned char *rgBits, unsigned int bitPerSample, unsigned int countOfSamples);
DWFAPI int FDwfDigitalOutPlayUpdateSet(HDWF hdwf, unsigned char *rgBits, unsigned int indexOfSample, unsigned int countOfSamples);
DWFAPI int FDwfDigitalOutPlayRateSet(HDWF hdwf, double hzRate);

// UART
DWFAPI int FDwfDigitalUartReset(HDWF hdwf);
DWFAPI int FDwfDigitalUartRateSet(HDWF hdwf, double hz);
DWFAPI int FDwfDigitalUartBitsSet(HDWF hdwf, int cBits);
DWFAPI int FDwfDigitalUartParitySet(HDWF hdwf, int parity); // 0 none, 1 odd, 2 even
DWFAPI int FDwfDigitalUartPolaritySet(HDWF hdwf, int polarity); // 0 normal, 1 inverted
DWFAPI int FDwfDigitalUartStopSet(HDWF hdwf, double cBit);
DWFAPI int FDwfDigitalUartTxSet(HDWF hdwf, int idxChannel);
DWFAPI int FDwfDigitalUartRxSet(HDWF hdwf, int idxChannel);

DWFAPI int FDwfDigitalUartTx(HDWF hdwf, char *szTx, int cTx);
DWFAPI int FDwfDigitalUartRx(HDWF hdwf, char *szRx, int cRx, int *pcRx, int *pParity);

// SPI
DWFAPI int FDwfDigitalSpiReset(HDWF hdwf);
DWFAPI int FDwfDigitalSpiFrequencySet(HDWF hdwf, double hz);
DWFAPI int FDwfDigitalSpiClockSet(HDWF hdwf, int idxChannel);
DWFAPI int FDwfDigitalSpiDataSet(HDWF hdwf, int idxDQ, int idxChannel); // 0 DQ0_MOSI_SISO, 1 DQ1_MISO, 2 DQ2, 3 DQ3
DWFAPI int FDwfDigitalSpiIdleSet(HDWF hdwf, int idxDQ, DwfDigitalOutIdle idle);
DWFAPI int FDwfDigitalSpiModeSet(HDWF hdwf, int iMode); // bit1 CPOL, bit0 CPHA
DWFAPI int FDwfDigitalSpiOrderSet(HDWF hdwf, int fMSBFirst); // bit order: 1 MSB first, 0 LSB first
DWFAPI int FDwfDigitalSpiDelaySet(HDWF hdwf, int cStart, int cCmd, int cWord, int cStop); // clock cycles delays
DWFAPI int FDwfDigitalSpiSelectSet(HDWF hdwf, int idxSelect, int fIdle); // chip select DIO, idle 0-low 1-high

DWFAPI int FDwfDigitalSpiSelect(HDWF hdwf, int idxChannel, int level); // software control for select 0 low, 1 high, -1 Z
// cDQ 0 SISO, 1 MOSI/MISO, 2 dual, 4 quad, // 1-32 bits / word
DWFAPI int FDwfDigitalSpiWriteRead(HDWF hdwf, int cDQ, int cBitPerWord, unsigned char *rgTX, int cTX, unsigned char *rgRX, int cRX);
DWFAPI int FDwfDigitalSpiWriteRead16(HDWF hdwf, int cDQ, int cBitPerWord, unsigned short *rgTX, int cTX, unsigned short *rgRX, int cRX);
DWFAPI int FDwfDigitalSpiWriteRead32(HDWF hdwf, int cDQ, int cBitPerWord, unsigned int *rgTX, int cTX, unsigned int *rgRX, int cRX);
DWFAPI int FDwfDigitalSpiRead(HDWF hdwf, int cDQ, int cBitPerWord, unsigned char *rgRX, int cRX);
DWFAPI int FDwfDigitalSpiReadOne(HDWF hdwf, int cDQ, int cBitPerWord, unsigned int *pRX);
DWFAPI int FDwfDigitalSpiRead16(HDWF hdwf, int cDQ, int cBitPerWord, unsigned short *rgRX, int cRX);
DWFAPI int FDwfDigitalSpiRead32(HDWF hdwf, int cDQ, int cBitPerWord, unsigned int *rgRX, int cRX);
DWFAPI int FDwfDigitalSpiWrite(HDWF hdwf, int cDQ, int cBitPerWord, unsigned char *rgTX, int cTX);
DWFAPI int FDwfDigitalSpiWriteOne(HDWF hdwf, int cDQ, int cBits, unsigned int vTX);
DWFAPI int FDwfDigitalSpiWrite16(HDWF hdwf, int cDQ, int cBitPerWord, unsigned short *rgTX, int cTX);
DWFAPI int FDwfDigitalSpiWrite32(HDWF hdwf, int cDQ, int cBitPerWord, unsigned int *rgTX, int cTX);

DWFAPI int FDwfDigitalSpiCmdWriteRead(HDWF hdwf, int cBitCmd, unsigned int cmd, int cDummy, int cDQ, int cBitPerWord, unsigned char *rgTX, int cTX, unsigned char *rgRX, int cRX);
DWFAPI int FDwfDigitalSpiCmdWriteRead16(HDWF hdwf, int cBitCmd, unsigned int cmd, int cDummy, int cDQ, int cBitPerWord, unsigned short *rgTX, int cTX, unsigned short *rgRX, int cRX);
DWFAPI int FDwfDigitalSpiCmdWriteRead32(HDWF hdwf, int cBitCmd, unsigned int cmd, int cDummy, int cDQ, int cBitPerWord, unsigned int *rgTX, int cTX, unsigned int *rgRX, int cRX);
DWFAPI int FDwfDigitalSpiCmdRead(HDWF hdwf, int cBitCmd, unsigned int cmd, int cDummy, int cDQ, int cBitPerWord, unsigned char *rgRX, int cRX);
DWFAPI int FDwfDigitalSpiCmdReadOne(HDWF hdwf, int cBitCmd, unsigned int cmd, int cDummy, int cDQ, int cBitPerWord, unsigned int *pRX);
DWFAPI int FDwfDigitalSpiCmdRead16(HDWF hdwf, int cBitCmd, unsigned int cmd, int cDummy, int cDQ, int cBitPerWord, unsigned short *rgRX, int cRX);
DWFAPI int FDwfDigitalSpiCmdRead32(HDWF hdwf, int cBitCmd, unsigned int cmd, int cDummy, int cDQ, int cBitPerWord, unsigned int *rgRX, int cRX);
DWFAPI int FDwfDigitalSpiCmdWrite(HDWF hdwf, int cBitCmd, unsigned int cmd, int cDummy, int cDQ, int cBitPerWord, unsigned char *rgTX, int cTX);
DWFAPI int FDwfDigitalSpiCmdWriteOne(HDWF hdwf, int cBitCmd, unsigned int cmd, int cDummy, int cDQ, int cBits, unsigned int vTX);
DWFAPI int FDwfDigitalSpiCmdWrite16(HDWF hdwf, int cBitCmd, unsigned int cmd, int cDummy, int cDQ, int cBitPerWord, unsigned short *rgTX, int cTX);
DWFAPI int FDwfDigitalSpiCmdWrite32(HDWF hdwf, int cBitCmd, unsigned int cmd, int cDummy, int cDQ, int cBitPerWord, unsigned int *rgTX, int cTX);



// I2C
DWFAPI int FDwfDigitalI2cReset(HDWF hdwf);
DWFAPI int FDwfDigitalI2cClear(HDWF hdwf, int *pfFree);
DWFAPI int FDwfDigitalI2cStretchSet(HDWF hdwf, int fEnable);
DWFAPI int FDwfDigitalI2cRateSet(HDWF hdwf, double hz);
DWFAPI int FDwfDigitalI2cReadNakSet(HDWF hdwf, int fNakLastReadByte);
DWFAPI int FDwfDigitalI2cSclSet(HDWF hdwf, int idxChannel);
DWFAPI int FDwfDigitalI2cSdaSet(HDWF hdwf, int idxChannel);
DWFAPI int FDwfDigitalI2cTimeoutSet(HDWF hdwf, double sec);

DWFAPI int FDwfDigitalI2cWriteRead(HDWF hdwf, unsigned char adr8bits, unsigned char *rgbTx, int cTx, unsigned char *rgRx, int cRx, int *pNak);
DWFAPI int FDwfDigitalI2cRead(HDWF hdwf, unsigned char adr8bits, unsigned char *rgbRx, int cRx, int *pNak);
DWFAPI int FDwfDigitalI2cWrite(HDWF hdwf, unsigned char adr8bits, unsigned char *rgbTx, int cTx, int *pNak);
DWFAPI int FDwfDigitalI2cWriteOne(HDWF hdwf, unsigned char adr8bits, unsigned char bTx, int *pNak);

DWFAPI int FDwfDigitalI2cSpyStart(HDWF hdwf);
DWFAPI int FDwfDigitalI2cSpyStatus(HDWF hdwf, int *fStart, int *fStop, unsigned char *rgData, int *cData, int *iNak);

// CAN
DWFAPI int FDwfDigitalCanReset(HDWF hdwf);
DWFAPI int FDwfDigitalCanRateSet(HDWF hdwf, double hz);
DWFAPI int FDwfDigitalCanPolaritySet(HDWF hdwf, int fHigh); // 0 low, 1 high
DWFAPI int FDwfDigitalCanTxSet(HDWF hdwf, int idxChannel);
DWFAPI int FDwfDigitalCanRxSet(HDWF hdwf, int idxChannel);

DWFAPI int FDwfDigitalCanTx(HDWF hdwf, int vID, int fExtended, int fRemote, int cDLC, unsigned char *rgTX);
DWFAPI int FDwfDigitalCanRx(HDWF hdwf, int *pvID, int *pfExtended, int *pfRemote, int *pcDLC, unsigned char *rgRX, int cRX, int *pvStatus);

// SWD
DWFAPI int FDwfDigitalSwdReset(HDWF hdwf);
DWFAPI int FDwfDigitalSwdRateSet(HDWF hdwf, double hz);
DWFAPI int FDwfDigitalSwdCkSet(HDWF hdwf, int idxChannel);
DWFAPI int FDwfDigitalSwdIoSet(HDWF hdwf, int idxChannel);
DWFAPI int FDwfDigitalSwdTurnSet(HDWF hdwf, int cTurn);
DWFAPI int FDwfDigitalSwdTrailSet(HDWF hdwf, int cTrail);
DWFAPI int FDwfDigitalSwdParkSet(HDWF hdwf, int fDrive);
DWFAPI int FDwfDigitalSwdNakSet(HDWF hdwf, int fContinue);
DWFAPI int FDwfDigitalSwdIoIdleSet(HDWF hdwf, int fHigh);
DWFAPI int FDwfDigitalSwdClear(HDWF hdwf, int cReset, int cTrail);
DWFAPI int FDwfDigitalSwdWrite(HDWF hdwf, int APnDP, int A32, int *pAck, unsigned int Write);
DWFAPI int FDwfDigitalSwdRead(HDWF hdwf, int APnDP, int A32, int *pAck, unsigned int *pRead, int *pCrc);


// Impedance
DWFAPI int FDwfAnalogImpedanceReset(HDWF hdwf);
DWFAPI int FDwfAnalogImpedanceModeSet(HDWF hdwf, int mode); // 0 W1-C1-DUT-C2-R-GND, 1 W1-C1-R-C2-DUT-GND, 8 Impedance Analyzer for AD
DWFAPI int FDwfAnalogImpedanceModeGet(HDWF hdwf, int *mode);
DWFAPI int FDwfAnalogImpedanceReferenceSet(HDWF hdwf, double ohms);
DWFAPI int FDwfAnalogImpedanceReferenceGet(HDWF hdwf, double *pohms);
DWFAPI int FDwfAnalogImpedanceFrequencySet(HDWF hdwf, double hz);
DWFAPI int FDwfAnalogImpedanceFrequencyGet(HDWF hdwf, double *phz);
DWFAPI int FDwfAnalogImpedanceAmplitudeSet(HDWF hdwf, double volts);
DWFAPI int FDwfAnalogImpedanceAmplitudeGet(HDWF hdwf, double *pvolts);
DWFAPI int FDwfAnalogImpedanceOffsetSet(HDWF hdwf, double volts);
DWFAPI int FDwfAnalogImpedanceOffsetGet(HDWF hdwf, double *pvolts);
DWFAPI int FDwfAnalogImpedanceProbeSet(HDWF hdwf, double ohmRes, double faradCap);
DWFAPI int FDwfAnalogImpedanceProbeGet(HDWF hdwf, double *pohmRes, double *pfaradCap);
DWFAPI int FDwfAnalogImpedancePeriodSet(HDWF hdwf, int cMinPeriods);
DWFAPI int FDwfAnalogImpedancePeriodGet(HDWF hdwf, int *cMinPeriods);
DWFAPI int FDwfAnalogImpedanceCompReset(HDWF hdwf);
DWFAPI int FDwfAnalogImpedanceCompSet(HDWF hdwf, double ohmOpenResistance, double ohmOpenReactance, double ohmShortResistance, double ohmShortReactance);
DWFAPI int FDwfAnalogImpedanceCompGet(HDWF hdwf, double *pohmOpenResistance, double *pohmOpenReactance, double *pohmShortResistance, double *pohmShortReactance);
DWFAPI int FDwfAnalogImpedanceConfigure(HDWF hdwf, int fStart); // 1 start, 0 stop
DWFAPI int FDwfAnalogImpedanceStatus(HDWF hdwf, DwfState *psts);
DWFAPI int FDwfAnalogImpedanceStatusInput(HDWF hdwf, int idxChannel, double *pgain, double *pradian);
DWFAPI int FDwfAnalogImpedanceStatusWarning(HDWF hdwf, int idxChannel, int *pWarning);
DWFAPI int FDwfAnalogImpedanceStatusMeasure(HDWF hdwf, DwfAnalogImpedance measure, double *pvalue);

// Miscellaneous
DWFAPI int FDwfSpectrumWindow(double *rgdWin, int cdWin, DwfWindow iWindow, const double vBeta, double *vNEBW);
DWFAPI int FDwfSpectrumFFT(const double *rgdData, int cdData, double *rgdBin, double *rgdPhase, int cdBin);
DWFAPI int FDwfSpectrumTransform(const double *rgdData, int cdData, double *rgdBin, double *rgdPhase, int cdBin, double iFirst, double iLast);


// OBSOLETE but supported, avoid using the following in new projects:
const DwfParam DwfParamKeepOnClose     = 1; // keep the device running after close, use DwfParamOnClose

// use FDwfDigitalInTriggerSourceSet trigsrcAnalogIn
// call FDwfDigitalInConfigure before FDwfAnalogInConfigure
DWFAPI int FDwfDigitalInMixedSet(HDWF hdwf, int fEnable);

// use DwfTriggerSlope
typedef int TRIGCOND;
const TRIGCOND trigcondRisingPositive   = 0;
const TRIGCOND trigcondFallingNegative  = 1;

// use FDwfDeviceTriggerInfo(hdwf, ptrigsrcInfo);
DWFAPI int FDwfAnalogInTriggerSourceInfo(HDWF hdwf, int *pfstrigsrc); // use IsBitSet
DWFAPI int FDwfAnalogOutTriggerSourceInfo(HDWF hdwf, int idxChannel, int *pfstrigsrc); // use IsBitSet
DWFAPI int FDwfDigitalInTriggerSourceInfo(HDWF hdwf, int *pfstrigsrc); // use IsBitSet
DWFAPI int FDwfDigitalOutTriggerSourceInfo(HDWF hdwf, int *pfstrigsrc); // use IsBitSet

// use DwfState
typedef unsigned char STS;
const STS stsRdy        = 0;
const STS stsArm        = 1;
const STS stsDone       = 2;
const STS stsTrig       = 3;
const STS stsCfg        = 4;
const STS stsPrefill    = 5;
const STS stsNotDone    = 6;
const STS stsTrigDly    = 7;
const STS stsError      = 8;
const STS stsBusy       = 9;
const STS stsStop       = 10;


// use FDwfAnalogOutNode*
DWFAPI int FDwfAnalogOutEnableSet(HDWF hdwf, int idxChannel, int fEnable);
DWFAPI int FDwfAnalogOutEnableGet(HDWF hdwf, int idxChannel, int *pfEnable);
DWFAPI int FDwfAnalogOutFunctionInfo(HDWF hdwf, int idxChannel, unsigned int *pfsfunc); // use IsBitSet
DWFAPI int FDwfAnalogOutFunctionSet(HDWF hdwf, int idxChannel, FUNC func);
DWFAPI int FDwfAnalogOutFunctionGet(HDWF hdwf, int idxChannel, FUNC *pfunc);
DWFAPI int FDwfAnalogOutFrequencyInfo(HDWF hdwf, int idxChannel, double *phzMin, double *phzMax);
DWFAPI int FDwfAnalogOutFrequencySet(HDWF hdwf, int idxChannel, double hzFrequency);
DWFAPI int FDwfAnalogOutFrequencyGet(HDWF hdwf, int idxChannel, double *phzFrequency);
DWFAPI int FDwfAnalogOutAmplitudeInfo(HDWF hdwf, int idxChannel, double *pvoltsMin, double *pvoltsMax);
DWFAPI int FDwfAnalogOutAmplitudeSet(HDWF hdwf, int idxChannel, double voltsAmplitude);
DWFAPI int FDwfAnalogOutAmplitudeGet(HDWF hdwf, int idxChannel, double *pvoltsAmplitude);
DWFAPI int FDwfAnalogOutOffsetInfo(HDWF hdwf, int idxChannel, double *pvoltsMin, double *pvoltsMax);
DWFAPI int FDwfAnalogOutOffsetSet(HDWF hdwf, int idxChannel, double voltsOffset);
DWFAPI int FDwfAnalogOutOffsetGet(HDWF hdwf, int idxChannel, double *pvoltsOffset);
DWFAPI int FDwfAnalogOutSymmetryInfo(HDWF hdwf, int idxChannel, double *ppercentageMin, double *ppercentageMax);
DWFAPI int FDwfAnalogOutSymmetrySet(HDWF hdwf, int idxChannel, double percentageSymmetry);
DWFAPI int FDwfAnalogOutSymmetryGet(HDWF hdwf, int idxChannel, double *ppercentageSymmetry);
DWFAPI int FDwfAnalogOutPhaseInfo(HDWF hdwf, int idxChannel, double *pdegreeMin, double *pdegreeMax);
DWFAPI int FDwfAnalogOutPhaseSet(HDWF hdwf, int idxChannel, double degreePhase);
DWFAPI int FDwfAnalogOutPhaseGet(HDWF hdwf, int idxChannel, double *pdegreePhase);
DWFAPI int FDwfAnalogOutDataInfo(HDWF hdwf, int idxChannel, int *pnSamplesMin, int *pnSamplesMax);
DWFAPI int FDwfAnalogOutDataSet(HDWF hdwf, int idxChannel, double *rgdData, int cdData);
DWFAPI int FDwfAnalogOutPlayStatus(HDWF hdwf, int idxChannel, int *cdDataFree, int *cdDataLost, int *cdDataCorrupted);
DWFAPI int FDwfAnalogOutPlayData(HDWF hdwf, int idxChannel, double *rgdData, int cdData);

// use FDwfAnalogInChannelCount
DWFAPI int FDwfEnumAnalogInChannels(int idxDevice, int *pnChannels);
// use FDwfEnumConfigInfo
DWFAPI int FDwfEnumAnalogInBufferSize(int idxDevice, int *pnBufferSize);
// use FDwfAnalogInBitsInfo
DWFAPI int FDwfEnumAnalogInBits(int idxDevice, int *pnBits);
// use FDwfEnumAnalogInFrequency
DWFAPI int FDwfEnumAnalogInFrequency(int idxDevice, double *phzFrequency);

// use device ID
const ENUMFILTER enumfilterEExplorer    = 1;
const ENUMFILTER enumfilterDiscovery    = 2;
const ENUMFILTER enumfilterDiscovery2   = 3;
const ENUMFILTER enumfilterDDiscovery   = 4;


#endif
