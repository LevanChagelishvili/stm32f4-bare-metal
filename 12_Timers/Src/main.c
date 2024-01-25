#include "stm32f4xx.h"
#include <stdio.h>
#include "uart.h"
#include "adc.h"
#include "systick.h"
#include "tim.h"

int main(void)
{
	uart2_Rxtx_init();


	while(1)
	{
		// Wait for UIF
		while(!(TIM2->SR & (1U << 0))){}

		// Clear UIF
		TIM2->SR &= ~(1U << 0);
		printf("STM32F4xx");
	}

	return 0;
}




