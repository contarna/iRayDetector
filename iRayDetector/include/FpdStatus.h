/****************************************************************** 
**  FileName   : FpdStatus.h
**
**  Description: This is the detector feedback information definition file.
**  
**  Copyright  : iRay Technology (Shanghai) Ltd.
******************************************************************/ 

#ifndef _FPD_STATUS_
#define _FPD_STATUS_

/*=========================================================================
/*DESCRIPTION: return exposure prohibit
=========================================================================*/
#define FPD_EXP_PROHIBIT					1

/*=========================================================================
/*DESCRIPTION: return exposure enable
=========================================================================*/
#define FPD_EXP_ENABLE						2

/*=========================================================================
/*DESCRIPTION: return exposure timeout
=========================================================================*/
#define FPD_EXP_TIMEOUT						3

/*=========================================================================
/*DESCRIPTION: return exposure prohibit (auto clear mode)
=========================================================================*/
#define FPD_EXP_PROHIBIT_AUTO				4

/*=========================================================================
/*DESCRIPTION: return exposure enable (auto clear mode)
=========================================================================*/
#define FPD_EXP_ENABLE_AUTO					5

/*=========================================================================
/*DESCRIPTION: return exposure invalid (auto clear mode)
=========================================================================*/
#define FPD_EXP_INVALID_AUTO				6

/*=========================================================================
/*DESCRIPTION: return exposure prohibit (post offset mode)
=========================================================================*/
#define FPD_EXP_PROHIBIT_POST				7

/*=========================================================================
/*DESCRIPTION: return exposure enable (post offset mode)
=========================================================================*/
#define FPD_EXP_ENABLE_POST					8

/*=========================================================================
/*DESCRIPTION: return image
=========================================================================*/
#define FPD_IMAGE							9

/*=========================================================================
/*DESCRIPTION: return preview image
=========================================================================*/
#define FPD_IMAGE_PREV						10

/*=========================================================================
/*DESCRIPTION: return time
=========================================================================*/
#define FPD_IMAGE_TIME						11

/*=========================================================================
/*DESCRIPTION: return time (auto clear mode)
=========================================================================*/
#define FPD_IMAGE_TIME_AUTO					12

/*=========================================================================
/*DESCRIPTION: return start acquire image (dynamic detector)
=========================================================================*/
#define FPD_DYNA_ACQU_START					15

/*=========================================================================
/*DESCRIPTION: return end acquire image (dynamic detector)
=========================================================================*/
#define FPD_DYNA_ACQU_END					16

/*=========================================================================
/*DESCRIPTION: return write detector ROM successfully
=========================================================================*/
#define FPD_GET_WRITE_ROM_OK				17

/*=========================================================================
/*DESCRIPTION: return temperature
=========================================================================*/
#define FPD_GET_TEMPERATURE					18

/*=========================================================================
/*DESCRIPTION: return humidity
=========================================================================*/
#define FPD_GET_HUMIDITY					19

/*=========================================================================
/*DESCRIPTION: return enable detector (a controlbox when two detector)
=========================================================================*/
#define FPD_GET_OPEN_DETECTOR				20

/*=========================================================================
/*DESCRIPTION: return detector log
=========================================================================*/
#define FPD_GET_DETECOTR_LOG				21

/*=========================================================================
/*DESCRIPTION: return exposure information
=========================================================================*/
#define FPD_GET_DETECOTR_EXP_INFO			22

/*=========================================================================
/*DESCRIPTION: return detector version
=========================================================================*/
#define FPD_GET_READ_VERSION				23

/*=========================================================================
/*DESCRIPTION: return send to PREP cmd
=========================================================================*/
#define FPD_CORR_START_PREP_CMD				24

/*=========================================================================
/*DESCRIPTION: return create correct successfully
=========================================================================*/
#define FPD_CORR_CREATE_OK					25

/*=========================================================================
/*DESCRIPTION: return create correct failed
=========================================================================*/
#define FPD_CORR_CREATE_FAILED				26

/*=========================================================================
/*DESCRIPTION: return get offset image
=========================================================================*/
#define FPD_CORR_GET_OFFSET_IMAGE			27

