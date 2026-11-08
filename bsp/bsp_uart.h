/**
 * @file    bsp_uart.h
 * @brief   USART6 串口接收板级封装（DMA + 空闲中断）
 * @note    Bsp_Uart_Idle_Irq() 只允许在 USART6 中断上下文调用；
 *          其余接口在任务上下文调用。
 */
#ifndef __BSP_UART_H
#define __BSP_UART_H

#include <stdint.h>
#include <stdbool.h>

/** 串口命令帧缓冲区大小（字节） */
#define UART_CMD_BUF_SIZE 64U

/**
 * @brief  初始化串口接收：使能空闲中断 + 启动 DMA 接收
 * @note   在 main() 的外设初始化之后、调度器启动之前调用一次
 */
void Bsp_Uart_Init(void);

/**
 * @brief  USART6 空闲中断处理入口
 * @note   只允许在 USART6_IRQHandler 的 USER CODE 区调用；
 *         内部完成：判 IDLE 标志、取帧长、拷贝、重启 DMA
 */
void Bsp_Uart_Idle_Irq(void);

/**
 * @brief  取走一帧完整命令（取出后内部标志自动清除）
 * @param[out] buf 命令数据输出缓冲区，容量不小于 UART_CMD_BUF_SIZE
 * @param[out] len 实际数据长度（字节）
 * @retval true  取到一帧
 * @retval false 当前没有新命令
 */
bool Bsp_Uart_Get_Cmd(uint8_t *buf, uint16_t *len);

/* 共享帧缓冲：定义在 bsp_uart.c，ISR 写入、cmd_parser 读取 */
extern uint8_t           cmd_buf[UART_CMD_BUF_SIZE];
extern volatile uint16_t cmd_len;
extern volatile bool     cmd_ready;

#endif /* __BSP_UART_H */
