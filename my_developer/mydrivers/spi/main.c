/*******************************************************************************
 * (c) Copyright 2012 Actel Corporation. All rights reserved.
 * (c) Copyright 2012 Emcraft Systems.  All rights reserved.
 *
 *  Simple SmartFusion2 microcontroller subsystem (MSS)
 *  GPIO and UART example program.This sample program is targeted at
 *  the Emcraft Systems SmartFusion2 SOM Starter Kit.
 *  It blinks the board's LEDs and prints messages onto UART using a delay loop.
 *
 *  IMPORTANT NOTE:
 *          If you re-generate this SoftConsole project in context of the Libero
 *          project the SoftConsole project is included with, Libero will
 *          set the following line:
 *
 *  #define MSS_SYS_MDDR_CONFIG_BY_CORTEX 1
 *          in
 *  g4m_system_MSS_CM3_hw_platform/drivers_config/sys_config/sys_config.h.
 *
 *          This is because the DDR interface is enabled in the Libero project.
 *          However, the DDR initialization code included with the current rev
 *          of Libero is not compatible with Emcraft Systems's SOM design.
 *          When called, the DDR initialization code will
 *          loop in config_ddr_subsys().
 *          Disable MSS_SYS_MDDR_CONFIG_BY_CORTEX to let this
 *          SoftConsole project run.
 *
 *  NOTE:   This sample project expects that the MSS GPIOs are connected to
 *          external pins through the FPGA fabric as follows:
 *              - MSS_GPIO_1: input from pin B20
 *              - MSS_GPIO_2: input from pin C19
 *          MSS UART0 is used as the serial console.
 *
 */

//#include "drivers/mss_gpio/mss_gpio.h"
//#include "drivers/mss_uart/mss_uart.h"
#include "drivers/mss_spi/mss_spi.h"
//#include "drivers_config/sys_config/sys_config.h"
#include <stdio.h>
#include "lmk04800.h"


/*
 * Delay loop down counter load value.
 */
#define DELAY_LOAD_VALUE     0x00800000


/*
 * LEDs GPIOs
 */
#define DS3_LED_GPIO	MSS_GPIO_1
#define DS4_LED_GPIO	MSS_GPIO_2
#define DS3_LED_MASK	MSS_GPIO_1_MASK
#define DS4_LED_MASK	MSS_GPIO_2_MASK


uint32_t MDDR_status=0;

static void spi_write(uint16_t addr, uint8_t cmd);


uint8_t LMK04800_Read(mss_spi_instance_t* spi, mss_spi_slave_t slave, uint16_t addr) {
    uint8_t tx_block[2];
    uint8_t rx_block[1];

    tx_block[0] = 0x80 | (addr >> 8);
    tx_block[1] = (addr & 0xFF);

    MSS_SPI_set_slave_select(spi, slave);
    MSS_SPI_transfer_block(spi, tx_block, 2, rx_block, 1);
    MSS_SPI_clear_slave_select(spi, slave);

    return rx_block[0];
}

void LMK04800_Write(mss_spi_instance_t* spi, mss_spi_slave_t slave, uint16_t addr, uint8_t cmd) {
    uint8_t tx_block[3];

    tx_block[0] = (addr >> 8);
    tx_block[1] = (addr & 0xFF);
    tx_block[2] = cmd;

    MSS_SPI_set_slave_select(spi, slave);
    MSS_SPI_transfer_block(spi, tx_block, 3, 0, 0);
    MSS_SPI_clear_slave_select(spi, slave);
}


/*
 * main() function.
 */
int main()
{	int32_t n;
    int32_t delay_count = 0;


    /*
     * Configure SPI
     */
	printf("1...");
    MSS_SPI_init(&g_mss_spi1);
	printf("2...");
    MSS_SPI_configure_master_mode(&g_mss_spi1, MSS_SPI_SLAVE_0, MSS_SPI_MODE0, 256u, MSS_SPI_BLOCK_TRANSFER_FRAME_SIZE);

LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x000, 0x80);			// Reset
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x000, 0x10);			// Disable 3-wire
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x14A, (0x06 << 3) | 0x03);	// Enable 4-wire SPI

    uint8_t devtype 	= LMK04800_Read(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x003);
    uint8_t product_hi 	= LMK04800_Read(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x004);
    uint8_t product_lo 	= LMK04800_Read(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x005);
    uint8_t maskrev 	= LMK04800_Read(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x006);
    uint8_t vendor_hi 	= LMK04800_Read(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x00C);
    uint8_t vendor_lo 	= LMK04800_Read(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x00D);
printf(" vendor_hi=%d,  vendor_lo=%d ", vendor_hi, vendor_lo);


