#include "stm32f4xx.h"
#include "adc.h"

void pa1_adc_int(void)
{
	// Enable clock to GPIOA
	RCC->AHB1ENR |= (1U << 0);

	// Set the mode of PA1 to analog
	GPIOA->MODER &= ~0x0C;// |= (1U << 2);
	GPIOA->MODER |= 0x0C;// (1U << 3);

	// Enable clock to ADC
	RCC->APB2ENR |= (1U << 8);

	// Sampling time
	ADC1->SMPR2 |= (1U << 3);

	// Common control register / Set prescaler
	ADC->CCR = 0x00;// PCLK2 dividted by 2

	// Control register 1 / Select resolution
	ADC1->CR1 |= (1U << 0);// 12 bit / minimum 12 ADCCLK cycles + sampling time

	// Conversion sequence start
	//ADC1->SQR3 = 0;
	ADC1->SQR3 = (1U << 0);

	// Conversion sequence length
	ADC1->SQR1 = 0x00;

	// Enable ADC module
	ADC1->CR2 |= (1U << 0);// Continuous conversion mode

	// Enable DMA for ADC
	ADC1->CR2 |= (1U << 8);

	// Enable continuous Request
	ADC1->CR2 |= (1U << 9);
}

void dma_init(void)
{
	// Enable the DMA clock
	RCC->AHB1ENR |= (1U << 22);

	// Select data direction
	DMA2_Stream0->CR &= ~(3U << 6);// Peripheral to memory

	// Select circular mode
	DMA2_Stream0->CR |= (1U << 8);// CIRC = 1

	// Enable Memory Address Increment
	DMA2_Stream0->CR |= (1U << 10);// MINC = 1

	// Set size for data
	DMA2_Stream0->CR |= (1U << 11) | (1U << 13); // 16 bit data

	// Select channel for the stream
	DMA2_Stream0->CR &= ~(7U << 25);// Channel 0 selected
}

void dma_config(uint32_t sourcAdd, uint32_t destinationAdd, uint16_t size)
{
	// Set the size of the transfer
	DMA2_Stream0->NDTR = size;

	// Source/ Peripheral address
	DMA2_Stream0->PAR = sourcAdd;

	// Destination address in memory
	DMA2_Stream0->M0AR = destinationAdd;

	// Enable DMA
	DMA2_Stream0->CR |= (1U << 0);
}

void start_conversion(void)
{
	// Enable continuous conversion
	ADC1->CR2 |= (1U << 0);

	// Start ADC conversion
	//ADC1->CR2 |= 0;
	ADC1->CR2 |= (1U << 30);
}

uint32_t adc_read(void)
{
	// Wait for conversion to be complete
	while(!(ADC1->SR & (1U << 1))){}

	// Read conversion result
	return (ADC1->DR);
}
