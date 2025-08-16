/*
 * Author: Rishit Darwade
 */

#include "pid.h"

static float g_kp = 0.0f, g_ki = 0.0f, g_kd = 0.0f;
static float pid_integral = 0.0f;
static float pid_prev_error = 0.0f;

void pid_init(float kp, float ki, float kd) {
    g_kp = kp; g_ki = ki; g_kd = kd;
    pid_reset();
}

void pid_reset(void) {
    pid_integral = 0.0f;
    pid_prev_error = 0.0f;
}

float pid_control(float setpoint, float measured)
{
    float error = setpoint - measured;

    pid_integral += error;
    if (pid_integral > 1000.0f) pid_integral = 1000.0f;
    if (pid_integral < -1000.0f) pid_integral = -1000.0f;

    float derivative = error - pid_prev_error;
    pid_prev_error = error;

    float output = g_kp * error + g_ki * pid_integral + g_kd * derivative;

    if (output > 999.0f) output = 999.0f;
    else if (output < 0.0f) output = 0.0f;

    return output;
}
