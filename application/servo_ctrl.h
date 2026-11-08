/**
 * @file    servo_ctrl.h
 * @brief   舵机按键控制应用逻辑（每按一次 KEY 旋转 +20°）
 */
#ifndef __SERVO_CTRL_H
#define __SERVO_CTRL_H

/** 单次按键角度步进（度） */
#define SERVO_STEP_DEG 20.0f

/**
 * @brief  舵机控制初始化：调用 Bsp_Servo_Init，角度回中位
 * @note   在 main() 的外设初始化之后调用一次
 */
void Servo_Ctrl_Init(void);

/**
 * @brief  舵机控制一步：检查按键事件，角度 +20°（180° 处回绕到 0°）
 * @note   由 ServoTask 循环调用；内部通过 Bsp_Key_Take_Press() 取事件
 */
void Servo_Ctrl_Update(void);

#endif /* __SERVO_CTRL_H */
