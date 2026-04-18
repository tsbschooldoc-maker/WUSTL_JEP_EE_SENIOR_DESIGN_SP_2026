/*
   Copyright (c) 2023 by Plexim GmbH
   All rights reserved.

   A free license is granted to anyone to use this software for any legal
   non safety-critical purpose, including commercial applications, provided
   that:
   1) IT IS NOT USED TO DIRECTLY OR INDIRECTLY COMPETE WITH PLEXIM, and
   2) THIS COPYRIGHT NOTICE IS PRESERVED in its entirety.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
 */

#include "includes.h"

#include "sysctl.h"
#include "flash.h"

void ISR_ILLEGAL(void);

static void PieCntlInit(void);
static void PieVectTableInit(void);

void DevInit(uint32_t aDeviceClkConf){
    SysCtl_disableWatchdog();

	DINT;			// Global Disable all Interrupts
	IER = 0x0000;	// Disable CPU interrupts
	IFR = 0x0000;	// Clear all CPU interrupt flags

	PieCntlInit();
	PieVectTableInit();

    SysCtl_setClock(aDeviceClkConf);

#ifndef _FLASH
    //
    // Call Device_cal function when run using debugger
    // This function is called as part of the Boot code. The function is called
    // in the Device_init function since during debug time resets, the boot code
    // will not be executed and the gel script will reinitialize all the
    // registers and the calibrated values will be lost.
    // Sysctl_deviceCal is a wrapper function for Device_Cal
    //
    SysCtl_deviceCal();
#endif
}


// This function initializes the PIE control registers to a known state.
//
static void PieCntlInit(void)
{
    //
    // Disable Interrupts at the CPU level:
    //
    DINT;

    //
    // Disable the PIE
    //
    PieCtrlRegs.PIECTRL.bit.ENPIE = 0;

    //
    // Clear all PIEIER registers:
    //
    PieCtrlRegs.PIEIER1.all = 0;
    PieCtrlRegs.PIEIER2.all = 0;
    PieCtrlRegs.PIEIER3.all = 0;
    PieCtrlRegs.PIEIER4.all = 0;
    PieCtrlRegs.PIEIER5.all = 0;
    PieCtrlRegs.PIEIER6.all = 0;
    PieCtrlRegs.PIEIER7.all = 0;
    PieCtrlRegs.PIEIER8.all = 0;
    PieCtrlRegs.PIEIER9.all = 0;
    PieCtrlRegs.PIEIER10.all = 0;
    PieCtrlRegs.PIEIER11.all = 0;
    PieCtrlRegs.PIEIER12.all = 0;

    //
    // Clear all PIEIFR registers:
    //
    PieCtrlRegs.PIEIFR1.all = 0;
    PieCtrlRegs.PIEIFR2.all = 0;
    PieCtrlRegs.PIEIFR3.all = 0;
    PieCtrlRegs.PIEIFR4.all = 0;
    PieCtrlRegs.PIEIFR5.all = 0;
    PieCtrlRegs.PIEIFR6.all = 0;
    PieCtrlRegs.PIEIFR7.all = 0;
    PieCtrlRegs.PIEIFR8.all = 0;
    PieCtrlRegs.PIEIFR9.all = 0;
    PieCtrlRegs.PIEIFR10.all = 0;
    PieCtrlRegs.PIEIFR11.all = 0;
    PieCtrlRegs.PIEIFR12.all = 0;
}


static void PieVectTableInit(void)
{
	Uint16  i;
	Uint32  *Source  =  (void  *)  &ISR_ILLEGAL;
	Uint32  *Dest  =  (void  *)  &PieVectTable;

	//
	// Do not write over first 3 32-bit locations (these locations are
	// initialized by Boot ROM with boot variables)
	//
	Dest  =  Dest  +  3;

	EALLOW;
	for(i  =  0;  i  <  221;  i++)
	{
		*Dest++  =  *Source;
	}
	EDIS;

	//
	// Enable the PIE Vector Table
	//
	PieCtrlRegs.PIECTRL.bit.ENPIE  =  1;
}

interrupt void ISR_ILLEGAL(void)   // Illegal operation TRAP
{
	PLX_ASSERT(0);
}

void InitFlashHz(uint32_t clkHz)
{
    uint16_t waitstates;
    uint16_t clkMHz = (uint16_t)(clkHz / 1000000L);

    PLX_ASSERT(clkMHz <= 100);
    if((ClkCfgRegs.CLKSRCCTL1.bit.OSCCLKSRCSEL == 0x0)   ||
       (ClkCfgRegs.CLKSRCCTL1.bit.OSCCLKSRCSEL == 0x2)   ||
       (ClkCfgRegs.CLKSRCCTL1.bit.OSCCLKSRCSEL == 0x3))
    {
    	// internal oscillator
        if(clkMHz > 97){
        	waitstates = 0x5;
        } else if(clkMHz > 77){
        	waitstates= 0x4;
        } else if(clkMHz > 58){
        	waitstates = 0x3;
        } else if(clkMHz > 38){
         	waitstates = 0x2;
        } else if(clkMHz > 19){
         	waitstates = 0x1;
        } else {
        	waitstates = 0x0;
        }
    }
    else
    {
    	// external oscillator
        if(clkMHz > 80){
        	waitstates = 0x4;
        } else if(clkMHz > 60){
        	waitstates = 0x3;
        } else if(clkMHz > 40){
         	waitstates = 0x2;
        } else if(clkMHz > 20){
         	waitstates = 0x1;
        } else {
        	waitstates = 0x0;
        }
    }
    Flash_initModule(FLASH0CTRL_BASE, FLASH0ECC_BASE, waitstates);
}

void MemCopy(Uint16 *SourceAddr, Uint16* SourceEndAddr, Uint16* DestAddr)
{
	while(SourceAddr < SourceEndAddr)
	{
		*DestAddr++ = *SourceAddr++;
	}
	return;
}

