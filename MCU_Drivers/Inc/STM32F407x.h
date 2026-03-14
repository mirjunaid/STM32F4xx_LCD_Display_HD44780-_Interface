/*
 * STM32F40xx.h
 *
 *  Created on: 14-Mar-2026
 *      Author: junaid
 */

#ifndef INC_STM32F407X_H_
#define INC_STM32F407X_H_


#include <stdint.h>
#include <string.h>
#include <stddef.h>

#define __vo volatile
#define __weak __attribute((weak))


//******************************MCU Specific Specifications**************************************************

//ARM Cortex Mx Processor NVIC ISER(Interrupt Set-Enable Register ) Addresses
#define NVIC_ISER0				( (__vo uint32_t*)0xE000E100 )
#define NVIC_ISER1				( (__vo uint32_t*)0xE000E104 )
#define NVIC_ISER2				( (__vo uint32_t*)0xE000E108 )
#define NVIC_ISER3				( (__vo uint32_t*)0xE000E10c )


// ARM Cortex Mx Processor NVIC ICER(Interrupt Control Enable Register) Addresses
#define NVIC_ICER0				((__vo uint32_t*)0XE000E180)
#define NVIC_ICER1				((__vo uint32_t*)0XE000E184)
#define NVIC_ICER2				((__vo uint32_t*)0XE000E188)
#define NVIC_ICER3				((__vo uint32_t*)0XE000E18c)


// ARM Cortex Mx Processor Priority Register Address along with No of Bits Implemented
#define NVIC_PR_BASEADDR		((__vo uint32_t*)0xE000E400)
#define NO_PR_BITS_IMPLEMENTED		4U

// Clock Enable/Disable for SYSCFG (APB2)
#define SYSCFG_PCLK_EN()     (RCC->APB2ENR |= (1U << 14))
#define SYSCFG_PCLK_DI()     (RCC->APB2ENR &= ~(1U << 14))


// Macros for various Priority Levels based on the Priority register
#define NVIC_IRQ_PRI0				0
#define NVIC_IRQ_PRI1				1
#define NVIC_IRQ_PRI2				2
#define NVIC_IRQ_PRI3				3
#define NVIC_IRQ_PRI4				4
#define NVIC_IRQ_PRI5				5
#define NVIC_IRQ_PRI6				6
#define NVIC_IRQ_PRI7				7
#define NVIC_IRQ_PRI8				8
#define NVIC_IRQ_PRI9				9
#define NVIC_IRQ_PRI10				10
#define NVIC_IRQ_PRI11				11
#define NVIC_IRQ_PRI12				12
#define NVIC_IRQ_PRI13				13
#define NVIC_IRQ_PRI14				14
#define NVIC_IRQ_PRI15				15



// Macros for memory types in the STM32F40xx
#define FLASH_BASEADDR          0x08000000U
#define SRAM1_BASEADDR          0x20000000U
#define SRAM2_BASEADDR          0x2001C000U
#define CCMRAM_BASEADDR         0x10000000U  // Core Coupled Memory
#define SYSTEM_MEMORY_BASEADDR  0x1FFF0000U  // Bootloader/system memory
#define OTP_BASEADDR            0x1FFF7800U  // One-Time Programmable

// Macros for peripheral buses in STM32F40xx
#define APB1_BASEADDR           0x40000000U
#define APB2_BASEADDR           0x40010000U
#define AHB1_BASEADDR           0x40020000U
#define AHB2_BASEADDR           0x50000000U
#define AHB3_BASEADDR           0xA0000000U  // FSMC

// Additional important base addresses from memory map
#define PERIPH_BLOCK2_BASE      0x40000000U  // 512MB block for peripherals
#define FSMC_BANK1_2_BASE       0x60000000U  // FSMC Bank 1 & 2
#define FSMC_BANK3_4_BASE       0x80000000U  // FSMC Bank 3 & 4
#define CORTEX_M4_PERIPH_BASE   0xE0000000U  // Cortex-M4 internal peripherals


// Peripheral interface addresses on APB2 BUS
#define SYSCFG_BASEADDR 			(APB2_BASEADDR + 0x3800)  // 0x40013800U
#define EXTI_BASEADDR   			(APB2_BASEADDR + 0x3C00)  // 0x40013C00U

// Peripheral interface base addresses on AHB1 BUS
#define GPIOA_BASEADDR				(AHB1_BASEADDR + 0x0000)
#define GPIOB_BASEADDR				(AHB1_BASEADDR + 0x0400)
#define GPIOC_BASEADDR				(AHB1_BASEADDR + 0x0800)
#define GPIOD_BASEADDR				(AHB1_BASEADDR + 0x0C00)
#define GPIOE_BASEADDR				(AHB1_BASEADDR + 0x1000)
#define GPIOF_BASEADDR				(AHB1_BASEADDR + 0x1400)
#define GPIOG_BASEADDR				(AHB1_BASEADDR + 0x1800)
#define GPIOH_BASEADDR				(AHB1_BASEADDR + 0x1C00)
#define GPIOI_BASEADDR				(AHB1_BASEADDR + 0x2000)
#define ETHERNET_MAC_BASEADDR		(AHB1_BASEADDR + 0x8000)
#define USB_OTG_HS_BASEADDR			(AHB1_BASEADDR + 0x0000)
#define RCC_BASEADDR				(AHB1_BASEADDR + 0x3800)


