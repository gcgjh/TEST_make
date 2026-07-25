#ifndef __STATEMACHINE_H
#define __STATEMACHINE_H

#include "main.h"

#define OK 0
#define LED_ERROR 101
#define CDC_ERROR 102

uint8_t CDC_Send(uint8_t *buf, uint16_t len);
int led_toggle(void);
int statemachine(int (*func)(void));
int DI_KEY_check(void);

#endif /* __STATEMACHINE_H */