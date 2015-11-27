/*
 * lmk04800.h
 *
 *  Created on: Aug 31, 2015
 *      Author: bryerton
 */

#ifndef LMK04800_H_
#define LMK04800_H_

#include <stdint.h>

#define LMK04826 37
#define LMK04828 32

typedef struct {
	unsigned char CLKoutX_Y_ODL;		// Output Drive Level
	unsigned char CLKoutX_Y_IDL;		// Input Drive level
	unsigned char DCLKoutX_DIV; 		// divisor
	unsigned char DCLKoutX_DDLY_CNTH; 	// Digital Delay High Count
	unsigned char DCLKoutX_DDLY_CNTL; 	// Digital Delay Low Count
	unsigned char DCLKoutX_ADLY;	// Analog Delay value (n*25ps)
	unsigned char DCLKoutX_ADLY_MUX; // Input to device clock buffer
	unsigned char DCLKoutX_MUX;
	unsigned char DCLKoutX_HS;
	unsigned char SDCLKoutY_MUX;
	unsigned char SDCLKoutY_DDLY;
	unsigned char SDCLKoutY_HS;
	unsigned char SDCLKoutY_ADLY_EN;
	unsigned char SDCLKoutY_ADLY;
	unsigned char DCLKoutX_DDLY_PD;
	unsigned char DCLKoutX_HSg_PD;
	unsigned char DCLKoutX_ADLYg_PD;
	unsigned char DCLKoutX_ADLY_PD;
	unsigned char CLKoutX_Y_PD;			// Clock Group (X_Y) powerdown
	unsigned char SDCLKoutY_DIS_MODE;
	unsigned char SDCLKoutY_PD;
	unsigned char SDCLKoutY_POL;
	unsigned char SDCLKoutY_FMT;
	unsigned char DCLKoutX_POL;
	unsigned char DCLKoutX_FMT;
} tLMK04800Channel;

typedef struct {
	unsigned char SPI_3WIRE_DIS;
	unsigned char VCO_MUX;
	unsigned char OSCout_MUX;
	unsigned char OSCout_FMT;
	unsigned char SYSREF_CLKin0_MUX;
	unsigned char SYSREF_MUX;
	unsigned short SYSREF_DIV;
	unsigned short SYSREF_DDLY;
	unsigned char SYSREF_PULSE_CNT;
	unsigned char PLL2_NCLK_MUX;
	unsigned char PLL1_NCLK_MUX;
	unsigned char FB_MUX;
	unsigned char FB_MUX_EN;
	unsigned char PLL1_PD;
	unsigned char VCO_LDO_PD;
	unsigned char VCO_PD;
	unsigned char OSCin_PD;
	unsigned char SYSREF_GBL_PD;
	unsigned char SYSREF_PD;
	unsigned char SYSREF_DDLY_PD;
	unsigned char SYSREF_PLSR_PD;
	unsigned char DDLYd_SYSREF_EN;
	unsigned char DDLYd12_EN;
	unsigned char DDLYd10_EN;
	unsigned char DDLYd8_EN;
	unsigned char DDLYd6_EN;
	unsigned char DDLYd4_EN;
	unsigned char DDLYd2_EN;
	unsigned char DDLYd0_EN;
	unsigned char DDLYd_STEP_CNT;
	unsigned char SYSREF_CLR;
	unsigned char SYNC_1SHOT_EN;
	unsigned char SYNC_POL;
	unsigned char SYNC_EN;
	unsigned char SYNC_PLL2_DLD;
	unsigned char SYNC_PLL1_DLD;
	unsigned char SYNC_MODE;
	unsigned char SYNC_DISSYSREF;
	unsigned char SYNC_DIS12;
	unsigned char SYNC_DIS10;
	unsigned char SYNC_DIS8;
	unsigned char SYNC_DIS6;
	unsigned char SYNC_DIS4;
	unsigned char SYNC_DIS2;
	unsigned char SYNC_DIS0;
	unsigned char CLKin2_EN;
	unsigned char CLKin1_EN;
	unsigned char CLKin0_EN;
	unsigned char CLKin2_TYPE;
	unsigned char CLKin1_TYPE;
	unsigned char CLKin0_TYPE;
	unsigned char CLKin_SEL_POL;
	unsigned char CLKin_SEL_MODE;
	unsigned char CLKin1_OUT_MUX;
	unsigned char CLKin0_OUT_MUX;
	unsigned char CLKin_SEL0_MUX;
	unsigned char CLKin_SEL0_TYPE;
	unsigned char SDIO_RDBK_TYPE;
	unsigned char CLKin_SEL1_MUX;
	unsigned char CLKin_SEL1_TYPE;
	unsigned char RESET_MUX;
	unsigned char RESET_TYPE;
	unsigned char LOS_TIMEOUT;
	unsigned char LOS_EN;
	unsigned char TRACK_EN;
	unsigned char HOLDOVER_FORCE;
	unsigned char MAN_DAC_EN;
	unsigned short MAN_DAC;
	unsigned char DAC_TRIP_LOW;
	unsigned char DAC_CLK_MULT;
	unsigned char DAC_TRIP_HIGH;
	unsigned char DAC_CLK_CNTR;
	unsigned char CLKin_OVERRIDE;
	unsigned char HOLDOVER_PLL1_DET;
	unsigned char HOLDOVER_LOS_DET;
	unsigned char HOLDOVER_VTUNE_DET;
	unsigned char HOLDOVER_HITLESS_SWITCH;
	unsigned char HOLDOVER_EN;
	unsigned short HOLDOVER_DLD_CNT;
	unsigned short CLKin0_R;
	unsigned short CLKin1_R;
	unsigned short CLKin2_R;
	unsigned short PLL1_N;
	unsigned char PLL1_WND_SIZE;
	unsigned char PLL1_CP_TRI;
	unsigned char PLL1_CP_POL;
	unsigned char PLL1_CP_GAIN;
	unsigned short PLL1_DLD_CNT;
	unsigned char PLL1_R_DLY;
	unsigned char PLL1_N_DLY;
	unsigned char PLL1_LD_MUX;
	unsigned char PLL1_LD_TYPE;
	unsigned short PLL2_R;
	unsigned char PLL2_P;
	unsigned char OSCin_FREQ;
	unsigned char PLL2_XTAL_EN;
	unsigned char PLL2_REF_2X_EN;
	unsigned int PLL2_N_CAL;
	unsigned char PLL2_FCAL_DIS;
	unsigned int PLL2_N;
	unsigned char PLL2_WND_SIZE;
	unsigned char PLL2_CP_GAIN;
	unsigned char PLL2_CP_POL;
	unsigned char PLL2_CP_TRI;
	unsigned char SYSREF_REQ_EN;
	unsigned short PLL2_DLD_CNT;
	unsigned char PLL2_LF_R4;
	unsigned char PLL2_LF_R3;
	unsigned char PLL2_LF_C4;
	unsigned char PLL2_LF_C3;
	unsigned char PLL2_LD_MUX;
	unsigned char PLL2_LD_TYPE;
	unsigned char PLL2_PRE_PD;
	unsigned char PLL2_PD;
	unsigned char VCO1_DIV; // LMK04821 ONLY
	unsigned char OPT_REG_1;
	unsigned char OPT_REG_2;

	tLMK04800Channel ch[7];
} tLMK04800;


typedef void (*SPI_Write)(uint16_t addr, uint8_t cmd);

void LMK04800_SetDefaults(tLMK04800* settings);
void LMK04800_Program(tLMK04800* settings, SPI_Write fSPI_Write);

#endif /* LMK04800_H_ */
