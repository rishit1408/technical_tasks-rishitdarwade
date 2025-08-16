#ifndef PID_H
#define PID_H

#ifdef __cplusplus
extern "C" {
#endif

void  pid_init(float kp, float ki, float kd);
void  pid_reset(void);
float pid_control(float setpoint, float measured);

#ifdef __cplusplus
}
#endif
#endif // PID_H
