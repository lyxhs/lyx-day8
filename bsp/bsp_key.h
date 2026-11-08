/**
 * @file    bsp_key.h
 * @brief   用户按键（PA0，EXTI0 下降沿）板级封装
 */
#ifndef __BSP_KEY_H
#define __BSP_KEY_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief  取走一次按键事件（取出后内部标志自动清除）
 * @note   中断里由本文件的 HAL_GPIO_EXTI_Callback 置位，任务里调这里取走
 * @retval true  发生过一次按键按下
 * @retval false 无事件
 */
bool Bsp_Key_Take_Press(void);

#endif /* __BSP_KEY_H */