/*=========================================================================
/*DESCRIPTION: return throw offset image
=========================================================================*/
#define FPD_CORR_THROW_OFFSET_IMAGE			28

/*=========================================================================
/*DESCRIPTION: return get dynamic light image
=========================================================================*/
#define FPD_CORR_DY_LIGHT_IMAGE				29

/*=========================================================================
/*DESCRIPTION: OK: FPD Received the Cmd Correctly:Ack:80
=========================================================================*/
#define FPD_IO_CMD_OK						30

/*=========================================================================
/*DESCRIPTION: FPD Received the Cmd Correctly,there is no such cmd in the cmd list:Ack:81
=========================================================================*/
#define FPD_IO_CMD_ERROR					31

/*=========================================================================
/*DESCRIPTION: Master Receive Cmd Error , Time Out:Ack:82
=========================================================================*/
#define FPD_IO_CMD_MAIN_TIMEOUT				32

/*=========================================================================
/*DESCRIPTION: Master Receive Cmd Error , Checksum Error:Ack:83
=========================================================================*/
#define FPD_IO_CMD_MAIN_GET_CHK_ERROR		33

/*=========================================================================
/*DESCRIPTION: Master Receive Cmd Error , Length Error:Ack:84
=========================================================================*/
#define FPD_IO_CMD_MAIN_GET_LEN_ERROR		34

/*=========================================================================
/*DESCRIPTION: No response from the Slave:Ack:90
=========================================================================*/
#define FPD_IO_CMD_READ_RESPONSE_ERROR		35

/*=========================================================================
/*DESCRIPTION: Master Receive The Cmd From Slave Error , Time Out:Ack:91
=========================================================================*/
#define FPD_IO_CMD_READ_TIMEOUT				36

/*=========================================================================
/*DESCRIPTION: Master Receive The Cmd From Slave Error , Checksum Error:Ack:92
=========================================================================*/
#define FPD_IO_CMD_READ_CHK_ERROR			37

/*=========================================================================
/*DESCRIPTION: Master Receive The Cmd From Slave Error , Length Error:Ack:93
=========================================================================*/
#define FPD_IO_CMD_READ_LEN_ERROR			38

/*=========================================================================
/*DESCRIPTION: Slave Receive The Cmd From Master Error , Time Out:Ack:94
=========================================================================*/
#define FPD_IO_CMD_MAIN_READ_TIMEOUT		39

/*=========================================================================
/*DESCRIPTION: Slave Receive The Cmd From Master Error , Checksum Error:Ack:95
=========================================================================*/
#define FPD_IO_CMD_MAIN_SEND_CHK_ERROR		40

/*=========================================================================
/*DESCRIPTION: Slave Receive The Cmd From Master Error , Length Error:Ack:96
=========================================================================*/
#define FPD_IO_CMD_MAIN_SEND_LEN_ERROR		41

/*=========================================================================
/*DESCRIPTION: return detector configuration
=========================================================================*/
#define FPD_CONFIG_DETECTOR					42 

/*=========================================================================
/*DESCRIPTION: return controlbox configuration
=========================================================================*/
#define FPD_CONFIG_CONTROL_BOX				43

/*=========================================================================
/*DESCRIPTION: return the configuration information of the original detector
=========================================================================*/
#define FPD_CONFIG_FACTORY_DETECTOR			44

/*=========================================================================
/*DESCRIPTION: return the configuration information of the original controlbox
=========================================================================*/
#define FPD_CONFIG_FACTORY_CONTROL_BOX		45

/*=========================================================================
/*DESCRIPTION: return sync controlbox Send exposure cmd to the HVG.
=========================================================================*/
#define FPD_SYNC_BOX_SEND_EXPOSURE			46

/*=========================================================================
/*DESCRIPTION: return sync controlbox to enable
=========================================================================*/
#define FPD_SYNC_BOX_ENABLE					47

/*=========================================================================
/*DESCRIPTION: return detector do PREP cmd
=========================================================================*/
#define FPD_SYNC_BOX_CMD_PREP				48

/*=========================================================================
/*DESCRIPTION: return sync controlbox disconnected
=========================================================================*/
#define FPD_SYNC_BOX_CONN_BREAK				49

