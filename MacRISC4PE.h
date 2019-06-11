/*
 * Copyright (c) 2002-2004 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * Copyright (c) 1999-2003 Apple Computer, Inc.  All Rights Reserved.
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
 * Copyright (c) 2002-2004 Apple Computer, Inc.  All rights reserved.
 *
 *  DRI: Dave Radcliffe
 *
 */
 

#ifndef _IOKIT_MACRISC4PE_H
#define _IOKIT_MACRISC4PE_H

#include <IOKit/platform/ApplePlatformExpert.h>
//#include <IOKit/pci/IOPCIDevice.h>
//#include <IOKit/pci/IOPCIBridge.h>

#include "IOPMSlotsMacRISC4.h"
#include "IOPMUSBMacRISC4.h"
#include "U3.h"
#include "IOPlatformPlugin.h"

enum
{
	kMacRISC4TypeUnknown = kMachineTypeUnknown,
    kMacRISC4TypePowerMac,
    kMacRISC4TypePowerBook,
};

#define kMacRISC4ParentICKey "AAPL,parentIC"

class MacRISC4PE : public ApplePlatformExpert
{
    OSDeclareDefaultStructors(MacRISC4PE);
  
    friend class MacRISC4CPU;
  
private:
    const char 				*provider_name;
    unsigned long			uniNVersion;
	MacRISC4CPU				*macRISC4CPU;
	AppleU3					*uniN;
    class IOPMSlotsMacRISC4	*slotsMacRISC4;
    IOLock					*pmmutex;
	bool					isPortable;
	
	IOService				*ioPPluginNub;
	IOService				*plFuncNub;

    void getDefaultBusSpeeds(long *numSpeeds, unsigned long **speedList);
	//IOReturn instantiatePlatformFunctions (IOService *nub, OSArray **pfArray);
  
    void PMInstantiatePowerDomains ( void );
    void PMRegisterDevice(IOService * theNub, IOService * theDevice);
    IORegistryEntry * retrievePowerMgtEntry (void);

public:
    virtual bool start(IOService *provider);
    virtual bool platformAdjustService(IOService *service);
    virtual IOReturn callPlatformFunction(const OSSymbol *functionName,
					bool waitForFunction, void *param1, void *param2,
                    void *param3, void *param4);
};

#endif // _IOKIT_MACRISC4PE_H
