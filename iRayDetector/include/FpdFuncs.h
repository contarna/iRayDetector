/******************************************************************
**  FileName   : FpdFuncs.h
**
**  Description: This is the main interface definition file.
**  
**  Copyright  : iRay Technology (Shanghai) Ltd.
******************************************************************/

#ifndef _FPD_FUNCS_
#define _FPD_FUNCS_

#ifndef FPD_API
	#define FPD_API  extern "C" __declspec(dllimport)
#endif

/*========================================Hardware============================================*/
FPD_API int FPD_Reset(HANDLE hID);
FPD_API int FPD_Acq(HANDLE hID);
FPD_API int FPD_StartSequ(HANDLE hID);
FPD_API int FPD_StopSequ(HANDLE hID);
FPD_API int FPD_Prep(HANDLE hID);
FPD_API int FPD_PrepAcq(HANDLE hID, int nDelayTime);
FPD_API int FPD_RecoverImage(HANDLE hID, int nPackNumStart, int nPackNumEnd);
FPD_API int FPD_EnableDetector(HANDLE hID, char* pIP1, char* pIP2);
FPD_API int FPD_ReadDetectorStatus(HANDLE hID);
FPD_API int FPD_SleepDetector(HANDLE hID);
FPD_API int FPD_WakeDetector(HANDLE hID);
FPD_API int FPD_ReadFactoryConfiguration(HANDLE hID);
FPD_API int FPD_ResetFactoryConfiguration(HANDLE hID);
FPD_API int FPD_ReadDetectorLog(HANDLE hID);
FPD_API int FPD_WriteConfiguration(HANDLE hID, ConfigMode configMode, ConfigInfo configInfo);
FPD_API int FPD_ReadConfiguration(HANDLE hID);
FPD_API int FPD_ReadTemperature(HANDLE hID);
FPD_API int FPD_ReadHumidity(HANDLE hID);
FPD_API int FPD_WriteControlboxConfiguration(HANDLE hID, ConfigMode configMode, ControlboxInfo controlInfo);// Reserved
FPD_API int FPD_ReadControlboxConfiguration(HANDLE hID);	// Reserved
FPD_API int PD_WriteDetectorUpdateMode(HANDLE hID, UptFirmwareMode firmwareMode, UptCorrectMode correctMode);
FPD_API int FPD_UploadUpdateData(HANDLE hID, UptFirmwareMode fwMode, UptCorrectMode corrMode, char* pData, int nSize);
FPD_API int FPD_ReadExpInfo(HANDLE hID);
FPD_API int FPD_ReadDetectorVersion(HANDLE hID);
FPD_API int FPD_CloseExposureWindow(HANDLE hID);
/*=========================================Software=============================================*/
FPD_API int FPD_Initialize(InitializeInfo initInfo, IdInfo &idInfo, DRCallback pDrCallback);
FPD_API int FPD_GetDetectorStatus(HANDLE hID, DetectorStatus &detectStatus);
FPD_API int FPD_GetDetectorError(HANDLE hID, int &nErrNumber);
FPD_API int FPD_GetDetectError(int &nErrNumber, char *&strErrMessage);
FPD_API int FPD_GetDetectorConfiguration(HANDLE hID, ConfigInfo &configInfo);
FPD_API int FPD_GetControlboxConfiguration(HANDLE hID, ControlboxInfo &controlInfo);
FPD_API int FPD_GetDetectorLog(HANDLE hID, DetectorLog &detectLog);
FPD_API int FPD_GetDetectorExpInfo(HANDLE hID, ExposureInfo &expInfo);
FPD_API int FPD_OffsetGeneration(HANDLE hID, int nFrames);
FPD_API int FPD_AbortOffsetGeneration(HANDLE hID);
FPD_API int FPD_GainGeneration(HANDLE hID, int nFramesH, int nFramesL);
FPD_API int FPD_AbortGainGeneration(HANDLE hID);
FPD_API int FPD_DefectMapGeneration(HANDLE hID, int nFramesH, int nFramesL);
FPD_API int FPD_MaxResponseGeneration(HANDLE hID);
FPD_API int FPD_SetPreOffsetCorrection(HANDLE hID, bool bDoOffset);
FPD_API int FPD_SetPostOffsetCorrection(HANDLE hID, bool bDoOffset);
FPD_API int FPD_SetGainCorrection(HANDLE hID, bool bDoGain, CorrectMode correctMode);
FPD_API int FPD_SetDefectCorrection(HANDLE hID, bool bDoDefect, CorrectMode correctMode);
FPD_API int FPD_GetCorrectionStatus(HANDLE hID, bool &bDoOffset, bool &bDoGain, bool &bDoDefect);
FPD_API int FPD_SetFlipRotate(HANDLE hID, ImageFlipRotateMode imgMode);
FPD_API int FPD_InitDefectMapData(int nWidth, int nHeight);
FPD_API int FPD_ModifyDefectMap(DefectType defectType, DefectModifyMode modifyMode, int iX1, int iY1, int iX2, int iY2);
FPD_API int FPD_SaveDefectMapFile(char* strFullPathFile);
FPD_API int FPD_CloseDefectMapData();
FPD_API int FPD_DY_InitGainCorrection(HANDLE hID);
FPD_API int FPD_DY_SelectLightImage(HANDLE hID, int nNewGain, int nCurImage);
FPD_API int FPD_DY_CorrectGeneration(HANDLE hID, char* pPath, int nWidth, int nHeight);
FPD_API int FPD_DY_MaxResponseGeneration(HANDLE hID);
FPD_API int FPD_GetAutoClearMode(HANDLE hID, bool &bDoAutoClear);
FPD_API int FPD_SetDoAutoClear(HANDLE hID, bool bDoAutoClear);
FPD_API int FPD_SY_Initialize(SyncBoxCallback hSyncBoxCallback);
FPD_API int FPD_SY_Close();
FPD_API int FPD_SY_SendExposure();
FPD_API int FPD_SY_SendEnable();
FPD_API int FPD_SY_WriteConfiguration(ConfigMode configMode, SyncboxInfo syncInfo);
FPD_API int FPD_SY_GetSyncboxConfiguration(SyncboxInfo &syncInfo);
FPD_API int FPD_Close(IdInfo idInfo);
FPD_API int FPD_Open(HANDLE hID);
FPD_API int FPD_InitFWUpdata(HANDLE hID,UptFirmwareMode uptFWMode, char* pPathFile);
FPD_API int FPD_StartFWUpdata(HANDLE hID);
FPD_API int FPD_GetFWUpdataProcess(HANDLE hID, float &fProgress);
FPD_API int FPD_Initialize2(InitializeInfo initInfo, IdInfo &idInfo);
FPD_API int FPD_RegisterCallback(HANDLE hID, DRCallback pDrCallback);
FPD_API int FPD_GetImageSize(HANDLE hID, int &nWidth, int &nHeight);
FPD_API int FPD_SI_GainGeneration(HANDLE hID, int nCurrentIndex, int nTotalFrame);
FPD_API int FPD_SI_OffsetGeneration(HANDLE hID, int nFrames);
FPD_API int FPD_SI_AbortCalibration(HANDLE hID);
FPD_API int FPD_GetVoltages(HANDLE hID, char *&strVT);
FPD_API int FPD_GetNetworkParameter(HANDLE hID, char *&strParameter, NetInfo &netInfo, DetectorNetInfo &deteNetInfo);
FPD_API int FPD_GetFWVersion(HANDLE hID, char *&strFWName, char *&strFWVersion);
FPD_API int FPD_GetDllVersion(HANDLE hID, char *&strDllName, char *&strDllVersion);
FPD_API int FPD_GetTemperature(HANDLE hID, TemperatureInfo &tempInfo);
FPD_API int FPD_GetShockSensorValue(HANDLE hID, char *&strShockSensorValue);
FPD_API int FPD_GetAcqMode(HANDLE hID, int &iMode);
FPD_API int FPD_SetAcqMode(HANDLE hID, int iMode);
FPD_API int FPD_InitApplyCorrection(HANDLE hID, bool bApplyCorrection);
FPD_API int FPD_ApplyCorrection(HANDLE hID, WORD *pImageInOut, BOOL bDoGain, BOOL bDoDefect);
FPD_API int FPD_GetSerialNumber(HANDLE hID, char *&strSerialNumber);
FPD_API int FPD_SetFlipRotateEx(HANDLE hID, int FlipX, int FlipY, int Rotate90);
FPD_API int FPD_GetPixelSize(HANDLE hID, int &nPixelSize);
FPD_API int FPD_SetMultCorrectFolder(HANDLE hID, int nFolder);
FPD_API INT FPD_GigeReturnExposureImage(HANDLE hID, int iMode, int nTimes);
FPD_API int FPD_M_GainInit(HANDLE hID);
FPD_API int FPD_M_GainSelect(HANDLE hID);
FPD_API int FPD_M_GainSave(HANDLE hID);
FPD_API int FPD_M_GainUnload(HANDLE hID);
FPD_API int FPD_GetMultCorrectFolder(HANDLE hID, int &nFolder);
FPD_API int FPD_SetExposureMode(HANDLE hID, int nExpMode);
FPD_API int FPD_GetExposureMode(HANDLE hID, int &nExpMode);
FPD_API int FPD_ReadGridSensorStatus(HANDLE hID);
FPD_API int FPD_ReadShockSensorLog(HANDLE hID);
FPD_API int FPD_ClearUserShockSensorLog(HANDLE hID);
FPD_API int FPD_WriteUserShockSensorThreshold(HANDLE hID, float fThreshold);
FPD_API int FPD_ReadUserShockSensorThreshold(HANDLE hID);
FPD_API int FPD_ReloadFW(HANDLE hID, UptFirmwareMode uptFWMode);
FPD_API int FPD_GigeReturnExposureImage(HANDLE hID, int iMode, int nTimes);
/*=========================================Protocol E4=============================================*/
FPD_API int FPD_ScanDetectors();
FPD_API int FPD_SwitchSSID(HANDLE hID, char* ssid, char* password);
FPD_API int FPD_GetWifiStatus(HANDLE hID);

#endif