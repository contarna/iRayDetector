/******************************************************************
**  FileName   : FpdStructsEx.h
**
**  Description: This file is the expand structures and related enums.
**  
**  Copyright  : iRay Technology (Shanghai) Ltd.
******************************************************************/

#ifndef _FPD_STRUCTS_EX_
#define _FPD_STRUCTS_EX_

/*=========================================================================
/*NAME				: DetectorStatus
/*DESCRIPTION		: Detector status
/*MEMBER			: 
/*FPD_STS_READY		: Ready status of detector
/*FPD_STS_TIMEOUT	: Timeout status of detector
/*FPD_STS_BUSY		: Busy status of detector
/*FPD_STS_BREAK		: Break status of detector
/*FPD_STS_OFFLINE	: off line of detector (wireless)
/*FPD_STS_ONLINE	: on line of detector (wireless)
/*FPD_STS_INUSE		: in use (wireless)
=========================================================================*/
enum DetectorStatus
{
	FPD_STS_READY,
	FPD_STS_BUSY,
	FPD_STS_TIMEOUT,
	FPD_STS_BREAK,
	FPD_STS_OFFLINE,
	FPD_STS_ONLINE,
	FPD_STS_INUSE,
};

#endif