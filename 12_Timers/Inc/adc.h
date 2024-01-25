/*
 * adc.h
 *
 *  Created on: Aug 11, 2023
 *      Author: DELL
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

void pa1_adc_int(void);
void start_conversion(void);
uint32_t adc_read(void);

#endif /* ADC_H_ */
