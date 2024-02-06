/**
 ******************************************************************************
 * @file     main.c
 * @author   正点原子团队(ALIENTEK)
 * @version  V1.0
 * @date     2020-08-20
 * @brief    新建工程实验-HAL库版本 实验
 * @license  Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ******************************************************************************
 * @attention
 * 
 * 实验平台:正点原子 STM32F103 开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
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
    HAL_Init();                              /* 初始化HAL库 */
    SystemClock_Config();                    /* 设置时钟, 72Mhz */
    delay_init(72);                          /* 延时初始化 */
    gtim_timx_pwm_chy_init(199,7200-1);//周期为20ms
	
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

