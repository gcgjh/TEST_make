#include "statemachine.h"
#include "main.h"
#include "myinclude.h"

static uint16_t custom_cnt = 0, last_cnt = 0, use_cnt = 0, use_cnt_last = 0;

uint8_t CDC_Send(uint8_t *buf, uint16_t len)
{   uint32_t tick_start = HAL_GetTick();
    const uint32_t timeout = 5; // Timeout
    while(CDC_Transmit_FS((uint8_t *)buf, len)==USBD_BUSY)
    {
        if (HAL_GetTick() - tick_start >= timeout)
        {
            return CDC_ERROR;
        }
        HAL_Delay(1);
    }
    return OK;
}

int statemachine(int (* func)(void)) {
    func();
    
    return 0;
}

int led_toggle(void)
{
    HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
    if (HAL_GPIO_ReadPin(LED1_GPIO_Port, LED1_Pin) == GPIO_PIN_RESET)
    {
        CDC_Send((uint8_t *)"Circular log : LED_ONN\r\n", sizeof("Circular log : LED_ONN\r\n") - 1);
    }
    else
    {
        CDC_Send((uint8_t *)"Circular log : LED_OFF\r\n", sizeof("Circular log : LED_OFF\r\n") - 1);
        CDC_Send((uint8_t *)"A cycle\r\n", sizeof("A cycle\r\n") - 1);
    }
    return OK;
}

int DI_KEY_check(void)
{
    if (DI_KEY_Flag == 1)
    {
        DI_KEY_Flag = 0;
        CDC_Send((uint8_t *)"DI_KEY Pressed\r\n", sizeof("DI_KEY Pressed\r\n") - 1); 
        __HAL_TIM_SET_COUNTER(&htim3, 30000);
        return OK;
    }
    return 0;
}



int digit_encoder_check(void)
{
    uint16_t currenr_cnt = __HAL_TIM_GET_COUNTER(&htim3);
    uint16_t diff = currenr_cnt - last_cnt;
    last_cnt = currenr_cnt;
    custom_cnt += diff;
    use_cnt = custom_cnt/12;
    if (use_cnt != use_cnt_last)
    {
        use_cnt_last = use_cnt;
        CDC_Send((uint8_t *)"Digit Encoder : ", sizeof("Digit Encoder : ") - 1);
        char buffer[10];
        int length = snprintf(buffer, sizeof(buffer), "%d\r\n", use_cnt);
        CDC_Send((uint8_t *)buffer, length);
    }
    return 0;
}