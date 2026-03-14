/*
 * STM32_GPIO.h
 *
 *  Created on: 14-Mar-2026
 *      Author: junaid
 */

#ifndef INC_STM32_GPIO_H_
#define INC_STM32_GPIO_H_


#include "STM32F407x.h"

// This is Configuration Structure for GPIO

typedef struct
{
	uint8_t GPIO_PinNumber;
	uint8_t GPIO_PinMode;			// Possible values from @GPIO Possible Input Pin Modes
	uint8_t GPIO_PinSpeed;			// Possible values from @GPIO Pin Output Speeds
	uint8_t GPIO_PinPupControl;		// Possible values from @GPIO Pin Pull up and Pull Down Macros
	uint8_t GPIO_PinOPType;			// Possible values from @GPIO Possible Output Modes
	uint8_t GPIO_PinAltFuncMode;
} GPIO_PinConfig_t;

// This is a Handle Structure for GPIO

typedef struct
{
	GPIO_RegDef_t *pGPIOx; // This holds the base address of the GPIO port to which the pin belongs
	GPIO_PinConfig_t GPIO_PinConfig; // Initialize the configuration structure here
} GPIO_Handle_t;

// GPIO Pin Numbers
#define GPIO_PIN_NO_0	0
#define GPIO_PIN_NO_1	1
#define GPIO_PIN_NO_2	2
#define GPIO_PIN_NO_3	3
#define GPIO_PIN_NO_4	4
#define GPIO_PIN_NO_5	5
#define GPIO_PIN_NO_6	6
#define GPIO_PIN_NO_7	7
#define GPIO_PIN_NO_8	8
#define GPIO_PIN_NO_9	9
#define GPIO_PIN_NO_10	10
#define GPIO_PIN_NO_11	11
#define GPIO_PIN_NO_12	12
#define GPIO_PIN_NO_13	13
#define GPIO_PIN_NO_14	14
#define GPIO_PIN_NO_15	15


// GPIO Possible Input Pin Modes
#define GPIO_MODE_IN		0
#define GPIO_MODE_OUT		1
#define GPIO_MODE_ANALOG	2
#define GPIO_MODE_ALTFN		3
#define GPIO_MODE_IT_FT		4
#define GPIO_MODE_IT_RT		5
#define GPIO_MODE_IT_RFT	6

// GPIO Possible Output Modes
#define GPIO_OP_TYPE_PP		0
#define GPIO_OP_TYPE_OD		1

// GPIO Pin Output Speeds
#define GPIO_SPEED_LOW		0
#define GPIO_SPEED_MEDIUM	1
#define GPIO_SPEED_FAST		2
#define GPIO_SPEED_HIGH		3

// GPIO Pin Pull up and Pull Down Macros
#define GPIO_PIN_NO_PUPD		0
#define GPIO_PIN_PU			1
#define GPIO_PIN_PD			2


// API Supported by this Driver

// Peripheral Clock API
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi);

// init and de-init
void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_deinit(GPIO_RegDef_t *pGPIOx);

// Data Read-Write
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value);
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value);
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);

// Interrupt configuration and ISR handling
void GPIO_IRQ_INTConfig(uint8_t IRQNumber, uint8_t EnorDi);
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority);
void GPIO_IRQHandling(uint8_t PinNumber);

#endif /* INC_STM32_GPIO_H_ */