/*=========================================================================
/*DESCRIPTION: return sync controlbox connection is successful
=========================================================================*/
#define FPD_SYNC_BOX_CONN_OK				50

/*=========================================================================
/*DESCRIPTION: return sync controlbox configuration
=========================================================================*/
#define FPD_SYNC_BOX_CONFIG					51

/*=========================================================================
/*DESCRIPTION: return factory sync controlbox configuration
=========================================================================*/
#define FPD_SYNC_BOX_CONFIG_INIT			52

/*=========================================================================
/*DESCRIPTION: return image lost packet
=========================================================================*/
#define FPD_IMAGE_LOST_PACKET				53

/*=========================================================================
/*DESCRIPTION: return detector reday status
=========================================================================*/
#define FPD_STATUS_READY					55

/*=========================================================================
/*DESCRIPTION: return detector busy status
=========================================================================*/
#define FPD_STATUS_BUSY						56

/*=========================================================================
/*DESCRIPTION: return detector timeout status
=========================================================================*/
#define FPD_STATUS_TIMEOUT					57

/*=========================================================================
/*DESCRIPTION: return detector Ethernet break
=========================================================================*/
#define FPD_STATUS_ETHERNET_BREAK			58

/*=========================================================================
/*DESCRIPTION: return detector PREP status
=========================================================================*/
#define FPD_STATUS_PREP						59

/*=========================================================================
/*DESCRIPTION: return detector acquire status
=========================================================================*/
#define FPD_STATUS_ACQUIRE					60

/*=========================================================================
/*DESCRIPTION: return detector sequence acquire status
=========================================================================*/
#define FPD_STATUS_SEQU_ACQUIRE				61

/*=========================================================================
/*DESCRIPTION: return detector wait exposure
=========================================================================*/
#define FPD_STATUS_WAIT_EXP					62

/*=========================================================================
/*DESCRIPTION: return wait firmware data status
=========================================================================*/
#define FPD_STATUS_WAIT_FW_DATA				63

/*=========================================================================
/*DESCRIPTION: return detector update firmware status
=========================================================================*/
#define FPD_STATUS_UPT_FW					64

/*=========================================================================
/*DESCRIPTION: return wait correct file status
=========================================================================*/
#define FPD_STATUS_WAIT_CORR_DATA			65

/*=========================================================================
/*DESCRIPTION: return detector update correct file status
=========================================================================*/
#define FPD_STATUS_UPT_CORR					66

/*=========================================================================
/*DESCRIPTION: Get image packet
=========================================================================*/
#define FPD_IMAGE_PACKET					67

/*=========================================================================
/*DESCRIPTION: Main firmware update mode
=========================================================================*/
#define FPD_UPT_MODE_MAIN					68

/*=========================================================================
/*DESCRIPTION: Read firmware update mode
=========================================================================*/
#define FPD_UPT_MODE_READ					69

/*=========================================================================
/*DESCRIPTION: Controlbox firmware update mode
=========================================================================*/
#define FPD_UPT_MODE_CONTROLBOX				70

/*=========================================================================
/*DESCRIPTION: CMD timeout
=========================================================================*/
#define FPD_STATUS_CMD_TIMEOUT				71

/*=========================================================================
/*DESCRIPTION: check network cable is disconnected
=========================================================================*/
#define FPD_CHECK_NET_CONN_BREAK			72

/*=========================================================================
/*DESCRIPTION: check network cable is connected, but FPD is not ready yet
=========================================================================*/
#define FPD_CHECK_NET_CONN_OK_READY_FPD_NOT	73

/*=========================================================================
/*DESCRIPTION: check network cable is connected and FPD is ready
=========================================================================*/
#define FPD_CHECK_NET_CONN_OK_READY_FPD_YES	74

/*=========================================================================
/*DESCRIPTION: please plug in the net cable again
=========================================================================*/
#define FPD_CHECK_NET_CONN_PLUG				75

/*=========================================================================
/*DESCRIPTION: event: Light calibration frame complete
=========================================================================*/
#define FPD_EVENT_LIGHT_CAL_FRAME_COMPLETE	76

/*=========================================================================
/*DESCRIPTION: SeqNo is out of sync:Ack:85
=========================================================================*/
#define FPD_IO_CMD_SEQ_NO_IS_OUT_SYNC_ERROR	77

