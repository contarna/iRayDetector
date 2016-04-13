/****************************************************************** 
**  FileName   : FpdErrors.h
**
**  Description: This is the error codes and associated error strings file.
**  
**  Copyright  : iRay Technology (Shanghai) Ltd.
******************************************************************/ 

#ifndef _FPD_ERRORS_
#define _FPD_ERRORS_

#define FPD_NO_ERR							0
#define FPD_READ_FILE_ERR					1
#define FPD_WRITE_FILE_ERR					2
#define FPD_ADAPTER_OBJECT_ERR				3
#define FPD_DETECTOR_CONN_ERR				4
#define FPD_A_DETECTOR_CONN_ERR				5
#define FPD_B_DETECTOR_CONN_ERR				6
#define FPD_A_B_DETECTOR_CONN_ERR			7
#define FPD_DETECTOR_CLOSE_ERR				8
#define FPD_A_DETECTOR_CLOSE_ERR			9
#define FPD_B_DETECTOR_CLOSE_ERR			10
#define FPD_A_B_DETECTOR_CLOSE_ERR			11		
#define FPD_REGISTER_CALLBACK_ERR			12
#define FPD_A_DETECTOR_OPEN_ERR				13
#define FPD_B_DETECTOR_OPEN_ERR				14
#define FPD_CREATE_STATIC_OFFSET_ERR		15
#define FPD_CREATE_DYNAMIC_OFFSET_ERR		16
#define FPD_CREATE_GAIN_ERR					17
#define FPD_CREATE_DEFECT_ERR				18
#define FPD_CREATE_DEFECT_INFO_ERR			19
#define FPD_CREATE_MAX_RESPONSE_ERR			20
#define FPD_SET_PRE_OFFSET_CORR_ERR			21
#define FPD_SET_POST_OFFSET_CORR_ERR		22
#define FPD_SET_GAIN_CORR_ERR				23
#define FPD_SET_DEFECT_CORR_ERR				24
#define FPD_GET_CORRECTION_STATUS_ERR		25
#define FPD_SET_FLIP_ROTATE_ERR				26
#define FPD_GET_DETECTOR_STATUS_ERR			27
#define FPD_GET_DETECTOR_ERROR_ERR			28
#define FPD_SET_CONFIG_ERR					29
#define FPD_OTHER_ERR						30
#define FPD_SET_UPDATE_MODE_ERR				31
#define FPD_SET_UPLOAD_DATA_ERR				32
#define FPD_RECOVER_IMAGE_ERR				33
#define FPD_INIT_DEFECT_MAP_DATA_ERR		34
#define FPD_MODIFY_DEFECT_MAP_ERR			35
#define FPD_SAVE_DEFECT_MAP_FILE_ERR		36
#define FPD_CLOSE_DEFECT_MAP_DATA_ERR		37
#define FPD_GET_DETECTOR_CONFIG_ERR			38
#define FPD_GET_CONTROL_BOX_CONFIG_ERR		39
#define FPD_GET_SYNC_BOX_CONFIG_ERR			40
#define FPD_GET_DETECTOR_LOG_ERR			41
#define FPD_GET_DETECTOR_EXP_INFO_ERR		42
#define FPD_SYNC_BOX_INIT_ERR				43
#define FPD_SYNC_BOX_CLOSE_ERR				44
#define FPD_SYNC_BOX_SEND_EXP_ERR			45
#define FPD_SYNC_BOX_ENABLE_ERR				46
#define FPD_SYNC_BOX_CONFIG_ERR				47
#define FPD_CMD_SEND_ERR					48
#define FPD_DY_INIT_GAIN_CORR_ERR			49
#define FPD_DY_SELECT_LIGHT_CORR_ERR		50
#define FPD_DY_CREATE_GAIN_ERR				51
#define FPD_DY_CREATE_DEFECT_ERR			52
#define FPD_DY_CREATE_MAX_RESPONSE_ERR		53
#define FPD_GET_AUTO_CLEAR_MODE_ERR			54
#define FPD_SET_DO_AUTO_CLEAR_ERR			55
#define FPD_ERROR_NOT_OPENED				56
#define FPD_ERROR_FAILURE					57
#define FPD_BAD_FILE_PATH_ERR				58
#define FPD_CREATE_DIR_ERR					59
#define FPD_CONFIG_FILE_ERR					60
#define FPD_DLL_VERSION_ERR					61
#define FPD_ETHERNET_BREAK_ERR				62
#define FPD_EXPOSURE_REQUEST_ERR			63
#define FPD_EXPOSURE_OK_ERR					64
#define FPD_TEMPERATURE_OVER_ERR			65
#define FPD_NO_IMAGE_ERR					66
#define FPD_DATA_TRANSMISSION_ERR			67
#define FPD_IMAGE_TRANSFER_TIMEOUT_ERR		68
#define FPD_STATE_ERR						69
#define FPD_RESOURCE_ALLOCATED_ERR			70
#define FPD_LINK_SPEED_ERR					71
#define FPD_DATA_ERR						72
#define FPD_NOT_IMPLEMENT_ERR				73
#define FPD_MEMORY_ALLOCATION_ERR			74
#define FPD_BAD_PARAMETER_ERR				75
#define FPD_RESOURCE_ALLOCATION_ERR			76
#define FPD_MULT_PROCESS_ERR				77
#define FPD_OPERATION_NOT_AVAILABLE_ERR		78
#define FPD_DISK_FREE_SPACE_INVALID_ERR		200

