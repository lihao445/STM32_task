#include "sr04.h"
#include "pid.h"
uint16_t count;
float distance;
extern TIM_HandleTypeDef htim3;
extern int Target_turn;

//�ӳٺ��������ϸ��Ƶģ���λ΢��
void RCCdelay_us(uint32_t udelay)
{
  __IO uint32_t Delay = udelay * 72 / 8;//(SystemCoreClock / 8U / 1000000U)
    //��stm32f1xx_hal_rcc.c -- static void RCC_Delay(uint32_t mdelay)
  do
  {
    __NOP();
  }
  while (Delay --);
}


//�ó�������һ�ᣬ10΢��
void GET_Distance(void)
{
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_SET);
	RCCdelay_us(10);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_RESET);
}


//�жϻص�����
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin==GPIO_PIN_2)//���ding'si'qi��pa2
	{
		if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_2)==GPIO_PIN_SET)//���PA2�Ǹߵ�ƽ�����������ж�
		{
			__HAL_TIM_SetCounter(&htim3,0);//��ʱ������ֵ����
			HAL_TIM_Base_Start(&htim3);//��������
		}
		else
		{
			HAL_TIM_Base_Stop(&htim3);//ֹͣ����
			count=__HAL_TIM_GetCounter(&htim3);//��ȡʱ�䣨��ʱ���ļ���ֵ��������ֵ
			//distance=count/1000000*340*100/2;
			distance=count*0.017;//��λ����
		}
//		if((distance>=0)&&(distance<=30))
//	{
//		Target_turn-=30;
//	}
	}
	if(GPIO_Pin==GPIO_PIN_5)
		Control();
}






