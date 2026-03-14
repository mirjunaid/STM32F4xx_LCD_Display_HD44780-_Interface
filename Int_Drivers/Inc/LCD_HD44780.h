/*
 * LCD_HD44780.h
 *
 *  Created on: 14-Mar-2026
 *      Author: junaid
 */

#ifndef INC_LCD_HD44780_H_
#define INC_LCD_HD44780_H_

#include "STM32F407x.h"

// Application configurable Macros
#define LCD_GPIO_PORT		GPIOD
#define LCD_GPIO_RS			GPIO_PIN_NO_0
#define LCD_GPIO_RW			GPIO_PIN_NO_1
#define LCD_GPIO_EN			GPIO_PIN_NO_2
#define LCD_GPIO_D4			GPIO_PIN_NO_3
#define LCD_GPIO_D5			GPIO_PIN_NO_4
#define LCD_GPIO_D6			GPIO_PIN_NO_5
#define LCD_GPIO_D7			GPIO_PIN_NO_6

// LCD Commands
#define LCD_CMD_4DL_2N_5X8F				0x28
#define LCD_CMD_DON_CURON				0x0E
#define LCD_CMD_INCADD					0x06
#define LCD_CMD_DIS_CLEAR				0x01
#define LCD_CMD_DIS_RETURN_HOME			0x02


// BSP exposed APIs
void LCD_init(void);
void LCDSendCommand(uint8_t cmd);
void LCDSendChar(uint8_t data);
void LCDDisplayReturnHome(void);
void LCDPrintString(char*);
void LCDSetCursor(uint8_t row, uint8_t col);
void LCDDisplayClear(void);


#endif /* INC_LCD_HD44780_H_ */
