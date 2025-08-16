#ifndef TIMER_H
#define TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"
#include <stdint.h>

void timer_init(TIM_TypeDef *TIMx, uint32_t freq, void (*callback)(void));

/* Expose timer handles (defined in timer.c) so other modules can use them */
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;

/* Expose callback pointers (defined in timer.c) if other code needs to change them */
extern void (*callback_tim2)(void);
extern void (*callback_tim3)(void);
extern void (*callback_tim4)(void);

/* IRQ handler prototypes (defined in timer.c) */
void TIM2_IRQHandler(void);
void TIM3_IRQHandler(void);
void TIM4_IRQHandler(void);

/* HAL callback prototype (optional to declare; HAL already declares it weakly) */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

#ifdef __cplusplus
}
#endif

#endif /* TIMER_H */
