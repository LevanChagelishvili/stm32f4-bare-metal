#include "stm32f4xx.h"

#define SYSTICK_LOAD_VAL		16000
#define CTRL_ENABLE				(1U << 0)
#define CTRL_CLKSRC				(1U << 2)
#define CTRL_COUNTFLAG			(1U << 16)

void systickDelayMs(int delay)
{
	// Reload with number of clock per millis
	SysTick->LOAD = SYSTICK_LOAD_VAL;

	// Clear systick current value register
	SysTick->VAL = 0;

	// Enable systick and select internal clk src
	SysTick->CTRL = CTRL_ENABLE | CTRL_CLKSRC;

	for(int i = 0; i < delay; i++)
	{
		// Wait until countflag is set
		while((SysTick->CTRL & CTRL_COUNTFLAG) == 0) {}

	}
	SysTick->CTRL = 0;
}
