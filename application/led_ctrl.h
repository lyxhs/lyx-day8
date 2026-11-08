/**
 * @file    led_ctrl.h
 * @brief   LED 状态指示应用逻辑（绿灯常亮 / 红灯 2s 呼吸）
 */
#ifndef __LED_CTRL_H
#define __LED_CTRL_H

#include <stdbool.h>

/** LED 工作状态 */

/**
 * @brief  LED 控制初始化：熄灭三色灯，进入正常状态
 * @note   在 main() 的外设初始化之后调用一次
 */
void Led_Ctrl_Init(void);

/**
 * @brief  LED 状态机一步：按状态刷新绿灯与红灯呼吸亮度
 * @param[in] motor_online 电机在线标志（来自 Motor_Ctrl_Is_Online()）
 * @note   由 LedTask 以 1ms 周期调用；红灯呼吸用 TIM5_CH3 硬件 PWM，
 *         每 20ms 更新一次比较值，2s 一个周期
 */
void Led_Ctrl_Update();

#endif /* __LED_CTRL_H */
