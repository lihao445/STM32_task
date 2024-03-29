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

void led_init(void);                       /* LED初始化函数声明 */

int main(void)
{
    HAL_Init();                              /* 初始化HAL库 */
    SystemClock_Config();                    /* 设置时钟, 72Mhz */
    delay_init(72);                          /* 延时初始化 */
    usart_init(9600);                     /* 波特率设为9600 */
		led_init();

  while (1)
  {
		if(g_usart_rx_sta== 1)
		{
		switch( g_rx_buffer[0] )
      {
        case '1':
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);         
        break;

        case '0':
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);         
        break;

        default:
        break;
			}
		}
	}
}




