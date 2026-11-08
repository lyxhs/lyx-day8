/**
 * @file    bsp_servo.h
 * @brief   舵机板级封装（TIM1_CH1 / PE9，50Hz PWM，0.5~2.5ms 对应 0~180°）
 */
#ifndef __BSP_SERVO_H
#define __BSP_SERVO_H

/**
 * @brief  舵机初始化：启动 TIM1_CH1 的 PWM 输出，回到中位
 * @note   初始化
 */
void Bsp_Servo_Init(void);

/**
 * @brief  设置舵机角度
 * @param angle 是目标角度
 */
void Bsp_Servo_Set_Angle(int angle);

#endif /* __BSP_SERVO_H */
