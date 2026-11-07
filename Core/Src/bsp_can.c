#include "bsp_can.h"
extern CAN_HandleTypeDef hcan1;

static void BSP_CAN_FilterInit(void)
{
    CAN_FilterTypeDef filter = {0};

    filter.FilterBank           = 0;
    filter.FilterMode           = CAN_FILTERMODE_IDMASK;
    filter.FilterScale          = CAN_FILTERSCALE_32BIT;
    filter.FilterIdHigh         = 0x0000;
    filter.FilterIdLow          = 0x0000;
    filter.FilterMaskIdHigh     = 0x0000;
    filter.FilterMaskIdLow      = 0x0000;
    filter.FilterFIFOAssignment = BSP_CAN_RX_FIFO;
    filter.FilterActivation     = ENABLE;
    filter.SlaveStartFilterBank = 14;

    if (HAL_CAN_ConfigFilter(&hcan1, &filter) != HAL_OK)
    {
        Error_Handler();
    }
}

void BSP_CAN_Init(void)
{
    BSP_CAN_FilterInit();

    if (HAL_CAN_Start(&hcan1) != HAL_OK)
    {
        Error_Handler();
    }

    if (HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)
    {
        Error_Handler();
    }
}

HAL_StatusTypeDef BSP_CAN_SendStd(uint32_t std_id, const uint8_t *data, uint8_t len)
{
    CAN_TxHeaderTypeDef tx_header = {0};
    uint32_t tx_mailbox;
    uint8_t  payload[8] = {0};

    if (len > 8U)
    {
        len = 8U;
    }
    for (uint8_t i = 0; i < len; i++)
    {
        payload[i] = data[i];
    }

    tx_header.StdId              = std_id;
    tx_header.IDE                = CAN_ID_STD;
    tx_header.RTR                = CAN_RTR_DATA;
    tx_header.DLC                = len;
    tx_header.TransmitGlobalTime = DISABLE;

    return HAL_CAN_AddTxMessage(&hcan1, &tx_header, payload, &tx_mailbox);
}
