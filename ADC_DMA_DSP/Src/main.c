#include <stdio.h>
#include "stm32f4xx.h"
#include "uart.h"
#include "adc.h"

#define ADC_RX_BUFF	12

uint16_t ADC_DATA[ADC_RX_BUFF];

static void dma_callback(void);
void DMA1_Stream6_IRQHandler(void);
char message[21] = "Andro magari YLEA\n\r";

int main(void)
{
	uart2_Rxtx_init();
	//dma1_strem6_init((uint32_t) message, (uint32_t)&USART2->DR,  31);
	dma_uart_init((uint32_t) message, (uint32_t)&USART2->DR,  31);

	pa1_adc_int();
	dma_init();

	dma_config((uint32_t) &ADC1->DR, (uint32_t) ADC_DATA, ADC_RX_BUFF);

	start_conversion();
	adc_read();
	while(1)
	{

		//adc_read();
		//printf("Sensor Value: %u \n\r", ADC_DATA);
	}

	return 0;
}

static void dma_callback(void)
{
	dma_uart_init((uint32_t) message, (uint32_t)&USART2->DR,  31);
}

void DMA1_Stream6_IRQHandler(void)
{
	// Check for transfer complete interrupt
	if(DMA1->HISR & (1U << 21))
	{
		// Clear flag
		DMA1->HIFCR |= (1U << 21);
		// Do something
		dma_callback();
	}
}