/*

    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0000, 0x90);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0000, 0x10);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0002, 0x00);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0100, 0x19);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0101, 0x55);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0103, 0x00);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0104, 0x00);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0105, 0x00);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0106, 0x70);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0107, 0x11);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0108, 0x19);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0109, 0x55);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x010B, 0x00);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x010C, 0x00);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x010D, 0x00);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x010E, 0x70);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x010F, 0x11);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0110, 0x19);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0111, 0x55);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0113, 0x00);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0114, 0x00);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0115, 0x00);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0116, 0x70);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0117, 0x11);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0118, 0x19);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0119, 0x55);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x011B, 0x00);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x011C, 0x00);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x011D, 0x00);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x011E, 0x70);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x011F, 0x11);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0120, 0x19);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0121, 0x55);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0123, 0x00);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0124, 0x00);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0125, 0x00);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0126, 0x70);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0127, 0x11);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0128, 0x19);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0129, 0x55);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x012B, 0x00);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x012C, 0x00);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x012D, 0x00);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x012E, 0x70);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x012F, 0x11);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0130, 0x19);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0131, 0x55);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0133, 0x00);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0134, 0x00);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0135, 0x00);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0136, 0x70);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0137, 0x11);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0138, 0x00);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0139, 0x00);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x013A, 0x0C);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x013B, 0x00);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x013C, 0x00);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0000, 0x00);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0000, 0x00);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x013F, 0x00);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0140, 0x0F);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0141, 0x00);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0142, 0x00);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0143, 0x00);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0144, 0x80);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0145, 0x7F);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0146, 0x38);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0147, 0x0A);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0148, 0x13);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0149, 0x1B);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x014A, 0x33);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x014B, 0x13);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x014C, 0x00);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x014D, 0x00);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x014E, 0xC0);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x014F, 0x7F);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0150, 0x40);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0151, 0x02);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0152, 0x00);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0153, 0x00);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0154, 0x01);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0155, 0x00);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0156, 0x0A);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0157, 0x00);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0158, 0x0A);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0159, 0x00);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x015A, 0x0A);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x015B, 0xDF); // PLL1 CP Polarity is bit 4 (0x10)
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x015C, 0x20);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x015D, 0x00);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x015E, 0x00);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x015F, 0x0B);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0160, 0x00);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0161, 0x18);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0162, 0xC5);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0163, 0x00);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0164, 0x00);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0165, 0x0C);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x017C, 0x15);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x017D, 0x33);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0166, 0x00);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0167, 0x00);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0168, 0x32);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0169, 0x59);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x016A, 0x20);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x016B, 0x00);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x016C, 0x00);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x016D, 0x00);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x016E, 0x13);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x0173, 0x00);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x1FFD, 0x00);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x1FFE, 0x00);
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x1FFF, 0x53);


    /*
     * Set initial delay used to blink the LED.
     */
    delay_count = DELAY_LOAD_VALUE;

    /*
     * Initialize the UART0 controller (115200, 8N1)
     */
    //MSS_UART_init(&g_mss_uart0, MSS_UART_115200_BAUD, MSS_UART_DATA_8_BITS |  MSS_UART_NO_PARITY | MSS_UART_ONE_STOP_BIT);

    //config_mddr_lpddr();

    //sprintf(memptr, "%s\n\r", "Hello, SmartFusion2!");


    /*
    // Configure SPI1
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x000, 0x80);			// Reset
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x000, 0x10);			// Disable 3-wire
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x14A, (0x06 << 3) | 0x03);	// Enable 4-wire SPI
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x14A, (0x06 << 3) | 0x03);	// Enable 4-wire SPI
	*/

    // Check here for which version of the chip is in, we have to program them slightly differently if its the 4821
/*
    // LMK04828 version
    tLMK04800 settings;

    LMK04800_SetDefaults(&settings);

    settings.SPI_3WIRE_DIS = 1;
    settings.RESET_MUX 	= 6;	// SPI Readback
    settings.RESET_TYPE = 3;	// Output Push/Pull
    settings.OSCin_FREQ = 1; 	// 63-127 MHz

    for(n=0; n<7; n++) {
    	settings.ch[n].DCLKoutX_DIV = 25;		// Should come out as 100 MHz on LMK04828BVCO0
    	//settings.ch[n].DCLKoutX_DIV = 32;		// Should come out as 62.5 MHz on LMK04821
    	settings.ch[n].DCLKoutX_DDLY_PD = 1;	// Disable delay
    	settings.ch[n].CLKoutX_Y_PD = 0;	// Enable
    	settings.ch[n].SDCLKoutY_PD = 0;	// Enable
    	settings.ch[n].DCLKoutX_FMT = 1;	// LVPECL
    	settings.ch[n].SDCLKoutY_FMT = 1;	// LVPECL
    }

    settings.OSCout_FMT = 0; // Powerdown (CLKin2)
    settings.CLKin2_EN  = 0;
    settings.CLKin1_EN 	= 0;
    settings.CLKin0_EN 	= 1;
    settings.CLKin2_TYPE = 0; // Bipolar (LVDS)
    settings.CLKin1_TYPE = 0; // Bipolar (LVDS)
    settings.CLKin0_TYPE = 0; // Bipolar (LVDS)
    settings.CLKin_SEL_MODE = 0; // Auto mode
    settings.CLKin0_OUT_MUX = 2;
    settings.CLKin1_OUT_MUX = 2; // switched from 2 to 1 to test 0delay
    settings.CLKin_SEL0_MUX = 2; // LED9, 2-Selected
    settings.CLKin_SEL0_TYPE = 3;
    settings.CLKin_SEL1_MUX = 1;// LED10 - Loss Of Signal
    settings.CLKin_SEL1_TYPE = 3;
    settings.VCO_MUX = 0;
    settings.SYNC_MODE = 0;
    settings.SYNC_EN = 0;
    settings.SYNC_POL = 1;
    settings.CLKin_OVERRIDE = 0;
    settings.HOLDOVER_HITLESS_SWITCH = 0;
    settings.HOLDOVER_LOS_DET = 0;
    settings.HOLDOVER_PLL1_DET = 0;
    settings.HOLDOVER_EN = 0;
    settings.PLL1_CP_POL = 0;
    settings.PLL1_CP_GAIN = 15;
    settings.MAN_DAC_EN = 0;
    settings.TRACK_EN = 1;
    */

