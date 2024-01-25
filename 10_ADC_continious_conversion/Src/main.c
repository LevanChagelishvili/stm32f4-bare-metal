#include <stdio.h>
#include "stm32f4xx.h"
#include "uart.h"
#include "adc.h"

uint32_t sensor_value;

int main(void)
{
	uart2_Rxtx_init();

	pa1_adc_int();

	while(1)
	{
		start_conversion();
		sensor_value = adc_read();
		printf("Sensor Value: %ld \n\r", sensor_value);
	}

	return 0;
}




