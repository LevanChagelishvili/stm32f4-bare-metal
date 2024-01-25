#include "stm32f4xx.h"

void tim2_1hz_init(void)
{
	// Enable Tim2 clock
	RCC->APB1ENR |= (1U << 0);

	// Set prescaler
	TIM2->PSC = 16000 - 1;// 16000000 / 16000 = 10000

	// Set auto reload
	TIM2->ARR |= 10000 - 1;// 1 Hz

	// Clear timer2
	TIM2->CNT = 0x00;

	// Enable counter
	TIM2->CR1 = (1U << 0);
}

void tim2_pa5_output_compare(void)
{
	// Enable Clock to pa5
	RCC->AHB1ENR |= (1U << 0);

	// Set pa5 to alternate function
	GPIOA->MODER &= ~(1U << 10);
	GPIOA->MODER |= (1U << 11);

	// Set pa5 alternate function type to TIM2_CH1
	GPIOA->AFR[0] |= (1U << 0);

	// Enable Tim2 clock
	RCC->APB1ENR |= (1U << 0);

	// Set prescaler
	TIM2->PSC = 16000 - 1;// 16000000 / 16000 = 10000

	// Set auto reload
	TIM2->ARR |= 10000 - 1;// 1 Hz

	// Set output compare toggle mode
	TIM2->CCMR1 = (1U << 4) | (1U << 5);

	// Enable Tim2 ch1 in capture mode
	TIM2->CCER = (1U << 0);

	// Clear timer2
	TIM2->CNT = 0x00;

	// Enable counter
	TIM2->CR1 = (1U << 0);
}

void tim3_input_compare(void)
{
	// Enable Clock to pa5
	RCC->AHB1ENR |= (1U << 0);

	// Set pa5 to alternate function
	GPIOA->MODER &= ~(1U << 12);
	GPIOA->MODER |= (1U << 13);

	// Set pa5 alternate function type to TIM3_CH1
	GPIOA->AFR[0] |= (1U << 25);

	// Enable Tim3 clock
	RCC->APB1ENR |= (1U << 1);

	// Set prescaler
	TIM3->PSC = 16000 - 1;// 16000000 / 16000 = 10000

	// Set CH1 to capture at every edge
	TIM3->CCMR1 = (1U << 0);

	// Set Ch1 to capture at rising edge
	TIM3->CCER = (1U << 0);

	// Enable TIM3
	TIM2->CR1 = (1U << 0);
}
