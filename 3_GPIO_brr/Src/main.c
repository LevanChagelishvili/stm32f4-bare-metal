#include "stm32f4xx.h"

#define GPIOAEN  (1U << 0)
#define GPIOCEN  (1U << 2)

#define PIN5_ON	 (1U << 5)
#define PIN5_OFF (1U << 21)
#define PIN13	 (1U << 13)

#define LED_ON	 PIN5_ON
#define LED_OFF	 PIN5_OFF
#define BUTTON   PIN13

int main(void)
{

	RCC->AHB1ENR |= GPIOAEN;
	RCC->AHB1ENR |= GPIOCEN;

	GPIOA->MODER |= (1U << 10);
	GPIOA->MODER &= ~(1U << 11);

	GPIOC->MODER &= ~(1U << 26);
	GPIOC->MODER &= ~(1U << 27);

	while(1)
	{

		if(GPIOC->IDR == 0)
		{
			GPIOA->BSRR = LED_ON;
		}
		else
		{
			GPIOA->BSRR = PIN5_OFF;
		}

	}

	return 0;
}
