/*
 * Copyright (c) 2002-2004 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */
/*
 * Copyright (c) 2004 Apple Computer, Inc.  All rights reserved.
 *
 *  File: $Id: SMU_Neo2_SlotsPowerSensor.cpp,v 1.5 2005/01/27 00:23:33 dirty Exp $
 */



#include "IOPlatformPluginSymbols.h"
#include "SMU_Neo2_PlatformPlugin.h"

#include "SMU_Neo2_SlotsPowerSensor.h"


OSDefineMetaClassAndStructors(SMU_Neo2_SlotsPowerSensor, IOPlatformSensor)


IOReturn SMU_Neo2_SlotsPowerSensor::initPlatformSensor(const OSDictionary* dict)
{

	UInt16		scalingValue;
	SInt16		offsetValue;
	IOReturn	status;

	status = IOPlatformSensor::initPlatformSensor(dict);

	// scalingValue is a 4.12 unsigned number.
	// offsetValue is a 4.12 signed number.

	if (!gPlatformPlugin->getSDBPartitionData(kSlotsPowerADCConstantsPartID, 4, 2, (UInt8 *) &scalingValue))
	{
		return( kIOReturnError );
	}

	if (!gPlatformPlugin->getSDBPartitionData(kSlotsPowerADCConstantsPartID, 6, 2, (UInt8 *) &offsetValue))
	{
		return( kIOReturnError );
	}

	scalingFactor = scalingValue;
	offsetFactor = offsetValue;

	return status;

}


SensorValue SMU_Neo2_SlotsPowerSensor::applyCurrentValueTransform(SensorValue hwReading) const
{

	SensorValue	scaledReading;

	scaledReading.sensValue = (SInt32)(scalingFactor * (UInt32) hwReading.sensValue) + offsetFactor;

	// Now convert to 16.16

	scaledReading.sensValue <<= 4;

	return scaledReading;

}
