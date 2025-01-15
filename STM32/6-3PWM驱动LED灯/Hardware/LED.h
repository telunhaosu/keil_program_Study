#ifndef __LED_H
#define __LED_H
#define LED_1 1
#define LED_2 2
#define LED_OFF 0
#define LED_ON 1

void LED_Init(void);
void LED_Set(uint8_t LED, uint8_t Mode);
void LED_Turn(uint8_t LED);

#endif