// Peripheral Register structure for GPIO
typedef struct
{
	__vo uint32_t MODER;
	__vo uint32_t OTYPER;
	__vo uint32_t OSPEEDR;
	__vo uint32_t PUPDR;
	__vo uint32_t IDR;
	__vo uint32_t ODR;
	__vo uint32_t BSRR;
	__vo uint32_t LCKR;
	__vo uint32_t AFR[2];
}GPIO_RegDef_t;


// Peripheral Register structure for RCC
typedef struct
{
	__vo uint32_t CR;
	__vo uint32_t PLLCFGR;
	__vo uint32_t CFGR;
	__vo uint32_t CIR;
	__vo uint32_t AHB1RSTR;
	__vo uint32_t AHB2RSTR;
	__vo uint32_t AHB3RSTR;
	__vo uint32_t RESERVED0;
	__vo uint32_t APB1RSTR;
	__vo uint32_t APB2RSTR;
	__vo uint32_t RESERVED1;
	__vo uint32_t RESERVED2;
	__vo uint32_t AHB1ENR;
	__vo uint32_t AHB2ENR;
	__vo uint32_t AHB3ENR;
	__vo uint32_t RESERVED3;
	__vo uint32_t APB1ENR;
	__vo uint32_t APB2ENR;
	__vo uint32_t RESERVED4;
	__vo uint32_t RESERVED5;
	__vo uint32_t AHB1LPENR;
	__vo uint32_t AHB2LPENR;
	__vo uint32_t AHB3LPENR;
	__vo uint32_t RESERVED6;
	__vo uint32_t APB1LPENR;
	__vo uint32_t APB2LPENR;
	__vo uint32_t RESERVED7;
	__vo uint32_t RESERVED8;
	__vo uint32_t BDCR;
	__vo uint32_t CSR;
	__vo uint32_t RESERVED9;
	__vo uint32_t RESERVED10;
	__vo uint32_t SSCGR;
	__vo uint32_t PLLI2SCFGR;
} RCC_RegDef_t;


// Peripheral Register structure for EXTI
typedef struct
{
	__vo uint32_t IMR;
	__vo uint32_t EMR;
	__vo uint32_t RTSR;
	__vo uint32_t FTSR;
	__vo uint32_t SWIER;
	__vo uint32_t PR;
}EXTI_RegDef_t;


// Peripheral Register structure for SYSCFG
typedef struct
{
    __vo uint32_t MEMRMP;
    __vo uint32_t PMC;
    __vo uint32_t EXTICR[4];
    uint32_t RESERVED1[2];   // between EXTICR and CMPCR
    __vo uint32_t CMPCR;
    uint32_t RESERVED2[2];   // between CMPCR and CFGR
    __vo uint32_t CFGR;
} SYSCFG_RegDef_t;


// Peripheral Definitions (Peripheral base addresses type casted to xxx_RegDef_t)
#define RCC							((RCC_RegDef_t*)RCC_BASEADDR)
#define GPIOA						((GPIO_RegDef_t*)GPIOA_BASEADDR)
#define GPIOB						((GPIO_RegDef_t*)GPIOB_BASEADDR)
#define GPIOC						((GPIO_RegDef_t*)GPIOC_BASEADDR)
#define GPIOD						((GPIO_RegDef_t*)GPIOD_BASEADDR)
#define GPIOE						((GPIO_RegDef_t*)GPIOE_BASEADDR)
#define GPIOF						((GPIO_RegDef_t*)GPIOF_BASEADDR)
#define GPIOG						((GPIO_RegDef_t*)GPIOG_BASEADDR)
#define GPIOH						((GPIO_RegDef_t*)GPIOH_BASEADDR)
#define GPIOI						((GPIO_RegDef_t*)GPIOI_BASEADDR)
#define EXTI   						((EXTI_RegDef_t*)EXTI_BASEADDR)
#define SYSCFG 						((SYSCFG_RegDef_t*)SYSCFG_BASEADDR)


// Clock Enable Macro for GPIOx
#define GPIOA_PCLK_EN()		(RCC->AHB1ENR |= (1U << 0))
#define GPIOB_PCLK_EN()		(RCC->AHB1ENR |= (1U << 1))
#define GPIOC_PCLK_EN()		(RCC->AHB1ENR |= (1U << 2))
#define GPIOD_PCLK_EN()		(RCC->AHB1ENR |= (1U << 3))
#define GPIOE_PCLK_EN()		(RCC->AHB1ENR |= (1U << 4))
#define GPIOF_PCLK_EN()		(RCC->AHB1ENR |= (1U << 5))
#define GPIOG_PCLK_EN()		(RCC->AHB1ENR |= (1U << 6))
#define GPIOH_PCLK_EN()		(RCC->AHB1ENR |= (1U << 7))
#define GPIOI_PCLK_EN()		(RCC->AHB1ENR |= (1U << 8))


