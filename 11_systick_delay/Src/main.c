#include <stdio.h>
#include "stm32f4xx.h"
#include "uart.h"
#include "adc.h"
#include "systick.h"


int main(void)
{
	uart2_Rxtx_init();


	while(1)
	{

		printf("Andro Ylea");
		systickDelayMs(1000);
	}

	return 0;
}




