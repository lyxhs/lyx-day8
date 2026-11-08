#include "pid.h"
#include "motor.h"

#define Kp 25.0f
#define Ki 80.0f
#define Kd 200.0f
#define MAX_OUT 15000

pid_t pidnum;

void PID_Init(void) {
    pidnum.kp = Kp;
    pidnum.ki = Ki;
    pidnum.kd = Kd;
    pidnum.max_out = MAX_OUT;
    pidnum.target = 0;
}

float PID_Calc() {
    float e = pidnum.target - motor_gm6020[0].speed_rpm;
    float de = e-pidnum.err;
    float dde = de - pidnum.d_err;
    float du = de*pidnum.kp+pidnum.ki*e*0.001f+pidnum.kd*dde*0.001f;
    float u = du+pidnum.d_out;
    if (u>pidnum.max_out) u = pidnum.max_out;
    if (u<-pidnum.max_out) u = -pidnum.max_out;
    pidnum.err = e;
    pidnum.d_err = de;
    pidnum.d_out = u;
    return u;
}

void PID_Reset(int target) {
    pidnum.target = target;
}