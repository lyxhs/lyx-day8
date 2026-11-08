/**
 * @file    pid.h
 * @brief   通用 PID 控制器组件（位置式，带输出限幅）
 * @note    纯算法组件，不依赖任何硬件；每个控制对象实例化一个 pid_t
 */
#ifndef __PID_H
#define __PID_H

/** PID 输出限幅缺省值（对应 GM6020 电压指令范围） */
#define PID_OUT_LIMIT 15000.0f

/** 控制周期（秒），与 MotorTask 的 1kHz 对应 */
#define PID_DT_S 0.001f

/**
 * @brief PID 控制器实例
 * @note  err[0]/err[1] 保存 e(k)、e(k-1)；d_err 用于增量式差分
 */
typedef struct
{
    float kp;
    float ki;
    float kd;
    int target;
    float max_out;
    float err;
    float d_err;
    float out;
    float d_out;
} pid_t;

/** 当前系统里唯一的 PID 实例（定义在 pid.c，供 motor_ctrl 读写 target） */
extern pid_t pidnum;

void PID_Init(void);

/**
 * @brief  PID 计算（在固定控制周期内调用，如 1kHz）
 * @param[in,out] pid 控制器实例
 * @param[in]  ref 反馈值（如当前转速 rpm）
 * @param[in]  set 期望值（如目标转速 rpm）
 * @retval 本次控制输出，范围 [-max_out, +max_out]
 */
float PID_Calc();

/**
 * @brief  复位控制器内部状态（切换目标/重新启动时调用，防止旧误差跳变）
 * @param[out] pid 控制器实例
 */
void PID_Reset(int target);

#endif /* __PID_H */
