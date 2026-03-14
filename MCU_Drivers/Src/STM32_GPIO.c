/*
 * STM32_GPIO.c
 *
 *  Created on: 14-Mar-2026
 *      Author: junaid
 */


// Driver Source File "STM32F40xx_GPIO_Driver.c"

#include "STM32_GPIO.h"

// API Supported by this Driver

// Peripheral Clock Setup
/*****************************************************************

@FN :	GPIO_PeriClockControl

@Brief intro:	This function enables or disables peripheral GPIO Clock for given GPIO Port

@in_Param:	Base address of peripheral GPIO, ENABLE or DISABLE Macro

@Return:	none

@Note:	none

*****************************************************************/

void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(pGPIOx == GPIOA)
		{
			GPIOA_PCLK_EN();
		}else if(pGPIOx == GPIOB)
		{
			GPIOB_PCLK_EN();
		}else if(pGPIOx == GPIOC)
		{
			GPIOC_PCLK_EN();
		}else if(pGPIOx == GPIOD)
		{
			GPIOD_PCLK_EN();
		}else if(pGPIOx == GPIOE)
		{
			GPIOE_PCLK_EN();
		}else if(pGPIOx == GPIOF)
		{
			GPIOF_PCLK_EN();
		}else if(pGPIOx == GPIOG)
		{
			GPIOG_PCLK_EN();
		}else if(pGPIOx == GPIOH)
		{
			GPIOH_PCLK_EN();
		}else if(pGPIOx == GPIOI)
		{
			GPIOI_PCLK_EN();
		}
	}
	else
	{
		if(pGPIOx == GPIOA)
		{
			GPIOA_PCLK_DI();
		}else if(pGPIOx == GPIOB)
		{
			GPIOB_PCLK_DI();
		}else if(pGPIOx == GPIOC)
		{
			GPIOC_PCLK_DI();
		}else if(pGPIOx == GPIOD)
		{
			GPIOD_PCLK_DI();
		}else if(pGPIOx == GPIOE)
		{
			GPIOE_PCLK_DI();
		}else if(pGPIOx == GPIOF)
		{
			GPIOF_PCLK_DI();
		}else if(pGPIOx == GPIOG)
		{
			GPIOG_PCLK_DI();
		}else if(pGPIOx == GPIOH)
		{
			GPIOH_PCLK_DI();
		}else if(pGPIOx == GPIOI)
		{
			GPIOI_PCLK_DI();
		}
	}

}

// GPIO Initialize Function
/*****************************************************************

@FN :	GPIO_Init

@Brief intro:	This function initializes GPIO Port

@in_Param:	Base address of peripheral GPIO

@Return:	none

@Note:	none

*****************************************************************/
void GPIO_Init(GPIO_Handle_t *p)
{
    uint32_t pin = p ->GPIO_PinConfig.GPIO_PinNumber;

    GPIO_PeriClockControl(p -> pGPIOx, ENABLE);

    if(p->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG)
    {
    	// 1) MODE
    	p->pGPIOx->MODER &= ~(0x3 << (2 * pin));
    	p->pGPIOx->MODER |=  (p->GPIO_PinConfig.GPIO_PinMode << (2 * pin));

    	// 2) SPEED
    	p->pGPIOx->OSPEEDR &= ~(0x3 << (2 * pin));
    	p->pGPIOx->OSPEEDR |=  (p->GPIO_PinConfig.GPIO_PinSpeed << (2 * pin));

    	// 3) PULL-UP/DOWN
    	p->pGPIOx->PUPDR &= ~(0x3 << (2 * pin));
    	p->pGPIOx->PUPDR |=  (p->GPIO_PinConfig.GPIO_PinPupControl << (2 * pin));

    	// 4) OUTPUT TYPE
    	p->pGPIOx->OTYPER &= ~(1 << pin);
    	p->pGPIOx->OTYPER |=  (p->GPIO_PinConfig.GPIO_PinOPType << pin);
    }

    // 5) ALTERNATE FUNCTION
    else if (p -> GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN)
    {
        uint8_t reg = pin / 8;
        uint8_t pos = pin % 8;

        p->pGPIOx->AFR[reg] &= ~(0xF << (4 * pos));
        p->pGPIOx->AFR[reg] |=  (p->GPIO_PinConfig.GPIO_PinAltFuncMode << (4 * pos));
    } else
    {
    	if(p -> GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT)
    	{
    		EXTI -> FTSR |= (1 << pin);
    		EXTI -> RTSR &= ~(1 << pin);

    	} else if(p -> GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RFT)
    	{
    		EXTI -> FTSR |= (1 << pin);
    		EXTI -> RTSR |= (1 << pin);
    	} else if(p -> GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT)
    	{
    		EXTI -> RTSR |= (1 << pin);
    		EXTI -> FTSR &= ~(1 << pin);
    	}

    	// Enable the EXTI interrupt delivery using IMR
    	SYSCFG_PCLK_EN();

    	uint8_t exti_idx = pin / 4;
    	uint8_t shift    = (pin % 4) * 4;
    	uint8_t portcode = GPIO_BASEADDR_TO_CODE(p->pGPIOx);

    	SYSCFG->EXTICR[exti_idx] &= ~(0xF << shift);
    	SYSCFG->EXTICR[exti_idx] |=  (portcode << shift);
    }
}


// deinit
/*****************************************************************

@FN :	GPIO_deinit

@Brief intro:	This function enables or disables peripheral GPIO Clock for given GPIO Port

@in_Param:	Base address of peripheral GPIO

@Return:	none

@Note:	none

*****************************************************************/

