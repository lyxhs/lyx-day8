#ifndef __MOTOR_H
#define __MOTOR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

/* ---------------- GM6020 协议常量 ---------------- */
#define GM6020_CTRL_ID          0x1FFU   /* 控制 ID1~ID4 的电压命令帧 */
#define GM6020_FB_ID_FIRST      0x205U   /* ID1 的反馈帧 ID，ID2~ID4 依次 0x206~0x208 */
#define GM6020_MOTOR_NUM        4U
#define GM6020_VOLTAGE_MAX      30000    /* 电压指令范围 -30000 ~ +30000 */

/* ---------------- 电机反馈数据 ---------------- */
typedef struct
{
    uint16_t ecd;              /* 机械角度 0~8191，对应 0~360° */
    int16_t  speed_rpm;        /* 转子转速，单位 rpm，有正负 */
    int16_t  current;          /* 实际转矩电流 */
    uint8_t  temperature;      /* 温度，单位 ℃ */
    uint16_t last_ecd;         /* 上一帧角度，用来算角度差 */
    uint32_t last_update_tick; /* 最近一次收到反馈时的 HAL_GetTick() */
} motor_measure_t;

/* 全局数组：CubeMonitor 观测、离线检测都直接读它。
   加 volatile 是防止编译器把它优化到看不见的地方（调试器读不到）。 */
extern volatile motor_measure_t motor_gm6020[GM6020_MOTOR_NUM];

void Motor_Init(void);

/**
 * @brief  发送 GM6020 电压控制帧（ID 0x1FF）
 * @param  voltage 长度 4 的数组，依次对应 ID1~ID4，范围 -30000~30000
 */
void Motor_SendVoltage(const int16_t voltage[GM6020_MOTOR_NUM]);

/**
 * @brief  CAN 接收中断里调用，按 ID 把 8 字节反馈解析进 motor_gm6020[]
 * @note   解析时会顺便更新 last_update_tick，供上层做离线判断
 */
void Motor_CanRxHandler(uint32_t std_id, const uint8_t *data);

#ifdef __cplusplus
}
#endif

#endif /* __MOTOR_H */
