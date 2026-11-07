#include "motor.h"
#include "bsp_can.h"

volatile motor_measure_t motor_gm6020[GM6020_MOTOR_NUM];

void Motor_Init(void)
{
}

void Motor_SendVoltage(const int16_t voltage[GM6020_MOTOR_NUM])
{
    uint8_t data[8];

    for (uint8_t i = 0; i < GM6020_MOTOR_NUM; i++)
    {
        int16_t v = voltage[i];

        if (v > GM6020_VOLTAGE_MAX)
        {
            v = GM6020_VOLTAGE_MAX;
        }
        if (v < -GM6020_VOLTAGE_MAX)
        {
            v = -GM6020_VOLTAGE_MAX;
        }

        data[2U * i]      = (uint8_t)(v >> 8);
        data[2U * i + 1U] = (uint8_t)(v & 0xFF);
    }

    BSP_CAN_SendStd(GM6020_CTRL_ID, data, 8);
}

/**
 * @brief  按 ID 找到对应电机，把 8 字节反馈解出来
 * @note   反馈格式（GM6020 手册）：
 *         data[0..1] 机械角度 ecd  0~8191
 *         data[2..3] 转速 rpm      int16
 *         data[4..5] 转矩电流      int16
 *         data[6]    温度
 *         data[7]    保留
 */
void Motor_CanRxHandler(uint32_t std_id, const uint8_t *data)
{
    uint32_t index = std_id - GM6020_FB_ID_FIRST;

    if (index >= GM6020_MOTOR_NUM)
    {
        return;
    }

    volatile motor_measure_t *m = &motor_gm6020[index];

    m->last_ecd        = m->ecd;
    m->ecd             = (uint16_t)((data[0] << 8) | data[1]);
    m->speed_rpm       = (int16_t)((data[2] << 8) | data[3]);
    m->current         = (int16_t)((data[4] << 8) | data[5]);
    m->temperature     = data[6];
    m->last_update_tick = HAL_GetTick();
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    CAN_RxHeaderTypeDef rx_header;
    uint8_t rx_data[8];

    if (hcan->Instance != CAN1)
    {
        return;
    }

    if (HAL_CAN_GetRxMessage(hcan, BSP_CAN_RX_FIFO, &rx_header, rx_data) != HAL_OK)
    {
        return;
    }

    if ((rx_header.IDE == CAN_ID_STD) && (rx_header.RTR == CAN_RTR_DATA))
    {
        Motor_CanRxHandler(rx_header.StdId, rx_data);
    }
}