static const char *g_strErrList[] = 
{
	"No error",												// 0
	"Read file error",										// 1
	"Write file error",										// 2
	"Adapter object error",									// 3
	"Detector connection error",							// 4
	"A detector connection error",							// 5
	"B detector connection error",							// 6
	"A and B detector connection error",					// 7
	"Detector disconnected error",							// 8
	"A detector disconnected error",						// 9
	"B detector disconnected error",						// 10
	"A and B detector disconnected error",					// 11
	"Register callback function failed",					// 12
	"Open A detector error",								// 13
	"Open B detector error",								// 14
	"Create static offset template file error",				// 15
	"Create dynamic offset template file error",			// 16
	"Create gain template file error",						// 17
	"Create defect template file error",					// 18
	"Create defect template informaiton file error",		// 19
	"Create most gain template file error",					// 20
	"Set image do PRE offset correct error",				// 21
	"Set image do POST offset correct error",				// 22
	"Set image do gain correct error",						// 23
	"Set image do defect correct error",					// 24
	"Get correct status error",								// 25
	"Set image do flip and rotate error",					// 26
	"Get detector status error",							// 27
	"Get detector error information error",					// 28
	"Set configuration information error",					// 29
	"Other error",											// 30
	"Set update mode error",								// 31
	"Upload data error",									// 32
	"Recover image error",									// 33
	"The defect template temporary data initialization error",// 34
	"Modify defect template data error",					// 35
	"Save defect template file error",						// 36
	"Delete defect template temporary data errors",			// 37
	"Get detector configuration information error",			// 38
	"Get controlbox configuration information error",		// 39
	"Get sync controlbox configuration information error",	// 40
	"Get detector log information error",					// 41
	"Get detector exposure information error",				// 42
	"Syn controlbox initialization error",					// 43
	"Close sync controlbox error",							// 44
	"Sync controlbox send exposure cmd error",				// 45
	"Allow sync controlbox to enable error",				// 46
	"The configuration sync controlbox error",				// 47
	"Detector busy, send cmd error",						// 48
	"Dynamic correction initialization error",				// 49
	"Select dynamic light image error",						// 50
	"Create dynamic gain template file error",				// 51
	"Create dynamic defect template file error",			// 52
	"Create dynamic most gain template file error",			// 53
	"Get auto-clear mode from the detector error",			// 54
	"Set auto-clear mode in the detector error",			// 55
	"Can not open the detector",							// 56
	"The function returns error",							// 57
	"The specified file path was not found.",				// 58
	"Not able to create a new directory.",					// 59
	"The detector configuration file error.",				// 60
	"Dll version error.",									// 61
	"There is network cable disconnected.",					// 62
	"The system cannot get exposure request signal.",		// 63
	"The system cannot get exposure ok signal.",			// 64
	"The detector temperature has exceeded a certain limit standard value.",// 65
	"Image data packet have not been received when the image acquisition.",// 66
	"The image data transmission errors.",					// 67
	"Timeout when transfer image.",							// 68
	"Detector status error.",								// 69
	"Thread resource already created when function is called.",// 70
	"The link is 100M will cause this error.",				// 71
	"The detector configuration information data error.",	// 72
	"Application calls a function is not implemented.",		// 73
	"SDK could not allocate memory when the function is called.",// 74
	"Function parameter passing errors, this is an invalid parameter value.",// 75
	"SDK can not allocate window thread resources when the function is called.",// 76
	"Loading multiple processes error.",					// 77
	"Function operation not available.",					// 78
	"Disk available space is lower than 500M.",					// 200
};

#endif