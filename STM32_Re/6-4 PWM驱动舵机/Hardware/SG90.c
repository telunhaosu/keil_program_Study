#include "stm32f10x.h"
#include "PWM.h"

void SG90_Init(void)
{
    PWM_Init();
}

void SG90_SetAngle(float Angle)
{
    PWM_SetCompre2(Angle / 180 * 2000 + 500);
}