// Clock Disable Macro for GPIOx
#define GPIOA_PCLK_DI()		(RCC->AHB1ENR &= ~(1U << 0))
#define GPIOB_PCLK_DI()		(RCC->AHB1ENR &= ~(1U << 1))
#define GPIOC_PCLK_DI()		(RCC->AHB1ENR &= ~(1U << 2))
#define GPIOD_PCLK_DI()		(RCC->AHB1ENR &= ~(1U << 3))
#define GPIOE_PCLK_DI()		(RCC->AHB1ENR &= ~(1U << 4))
#define GPIOF_PCLK_DI()		(RCC->AHB1ENR &= ~(1U << 5))
#define GPIOG_PCLK_DI()		(RCC->AHB1ENR &= ~(1U << 6))
#define GPIOH_PCLK_DI()		(RCC->AHB1ENR &= ~(1U << 7))
#define GPIOI_PCLK_DI()		(RCC->AHB1ENR &= ~(1U << 8))


// Macros to reset GPIOx Peripherals
#define GPIOA_REG_RESET()				do{(RCC -> AHB1RSTR |= (1U << 0)); (RCC -> AHB1RSTR &= ~(1U << 0)); }while(0)
#define GPIOC_REG_RESET()				do{(RCC -> AHB1RSTR |= (1U << 2)); (RCC -> AHB1RSTR &= ~(1U << 2)); }while(0)
#define GPIOB_REG_RESET()				do{(RCC -> AHB1RSTR |= (1U << 1)); (RCC -> AHB1RSTR &= ~(1U << 1)); }while(0)
#define GPIOD_REG_RESET()				do{(RCC -> AHB1RSTR |= (1U << 3)); (RCC -> AHB1RSTR &= ~(1U << 3)); }while(0)
#define GPIOE_REG_RESET()				do{(RCC -> AHB1RSTR |= (1U << 4)); (RCC -> AHB1RSTR &= ~(1U << 4)); }while(0)
#define GPIOF_REG_RESET()				do{(RCC -> AHB1RSTR |= (1U << 5)); (RCC -> AHB1RSTR &= ~(1U << 5)); }while(0)
#define GPIOG_REG_RESET()				do{(RCC -> AHB1RSTR |= (1U << 6)); (RCC -> AHB1RSTR &= ~(1U << 6)); }while(0)
#define GPIOH_REG_RESET()				do{(RCC -> AHB1RSTR |= (1U << 7)); (RCC -> AHB1RSTR &= ~(1U << 7)); }while(0)
#define GPIOI_REG_RESET()				do{(RCC -> AHB1RSTR |= (1U << 8)); (RCC -> AHB1RSTR &= ~(1U << 8)); }while(0)


//Some Generic Macros
#define ENABLE				1
#define DISABLE				0
#define SET 				ENABLE
#define RESET				DISABLE
#define GPIO_PIN_SET		SET
#define GPIO_PIN_RESET		RESET
#define FLAG_RESET			RESET
#define FLAG_SET			SET


// Macro to return a code( 0 to 7) for a GPIO base address(x)
#define GPIO_BASEADDR_TO_CODE(x)   ( \
    (x == GPIOA) ? 0 : \
    (x == GPIOB) ? 1 : \
    (x == GPIOC) ? 2 : \
    (x == GPIOD) ? 3 : \
    (x == GPIOE) ? 4 : \
    (x == GPIOF) ? 5 : \
    (x == GPIOG) ? 6 : \
    (x == GPIOH) ? 7 : \
    (x == GPIOI) ? 8 : \
    0xFF )   // ← 0xFF = invalid (you can check for this value)

// Interrupt Request Numbers for STM32F40xx MCU
#define IRQ_NO_EXTI0		6
#define IRQ_NO_EXTI1		7
#define IRQ_NO_EXTI2		8
#define IRQ_NO_EXTI3		9
#define IRQ_NO_EXTI4		10
#define IRQ_NO_EXTI9_5		23
#define IRQ_NO_EXTI5_10		40
#define IRQ_NO_SPI1			35
#define IRQ_NO_SPI2			36
#define IRQ_NO_SPI3			51
#define IRQ_NO_SPI4
#define IRQ_NO_IIC1_EV		31
#define IRQ_NO_IIC1_ER		32


// Include the driver header file here so we don't have to include it at application layer
#include "STM32_GPIO.h"
#include "../Int_Drivers/Inc/LCD_HD44780.h"


#endif /* INC_STM32F407X_H_ */
