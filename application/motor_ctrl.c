#include "motor_ctrl.h"
#include "pid.h"
#include "motor.h"

void Motor_Ctrl_Init(void) {
    PID_Init();
}

void Motor_Ctrl_Set_Target(int16_t target_rpm) {
    PID_Reset(target_rpm);
}

void Motor_Ctrl_Update(void) {
    int16_t cmd[4] = {0,0,0,0};
    if (pidnum.target != 0) {
        cmd[0] = PID_Calc();
        Motor_SendVoltage(cmd);
    }
}

bool Motor_Ctrl_Is_Online(void) {
    return (HAL_GetTick()-motor_gm6020[0].last_update_tick>=500&&HAL_GetTick()>1000);
}