#include "bsp_key.h"
#include "main.h"

static volatile bool pulldown = false;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == KEY_Pin)
    {
        pulldown = true;
    }
}

bool Bsp_Key_Take_Press(void)
{
    bool pressed;

    __disable_irq();
    pressed  = pulldown;
    pulldown = false;
    __enable_irq();

    return pressed;
}

