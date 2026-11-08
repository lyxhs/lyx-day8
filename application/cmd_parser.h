/**
 * @file    cmd_parser.h
 * @brief   串口电机指令解析（协议：motor±目标转速，如 motor+100）
 */
#ifndef __CMD_PARSER_H
#define __CMD_PARSER_H

#include <stdint.h>
#include <stdbool.h>

/** 目标转速限幅（GM6020 调速范围 ±320rpm） */
#define MOTOR_TARGET_RPM_LIMIT 320

/**
 * @brief  解析一帧串口数据中的电机转速指令
 * @param[in]  buf        命令帧数据
 * @param[in]  len        数据长度（字节）
 * @param[out] target_rpm 解析成功时输出目标转速（rpm，有符号）
 * @retval true  本帧包含有效 motor 指令，target_rpm 已更新
 * @retval false 本帧不是有效指令
 * @note   仅在任务上下文调用；输入不需要以 '\0' 结尾
 */
void Cmd_Parse_Motor(void);

void Cmd_Print_Speed(void);

#endif /* __CMD_PARSER_H */
