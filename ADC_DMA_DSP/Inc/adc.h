
#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>
#include "stm32f4xx.h"

void pa1_adc_int(void);
void dma_init(void);
void dma_config(uint32_t sourcAdd, uint32_t destinationAdd, uint16_t size);
void start_conversion(void);
uint32_t adc_read(void);

#endif /* ADC_H_ */
