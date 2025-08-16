#ifndef ADC_H
#define ADC_H

#include "stm32f4xx_hal.h"

extern volatile uint16_t adc_value;

extern ADC_HandleTypeDef hadc1;

void adc_init(ADC_HandleTypeDef* hadc);
void adc_start(ADC_HandleTypeDef* hadc);

#endif // ADC_H