/*
    settings.PLL1_NCLK_MUX = 0; // OSCin
    settings.PLL2_NCLK_MUX = 1; // Feedback MUX
    settings.FB_MUX_EN = 1; // Enabled Feedback MUX
    settings.FB_MUX = 0; // DCLKout6
    settings.OSCin_PD = 0;
*/
    /*
    // LMK04828 settings
    settings.CLKin0_R = 1; 	// 10 MHz Input clock expected from Atomic Clock
    settings.CLKin1_R = 10; 	// 100 Mhz Input clock expected from eSATA
    settings.CLKin2_R = 10; 	// 100 Mhz Input clock expected from external clock
    settings.PLL1_N = 10; 	// This makes the above "R" settings work!
    settings.PLL2_R = 24;
    settings.PLL2_P = 6; // PLL2_N_Prescaler
    settings.PLL2_N = 50; // Due to doubler
    settings.PLL2_N_CAL = 40;
    settings.OPT_REG_1 = 21;
    settings.OPT_REG_2 = 51;
    */

    // LMK04821 settings
    /*
    settings.CLKin0_R = 32; 	// 10 MHz Input clock expected from Atomic Clock
    settings.CLKin1_R = 200; 	// 100 Mhz Input clock expected from eSATA
    settings.CLKin2_R = 200; 	// 100 Mhz Input clock expected from external clock
    settings.PLL1_N = 320; 	// This makes the above "R" settings work!
    settings.PLL2_R = 125;
    settings.PLL2_P = 4; // PLL2_N_Prescaler
    settings.PLL2_N = 625;
    settings.PLL2_N_CAL = 625;
    //settings.OPT_REG_1 = 21;
    //settings.OPT_REG_2 = 51;
	*/

    /*
    settings.PLL1_LD_MUX = 4; // LED8 - Holdover
    settings.PLL2_LD_MUX = 3; // LED7 - PLL1 & PLL2 DLD
    settings.PLL2_LD_TYPE = 3;
    settings.PLL1_LD_TYPE = 3;

    LMK04800_Program(&settings, spi_write);

    // Sync By Toggling SYNC_POL
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x143, 0x11);			// Toggle SYNC_POL
    LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x143, 0x31);			// Toggle SYNC_POL
*/
    // Test 4-wire by trying to readback device info
    /*
    uint8_t devtype 	= LMK04800_Read(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x003);
    uint8_t product_hi 	= LMK04800_Read(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x004);
    uint8_t product_lo 	= LMK04800_Read(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x005);
    uint8_t maskrev 	= LMK04800_Read(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x006);
    uint8_t vendor_hi 	= LMK04800_Read(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x00C);
    uint8_t vendor_lo 	= LMK04800_Read(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x00D);

    uint32_t pll2_n0 	= LMK04800_Read(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x166);
    uint32_t pll2_n1 	= LMK04800_Read(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x167);
    uint32_t pll2_n2 	= LMK04800_Read(&g_mss_spi1, MSS_SPI_SLAVE_0, 0x168);
	*/

    // 0x17C - 0x17D

    // 0x166 - 0x1FFF





























    /*
     * Infinite loop.
     */
    for(;;)
    {
	    uint32_t val;

	    /*
	     * Decrement delay counter.
	     */
	    --delay_count;

	    /*
	     * Check if delay expired.
	     */
	    if ( delay_count <= 0 )
	    {
		    /*
		     * Reload delay counter.
		     */
		    delay_count = DELAY_LOAD_VALUE;

//	printf("1...");

		
	    }
    }

    return 0;
}

static void spi_write(uint16_t addr, uint8_t cmd) {
	LMK04800_Write(&g_mss_spi1, MSS_SPI_SLAVE_0, addr, cmd);
}