/*=========================================================================
/*DESCRIPTION: FPD busy:Ack:86
=========================================================================*/
#define FPD_IO_CMD_FPD_BUSY_ERROR			78

/*=========================================================================
/*DESCRIPTION: return image row number
=========================================================================*/
#define FPD_IMAGE_ROW_NUMBER_RETURN         79 

/*=========================================================================
/*DESCRIPTION: return replenish image row number
=========================================================================*/
#define FPD_REPLENISH_IMAGE_ROW_NUMBER_RETURN     80 

/*=========================================================================
/*DESCRIPTION: Read Shock Sensor Log
=========================================================================*/
#define FPD_READ_SHOCK_SENSOR_LOG			81

/*=========================================================================
/*DESCRIPTION: Read the Grid Sensor Status
=========================================================================*/
#define FPD_READ_GRID_SENSOR_STATUS			82

/*=========================================================================
/*DESCRIPTION: Clear Shock Sensor Log
=========================================================================*/
#define FPD_CLEAR_SHOCK_SENSOR_LOG			83

/*=========================================================================
/*DESCRIPTION: Set Shock User Threshold
=========================================================================*/
#define FPD_WRITE_SHOCK_USER_THRESHOLD		84

/*=========================================================================
/*DESCRIPTION: Read the Shock Threshold Value
=========================================================================*/
#define FPD_READ_SHOCK_USER_THRESHOLD		85

/*=========================================================================
/*DESCRIPTION: Reset ROM ok
=========================================================================*/
#define FPD_RESET_ROM_OK					86

/*=========================================================================
/*DESCRIPTION: Reload firmware OK
=========================================================================*/
#define FPD_RELOAD_FIRMWARE_OK				87

/*=========================================================================
/*DESCRIPTION: return exposure request OK
=========================================================================*/
#define FPD_RECV_EXP_REQ_OK					88

/*=========================================================================
/*DESCRIPTION: return Exposure Interrupted.
=========================================================================*/
#define FPD_EXP_INTERRUPT					89

/*=========================================================================
/*DESCRIPTION: Slave initialization error after power on
=========================================================================*/
#define FPD_SLAVE_INIT_AFTER_POWER_ON_ERR	90

/*=========================================================================
/*DESCRIPTION: DDR buffer error, doesn't work
=========================================================================*/
#define FPD_DDR_BUFFER_ERROR				91

/*=========================================================================
/*DESCRIPTION: Master receives cmd from control box error, time out error
=========================================================================*/
#define FPD_MASTER_RECV_CMD_TIMEOUT_FROM_CTLBOX_ERR	92

/*=========================================================================
/*DESCRIPTION: Master receives cmd from control box error, length error
=========================================================================*/
#define FPD_MASTER_RECV_CMD_LENGTH_FROM_CTLBOX_ERR	93

/*=========================================================================
/*DESCRIPTION: Master receives cmd from control box error, checksum error
=========================================================================*/
#define FPD_MASTER_RECV_CMD_CHECKSUM_FROM_CTLBOX_ERR 94

/*=========================================================================
/*DESCRIPTION: No response from control box
=========================================================================*/
#define FPD_NO_RESPONSE_FROM_CTLBOX					95

/*=========================================================================
/*DESCRIPTION: Control box receives cmd from master error, time out error
=========================================================================*/
#define FPD_CTLBOX_RECV_CMD_TIMEOUT_FROM_MASTER_ERR	96

/*=========================================================================
/*DESCRIPTION: Control box receives cmd from master error, length error
=========================================================================*/
#define FPD_CTLBOX_RECV_CMD_LENGTH_FROM_MASTER_ERR	97

/*=========================================================================
/*DESCRIPTION: Control box receives cmd from master error, checksum error
=========================================================================*/
#define FPD_CTLBOX_RECV_CMD_CHECKSUM_FROM_MASTER_ERR 98

/*=========================================================================
/*DESCRIPTION: The cmd is not supported by control box
=========================================================================*/
#define FPD_CTLBOX_CMD_NOT_SUPPORT					99

