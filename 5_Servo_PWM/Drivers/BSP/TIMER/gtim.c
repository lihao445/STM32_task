#include "./BSP/TIMER/gtim.h"

TIM_HandleTypeDef g_timx_pwm_chy_handle;

void gtim_timx_pwm_chy_init(uint16_t arr,uint16_t psc)//ͨ�ö�ʱ��PWM�����ʼ������
{
	g_timx_pwm_chy_handle.Instance=TIM3;
	g_timx_pwm_chy_handle.Init.Prescaler=psc;
	g_timx_pwm_chy_handle.Init.Period=arr;
	g_timx_pwm_chy_handle.Init.CounterMode=TIM_COUNTERMODE_UP;//����ģʽ
	
	HAL_TIM_PWM_Init(&g_timx_pwm_chy_handle);
	
	TIM_OC_InitTypeDef timx_oc_pwm_chy;
    timx_oc_pwm_chy.OCMode=TIM_OCMODE_PWM1;                     
    timx_oc_pwm_chy.Pulse= (0.5/20)*arr;   //ʹ�����0�ȵ�λ��                                     
    timx_oc_pwm_chy.OCPolarity=TIM_BREAKPOLARITY_HIGH;//�ߵ�ƽ
    HAL_TIM_PWM_ConfigChannel(&g_timx_pwm_chy_handle, &timx_oc_pwm_chy,TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&g_timx_pwm_chy_handle, TIM_CHANNEL_2);//ʹ��Ӧ��ʱ���Ķ�Ӧͨ����ʼ PWM ���
}

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)//��ʱ�����PWM MSP��ʼ������
{
	if(htim->Instance==TIM3)
	{
		GPIO_InitTypeDef gpio_init_struct = {0};
    
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_TIM3_CLK_ENABLE();
    
    gpio_init_struct.Pin=GPIO_PIN_6;
    gpio_init_struct.Mode=GPIO_MODE_AF_PP;    //    ���츴��                     
    gpio_init_struct.Pull=GPIO_PULLUP;
    gpio_init_struct.Speed=GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &gpio_init_struct);
		
		//__HAL_RCC_AFIO_CLK_ENABLE();
		//__HAL_AFIO_REMAP_TIM3_PARTIAL();
	}
}
























































