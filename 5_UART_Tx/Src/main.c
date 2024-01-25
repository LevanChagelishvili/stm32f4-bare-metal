#include <stdio.h>
#include "stm32f4xx.h"
#include <stdint.h>

#define GPIOAEN			(1U << 0)
#define USART2EN		(1U << 17)

#define SYS_FREQ		16000000
#define APB1_CLK		SYS_FREQ
#define UART_BAUDRATE	115200

#define CR1_TE			(1U << 3)
#define CR1_UE			(1U << 13)
#define SR_TXE			(1U << 7)

void uart2_tx_init(void);
static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate);
static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate);
void uart2_write(int ch);


int __io_putchar(int ch)
{
	uart2_write(ch);
	return ch;
}

int main(void)
{
	uart2_tx_init();

	while(1)
	{
		printf("Progressus\n\r");
	}

	return 0;
}

void uart2_tx_init(void)
{
	// Enable clock access to GPIOA
	RCC->AHB1ENR |= GPIOAEN;

	// PA2 to ultimate function mode
	GPIOA->MODER &= ~ (1U << 4);
	GPIOA->MODER |= (1U << 5);

	// Set PA2 alternate function type to UART_Tx (AF07)
	GPIOA->AFR[0] |= (1U << 8);
	GPIOA->AFR[0] |= (1U << 9);
	GPIOA->AFR[0] |= (1U << 10);
	GPIOA->AFR[0] &= ~(1U << 11);

	// Enable clock access to uart2
	RCC->APB1ENR |= USART2EN;

	// Configure baudrate
	uart_set_baudrate(USART2, APB1_CLK, UART_BAUDRATE);

	// UART transmit enable
	USART2->CR1 = CR1_TE;

	// Enable uart module
	USART2->CR1 |= CR1_UE;
}

static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate)
{
	USARTx->BRR = compute_uart_bd(PeriphClk,BaudRate);
}

static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate)
{
	return (PeriphClk + BaudRate / 2) / BaudRate;
}

void uart2_write(int ch)
{
	// Make sure that transmit data register is empty
	while(!(USART2->SR & SR_TXE)){}

	// Write to transmit data register
	USART2->DR = (ch & 0xFF);
}

