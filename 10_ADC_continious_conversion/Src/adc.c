#include "stm32f4xx.h"
#include "adc.h"

#define GPIOAEN			(1U << 0)
#define ADC1EN			(1U << 8)
#define ADC_CH1			(1U << 0)
#define ADC_SEQ_LEN 	0x00
#define CR2_ADON		(1U << 0)
#define CR2_SWSART		(1U << 30)
#define SR_EOC1			(1U << 1)
#define CR2_CONT		(1U << 0)
#define SMPR2_SMP1		(1U << 3)
#define ADCPRE			0x00
#define ADCCR1_RES		(1U << 0)


void pa1_adc_int(void)
{
	// Enable clock to GPIOA
	RCC->AHB1ENR |= GPIOAEN;

	// Set the mode of PA1 to analog
	GPIOA->MODER &= ~0x0C;// |= (1U << 2);
	GPIOA->MODER |= 0x0C;// (1U << 3);

	// Enable clock to ADC
	RCC->APB2ENR |= ADC1EN;

	// Sampling time
	ADC1->SMPR2 |= SMPR2_SMP1;

	// Common control register / Set prescaler
	ADC->CCR = ADCPRE;// PCLK2 dividted by 2

	// Control register 1 / Select resolution
	ADC1->CR1 |= ADCCR1_RES;// 12 bit / minimum 12 ADCCLK cycles + sampling time

	// Conversion sequence start
	//ADC1->SQR3 = 0;
	ADC1->SQR3 = ADC_CH1;

	// Conversion sequence length
	ADC1->SQR1 = ADC_SEQ_LEN;

	// Enable ADC module
	ADC1->CR2 |= CR2_ADON;// Continious conversion mode
}

void start_conversion(void)
{
	// Enable continuous conversion
	ADC1->CR2 |= CR2_CONT;

	// Start ADC conversion
	//ADC1->CR2 |= 0;
	ADC1->CR2 |= CR2_SWSART;
}

uint32_t adc_read(void)
{
	// Wait for conversion to be complete
	while(!(ADC1->SR & SR_EOC1)){}

	// Read conversion result
	return (ADC1->DR);
}
