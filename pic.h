/*
 *
 *	Project:
 *		at.c
 *
 * 	Author:
 * 		Steve Bradford (cryptodad)
 * 
 * 	Date:
 * 		June 2018
 * 
 * *********************************************************************
 * 
 * 	History:
 * 		v1.0	June 2018 	- Initial release
 * 
 */

#ifndef __PIC_H_
#define __PIC_H_

/* 
 * PIC COMMANDS
 * ref: driver-btm-l3.h
 */
#define PIC_COMMAND_1                       		0x55
#define PIC_COMMAND_2                       		0xaa

#define GET_VOLTAGE                         		0x18
#define SET_VOLTAGE                         		0x10

#define JUMP_FROM_LOADER_TO_APP             		0x06
#define RESET_PIC                           		0x07

#define READ_PIC_SOFTWARE_VERSION           		0x17


/* 
 * PIC COMMANDS
 * ref: driver-btm-l3.h
 */
/* Register bits value */
#define CMD_TYPE            (0x2 << 5)

/* Command Description */
#define CMD_ALL             (0x01 << 4)
#define SET_ADDR            0x0
#define SET_CONFIG          0x1
#define GET_STATUS          0x2
#define CHAIN_INACTIVE      0x3

#define CMD_LENTH           0x4
#define CONFIG_LENTH        0x8

/* Register Description */
#define CHIP_ADDR           0x00
#define HASHRATE            0x04
#define PLL_PARAMETER       0x08
#define SNO                 0x0C
#define HCN                 0x10
#define TICKET_MASK         0x14
#define MISC_CONTROL        0x18
#define GENERAL_IIC         0x1C
#define SECURITY_IIC        0x20
#define SIG_INPUT           0x24
#define SIG_NONCE_0         0x28
#define SIG_NONCE_1         0x2c
#define SIG_ID              0x30
#define SEC_CTRL_STATUS     0x34
#define MEMORY_STSATUS      0x38
#define CORE_CMD_IN         0x3c
#define CORE_RESP_OUT       0x40
#define EXT_TEMP_SENSOR     0x44


#endif
