#include "bsp_servo.h"
#include "main.h"

extern TIM_HandleTypeDef htim1;

void Bsp_Servo_Init(void)
{
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
    Bsp_Servo_Set_Angle(0);
}

void Bsp_Servo_Set_Angle(int angle) {
    if (angle > 180) angle = 180;
    if (angle < 0) angle = 0;
    uint16_t pulse_cal = (uint16_t)(500+angle*2000/180);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, pulse_cal);
}