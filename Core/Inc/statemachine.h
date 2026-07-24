#ifndef __STATEMACHINE_H
#define __STATEMACHINE_H

#define OK 0
#define LED_ERROR 101

int led_toggle(void);
int statemachine(int (*func)(void));

#endif /* __STATEMACHINE_H */