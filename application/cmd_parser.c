#include "cmd_parser.h"
#include "motor.h"
#include "bsp_uart.h"
#include "motor_ctrl.h"
#include "stdio.h"
#include "main.h"

extern UART_HandleTypeDef huart6;

void Cmd_Parse_Motor() {
    if (cmd_ready) {
        cmd_ready = 0;
        for (uint16_t i = 0; i + 4 < cmd_len; i++) {
            int16_t turn=1;
            if (cmd_buf[i]=='m'&&cmd_buf[i+1]=='o'&&cmd_buf[i+2]=='t'&&cmd_buf[i+3]=='o'&&cmd_buf[i+4]=='r') {
                if (i+5<cmd_len && cmd_buf[i+5]=='-') {turn = -1;}
                int16_t get_num = 0;
                if (i+6<cmd_len) {
                    get_num += cmd_buf[i+6]-'0';
                }
                if (i+7<cmd_len) {
                    get_num*=10;
                    get_num += cmd_buf[i+7]-'0';
                }
                if (i+8<cmd_len) {
                    get_num*=10;
                    get_num += cmd_buf[i+8]-'0';
                }
                if (get_num!=0) Motor_Ctrl_Set_Target(get_num*turn);
            }
        }
    }
}

void Cmd_Print_Speed(void) {
    int16_t value = motor_gm6020[0].speed_rpm;
    char txbuf[16];
    int n = snprintf(txbuf, sizeof(txbuf), "%d\r\n", value);
    if (n > 0)
    {
        HAL_UART_Transmit(&huart6, (uint8_t *)txbuf, (uint16_t)n, 100);
    }
}