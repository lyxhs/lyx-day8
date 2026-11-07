#ifndef __BSP_CAN_H
#define __BSP_CAN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

/* CAN1 使用的接收 FIFO，收发两边要一致 */
#define BSP_CAN_RX_FIFO     CAN_RX_FIFO0

/**
 * @brief  初始化 CAN1：配置滤波器 -> 启动 CAN -> 打开接收中断
 * @note   必须在 MX_CAN1_Init() 之后调用
 */
void BSP_CAN_Init(void);

/**
 * @brief  发送一帧标准帧（11 位 ID）
 * @param  std_id  标准帧 ID，例如 0x1FF
 * @param  data    数据指针，最多 8 字节
 * @param  len     数据长度 0~8
 * @retval HAL_OK 表示成功放进发送邮箱
 */
HAL_StatusTypeDef BSP_CAN_SendStd(uint32_t std_id, const uint8_t *data, uint8_t len);

#ifdef __cplusplus
}
#endif

#endif /* __BSP_CAN_H */
