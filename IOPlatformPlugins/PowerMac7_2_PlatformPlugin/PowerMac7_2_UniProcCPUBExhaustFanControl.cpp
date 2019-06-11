/*
 * Copyright (c) 2003 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * The contents of this file constitute Original Code as defined in and
 * are subject to the Apple Public Source License Version 1.1 (the
 * "License").  You may not use this file except in compliance with the
 * License.  Please obtain a copy of the License at
 * http://www.apple.com/publicsource and read it before using this file.
 * 
 * This Original Code and all software distributed under the License are
 * distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE OR NON-INFRINGEMENT.  Please see the
 * License for the specific language governing rights and limitations
 * under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */
/*
 * Copyright (c) 2003 Apple Computer, Inc.  All rights reserved.
 *
 *
 */
//		$Log: PowerMac7_2_UniProcCPUBExhaustFanControl.cpp,v $
//		Revision 1.2  2003/07/16 02:02:10  eem
//		3288772, 3321372, 3328661
//		
//		Revision 1.1  2003/07/08 04:32:51  eem
//		3288891, 3279902, 3291553, 3154014
//		
//
//

#include "PowerMac7_2_UniProcCPUBExhaustFanControl.h"

#define super IOPlatformControl
OSDefineMetaClassAndStructors(PowerMac7_2_UniProcCPUBExhaustFanControl, IOPlatformControl)

IOReturn PowerMac7_2_UniProcCPUBExhaustFanControl::registerDriver( IOService * driver, const OSDictionary * dict, bool notify )
{
	IOReturn status = super::registerDriver(driver, dict, false);

	sendTargetValue( constantSpeed );
	setTargetValue( constantSpeed );

	return(status);
}

IOReturn PowerMac7_2_UniProcCPUBExhaustFanControl::initPlatformControl( const OSDictionary *dict )
{
	IOReturn status = super::initPlatformControl( dict );

	if ((constantSpeed = OSDynamicCast(OSNumber, dict->getObject("output-override"))) == NULL)
	{
		CONTROL_DLOG("PowerMac7_2_UniProcCPUBExhaustFanControl::initPlatformControl no speed supplied!!\n");
		return(kIOReturnError);
	}

	return(status);
}