#include "statemachine.h"
#include "main.h"
#include "myinclude.h"

int state = 0;

int statemachine(int (* func)(void)) {
    func();
    
    return 0;
}

int led_toggle(void)
{
    HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
    if (HAL_GPIO_ReadPin(LED1_GPIO_Port, LED1_Pin) == GPIO_PIN_RESET)
    {
        CDC_Transmit_FS((uint8_t *)"Circular log : LED_ONN\r\n", sizeof("Circular log : LED_ONN\r\n") - 1);
    }
    else
    {
        CDC_Transmit_FS((uint8_t *)"Circular log : LED_OFF\r\n", sizeof("Circular log : LED_OFF\r\n") - 1);
        HAL_Delay(1);/* 连续调用两次该函数第二个函数会直接丢包 */
        CDC_Transmit_FS((uint8_t *)"A cycle\r\n", sizeof("A cycle\r\n") - 1);
    }
    return OK;
}