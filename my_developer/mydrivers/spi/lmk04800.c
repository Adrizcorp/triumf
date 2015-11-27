/*
 * lmk04800.c
 *
 *  Created on: Aug 31, 2015
 *      Author: bryerton
 */

#include "lmk04800.h"

void LMK04800_SetDefaults(tLMK04800* settings) {
	unsigned int n;

	settings->VCO_MUX = 0;
	settings->OSCout_MUX = 0;
	settings->OSCout_FMT = 4;
	settings->SYSREF_CLKin0_MUX = 0;
	settings->SYSREF_MUX = 0;
	settings->SYSREF_DIV = 3072;
	settings->SYSREF_DDLY = 8;
	settings->SYSREF_PULSE_CNT = 3;
	settings->PLL2_NCLK_MUX = 0;
	settings->PLL1_NCLK_MUX = 0;
	settings->FB_MUX = 0;
	settings->FB_MUX_EN = 0;
	settings->PLL1_PD = 0;
	settings->VCO_LDO_PD = 0;
	settings->VCO_PD = 0;
	settings->OSCin_PD = 0;
	settings->SYSREF_GBL_PD = 0;
	settings->SYSREF_PD = 1;
	settings->SYSREF_DDLY_PD = 1;
	settings->SYSREF_PLSR_PD = 1;
	settings->DDLYd_SYSREF_EN = 0;
	settings->DDLYd12_EN = 0;
	settings->DDLYd10_EN = 0;
	settings->DDLYd8_EN = 0;
	settings->DDLYd6_EN = 0;
	settings->DDLYd4_EN = 0;
	settings->DDLYd2_EN = 0;
	settings->DDLYd0_EN = 0;
	settings->DDLYd_STEP_CNT = 0;
	settings->SYSREF_CLR = 1;
	settings->SYNC_1SHOT_EN = 0;
	settings->SYNC_POL = 0;
	settings->SYNC_EN = 1;
	settings->SYNC_PLL2_DLD = 0;
	settings->SYNC_PLL1_DLD = 0;
	settings->SYNC_MODE = 1;
	settings->SYNC_DISSYSREF = 0;
	settings->SYNC_DIS12 = 0;
	settings->SYNC_DIS10 = 0;
	settings->SYNC_DIS8 = 0;
	settings->SYNC_DIS6 = 0;
	settings->SYNC_DIS4 = 0;
	settings->SYNC_DIS2 = 0;
	settings->SYNC_DIS0 = 0;
	settings->CLKin2_EN = 0;
	settings->CLKin1_EN = 1;
	settings->CLKin0_EN = 1;
	settings->CLKin2_TYPE = 0;
	settings->CLKin1_TYPE = 0;
	settings->CLKin0_TYPE = 0;
	settings->CLKin_SEL_POL = 0;
	settings->CLKin_SEL_MODE = 3;
	settings->CLKin1_OUT_MUX = 2;
	settings->CLKin0_OUT_MUX = 2;
	settings->CLKin_SEL0_MUX = 0;
	settings->CLKin_SEL0_TYPE = 2;
	settings->SDIO_RDBK_TYPE = 1;
	settings->CLKin_SEL1_MUX = 0;
	settings->CLKin_SEL1_TYPE = 2;
	settings->RESET_MUX = 0;
	settings->RESET_TYPE = 2;
	settings->LOS_TIMEOUT = 0;
	settings->LOS_EN = 0;
	settings->TRACK_EN = 1;
	settings->HOLDOVER_FORCE = 0;
	settings->MAN_DAC_EN = 1;
	settings->MAN_DAC = 512;
	settings->DAC_TRIP_LOW = 0;
	settings->DAC_CLK_MULT = 0;
	settings->DAC_TRIP_HIGH = 0;
	settings->DAC_CLK_CNTR = 127;
	settings->CLKin_OVERRIDE = 0;
	settings->HOLDOVER_PLL1_DET = 0;
	settings->HOLDOVER_LOS_DET = 0;
	settings->HOLDOVER_VTUNE_DET = 0;
	settings->HOLDOVER_HITLESS_SWITCH = 1;
	settings->HOLDOVER_EN = 1;
	settings->HOLDOVER_DLD_CNT = 512;
	settings->CLKin0_R = 120;
	settings->CLKin1_R = 150;
	settings->CLKin2_R = 150;
	settings->PLL1_N = 120;
	settings->PLL1_WND_SIZE = 3;
	settings->PLL1_CP_TRI = 0;
	settings->PLL1_CP_POL = 1;
	settings->PLL1_CP_GAIN = 4;
	settings->PLL1_DLD_CNT = 8192;
	settings->PLL1_R_DLY = 0;
	settings->PLL1_N_DLY = 0;
	settings->PLL1_LD_MUX = 1;
	settings->PLL1_LD_TYPE = 6;
	settings->PLL2_R = 2;
	settings->PLL2_P = 2;
	settings->OSCin_FREQ = 7;
	settings->PLL2_XTAL_EN = 0;
	settings->PLL2_REF_2X_EN = 1;
	settings->PLL2_N_CAL = 12;
	settings->PLL2_FCAL_DIS = 0;
	settings->PLL2_N = 12;
	settings->PLL2_WND_SIZE = 2;
	settings->PLL2_CP_GAIN = 3;
	settings->PLL2_CP_POL = 0;
	settings->PLL2_CP_TRI = 0;
	settings->SYSREF_REQ_EN = 0;
	settings->PLL2_DLD_CNT = 8192;
	settings->PLL2_LF_R4 = 0;
	settings->PLL2_LF_R3 = 0;
	settings->PLL2_LF_C4 = 0;
	settings->PLL2_LF_C3 = 0;
	settings->PLL2_LD_MUX = 2;
	settings->PLL2_LD_TYPE = 6;
	settings->PLL2_PRE_PD = 0;
	settings->PLL2_PD = 0;
	settings->VCO1_DIV = 0; // LMK04821 ONLY

	for(n=0; n<7; n++) {
		settings->ch[n].CLKoutX_Y_ODL = 0;
		settings->ch[n].CLKoutX_Y_IDL = 0;
		settings->ch[n].DCLKoutX_DIV = 0;
		settings->ch[n].DCLKoutX_DDLY_CNTH = 5;
		settings->ch[n].DCLKoutX_DDLY_CNTL = 5;
		settings->ch[n].DCLKoutX_ADLY = 0;
		settings->ch[n].DCLKoutX_ADLY_MUX = 0;
		settings->ch[n].DCLKoutX_MUX = 0;
		settings->ch[n].DCLKoutX_HS = 0;
		settings->ch[n].SDCLKoutY_MUX = 0;
		settings->ch[n].SDCLKoutY_DDLY = 0;
		settings->ch[n].SDCLKoutY_HS = 0;
		settings->ch[n].SDCLKoutY_ADLY_EN = 0;
		settings->ch[n].SDCLKoutY_ADLY = 0;
		settings->ch[n].DCLKoutX_DDLY_PD = 0;
		settings->ch[n].DCLKoutX_HSg_PD = 1;
		settings->ch[n].DCLKoutX_ADLYg_PD = 1;
		settings->ch[n].DCLKoutX_ADLY_PD = 1;
		settings->ch[n].CLKoutX_Y_PD = 0;
		settings->ch[n].SDCLKoutY_DIS_MODE = 0;
		settings->ch[n].SDCLKoutY_PD = 1;
		settings->ch[n].SDCLKoutY_POL = 0;
		settings->ch[n].SDCLKoutY_FMT = 0;
		settings->ch[n].DCLKoutX_POL = 0;
		settings->ch[n].DCLKoutX_FMT = 0;
	}
}

