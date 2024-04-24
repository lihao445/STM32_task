#ifndef  _MOTOR_H
#define  _MOTOR_H

#include "main.h" 

extern TIM_HandleTypeDef htim1;

int abs(int p);
void Load(int moto1,int moto2);
void Limit(int *motoA,int *motoB);

#endif
