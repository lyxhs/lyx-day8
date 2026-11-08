/* servo_ctrl 实现待搬运：接口见 servo_ctrl.h */
#include "servo_ctrl.h"
#include "bsp_servo.h"
#include "bsp_key.h"
#include "cmsis_os.h"
#include "main.h"

#define SERVO_MAX_ANGLE 180

static int angle     = 0;
static int angle_turn = 1;
static bool press_pend = false;

void Servo_Ctrl_Init(void) {
    Bsp_Servo_Init();
}

void Servo_Ctrl_Update(void) {
    if (!press_pend) {
        press_pend = Bsp_Key_Take_Press();
        return;
    }

    osDelay(20);
    if (HAL_GPIO_ReadPin(KEY_GPIO_Port, KEY_Pin) == GPIO_PIN_SET) {
        press_pend = false;
        if (angle >= SERVO_MAX_ANGLE) {
            angle_turn = -1;
        }
        if (angle <= 0) {
            angle_turn = 1;
        }
        angle += (int)SERVO_STEP_DEG * angle_turn;
        Bsp_Servo_Set_Angle(angle);
    }
}
