#include "encoder.h"

int Read_Speed(TIM_HandleTypeDef *htim)
{
	int temp,encoder_old;
	temp=(short)__HAL_TIM_GetCounter(htim);//��ȡ�������ļ���ֵ(ÿ10ms��
//	
////	int encoder_now=temp;
////	int var=encoder_now-encoder_old;
////	encoder_old=encoder_now;
//	int vacr=temp*1000*60/4/11/30;
	
	__HAL_TIM_SetCounter(htim,0);//�������ļ���ֵ����
	return temp;//���ر������ļ���ֵ
}
