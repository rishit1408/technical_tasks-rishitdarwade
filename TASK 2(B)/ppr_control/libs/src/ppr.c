/*
 * Author: RISHIT DARWADE
 */

#include "ppr.h"
#include "adc.h"
#include "pid.h"
#include "main.h"
#include "stm32f4xx_hal.h"
#include <string.h>

#define PRESSURE_RANGE 10.0
#define PWM_MAX 999.0
#define PWM_MIN 0.0
#define HYSTERESIS_FRAC 0.05

static ppr_params_t params;

static volatile bool running = false;
static ppr_mode_t mode = PPR_IDLE;

static inline float adc_to_pressure(uint16_t a)
{
    return ((float)a / 4095) * PRESSURE_RANGE;
}

void ppr_init(void)
{
    memset(&params, 0, sizeof(params));
    params.set_pressure = 2.0;
    params.relief_pressure = 3.0;
    params.open_ms = 0;
    params.close_ms = 0;

    pid_init(1.0, 0.0, 0.01);

    mode = PPR_IDLE;
    running = false;
}

void ppr_start(void)
{
    running = true;
    mode = PPR_REGULATE;

    adc_start(&hadc1);
}

void ppr_stop(void)
{
    running = false;
    mode = PPR_IDLE;
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);
}

void ppr_set_params(const ppr_params_t *p)
{
    if (!p) return;
    params = *p;
}

void ppr_set_mode(ppr_mode_t m)
{
    mode = m;
}

ppr_mode_t ppr_get_mode(void)
{
    return mode;
}

void ppr_control_tick(void)
{
    if (!running)
    	return;

    uint16_t actuator_pos = adc_value;   // ADC1
    HAL_ADC_Start(&hadc2);
    HAL_ADC_PollForConversion(&hadc2, 10);
    uint16_t adc_press = HAL_ADC_GetValue(&hadc2); // ADC2
    float pressure = adc_to_pressure(adc_press);


    if (pressure >= params.relief_pressure) {
        mode = PPR_RELIEVE;
    }

    if (mode == PPR_RELIEVE) {
        /* open fully until pressure drops below relief  hysteresis */
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, (uint32_t)PWM_MAX);
        float hysteresis = params.relief_pressure * HYSTERESIS_FRAC;
        if (pressure <= (params.relief_pressure - hysteresis)) {
            mode = PPR_REGULATE;
        }
    } else {
        if (mode == PPR_REGULATE) {
            float out = pid_control(params.set_pressure, pressure);
            if (out < PWM_MIN) out = PWM_MIN;
            if (out > PWM_MAX) out = PWM_MAX;
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, (uint32_t)(out + 0.5f));
        } else {
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);
        }
    }

}
