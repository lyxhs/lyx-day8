#include "bsp_uart.h"
#include <string.h>
#include "main.h"

extern UART_HandleTypeDef huart6;
extern DMA_HandleTypeDef  hdma_usart6_rx;

uint8_t rx_buf[UART_CMD_BUF_SIZE];
uint8_t cmd_buf[UART_CMD_BUF_SIZE];
volatile uint16_t cmd_len   = 0;
volatile bool     cmd_ready = false;


void Bsp_Uart_Init(void)
{
    __HAL_UART_ENABLE_IT(&huart6, UART_IT_IDLE);
    HAL_UART_Receive_DMA(&huart6, rx_buf, UART_CMD_BUF_SIZE);
}


void Bsp_Uart_Idle_Irq(void)
{
    if (__HAL_UART_GET_FLAG(&huart6, UART_FLAG_IDLE) == RESET)
    {
        return;
    }

    __HAL_UART_CLEAR_IDLEFLAG(&huart6);

    uint16_t len = UART_CMD_BUF_SIZE - __HAL_DMA_GET_COUNTER(&hdma_usart6_rx);
    if (len > 0)
    {
        memcpy(cmd_buf, rx_buf, len);
        cmd_len   = len;
        cmd_ready = true;
    }

    HAL_UART_AbortReceive(&huart6);
    HAL_UART_Receive_DMA(&huart6, rx_buf, UART_CMD_BUF_SIZE);
}

bool Bsp_Uart_Get_Cmd(uint8_t *buf, uint16_t *len)
{
    bool got = false;

    __disable_irq();
    if (cmd_ready)
    {
        memcpy(buf, cmd_buf, cmd_len);
        *len        = cmd_len;
        cmd_ready = false;
        got         = true;
    }
    __enable_irq();

    return got;
}
