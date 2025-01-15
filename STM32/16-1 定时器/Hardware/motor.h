#ifndef __MOTOR_H
#define __MOTOR_H

typedef enum{
	L_Wheel= 0,
	R_Wheel
}wheel;

void motor_Init(void);
void motor_SetPWM(wheel LR, uint16_t Compare);

#endif
