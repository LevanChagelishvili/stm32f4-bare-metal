#include "stm32f4xx.h"
#include <stdio.h>
#include "uart.h"
#include "adc.h"
#include "systick.h"
#include "tim.h"


int timestamp = 0;

int main(void)
{
	//uart2_Rxtx_init();

	tim2_pa5_output_compare();
	tim3_input_compare();

	while(1)
	{
		// Wait until edge is captured
		while(!(TIM3->SR & (1U << 1))){}

		// Read value
		timestamp = TIM3->CCMR1;
	}

	return 0;
}