/*=========================================================================
/*DESCRIPTION: Packet number error of upgrade firmware file
=========================================================================*/
#define FPD_PACK_NUMBER_OF_UPGRADE_FW_FILE_ERR		100

/*=========================================================================
/*DESCRIPTION: No such controller needs firmware upgrade
=========================================================================*/
#define FPD_NO_CONTROLLER_NEED_FW_UPGRADE			101

/*=========================================================================
/*DESCRIPTION: No response from G-Sensor MCU
=========================================================================*/
#define FPD_NO_RESPONSE_FROM_G_SENSOR_MCU			102

/*=========================================================================
/*DESCRIPTION: Master receives cmd from G-Sensor MCU error, timeout error
=========================================================================*/
#define FPD_MASTER_RECV_CMD_TIMEOUT_FROM_G_SENSOR_MCU_ERR	103

/*=========================================================================
/*DESCRIPTION: Master receives cmd from G-Sensor MCU error, checksum error
=========================================================================*/
#define FPD_MASTER_RECV_CMD_CHECKSUM_FROM_G_SENSOR_MCU_ERR	104

/*=========================================================================
/*DESCRIPTION: Master receives cmd from G-Sensor MCU error, length error
=========================================================================*/
#define FPD_MASTER_RECV_CMD_LENGTH_FROM_G_SENSOR_MCU_ERR	105

/*=========================================================================
/*DESCRIPTION: G-Sensor MCU receives cmd from master error, timeout error
=========================================================================*/
#define FPD_G_SENSOR_MCU_RECV_CMD_TIMEOUT_FROM_MASTER_ERR	106

/*=========================================================================
/*DESCRIPTION: G-Sensor MCU receives cmd from master error, checksum error
=========================================================================*/
#define FPD_G_SENSOR_MCU_RECV_CMD_CHECKSUM_FROM_MASTER_ERR	107

/*=========================================================================
/*DESCRIPTION: G-Sensor MCU receives cmd from master error, length error
=========================================================================*/
#define FPD_G_SENSOR_MCU_RECV_CMD_LENGTH_FROM_MASTER_ERR	108

/*=========================================================================
/*DESCRIPTION: Cmd Execute Timeout error
=========================================================================*/
#define FPD_CMD_EXECUTE_TIMEOUT_ERR				109

/*=========================================================================
/*DESCRIPTION: Read User Defined ROM
=========================================================================*/
#define FPD_READ_USER_DEFINED_ROM				110

/*=========================================================================
/*DESCRIPTION: return detector Wireless offline
=========================================================================*/
#define FPD_STATUS_OFFLINE						111

/*=========================================================================
/*DESCRIPTION: return the online status of available FPDs
=========================================================================*/
#define FPD_AVAILABLE_LIST_INFO					112

/*=========================================================================
/*DESCRIPTION: return the WiFi working status of FPD
=========================================================================*/
#define FPD_GET_WIFI_STATUS						113

/*=========================================================================
/*DESCRIPTION: return the Battery working status of FPD
=========================================================================*/
#define FPD_GET_BATTERY_STATUS					114

/*=========================================================================
/*DESCRIPTION: Current Work Mode Do Not Support This Operation, ErrorCode: 0xC0
=========================================================================*/
#define FPD_CURRENT_MODE_NOT_SUPPORT_OPT_ERROR	115

/*=========================================================================
/*DESCRIPTION: return switch SSID result
=========================================================================*/
#define FPD_SWITCH_SSID							116

/*=========================================================================
/*DESCRIPTION: return write detector RAM and ROM successfully
=========================================================================*/
#define FPD_WRITE_CONFIG_DETECTOR				201

/*=========================================================================
/*DESCRIPTION: return binning image
=========================================================================*/
#define FPD_IMAGE_BINNING						202

/*=========================================================================
/*DESCRIPTION: return disk free space info
=========================================================================*/
#define FPD_DISK_FREE_SPACE_INVALID					203

/*=========================================================================
/*DESCRIPTION: return close exp window success
=========================================================================*/
#define FPD_CLOSE_EXP_WINDOW						204

/*=========================================================================
/*DESCRIPTION: return close exp window fail
=========================================================================*/
#define FPD_CLOSE_EXP_WINDOW_FAIL					205

#endif