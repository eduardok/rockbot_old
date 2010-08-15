#ifndef __PS2SDK_1_1__
#include <stdio.h>
#endif
#include <tamtypes.h>
#include <sifrpc.h>
#include <kernel.h>
#include <loadfile.h>
#include <fileio.h>
#include <errno.h>
#include <debug.h>
#include <iopcontrol.h>
#include "cdvd_rpc.h"



//Declare usbd module //
extern unsigned char usbd[];
extern unsigned int size_usbd;
//Declare usbhdfsd module //
extern unsigned char usbhdfsd[];
extern unsigned int size_usbhdfsd;
// cdfs IRX
extern unsigned char cdvd[];
extern unsigned int size_cdvd;


// adds support for basic I/O such as MC
void PS2loadMinimal() {
	int ret;
	ret = SifLoadModule("rom0:XSIO2MAN", 0, NULL);
    ret = SifLoadModule("rom0:XMCMAN", 0, NULL);
	#ifdef DEBUG_PS2
		if (ret < 0) {
			printf("Error '%d' loading module rom0:MCMAN\n", ret);
		} else {
			printf("Module rom0:MCMAN loaded\n");
		}
	#endif
	ret = SifLoadModule("rom0:XMCSERV", 0, NULL);
    ret = SifLoadModule("rom0:XPADMAN", 0, NULL);
    ret = SifLoadModule("rom0:XIOMAN", 0, NULL); 
	
	//mcInit(MC_TYPE_MC);
}


// usb mass support
void PS2loadUSB() {
	int ret;
	/*
	ret = SifLoadModule("mc0:usbd.irx", 0, NULL);
	#ifdef DEBUG_PS2
		if (ret < 0) {
			printf("Error '%d' loading module mc0:usbd.irx\n", ret);
		} else {
			printf("Module mc0:usbd.irx loaded\n");
		}
	#endif
	ret = SifLoadModule("mc0:usb_mass.irx", 0, NULL);
	#ifdef DEBUG_PS2
		if (ret < 0) {
			printf("Error '%d' loading module mc0:usb_mass.irx\n", ret);
		} else {
			printf("Module mc0:usb_mass.irx loaded\n");
		}
	#endif
	*/
	SifExecModuleBuffer(usbd, size_usbd, 0, NULL, &ret);
	SifExecModuleBuffer(usbhdfsd, size_usbhdfsd, 0, NULL, &ret);
}

void PS2loadCD() {
	int ret;
	SifExecModuleBuffer(cdvd, size_cdvd, 0, NULL, &ret);
	CDVD_Init();
}
/*
int LoadBasicModules()
{
	int ret = 0;
	int old = 0;

	smod_mod_info_t	mod_t;

	if(!smod_get_mod_by_name("sio2man", &mod_t))
	{
		ret = SifLoadModule("rom0:XSIO2MAN", 0, NULL);

		if (ret < 0)
		{
			printf("Failed to load module: SIO2MAN\n");
		}
	}
	if(mod_t.version == 257)
	{
		old = 1;
	}

	if(!smod_get_mod_by_name("mcman", &mod_t))
	{
		ret = SifLoadModule("rom0:XMCMAN", 0, NULL);

		if (ret < 0)
		{
			printf("Failed to load module: MCMAN\n");
		}
	}
	if(mod_t.version == 257)
	{
		old = 1;
	}

	if(!smod_get_mod_by_name("mcserv", &mod_t))
	{
		ret = SifLoadModule("rom0:XMCSERV", 0, NULL);

		if (ret < 0)
		{
			printf("Failed to load module: MCSERV\n");
		}
	}
	if(mod_t.version == 257)
		old = 1;
	else
		mcReset();

	if(!smod_get_mod_by_name("padman", &mod_t))
	{
		ret = SifLoadModule("rom0:XPADMAN", 0, NULL);

		if (ret < 0)
		{
			printf("Failed to load module: PADMAN\n");
		}
	}
	if(mod_t.version == 276)
		old = 1;
	else
		padReset();

	return old;
}
*/
