#include "stm32f4xx.h"

void tim2_1hz_init(void)
{
	// Enable Tim2 clock
	RCC->AHB1ENR |= (1U << 0);

	// Set prescaler
	TIM2->PSC = 1600 - 1;// 16000000 / 16000 = 10000

	// Set auto reload
	TIM2->ARR |= 10000 - 1;// 1 Hz

	// Clear timer2
	TIM2->CNT = 0x00;

	// Enable counter
	TIM2->CR1 |= (1U << 0);
}
