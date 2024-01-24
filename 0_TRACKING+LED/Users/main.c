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
#include "./BSP/xunji/xunji.h"

void led_init(void);                       /* LED��ʼ���������� */

int main(void)
{
    HAL_Init();                              /* ��ʼ��HAL�� */
    sys_stm32_clock_init(RCC_PLL_MUL9);      /* ����ʱ��, 72Mhz */
    delay_init(72);                          /* ��ʱ��ʼ�� */
    led_init();												  /* LED��ʼ�� */
    xunji_init();
	
    while(1)
    { 
			if(xunji_scan())
				{
						HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_SET);
				}
				else
				{	
						HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_RESET);
				} 
    }
}

