/*
 * Author: Rishit Darwade
 */

#include "main.h"
#include "stm32f4xx_hal_tim.h"
#include "timer.h"

/*----- TIMER HANDLES (kept non-static so other code can use them) ---------*/
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;

/* callback pointers */
void (*callback_tim2)(void) = NULL;
void (*callback_tim3)(void) = NULL;
void (*callback_tim4)(void) = NULL;

void timer_init(TIM_TypeDef *TIMx, uint32_t freq, void (*callback)(void))
{
    TIM_HandleTypeDef *htim = NULL;

    if (TIMx == TIM2) {
        __HAL_RCC_TIM2_CLK_ENABLE();
        htim = &htim2;
        callback_tim2 = callback;
    } else if (TIMx == TIM3) {
        __HAL_RCC_TIM3_CLK_ENABLE();
        htim = &htim3;
        callback_tim3 = callback;
    } else if (TIMx == TIM4) {
        __HAL_RCC_TIM4_CLK_ENABLE();
        htim = &htim4;
        callback_tim4 = callback;
    } else {
        return;
    }

    uint32_t timer_clock = HAL_RCC_GetPCLK1Freq();
    if ((RCC->CFGR & RCC_CFGR_PPRE1) != RCC_CFGR_PPRE1_DIV1) {
        timer_clock *= 2U;
    }

    const uint32_t base_hz = 1000000U;
    uint32_t prescaler = (timer_clock / base_hz) - 1U;
    uint32_t arr = (base_hz / freq) - 1U;

    htim->Instance = TIMx;
    htim->Init.Prescaler = prescaler;
    htim->Init.CounterMode = TIM_COUNTERMODE_UP;
    htim->Init.Period = arr;
    htim->Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;

    if (HAL_TIM_Base_Init(htim) != HAL_OK) {
        return; /* bail if init fails */
    }

    /* Start timer interrupt */
    HAL_TIM_Base_Start_IT(htim);

    /* NVIC enable */
    if (TIMx == TIM2) {
        HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(TIM2_IRQn);
    } else if (TIMx == TIM3) {
        HAL_NVIC_SetPriority(TIM3_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(TIM3_IRQn);
    } else if (TIMx == TIM4) {
        HAL_NVIC_SetPriority(TIM4_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(TIM4_IRQn);
    }
}

/* IRQ handlers (forward to HAL) */
void TIM2_IRQHandler(void) { HAL_TIM_IRQHandler(&htim2); }
void TIM3_IRQHandler(void) { HAL_TIM_IRQHandler(&htim3); }
void TIM4_IRQHandler(void) { HAL_TIM_IRQHandler(&htim4); }

/* HAL callback dispatch */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM2 && callback_tim2) {
        callback_tim2();
    } else if (htim->Instance == TIM3 && callback_tim3) {
        callback_tim3();
    } else if (htim->Instance == TIM4 && callback_tim4) {
        callback_tim4();
    }
}
