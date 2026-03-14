/*
 * LCD_HD44780.c
 *
 *  Created on: 14-Mar-2026
 *      Author: junaid
 */


#include "LCD_HD44780.h"
static void write4Bits(uint8_t value);
static void LCDEnable(void);
void mdelay(uint32_t cnt);
void udelay(uint32_t cnt);



void LCDSendCommand(uint8_t cmd)
{
	// Make RS and RW 0 for LCD CMD write
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RS, GPIO_PIN_RESET);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RW, GPIO_PIN_RESET);

	write4Bits(cmd >> 4);
	write4Bits(cmd & 0x0F);
}

void LCDSendChar(uint8_t data)
{
	// Make RS 1 for data write
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RS, GPIO_PIN_SET);

	// Make RW 0 for data write
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RW, GPIO_PIN_RESET);

	write4Bits(data >> 4);		// Higher Nibble
	write4Bits(data & 0x0F);		// Lower Nibble
}

void LCDPrintString(char *message)
{
    while (*message != '\0')
    {
        LCDSendChar((uint8_t)*message++);
    }
}

void LCDSendString(char *message)
{
	do
	{
		LCDSendChar((uint8_t) *message++);
	}
	while(*message != '\0');
}

void LCD_init(void)
{
	// Configure the GPIO pins used for LCD Connections
	GPIO_Handle_t lcdSignal;

	lcdSignal.pGPIOx = LCD_GPIO_PORT;
	lcdSignal.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	lcdSignal.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_RS;
	lcdSignal.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	lcdSignal.GPIO_PinConfig.GPIO_PinPupControl = GPIO_PIN_NO_PUPD;
	lcdSignal.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIO_Init(&lcdSignal);

	lcdSignal.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_RW;
	GPIO_Init(&lcdSignal);

	lcdSignal.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_EN;
	GPIO_Init(&lcdSignal);

	lcdSignal.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_D4;
	GPIO_Init(&lcdSignal);

	lcdSignal.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_D5;
	GPIO_Init(&lcdSignal);

	lcdSignal.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_D6;
	GPIO_Init(&lcdSignal);

	lcdSignal.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_D7;
	GPIO_Init(&lcdSignal);

	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RS, GPIO_PIN_RESET);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RW, GPIO_PIN_RESET);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_EN, GPIO_PIN_RESET);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D4, GPIO_PIN_RESET);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D5, GPIO_PIN_RESET);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D6, GPIO_PIN_RESET);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D7, GPIO_PIN_RESET);

	mdelay(40);

	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RS, GPIO_PIN_RESET);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RW, GPIO_PIN_RESET);

	write4Bits(0x3);

	mdelay(5);

	write4Bits(0x3);

	mdelay(150);

	write4Bits(0x3);
	write4Bits(0x2);

	// Function set cmd
	LCDSendCommand(LCD_CMD_4DL_2N_5X8F);

	// Display ON and Cursor ON
	LCDSendCommand(LCD_CMD_DON_CURON);

	// Display Clear CMD
	LCDDisplayClear();

	// Entry mode set CMD
	LCDSendCommand(LCD_CMD_INCADD);

}


void LCDDisplayClear(void)
{
	// Display Clear
	LCDSendCommand(LCD_CMD_DIS_CLEAR);

	udelay(5);		// Wait time as mentioned in datasheet
}

static void write4Bits(uint8_t value)
{
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D4, ((value >> 0) & 0x1));
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D5, ((value >> 1) & 0x1));
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D6, ((value >> 2) & 0x1));
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D7, ((value >> 3) & 0x1));

	LCDEnable();
}

static void LCDEnable(void)
{
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_EN, GPIO_PIN_SET);
	udelay(10);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_EN, GPIO_PIN_RESET);
	udelay(50);
}

void mdelay(uint32_t cnt)
{
	for(uint32_t i = 0; i < (cnt * 1000); i++);
}

void udelay(uint32_t cnt)
{
	for(uint32_t i = 0; i < (cnt * 1000); i++);
}

void LCDDisplayReturnHome(void)
{
	LCDSendCommand(LCD_CMD_DIS_RETURN_HOME);
	udelay(5);
}

void LCDSetCursor(uint8_t row, uint8_t col)
{
    uint8_t address;

    // Convert 1-based column to 0-based index
    col--;

    if (row == 1)
    {
        address = 0x80 + col;
    }
    else if (row == 2)
    {
        address = 0xC0 + col;
    }
    else
    {
        return; // Invalid row
    }

    LCDSendCommand(address);
}
