/**
 * @file    motor_ctrl.h
 * @brief   GM6020 转速闭环控制应用逻辑
 */
#ifndef __MOTOR_CTRL_H
#define __MOTOR_CTRL_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief  电机控制初始化：初始化速度环 PID，目标转速清零
 * @note   在 main() 的外设初始化之后调用一次
 */
void Motor_Ctrl_Init(void);

/**
 * @brief  设置目标转速（由串口指令解析结果调用）
 * @param[in] target_rpm 目标转速，范围 ±MOTOR_TARGET_RPM_LIMIT
 */
void Motor_Ctrl_Set_Target(int16_t target_rpm);

/**
 * @brief  速度环一步：读反馈 -> PID -> 发送 CAN 电压帧
 * @note   由 MotorTask 以 1ms 周期调用；无论目标是否为 0 都要发帧，
 *         否则目标清零后电机会保持最后一次电压
 */
void Motor_Ctrl_Update(void);

/**
 * @brief  查询电机是否在线
 * @retval true  反馈帧未超时
 * @retval false 超过 MOTOR_OFFLINE_MS 未收到反馈
 * @note   供 Led_Ctrl_Update / 打印任务使用
 */
bool Motor_Ctrl_Is_Online(void);

#endif /* __MOTOR_CTRL_H */
