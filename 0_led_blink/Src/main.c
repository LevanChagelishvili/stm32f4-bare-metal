// STM32F415RGT6
// LED blink code
// LED PORT C
// LED PIN 8

#define PERIPH_START_ADD		(0x40000000UL) // Peripherals starting address
// AHB = Advance High Performance Buss
#define AHB1_OFFSET				(0x20000UL)
#define AHB1_START_ADD			(PERIPH_START_ADD + AHB1_OFFSET)

#define GPIOA_OFFSET			(0x20000UL)
#define GPIOA_START_ADD			(AHB1_START_ADD + GPIOA_OFFSET)
// Clock
#define RCC_OFFSET				(0x23800UL)
#define RCC_START_ADD			(AHB1_START_ADD + RCC_OFFSET)
// Enable clock for AHB1
#define AHB1EN_R_OFFSET			(0x30UL)
#define RCC_AHB1EN_REGISTER		(*(volatile unsigned int *)(RCC_START_ADD + AHB1EN_R_OFFSET))
// MODE_R = GPIO port mode register
#define GPIOAEN 				(1U << 0) // IO port C clock enabled
#define MODE_R_OFFSET			(0x00UL)
#define GPIOA_MODE_REGISTER		(*(volatile unsigned int *)(GPIOA_START_ADD + MODE_R_OFFSET))
// OD_R = GPIO port output data register
#define OD_R_OFFSET				(0x14UL)
#define GPIOA_OD_REGISTER		(*(volatile unsigned int *)(GPIOA_START_ADD + OD_R_OFFSET))

#define PIN5					(1U << 5)
#define LED_PIN 				PIN5

int main(void)
{
	// 1. Enable clock access to GPIOA
	RCC_AHB1EN_REGISTER |= GPIOAEN;
	// 2. Set PC8 as OUTPUT
	//MODER4 (9,8) 01: General purpose output mode
	GPIOA_MODE_REGISTER |= (1U << 10);
	GPIOA_MODE_REGISTER &= ~(1U << 11);
	while(1)
	{
		// Set PC8 high = Turn on LED
		 //GPIOA_OD_REGISTER |= LED_PIN;

		// toggle LED
		GPIOA_OD_REGISTER ^= LED_PIN;
		// Create delay
		for(int i = 0; i < 100000; i++){}

	}

	return 0;
}
