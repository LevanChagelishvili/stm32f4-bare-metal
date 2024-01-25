#include "stm32f4xx.h"
#include "adc.h"

#define GPIOAEN			(1U << 0)
#define ADC1EN			(1U << 8)
#define ADC_CH1			(1U << 0)
#define ADC_SEQ_LEN 	0x00
#define CR2_ADOM		(1U << 0)
#define CR2_SWSART		(1U << 30)
#define SR_EOC1			(1U << 1)

void pa1_adc_int(void)
{
	// Enable clock to GPIOA
	RCC->AHB1ENR |= GPIOAEN;

	// Set the mode of PA1 to analog
	GPIOA->MODER |= (1U << 2);
	GPIOA->MODER |= (1U << 2);

	// Enable clock to ADC
	RCC->APB2ENR |= ADC1EN;

	// Conversion sequence start
	ADC1->SQR3 = ADC_CH1;\

	// Conversion sequence length
	ADC1->SQR1 = ADC_SEQ_LEN;

	// Enable ADC module
	ADC1->CR2 |= CR2_ADOM;
}

void start_conversion(void)
{
	// Start ADC conversion
	ADC1->CR2 |= CR2_SWSART;
}

uint32_t adc_read(void)
{
	// Wait for conversion to be complete
	while(!(ADC1->SR & SR_EOC1)){}

	// Read conversion result
	return (ADC1->DR);
}
