// This is standard for creating structure of register set
/*
#define __IO volatile

typedef struct
{
	__IO uint32_t MODER;		// GPIO port mode register Address offset: 0x00
	__IO uint32_t OTYPER;		// GPIO port output type register Address offset: 0x04
	__IO uint32_t OSPEEDR;		// GPIO port output speed register Address offset: 0x08
	__IO uint32_t PUPDR;		// GPIO port pull-up/pull-down register Address offset: 0x0C
	__IO uint32_t IDR;			// GPIO port input data register Address offset: 0x10
	__IO uint32_t ODR;			// GPIO port output data register Address offset: 0x14
	__IO uint32_t BSRR;			// GPIO port bit set/reset register Address offset: 0x18
	__IO uint32_t LCKR;			// GPIO port configuration lock register Address offset: 0x1C
	__IO uint32_t AFR[2];		// GPIO alternate function register Address offset: 0x20 - 0x24
}GPIO_TypeDef;
*/

#include "stdint.h"

#define PERIPH_START_ADD		(0x40000000UL) // Peripherals starting address
// AHB = Advance High Performance Buss
#define AHB1_OFFSET				(0x20000UL)
#define AHB1_START_ADD			(PERIPH_START_ADD + AHB1_OFFSET)

#define GPIOA_OFFSET			(0x20000UL)
#define GPIOA_START_ADD			(AHB1_START_ADD + GPIOA_OFFSET)
// Clock
#define RCC_OFFSET				(0x23800UL)
#define RCC_START_ADD			(AHB1_START_ADD + RCC_OFFSET)

#define GPIOAEN 				(1U << 0) // IO port C clock enabled

#define PIN5					(1U << 5)
#define LED_PIN 				PIN5


typedef struct
{
	volatile uint32_t MODER;
	volatile uint32_t JUST_MEMORY_OCUP[4];
	volatile uint32_t ODR;
}GPIO_TypeDef;

typedef struct
{
	volatile uint32_t JUST_MEMORY_OCUP[12];
	volatile uint32_t AHB1ENR;
}RCC_TypeDef;

#define GPIOA	((GPIO_TypeDef*)GPIOA_START_ADD)
#define RCC		((RCC_TypeDef*)RCC_START_ADD)

int main(void)
{
	// 1. Enable clock access to GPIOA
	RCC->AHB1ENR |= GPIOAEN;

	// 2. Set PC8 as OUTPUT
	GPIOA->MODER |= (1U << 10);
	GPIOA->MODER &= ~(1U << 11);

	while(1)
	{
		GPIOA->ODR ^= LED_PIN;
		for(int i = 0; i < 1000000; i++){}
	}

	return 0;
}
