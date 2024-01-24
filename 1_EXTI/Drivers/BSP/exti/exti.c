#include "./BSP/exti/exti.h"
#include "./SYSTEM/delay/delay.h"

void exti_init()    //��ʼ���ⲿ�ж�
{
	GPIO_InitTypeDef gpio_init_exti;//���ñ�����
	__HAL_RCC_GPIOB_CLK_ENABLE();//ʹ��GPIOʱ��
	
	gpio_init_exti.Pin= GPIO_PIN_9;  //����PB9
	gpio_init_exti.Mode= GPIO_MODE_IT_FALLING;//�����½��ش���
  gpio_init_exti.Pull= GPIO_PULLUP;//��������
	
	HAL_GPIO_Init(GPIOB,&gpio_init_exti);//һ����λ��
	
	HAL_NVIC_SetPriority(EXTI9_5_IRQn,2,0);//�����ж����ȼ�
	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);//ʹ���ж�
}

void EXTI9_5_IRQHandler(void)//�����жϷ�����
{                            //�жϻص���������
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_9);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)//Ҫ������������������¶���
{
	delay_ms(20);//����
	
	if(GPIO_Pin==GPIO_PIN_9)//������������
	{
		if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==0)//???
			{
					HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
			}
			else
			{
			    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
			}
	}
}