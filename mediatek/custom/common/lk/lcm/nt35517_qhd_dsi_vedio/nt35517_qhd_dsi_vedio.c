#ifndef BUILD_LK
#include <linux/string.h>
#endif
#include "lcm_drv.h"

#ifdef BUILD_LK
	#include <platform/mt_gpio.h>
#elif defined(BUILD_UBOOT)
	#include <asm/arch/mt_gpio.h>
#else
	#include <mach/mt_gpio.h>
	extern void DSI_clk_HS_mode(bool enter);extern void DSI_clk_HS_mode(bool enter);
	extern void DSI_clk_ULP_mode(bool enter);
#endif

#ifdef BUILD_LK
#define LCM_PRINT printf
#else
#if defined(BUILD_UBOOT)
#define LCM_PRINT printf
#else
#define LCM_PRINT printk
#endif
#endif

#define LCM_DBG(fmt, arg...) \
	LCM_PRINT ("[LCM-NT35517-QHD-DSI-VDO] %s (line:%d) :" fmt "\r\n", __func__, __LINE__, ## arg)

// ---------------------------------------------------------------------------
//  Local Constants
// ---------------------------------------------------------------------------

#define FRAME_WIDTH  										(540)
#define FRAME_HEIGHT 										(960)
#define  LCM_ID_NT35517 0x5517

#define REGFLAG_DELAY             							0XFE
#define REGFLAG_END_OF_TABLE      							0xFF   // END OF REGISTERS MARKER

#define LCM_DSI_CMD_MODE									0

static unsigned int lcm_esd_test = FALSE;      ///only for ESD test

// ---------------------------------------------------------------------------
//  Local Variables
// ---------------------------------------------------------------------------

static LCM_UTIL_FUNCS lcm_util = {0};

#define SET_RESET_PIN(v)    (lcm_util.set_reset_pin((v)))

#define UDELAY(n) (lcm_util.udelay(n))
#define MDELAY(n) (lcm_util.mdelay(n))


// ---------------------------------------------------------------------------
//  Local Functions
// ---------------------------------------------------------------------------

#define dsi_set_cmdq_V3(para_tbl,size,force_update)        lcm_util.dsi_set_cmdq_V3(para_tbl,size,force_update)
#define dsi_set_cmdq_V2(cmd, count, ppara, force_update)	        lcm_util.dsi_set_cmdq_V2(cmd, count, ppara, force_update)
#define dsi_set_cmdq(pdata, queue_size, force_update)		lcm_util.dsi_set_cmdq(pdata, queue_size, force_update)
#define wrtie_cmd(cmd)										lcm_util.dsi_write_cmd(cmd)
#define write_regs(addr, pdata, byte_nums)					lcm_util.dsi_write_regs(addr, pdata, byte_nums)
#define read_reg(cmd)											lcm_util.dsi_dcs_read_lcm_reg(cmd)
#define read_reg_v2(cmd, buffer, buffer_size)   				lcm_util.dsi_dcs_read_lcm_reg_v2(cmd, buffer, buffer_size)

static LCM_setting_table_V3 lcm_initialization_setting[] = {
	
	/*
	Note :

	Data ID will depends on the following rule.
	
		count of parameters > 1	=> Data ID = 0x39
		count of parameters = 1	=> Data ID = 0x15
		count of parameters = 0	=> Data ID = 0x05

	Structure Format :

	{DCS command, count of parameters, {parameter list}}
	{REGFLAG_DELAY, milliseconds of time, {}},

	...

	Setting ending by predefined flag
	
	{REGFLAG_END_OF_TABLE, 0x00, {}}
	*/

	{0x39, 0xF0, 5, {0x55, 0xAA, 0x52,0x08,0x01}},
	
	//AVDD
	{0x39, 0xB0, 3, {0x05, 0x05, 0x05}},
	
	//#AVEE 
	{0x39, 0xB1, 3, {0x05, 0x05, 0x05}},
	
	//#VCL 
	{0x39, 0xB2, 3, {0x01, 0x01, 0x01}},
	
	//#VGH
	{0x39, 0xB3, 3, {0x0E, 0x0E, 0x0E}},
	
	//#VGL
	{0x39, 0xB4, 3, {0x08, 0x08, 0x08}},
	
	//Pump Power Control for AVDD/AVEE/VCL/VGH/VGL
	{0x39, 0xB6, 3, {0x44, 0x44, 0x44}},
	{0x39, 0xB7, 3, {0x34, 0x34, 0x34}},
	{0x39, 0xB8, 3, {0x33, 0x33, 0x33}},
	{0x39, 0xB9, 3, {0x34, 0x34, 0x34}},
	{0x39, 0xBA, 3, {0x14, 0x14, 0x14}},
	
	//Setting VGMP and VGSP Voltage
	
	{0x39, 0xBC, 3, {0x00, 0x98, 0x00}},
	
	//Setting VGMN and VGSN Voltage
	{0x39, 0xBD, 3, {0x00, 0x98, 0x00}},
	
	//Setting VCOM Offset Voltage
	{0x15, 0xBE, 1, {0x62}},// 5e --> 62  tcl peter wang
	
	//General Purpose Output Pins Control
	{0x39, 0xC0, 2, {0x04, 0x00}},
	{0x15, 0xCA, 1, {0x00}},
	{0x39, 0xD0, 4, {0x0a,0x10,0x0d,0x0f}},

	//#Gamma Setting
	//R+
	{0x39, 0xD1, 16, {0x00,0x16,0x00,0x23,0x00,0x3e,0x00,0x58,0x00,0x72,0x00,0x95,0x00,0xa9,0x00,0xe0}},
	{0x39, 0xD2, 16, {0x01,0x06,0x01,0x41,0x01,0x71,0x01,0xbb,0x01,0xfa,0x01,0xfc,0x02,0x39,0x02,0x7e}},
	{0x39, 0xD3, 16, {0x02,0xa4,0x02,0xe0,0x03,0x04,0x03,0x3D,0x03,0x63,0x03,0x8e,0x03,0xad,0x03,0xcb}},
	{0x39, 0xD4, 4,  {0x03,0xf1,0x03,0xff}},
	//G+
	{0x39, 0xD5, 16, {0x00,0x16,0x00,0x23,0x00,0x3e,0x00,0x58,0x00,0x72,0x00,0x95,0x00,0xa9,0x00,0xe0}},
	{0x39, 0xD6, 16, {0x01,0x06,0x01,0x41,0x01,0x71,0x01,0xbb,0x01,0xfa,0x01,0xfc,0x02,0x39,0x02,0x7e}},
	{0x39, 0xD7, 16, {0x02,0xa4,0x02,0xe0,0x03,0x04,0x03,0x3D,0x03,0x63,0x03,0x8e,0x03,0xad,0x03,0xcb}},
	{0x39, 0xD8, 4,  {0x03,0xf1,0x03,0xff}},
	//B+
	{0x39, 0xD9, 16, {0x00,0x16,0x00,0x23,0x00,0x3e,0x00,0x58,0x00,0x72,0x00,0x95,0x00,0xa9,0x00,0xe0}},
	{0x39, 0xDD, 16, {0x01,0x06,0x01,0x41,0x01,0x71,0x01,0xbb,0x01,0xfa,0x01,0xfc,0x02,0x39,0x02,0x7e}},
	{0x39, 0xDE, 16, {0x02,0x97,0x02,0xC5,0x02,0xE4,0x03,0x0D,0x03,0x25,0x03,0x40,0x03,0x4B,0x03,0x55}},
	{0x39, 0xDF, 4,  {0x03,0xf1,0x03,0xff}},
	//R- 
	{0x39, 0xE0, 16, {0x00,0x16,0x00,0x23,0x00,0x3e,0x00,0x58,0x00,0x72,0x00,0x95,0x00,0xa9,0x00,0xe0}},
	{0x39, 0xE1, 16, {0x01,0x06,0x01,0x41,0x01,0x71,0x01,0xbb,0x01,0xfa,0x01,0xfc,0x02,0x39,0x02,0x7e}},
	{0x39, 0xE2, 16, {0x02,0xa4,0x02,0xe0,0x03,0x04,0x03,0x3D,0x03,0x63,0x03,0x8e,0x03,0xad,0x03,0xcb}},
	{0x39, 0xE3, 4,  {0x03,0xf1,0x03,0xff}},
	//G-
	{0x39, 0xE4, 16, {0x00,0x16,0x00,0x23,0x00,0x3e,0x00,0x58,0x00,0x72,0x00,0x95,0x00,0xa9,0x00,0xe0}},
	{0x39, 0xE5, 16, {0x01,0x06,0x01,0x41,0x01,0x71,0x01,0xbb,0x01,0xfa,0x01,0xfc,0x02,0x39,0x02,0x7e}},
	{0x39, 0xE6, 16, {0x02,0xa4,0x02,0xe0,0x03,0x04,0x03,0x3D,0x03,0x63,0x03,0x8e,0x03,0xad,0x03,0xcb}},
	{0x39, 0xE7, 4,  {0x03,0xf1,0x03,0xff}},
	//B-
	{0x39, 0xE8, 16, {0x00,0x16,0x00,0x23,0x00,0x3e,0x00,0x58,0x00,0x72,0x00,0x95,0x00,0xa9,0x00,0xe0}},
	{0x39, 0xE9, 16, {0x01,0x06,0x01,0x41,0x01,0x71,0x01,0xbb,0x01,0xfa,0x01,0xfc,0x02,0x39,0x02,0x7e}},
	{0x39, 0xEA, 16, {0x02,0xa4,0x02,0xe0,0x03,0x04,0x03,0x3D,0x03,0x63,0x03,0x8e,0x03,0xad,0x03,0xcb}},
	{0x39, 0xEB, 4,  {0x03,0xf1,0x03,0xff}},

/*

	//#Gamma Setting
	//R+
	{0x39, 0xD1, 16, {0x00,0x70,0x01,0x16,0x01,0x2A,0x01,0x48,0x01,0x61,0x01,0x7D,0x01,0x94,0x01,0xB7}},
	{0x39, 0xD2, 16, {0x01,0xD1,0x01,0xFE,0x02,0x1F,0x02,0x55,0x02,0x80,0x02,0x81,0x02,0x94,0x02,0xDF}},
	{0x39, 0xD3, 16, {0x02,0xF7,0x03,0x1F,0x03,0x3A,0x03,0x59,0x03,0x70,0x03,0x8B,0x03,0x99,0x03,0xAE}},
	{0x39, 0xD4, 4,  {0x03,0xFF,0x03,0xFF}},
	//G+
	{0x39, 0xD5, 16, {0x00,0x70,0x01,0x16,0x01,0x2A,0x01,0x48,0x01,0x61,0x01,0x7D,0x01,0x94,0x01,0xB7}},
	{0x39, 0xD6, 16, {0x01,0xD1,0x01,0xFE,0x02,0x1F,0x02,0x55,0x02,0x80,0x02,0x81,0x02,0x94,0x02,0xDF}},
	{0x39, 0xD7, 16, {0x02,0xF7,0x03,0x1F,0x03,0x3A,0x03,0x59,0x03,0x70,0x03,0x8B,0x03,0x99,0x03,0xAE}},
	{0x39, 0xD8, 4,  {0x03,0xFF,0x03,0xFF}},
	//B+
	{0x39, 0xD9, 16, {0x00,0x70,0x01,0x16,0x01,0x2A,0x01,0x48,0x01,0x61,0x01,0x7D,0x01,0x94,0x01,0xB7}},
	{0x39, 0xDD, 16, {0x01,0xD1,0x01,0xFE,0x02,0x1F,0x02,0x55,0x02,0x80,0x02,0x81,0x02,0x94,0x02,0xDF}},
	{0x39, 0xDE, 16, {0x02,0xF7,0x03,0x1F,0x03,0x3A,0x03,0x59,0x03,0x70,0x03,0x8B,0x03,0x99,0x03,0xAE}},
	{0x39, 0xDF, 4,  {0x03,0xFF,0x03,0xFF}},
	//R- 
	{0x39, 0xE0, 16, {0x00,0x70,0x01,0x16,0x01,0x2A,0x01,0x48,0x01,0x61,0x01,0x7D,0x01,0x94,0x01,0xB7}},
	{0x39, 0xE1, 16, {0x01,0xD1,0x01,0xFE,0x02,0x1F,0x02,0x55,0x02,0x80,0x02,0x81,0x02,0x94,0x02,0xDF}},
	{0x39, 0xE2, 16, {0x02,0xF7,0x03,0x1F,0x03,0x3A,0x03,0x59,0x03,0x70,0x03,0x8B,0x03,0x99,0x03,0xAE}},
	{0x39, 0xE3, 4,  {0x03,0xFF,0x03,0xFF}},
	//G-
	{0x39, 0xE4, 16, {0x00,0x70,0x01,0x16,0x01,0x2A,0x01,0x48,0x01,0x61,0x01,0x7D,0x01,0x94,0x01,0xB7}},
	{0x39, 0xE5, 16, {0x01,0xD1,0x01,0xFE,0x02,0x1F,0x02,0x55,0x02,0x80,0x02,0x81,0x02,0x94,0x02,0xDF}},
	{0x39, 0xE6, 16, {0x02,0xF7,0x03,0x1F,0x03,0x3A,0x03,0x59,0x03,0x70,0x03,0x8B,0x03,0x99,0x03,0xAE}},
	{0x39, 0xE7, 4,  {0x03,0xFF,0x03,0xFF}},
	//B-
	{0x39, 0xE8, 16, {0x00,0x70,0x01,0x16,0x01,0x2A,0x01,0x48,0x01,0x61,0x01,0x7D,0x01,0x94,0x01,0xB7}},
	{0x39, 0xE9, 16, {0x01,0xD1,0x01,0xFE,0x02,0x1F,0x02,0x55,0x02,0x80,0x02,0x81,0x02,0x94,0x02,0xDF}},
	{0x39, 0xEA, 16, {0x02,0xF7,0x03,0x1F,0x03,0x3A,0x03,0x59,0x03,0x70,0x03,0x8B,0x03,0x99,0x03,0xAE}},
	{0x39, 0xEB, 4,  {0x03,0xFF,0x03,0xFF}},
*/
	/*
	//#Gamma Setting
	//R+
	{0x39, 0xD1, 16, {0x00,0x00,0x00,0x42,0x00,0x69,0x00,0x84,0x00,0x8F,0x00,0xBB,0x00,0xD7,0x01,0x03}},
	{0x39, 0xD2, 16, {0x01,0x27,0x01,0x5E,0x01,0x87,0x01,0xCC,0x02,0x04,0x02,0x06,0x02,0x37,0x02,0x74}},
	{0x39, 0xD3, 16, {0x02,0x97,0x02,0xC5,0x02,0xE4,0x03,0x0D,0x03,0x25,0x03,0x40,0x03,0x4B,0x03,0x55}},
	{0x39, 0xD4, 4,  {0x03,0x5B,0x03,0x65}},
	//G+
	{0x39, 0xD5, 16, {0x00,0x00,0x00,0x42,0x00,0x69,0x00,0x84,0x00,0x8F,0x00,0xBB,0x00,0xD7,0x01,0x03}},
	{0x39, 0xD6, 16, {0x01,0x27,0x01,0x5E,0x01,0x87,0x01,0xCC,0x02,0x04,0x02,0x06,0x02,0x37,0x02,0x74}},
	{0x39, 0xD7, 16, {0x02,0x97,0x02,0xC5,0x02,0xE4,0x03,0x0D,0x03,0x25,0x03,0x40,0x03,0x4B,0x03,0x55}},
	{0x39, 0xD8, 4,  {0x03,0x5B,0x03,0x65}},
	//B+
	{0x39, 0xD9, 16, {0x00,0x00,0x00,0x42,0x00,0x69,0x00,0x84,0x00,0x8F,0x00,0xBB,0x00,0xD7,0x01,0x03}},
	{0x39, 0xDD, 16, {0x01,0x27,0x01,0x5E,0x01,0x87,0x01,0xCC,0x02,0x04,0x02,0x06,0x02,0x37,0x02,0x74}},
	{0x39, 0xDE, 16, {0x02,0x97,0x02,0xC5,0x02,0xE4,0x03,0x0D,0x03,0x25,0x03,0x40,0x03,0x4B,0x03,0x55}},
	{0x39, 0xDF, 4,  {0x03,0x5B,0x03,0x65}},
	//R- 
	{0x39, 0xE0, 16, {0x00,0x00,0x00,0x42,0x00,0x69,0x00,0x84,0x00,0x8F,0x00,0xBB,0x00,0xD7,0x01,0x03}},
	{0x39, 0xE1, 16, {0x01,0x27,0x01,0x5E,0x01,0x87,0x01,0xCC,0x02,0x04,0x02,0x06,0x02,0x37,0x02,0x74}},
	{0x39, 0xE2, 16, {0x02,0x97,0x02,0xC5,0x02,0xE4,0x03,0x0D,0x03,0x25,0x03,0x40,0x03,0x4B,0x03,0x55}},
	{0x39, 0xE3, 4,  {0x03,0x5B,0x03,0x65}},
	//G-
	{0x39, 0xE4, 16, {0x00,0x00,0x00,0x42,0x00,0x69,0x00,0x84,0x00,0x8F,0x00,0xBB,0x00,0xD7,0x01,0x03}},
	{0x39, 0xE5, 16, {0x01,0x27,0x01,0x5E,0x01,0x87,0x01,0xCC,0x02,0x04,0x02,0x06,0x02,0x37,0x02,0x74}},
	{0x39, 0xE6, 16, {0x02,0x97,0x02,0xC5,0x02,0xE4,0x03,0x0D,0x03,0x25,0x03,0x40,0x03,0x4B,0x03,0x55}},
	{0x39, 0xE7, 4,  {0x03,0x5B,0x03,0x65}},
	//B-
	{0x39, 0xE8, 16, {0x00,0x00,0x00,0x42,0x00,0x69,0x00,0x84,0x00,0x8F,0x00,0xBB,0x00,0xD7,0x01,0x03}},
	{0x39, 0xE9, 16, {0x01,0x27,0x01,0x5E,0x01,0x87,0x01,0xCC,0x02,0x04,0x02,0x06,0x02,0x37,0x02,0x74}},
	{0x39, 0xEA, 16, {0x02,0x97,0x02,0xC5,0x02,0xE4,0x03,0x0D,0x03,0x25,0x03,0x40,0x03,0x4B,0x03,0x55}},
	{0x39, 0xEB, 4,  {0x03,0x5B,0x03,0x65}},

	*/

	{0x39, 0xF0, 5,  {0x55,0xAA,0x52,0x08,0x00}},
	{0x15, 0xB3, 1,  {0x00}},
	{0x39, 0xB1, 3,  {0xFC,0x00,0x00}},
	{0x39, 0xB8, 4,  {0x01,0x02,0x02,0x02}},
	{0x39, 0xBC, 3,  {0x00,0x00,0x00}},
	{0x39, 0xC9, 6,  {0x63,0x06,0x0D,0x17,0x17,0x00}},
	{0x15, 0x3A, 1,  {0x77}},
	           
	{0x15, 0x36, 1,  {0x00}},
	{0x15, 0x35, 1,  {0x00}},
	
	{0x05,0x11,0,{}},		
	{REGFLAG_ESCAPE_ID,REGFLAG_DELAY_MS_V3, 120, {}},
	{0x05,0x29,0,{}},
	{REGFLAG_ESCAPE_ID,REGFLAG_DELAY_MS_V3, 10, {}},
};


// ---------------------------------------------------------------------------
//  LCM Driver Implementations
// ---------------------------------------------------------------------------

static void lcm_set_util_funcs(const LCM_UTIL_FUNCS *util)
{
	memcpy(&lcm_util, util, sizeof(LCM_UTIL_FUNCS));
}

static void lcm_get_params(LCM_PARAMS *params)
{
		memset(params, 0, sizeof(LCM_PARAMS));
	
		params->type   = LCM_TYPE_DSI;

		params->width  = FRAME_WIDTH;
		params->height = FRAME_HEIGHT;
		
	    // enable tearing-free
	    params->dbi.te_mode 				= LCM_DBI_TE_MODE_VSYNC_ONLY;
	    params->dbi.te_edge_polarity		= LCM_POLARITY_RISING;
	
        #if (LCM_DSI_CMD_MODE)
		params->dsi.mode   = CMD_MODE;
        #else
		params->dsi.mode   = SYNC_PULSE_VDO_MODE; //SYNC_PULSE_VDO_MODE;//BURST_VDO_MODE; 
        #endif
	
		// DSI
		/* Command mode setting */
		//1 Three lane or Four lane
		params->dsi.LANE_NUM				= LCM_TWO_LANE;
		//The following defined the fomat for data coming from LCD engine.
		params->dsi.data_format.format      = LCM_DSI_FORMAT_RGB888;

		// Video mode setting		
		params->dsi.PS=LCM_PACKED_PS_24BIT_RGB888;
		
		params->dsi.vertical_sync_active				= 0x05;// 
		params->dsi.vertical_backporch					= 14;//  
		params->dsi.vertical_frontporch					= 12; //  
		params->dsi.vertical_active_line				= FRAME_HEIGHT; 

		params->dsi.horizontal_sync_active				= 10;// x16
		params->dsi.horizontal_backporch				= 70;// 80
		params->dsi.horizontal_frontporch				= 30;//50
		params->dsi.horizontal_active_pixel				= FRAME_WIDTH;

	    //params->dsi.LPX=8; 

		// Bit rate calculation
		//1 Every lane speed
		//params->dsi.pll_select=1;
		//params->dsi.PLL_CLOCK  = LCM_DSI_6589_PLL_CLOCK_377;
		params->dsi.PLL_CLOCK=249;
	 	//params->dsi.pll_div1=0;		// div1=0,1,2,3;div1_real=1,2,4,4 ----0: 546Mbps  1:273Mbps
	 //	params->dsi.pll_div2=0;		// div2=0,1,2,3;div1_real=1,2,4,4	
#if (LCM_DSI_CMD_MODE)
	 //	params->dsi.fbk_div =9;
#else
	// 	params->dsi.fbk_div =9;    // fref=26MHz, fvco=fref*(fbk_div+1)*2/(div1_real*div2_real)	
#endif
	//params->dsi.compatibility_for_nvk = 1;
}

static unsigned int lcm_compare_id(void)
{

	unsigned int id=0;
	unsigned char buffer[2];
	unsigned int array[16];  

	//Do reset here
	SET_RESET_PIN(1);
	SET_RESET_PIN(0);
	MDELAY(10);
	
	SET_RESET_PIN(1);
	MDELAY(10);  
	    
	LCM_DBG();
	
	array[0]=0x00063902;
	array[1]=0x52aa55f0;
	array[2]=0x00000108;
	dsi_set_cmdq(array, 3, 1);
	MDELAY(10);

	array[0] = 0x00083700;
	dsi_set_cmdq(array, 1, 1);

	//read_reg_v2(0x04, buffer, 3);//if read 0x04,should get 0x008000,that is both OK.
	read_reg_v2(0xc5, buffer,2);

	id = buffer[0]<<8 |buffer[1];
	     
	LCM_DBG("id = 0x%x \n", id);

    if(id == LCM_ID_NT35517)
    	return 1;
    else
    	return 0;
}

static void lcm_init(void)
{

		SET_RESET_PIN(1);
		//lcm_compare_id();
		SET_RESET_PIN(0);
		MDELAY(120); 
		SET_RESET_PIN(1);
		MDELAY(120); 
		dsi_set_cmdq_V3(lcm_initialization_setting,sizeof(lcm_initialization_setting)/sizeof(lcm_initialization_setting[0]),1);		
}

static void lcm_suspend(void)
{
	unsigned int data_array[16];

    data_array[0] = 0x00063902; 
    data_array[1] = 0x52AA55F0; 
    data_array[2] = 0X00000008; 
   
	dsi_set_cmdq(data_array, 3, 1);
	
	data_array[0] = 0x80b31500;
	dsi_set_cmdq(data_array, 1, 1);

	data_array[0]=0x00280500; // Display Off
	dsi_set_cmdq(data_array, 1, 1);
	
	data_array[0] = 0x00100500; // Sleep In
	dsi_set_cmdq(data_array, 1, 1);
	MDELAY(120); 
	
}

static void lcm_resume(void)
{
	SET_RESET_PIN(1);
	SET_RESET_PIN(0);
	MDELAY(10);
	
	SET_RESET_PIN(1);
	MDELAY(120);  


    dsi_set_cmdq_V3(lcm_initialization_setting,sizeof(lcm_initialization_setting)/sizeof(lcm_initialization_setting[0]),1);	

	/*SET_RESET_PIN(0);
	MDELAY(10);
	
	SET_RESET_PIN(1);*/

}

#if 1
static unsigned int lcm_esd_check(void)
{
	#ifndef BUILD_LK

	char  buffer[8];
	int   array[4];
 
	buffer[0] = 0;
	array[0] = 0x00083700;
	dsi_set_cmdq(array, 1, 1);
 
	read_reg_v2(0x0A,buffer, 8);
	
    //LCM_DBG("buffer[0] = 0x%x, buffer[1]=0x%x, buffer[2]=0x%x, buffer[3]=0x%x",buffer[0],buffer[1],buffer[2],buffer[3]);
    //LCM_DBG("buffer[4] = 0x%x, buffer[5]=0x%x, buffer[6]=0x%x, buffer[7]=0x%x",buffer[4],buffer[5],buffer[6],buffer[7]);

	//if(buffer[0]==0x9C)
	if(buffer[0]==0x9C)
	{
		return FALSE;
	}
	else
	{ 
		return TRUE;
	}
	#else
	
	return FALSE;

	#endif

}
#else
static unsigned int lcm_esd_check(void)
{
    static int err_count = 0;
    unsigned char buffer_1[12];
    unsigned int array[16];
    int i;
    unsigned char fResult;
	unsigned int uncount = 0;
	unsigned int count = 0;
    LCM_DBG("lcm_esd_check<<<\n");
    for(i = 0; i < 11; i++)
      buffer_1[i] = 0x00;

    //---------------------------------
    // Set Maximum Return Size
    //---------------------------------    
    array[0] = 0x00013700;
    dsi_set_cmdq(array, 1, 1);

    //---------------------------------
    // Read [9Ch, 00h, ECC] + Error Report(4 Bytes)
    //---------------------------------
    read_reg_v2(0x0A, buffer_1, 7);

    LCM_DBG("lcm_esd_check: read(0x0A)\n");
    for(i = 0; i < 7; i++)                
      LCM_DBG("buffer_1[%d]:0x%x \n",i,buffer_1[i]);

    //---------------------------------
    // Judge Readout & Error Report
    //---------------------------------
    if(buffer_1[3] == 0x02) // Check data identifier of error report
    {
      if(buffer_1[4] & 0x02) // Check SOT sync error
        err_count++;
      else
        err_count = 0;
    }
    else
    {
      err_count = 0;
    }

    LCM_DBG("lcm_esd_check err_count=%d\n",err_count);
    if((buffer_1[0] != 0x9C) || (err_count >= 2))
    {
      err_count = 0;
      uncount++;

      LCM_DBG("lcm_esd_check unnormal uncount=%d\n",uncount);
      LCM_DBG("lcm_esd_check>>>\n");
      
      fResult = 1;
      //return TRUE;
    }
    else
    {        
      count++;
      LCM_DBG("lcm_esd_check normal count=%d\n",count);
      LCM_DBG("lcm_esd_check>>>\n");
      
      fResult = 0;
      //return FALSE;
    }

    //---------------------------------
    // Shut-Down Peripherial
    //---------------------------------    
    array[0] = 0x00002200;
    dsi_set_cmdq(array, 1, 1);

    //---------------------------------
    // Set Maximum Return Size
    //---------------------------------    
    array[0] = 0x00033700;
    dsi_set_cmdq(array, 1, 1);

    //---------------------------------
    // Clear D-PHY Buffer
    // Read [WC, WC, ECC, P1, P2, P3, CRC0, CRC1]+ Error Report(4 Bytes)
    //---------------------------------
    read_reg_v2(0xBC, buffer_1, 12);

    LCM_DBG("lcm_esd_check: read(0xBC)\n");
    for(i = 0; i < 12; i++)                
      LCM_DBG("buffer_1[%d]:0x%x \n",i,buffer_1[i]);
      
    if(fResult) return TRUE;
    else return FALSE;
}
#endif


static unsigned int lcm_esd_recover(void)
{
	DSI_clk_ULP_mode(1);
	MDELAY(10);
	DSI_clk_ULP_mode(0);
	MDELAY(10);
	DSI_clk_HS_mode(1);
	MDELAY(10);
	
	lcm_init();
	    LCM_DBG();
	return TRUE;
}


LCM_DRIVER nt35517_qhd_dsi_vdo_lcm_drv = 
{
	.name		= "nt35517_qhd_dsi_vdo",
	.set_util_funcs = lcm_set_util_funcs,
	.get_params     = lcm_get_params,
	.init           = lcm_init,
	.suspend        = lcm_suspend,
	.resume         = lcm_resume,
	.compare_id    = lcm_compare_id,
	.esd_check = lcm_esd_check,
	.esd_recover = lcm_esd_recover,
#if (LCM_DSI_CMD_MODE)	
	.update         = lcm_update,
#endif
};