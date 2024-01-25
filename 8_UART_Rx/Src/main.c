#include <stdio.h>
#include "stm32f4xx.h"
#include "uart.h"

#define GPIOAEN			(1U << 0)
#define GPIOA_PIN5		(1U << 5)
#define LED				GPIOA_PIN5

char key;

int main(void)
{
	uart2_Rxtx_init();

	RCC->AHB1ENR |= GPIOAEN;

	GPIOA->MODER |= (1U << 10);
	GPIOA->MODER &= ~(1U << 11);

	while(1)
	{
		key = uart2_read();

		if(key == '1')
		{
			GPIOA->ODR |= LED;
		}
		else
		{
			GPIOA->ODR &= ~LED;
		}
	}

	return 0;
}