void GPIO_deinit(GPIO_RegDef_t *pGPIOx)
{
	if(pGPIOx == GPIOA)
			{
				GPIOA_REG_RESET();
			}else if(pGPIOx == GPIOB)
			{
				GPIOB_REG_RESET();
			}else if(pGPIOx == GPIOC)
			{
				GPIOC_REG_RESET();
			}else if(pGPIOx == GPIOD)
			{
				GPIOD_REG_RESET();
			}else if(pGPIOx == GPIOE)
			{
				GPIOE_REG_RESET();
			}else if(pGPIOx == GPIOF)
			{
				GPIOF_REG_RESET();
			}else if(pGPIOx == GPIOG)
			{
				GPIOG_REG_RESET();
			}else if(pGPIOx == GPIOH)
			{
				GPIOH_REG_RESET();
			}else if(pGPIOx == GPIOI)
			{
				GPIOI_REG_RESET();
			}
}

// Data Read from pin
/*****************************************************************

@FN :	GPIO_ReadFromInputPin

@Brief intro:	This function is used to read from a specific pin of GPIO Port(Make pin Input)

@in_Param:	Base address of peripheral GPIO, ENABLE or DISABLE Macro, Pin Number

@Return:	none

@Note:	none

*****************************************************************/

uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
	uint8_t value;
	value = (uint8_t)((pGPIOx -> IDR >> PinNumber) & 0X00000001);
	return value;
}

//Read from Port
/*****************************************************************

@FN :	GPIO_ReadFromInputPort

@Brief intro:	This function enables the whole port to be used as input and read from the whole port.

@in_Param:	Base address of peripheral GPIO

@Return:	none

@Note:	none

*****************************************************************/

uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx)
{
	uint16_t value;
	value = (uint16_t)pGPIOx -> IDR;
	return value;
}

// Write to pin
/*****************************************************************

@FN :	GPIO_WriteToOutputPin

@Brief Intro:	This function is used to write to a pin making it Output Pin of a specific port

@in_Param:	Base address of peripheral GPIO, Pin Number, Value to be written to the pin

@Return:	none

@Note:	none

*****************************************************************/

void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value)
{
	if (Value == GPIO_PIN_SET)
	{
		// Write 1 to the output data register at the bit field corresponding to pin number
		pGPIOx -> ODR |= (1 << PinNumber);
	} else
	{
		// Write zero
		pGPIOx -> ODR &= ~(1 << PinNumber);
	}
}

// Write to port
/*****************************************************************

@FN :	GPIO_WriteToOutputPort

@Brief intro:	This function is used to write to a specific port making it Output

@in_Param:	Base address of peripheral GPIO, Value to be written

@Return:	none

@Note:	none

*****************************************************************/

void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value)
{
	pGPIOx -> ODR = Value;
}

// Toggle Output Pin
/*****************************************************************

@FN :	GPIO_ToggleOutputPin

@Brief intro:	This function this function is used to toggle Output Pin

@in_Param:	Base address of peripheral GPIO, Pin Number

@Return:	none

@Note:	none

*****************************************************************/

void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
	pGPIOx -> ODR = pGPIOx -> ODR ^ (1 << PinNumber);
}

// Interrupt configuration
/*****************************************************************

@FN :	GPIO_IRQ_INTConfig

@Brief intro:	This function deals with the interrupt services for given GPIO Port

@in_Param:	Base address of peripheral GPIO, ENABLE or DISABLE Macro

@Return:	none

@Note:	none

*****************************************************************/

void GPIO_IRQ_INTConfig(uint8_t IRQNumber, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(IRQNumber <= 31)
		{
			// Program ISER0 Register
			*NVIC_ISER0 |= (1 << IRQNumber);
		}else if(IRQNumber > 31 && IRQNumber < 64)
		{
			// Program ISER1 Register
			*NVIC_ISER1 |= (1 << (IRQNumber % 32));
		}else if(IRQNumber >= 64 && IRQNumber < 96)
		{
			// Program ISER2 Register
			*NVIC_ISER3 |= (1 << (IRQNumber % 64));
		}
	}
	else
	{
		if(IRQNumber <= 31)
		{
			// Program ICER0 Register
			*NVIC_ICER0 |= (1 << IRQNumber);
		}else if(IRQNumber > 31 && IRQNumber < 64)
		{
			// Program ICER1 Register
			*NVIC_ICER1 |= (1 << (IRQNumber % 32));
		}else if (IRQNumber >= 64 && IRQNumber <= 81)    // STM32F407 has up to IRQ 81
		{
			// Program ICER2 Register
		    *NVIC_ISER2 |= (1U << (IRQNumber - 64));
		}
	}
}


// Interrupt service Request Handling
/*****************************************************************

@FN :	GPIO_IRQPriorityConfig

@Brief intro:	This function deals with the interrupt priority for a given interrupt service

@in_Param:	IRQ Number, IRQ Priority

@Return:	none

@Note:	none

*****************************************************************/

void GPIO_IRQ_PriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority)
{
	uint8_t iprx = IRQNumber / 4;
	uint8_t iprx_section = IRQNumber % 4;
	uint8_t shift_amount = (8 * iprx_section) + NO_PR_BITS_IMPLEMENTED;
	*(NVIC_PR_BASEADDR + (iprx * 4)) |= (IRQPriority << shift_amount);
}


// Interrupt service Request Handling
/*****************************************************************

@FN :	GPIO_IRQHandling

@Brief intro:	This function handles various interrupts in manner of their order, and takes care that the interrupts dont cause the crash

@in_Param:	Pin Number

@in_Param:	-

@Return:	none

@Note:	none

*****************************************************************/

void GPIO_IRQHandling(uint8_t PinNumber)
{
	// Clear the EXTI PR register corresponding to the pin number.
	if (EXTI -> PR & (1 << PinNumber))
	{
		// Clear the bit
		EXTI -> PR |= (1 << PinNumber);
	}
}
