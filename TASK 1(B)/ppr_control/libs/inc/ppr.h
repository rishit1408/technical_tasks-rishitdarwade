#ifndef PPR_CONTROL_H
#define PPR_CONTROL_H

#include <stdint.h>
#include <stdbool.h>

typedef enum{
	PPR_IDLE=0,
	PPR_REGULATE,
	PPR_RELIEVE
}ppr_mode_t;

typedef struct{
    float set_pressure;     /* desired pressure */
    float relief_pressure;  /* relief threshold */
    uint32_t open_ms;       /* open duration (ms) when relieving */
    uint32_t close_ms;      /* close duration (ms) when relieving */
} ppr_params_t;

void ppr_init(void);
void ppr_start(void);
void ppr_stop(void);
void ppr_control_tick(void);

/* setters */
void ppr_set_params(const ppr_params_t *p);
void ppr_set_mode(ppr_mode_t m);

#endif /* PPR_CONTROL_H */
