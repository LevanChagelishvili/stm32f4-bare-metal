/*
 * uart.h
 *
 *  Created on: Aug 9, 2023
 *      Author: DELL
 */

#ifndef UART_H_
#define UART_H_
#include "stm32f4xx.h"
#include <stdint.h>

void uart2_Rxtx_init(void);
void uart2_tx_init(void);
void uart2_write(int ch);
char uart2_read(void);

#endif /* UART_H_ */
