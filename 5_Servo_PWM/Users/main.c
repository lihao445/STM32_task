/**
 ******************************************************************************
 * @file     main.c
 * @author   ����ԭ���Ŷ�(ALIENTEK)
 * @version  V1.0
 * @date     2020-08-20
 * @brief    �½�����ʵ��-HAL��汾 ʵ��
 * @license  Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ******************************************************************************
 * @attention
 * 
 * ʵ��ƽ̨:����ԭ�� STM32F103 ������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 ******************************************************************************
 */

#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/TIMER/gtim.h"

extern TIM_HandleTypeDef g_timx_pwm_chy_handle;

int main(void)
{
	  uint16_t ledrpwmval = 10;
		uint8_t dir=1;
    HAL_Init();                              /* ��ʼ��HAL�� */
    SystemClock_Config();                    /* ����ʱ��, 72Mhz */
    delay_init(72);                          /* ��ʱ��ʼ�� */
    gtim_timx_pwm_chy_init(199,7200-1);//����Ϊ20ms
	
    while(1)
    { 
			delay_ms(1000);
			if(ledrpwmval==10)
			{
				ledrpwmval=15;
				__HAL_TIM_SetCompare(&g_timx_pwm_chy_handle,TIM_CHANNEL_2,ledrpwmval);
			}
			else
			{
				ledrpwmval=10;
				__HAL_TIM_SetCompare(&g_timx_pwm_chy_handle,TIM_CHANNEL_2,ledrpwmval);
			}
    }
}