void LMK04800_Program(tLMK04800* settings, SPI_Write fSPI_Write) {
	unsigned int n;

	// Perform Reset
	fSPI_Write(0x000, 0x80);
	fSPI_Write(0x000, (settings->SPI_3WIRE_DIS & 0x1) << 4);
	for(n=0; n<7; n++) {
		fSPI_Write(0x100+(n*8),
			((settings->ch[n].CLKoutX_Y_ODL & 0x1) << 6) |
			((settings->ch[n].CLKoutX_Y_IDL & 0x1) << 5) |
			 (settings->ch[n].DCLKoutX_DIV 	& 0x1F));

		fSPI_Write(0x101+(n*8),
			((settings->ch[n].DCLKoutX_DDLY_CNTH & 0xF) << 4) |
			 (settings->ch[n].DCLKoutX_DDLY_CNTL & 0xF));

		fSPI_Write(0x103+(n*8),
			((settings->ch[n].DCLKoutX_ADLY 	& 0x1F) << 3) |
			((settings->ch[n].DCLKoutX_ADLY_MUX & 0x1)  << 2) |
			 (settings->ch[n].DCLKoutX_MUX 		& 0x3));

		fSPI_Write(0x104+(n*8),
			((settings->ch[n].DCLKoutX_HS 		& 0x1) 	<< 6) |
			((settings->ch[n].SDCLKoutY_MUX 	& 0x1)  << 5) |
			((settings->ch[n].SDCLKoutY_DDLY 	& 0xF)	<< 1) |
			 (settings->ch[n].SDCLKoutY_HS 		& 0x1));

		fSPI_Write(0x105+(n*8),
			((settings->ch[n].SDCLKoutY_ADLY_EN & 0x1)  << 4) |
			 (settings->ch[n].SDCLKoutY_ADLY 	& 0xF));

		fSPI_Write(0x106+(n*8),
			((settings->ch[n].DCLKoutX_DDLY_PD 		& 0x1)  << 7) |
			((settings->ch[n].DCLKoutX_HSg_PD 		& 0x1)  << 6) |
			((settings->ch[n].DCLKoutX_ADLYg_PD		& 0x1)  << 5) |
			((settings->ch[n].DCLKoutX_ADLY_PD		& 0x1)  << 4) |
			((settings->ch[n].CLKoutX_Y_PD 			& 0x1)  << 3) |
			((settings->ch[n].SDCLKoutY_DIS_MODE	& 0x3)  << 1) |
			 (settings->ch[n].SDCLKoutY_PD 			& 0x1));

		fSPI_Write(0x107+(n*8),
			((settings->ch[n].SDCLKoutY_POL 	& 0x1)  << 7) |
			((settings->ch[n].SDCLKoutY_FMT 	& 0x7)  << 4) |
			((settings->ch[n].DCLKoutX_POL		& 0x1)  << 3) |
			 (settings->ch[n].DCLKoutX_FMT		& 0x7));
	}

	fSPI_Write(0x138,
		((settings->VCO_MUX 		& 0x3) << 5) |
		((settings->OSCout_MUX 		& 0x1) << 4) |
		((settings->OSCout_FMT		& 0xF)));

	fSPI_Write(0x139,
		((settings->SYSREF_CLKin0_MUX	& 0x1) << 2) |
		((settings->SYSREF_MUX			& 0x3)));

	fSPI_Write(0x139,
		((settings->SYSREF_CLKin0_MUX	& 0x1) << 2) |
		((settings->SYSREF_MUX			& 0x3)));

	fSPI_Write(0x13A,
		(settings->SYSREF_DIV	& 0x1F00) >> 8);

	fSPI_Write(0x13B,
		(settings->SYSREF_DIV	& 0x00FF));

	fSPI_Write(0x13C,
		(settings->SYSREF_DDLY	& 0x1F00) >> 8);

	fSPI_Write(0x13D,
		(settings->SYSREF_DDLY	& 0x00FF));

	fSPI_Write(0x13E,
		(settings->SYSREF_PULSE_CNT	& 0x3));

	fSPI_Write(0x13F,
		((settings->PLL2_NCLK_MUX	& 0x1) << 4) |
		((settings->PLL1_NCLK_MUX	& 0x1) << 3) |
		((settings->FB_MUX			& 0x3) << 1) |
		((settings->FB_MUX_EN		& 0x1)));

	fSPI_Write(0x140,
		((settings->PLL1_PD			& 0x1) << 7) |
		((settings->VCO_LDO_PD		& 0x1) << 6) |
		((settings->VCO_PD			& 0x1) << 5) |
		((settings->OSCin_PD		& 0x1) << 4) |
		((settings->SYSREF_GBL_PD	& 0x1) << 3) |
		((settings->SYSREF_PD		& 0x1) << 2) |
		((settings->SYSREF_DDLY_PD	& 0x1) << 1) |
		((settings->SYSREF_PLSR_PD	& 0x1)));

	fSPI_Write(0x141,
		((settings->DDLYd_SYSREF_EN		& 0x1) << 7) |
		((settings->DDLYd12_EN			& 0x1) << 6) |
		((settings->DDLYd10_EN			& 0x1) << 5) |
		((settings->DDLYd8_EN			& 0x1) << 4) |
		((settings->DDLYd6_EN			& 0x1) << 3) |
		((settings->DDLYd4_EN			& 0x1) << 2) |
		((settings->DDLYd2_EN			& 0x1) << 1) |
		((settings->DDLYd0_EN			& 0x1)));

	fSPI_Write(0x142,
		(settings->DDLYd_STEP_CNT & 0xF));

	fSPI_Write(0x143,
		((settings->SYSREF_CLR		& 0x1) << 7) |
		((settings->SYNC_1SHOT_EN	& 0x1) << 6) |
		((settings->SYNC_POL		& 0x1) << 5) |
		((settings->SYNC_EN			& 0x1) << 4) |
		((settings->SYNC_PLL2_DLD	& 0x1) << 3) |
		((settings->SYNC_PLL1_DLD	& 0x1) << 2) |
		((settings->SYNC_MODE		& 0x3)));

	fSPI_Write(0x144,
		((settings->SYNC_DISSYSREF	& 0x1) << 7) |
		((settings->SYNC_DIS12		& 0x1) << 6) |
		((settings->SYNC_DIS10		& 0x1) << 5) |
		((settings->SYNC_DIS8		& 0x1) << 4) |
		((settings->SYNC_DIS6		& 0x1) << 3) |
		((settings->SYNC_DIS4		& 0x1) << 2) |
		((settings->SYNC_DIS2		& 0x1) << 1) |
		((settings->SYNC_DIS0		& 0x1)));

	// Documentation says always program reg 0x145 to 127
	fSPI_Write(0x145, 127);

	fSPI_Write(0x146,
		((settings->CLKin2_EN		& 0x1) << 5) |
		((settings->CLKin1_EN		& 0x1) << 4) |
		((settings->CLKin0_EN		& 0x1) << 3) |
		((settings->CLKin2_TYPE		& 0x1) << 2) |
		((settings->CLKin1_TYPE		& 0x1) << 1) |
		((settings->CLKin0_TYPE		& 0x1)));

	fSPI_Write(0x147,
		((settings->CLKin_SEL_POL	& 0x1) << 7) |
		((settings->CLKin_SEL_MODE	& 0x7) << 4) |
		((settings->CLKin1_OUT_MUX	& 0x3) << 2) |
		((settings->CLKin0_OUT_MUX	& 0x3)));

	fSPI_Write(0x148,
		((settings->CLKin_SEL0_MUX	& 0x7) << 3) |
		((settings->CLKin_SEL0_TYPE	& 0x7)));

	fSPI_Write(0x149,
		((settings->SDIO_RDBK_TYPE	& 0x1) << 6) |
		((settings->CLKin_SEL1_MUX	& 0x7) << 3) |
		((settings->CLKin_SEL1_TYPE	& 0x7)));

	fSPI_Write(0x14A,
		((settings->RESET_MUX	& 0x7) << 3) |
		((settings->RESET_TYPE	& 0x7)));

	fSPI_Write(0x14B,
		((settings->LOS_TIMEOUT		& 0x3) << 6) |
		((settings->LOS_EN			& 0x1) << 5) |
		((settings->TRACK_EN		& 0x1) << 3) |
		((settings->HOLDOVER_FORCE	& 0x1) << 3) |
		((settings->MAN_DAC_EN		& 0x1) << 2) |
		(((settings->MAN_DAC >> 8) 	& 0x3)));

	fSPI_Write(0x14C,
		(settings->MAN_DAC & 0xFF));

	fSPI_Write(0x14D,
		(settings->DAC_TRIP_LOW & 0x3F));

	fSPI_Write(0x14E,
		((settings->DAC_CLK_MULT	& 0x3) << 6) |
		((settings->DAC_TRIP_HIGH 	& 0x3F)));

	fSPI_Write(0x14F,
		(settings->DAC_CLK_CNTR & 0xFF));

	fSPI_Write(0x150,
		// 7 - Reserved
		((settings->CLKin_OVERRIDE			& 0x1) << 6) |
		// 5 - Reserved
		((settings->HOLDOVER_PLL1_DET		& 0x1) << 4) |
		((settings->HOLDOVER_LOS_DET		& 0x1) << 3) |
		((settings->HOLDOVER_VTUNE_DET		& 0x1) << 2) |
		((settings->HOLDOVER_HITLESS_SWITCH	& 0x1) << 1) |
		((settings->HOLDOVER_EN				& 0x1)));

	fSPI_Write(0x151,
		(settings->HOLDOVER_DLD_CNT >> 8) & 0x3F);

	fSPI_Write(0x152,
		(settings->HOLDOVER_DLD_CNT & 0xFF));

	fSPI_Write(0x153,
		(settings->CLKin0_R >> 8) & 0x3F);

	fSPI_Write(0x154,
		(settings->CLKin0_R & 0xFF));

	fSPI_Write(0x155,
		(settings->CLKin1_R >> 8) & 0x3F);

	fSPI_Write(0x156,
		(settings->CLKin1_R & 0xFF));

	fSPI_Write(0x157,
		(settings->CLKin2_R >> 8) & 0x3F);

	fSPI_Write(0x158,
		(settings->CLKin2_R & 0xFF));

	fSPI_Write(0x159,
		(settings->PLL1_N >> 8) & 0x3F);

	fSPI_Write(0x15A,
		(settings->PLL1_N & 0xFF));

	fSPI_Write(0x15B,
		((settings->PLL1_WND_SIZE	& 0x3) << 6) |
		((settings->PLL1_CP_TRI		& 0x1) << 5) |
		((settings->PLL1_CP_POL		& 0x1) << 4) |
		((settings->PLL1_CP_GAIN	& 0xF)));

	fSPI_Write(0x15C,
		(settings->PLL1_DLD_CNT >> 8) & 0x3F);

	fSPI_Write(0x15D,
		(settings->PLL1_DLD_CNT & 0xFF));

	fSPI_Write(0x15E,
		((settings->PLL1_R_DLY	& 0x7) << 3) |
		((settings->PLL1_N_DLY	& 0x7)));

	fSPI_Write(0x15F,
		((settings->PLL1_LD_MUX		& 0x1F) << 3) |
		((settings->PLL1_LD_TYPE	& 0x7)));

	fSPI_Write(0x160,
		(settings->PLL2_R >> 8) & 0xF);

	fSPI_Write(0x161,
		(settings->PLL2_R & 0xFF));

	fSPI_Write(0x162,
		((settings->PLL2_P			& 0x7) << 5) |
		((settings->OSCin_FREQ		& 0x7) << 2) |
		((settings->PLL2_XTAL_EN	& 0x1) << 1) |
		((settings->PLL2_REF_2X_EN	& 0x1)));

	fSPI_Write(0x163,
		(settings->PLL2_N_CAL >> 16) & 0x3);

	fSPI_Write(0x164,
		(settings->PLL2_N_CAL >> 8) & 0xFF);

	fSPI_Write(0x165,
		(settings->PLL2_N_CAL & 0xFF));

	// Program 0x17C - 0x17D as per instructions

	//fSPI_Write(0x174,(settings->VCO1_DIV & 0x1F));
	fSPI_Write(0x17C, (settings->OPT_REG_1 & 0xFF));
	fSPI_Write(0x17D, (settings->OPT_REG_2 & 0xFF));

	// Program 0x166 - 0x1FFF as necessary
	// Valid for LMK04828

	fSPI_Write(0x166,
		((settings->PLL2_FCAL_DIS	& 0x1) << 2) |
		((settings->PLL2_N >> 16)	& 0x3));

	fSPI_Write(0x167,
		(settings->PLL2_N >> 8) & 0xFF);

	fSPI_Write(0x168,
		(settings->PLL2_N & 0xFF));

	fSPI_Write(0x169,
		((settings->PLL2_WND_SIZE	& 0x3) << 5) |
		((settings->PLL2_CP_GAIN	& 0x3) << 3) |
		((settings->PLL2_CP_POL		& 0x1) << 2) |
		((settings->PLL2_CP_TRI		& 0x1) << 1) |
		1); // Fixed Value of 1 in low bit

	fSPI_Write(0x16A,
		((settings->SYSREF_REQ_EN		& 0x1) << 6) |
		((settings->PLL2_DLD_CNT >> 8)	& 0x3F));

	fSPI_Write(0x16B,
		(settings->PLL2_DLD_CNT & 0xFF));

	fSPI_Write(0x16C,
		((settings->PLL2_LF_R4	& 0x7) << 3) |
		((settings->PLL2_LF_R3 	& 0x7)));

	fSPI_Write(0x16D,
		((settings->PLL2_LF_C4	& 0xF) << 4) |
		((settings->PLL2_LF_C3 	& 0xF)));

	fSPI_Write(0x16E,
		((settings->PLL2_LD_MUX		& 0xF) << 3) |
		((settings->PLL2_LD_TYPE	& 0x7)));

	fSPI_Write(0x173,
		// 7 - Reserved
		((settings->PLL2_PRE_PD		& 0x1) << 6) |
		((settings->PLL2_PD			& 0x1) << 5));
		// 4-0 - Reserved


}
