#include "led_ctrl.h"
#include "motor_ctrl.h"
#include "main.h"

uint32_t last_time = 0;
uint16_t pwm_turn = 1;
extern TIM_HandleTypeDef htim5;

void Led_Ctrl_Init(void) {
    HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_3);
    HAL_GPIO_WritePin(GPIOH,GPIO_PIN_11,GPIO_PIN_SET);
}

void Led_Ctrl_Update() {
    if (!Motor_Ctrl_Is_Online()) {
        HAL_GPIO_WritePin(GPIOH, GPIO_PIN_11, GPIO_PIN_RESET);
        if (HAL_GetTick()-last_time>=1000) {
            last_time = HAL_GetTick();
            pwm_turn =!pwm_turn;
        }
        uint16_t precent = (HAL_GetTick()-last_time)/10;
        if (precent>100) {precent=100;}
        if (pwm_turn) {
            __HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_3, 65535*precent/100);
        }else {
            __HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_3, 65535*(100-precent)/100);
        }
    }else {
        __HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_3, 0);
        HAL_GPIO_WritePin(GPIOH, GPIO_PIN_11, GPIO_PIN_SET);
        pwm_turn = 1;
    }
}
