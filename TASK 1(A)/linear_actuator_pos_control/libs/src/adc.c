/*
 * Author: Rishit Darwade
 */

#include "main.h"
#include "stm32f4xx_hal.h"
#include "adc.h"

volatile uint16_t adc_value = 0;
ADC_HandleTypeDef hadc1;              /* <--- DEFINE it here (one definition) */
static ADC_HandleTypeDef *active_hadc = NULL; // Store last used ADC handle

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
    if (hadc == active_hadc)
    {
        adc_value = HAL_ADC_GetValue(hadc);
    }
}

void ADC_IRQHandler(void)
{
    if (active_hadc)
    {
        HAL_ADC_IRQHandler(active_hadc);
    }
}

void adc_start(ADC_HandleTypeDef* hadc)
{
    active_hadc = hadc;
    HAL_ADC_Start_IT(hadc);
}

void adc_init(ADC_HandleTypeDef* hadc)
{
    // Store the handle so IRQ knows which ADC to service
    active_hadc = hadc;

    hadc->Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
    hadc->Init.Resolution = ADC_RESOLUTION_12B;
    hadc->Init.ScanConvMode = DISABLE;
    hadc->Init.ContinuousConvMode = DISABLE;
    hadc->Init.DiscontinuousConvMode = DISABLE;
    hadc->Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    hadc->Init.ExternalTrigConv = ADC_SOFTWARE_START;
    hadc->Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc->Init.NbrOfConversion = 1;
    hadc->Init.DMAContinuousRequests = DISABLE;
    hadc->Init.EOCSelection = ADC_EOC_SINGLE_CONV;

    if (HAL_ADC_Init(hadc) != HAL_OK)
    {
        Error_Handler();
    }

    ADC_ChannelConfTypeDef sConfig = {0};
    sConfig.Channel = ADC_CHANNEL_0;
    sConfig.Rank = 1;
    sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
    HAL_ADC_ConfigChannel(&hadc1, &sConfig);


    HAL_NVIC_SetPriority(ADC_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(ADC_IRQn);
}
