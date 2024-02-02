#include "./BSP/TIMER/btim.h"
#include "./BSP/LED/led.h"

TIM_HandleTypeDef g_timx_handle;

void bit_timx_int_init(uint16_t psc,uint16_t arr)								//��ʱ���жϳ�ʼ������
{
	g_timx_handle.Instance=TIM6;																	//����Ĵ�������ַ
	g_timx_handle.Init.Prescaler=psc;															//��ʱ����ʼ���ṹ��
	g_timx_handle.Init.Period=arr;															  //��ʱ����ʼ���ṹ��
	g_timx_handle.Init.CounterMode=TIM_COUNTERMODE_UP;
	HAL_TIM_Base_Init(&g_timx_handle);														//��ʼ����ʱ����������
	
	HAL_TIM_Base_Start_IT(&g_timx_handle);//ʹ�ܸ����жϲ�����������
	
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)//��ʱ��msp��ʼ��
{
	if(htim->Instance==TIM6)																			//�жϼĴ�������ַ�Ƿ���TIM6
	{
		__HAL_RCC_TIM6_CLK_ENABLE();//�򿪶�ʱ��6��ʱ��
		HAL_NVIC_SetPriority(TIM6_IRQn,1,1);//����NVIC
		HAL_NVIC_EnableIRQ(TIM6_IRQn);
		
	}
}

void TIM6_IRQHandler(void)//��ʱ��6�жϷ�����
{
	HAL_TIM_IRQHandler(&g_timx_handle);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{   if(htim->Instance == TIM6)
    {
        HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
    }
}














































