#include "./BSP/xunji/xunji.h"
#include "./SYSTEM/delay/delay.h"

void xunji_init(void)
{
		GPIO_InitTypeDef gpio_init_struct={0};
		
		gpio_init_struct.Pin = GPIO_PIN_13;
		gpio_init_struct.Mode = GPIO_MODE_INPUT;
		gpio_init_struct.Pull = GPIO_PULLUP;
		
		__HAL_RCC_GPIOB_CLK_ENABLE();
		
		HAL_GPIO_Init(GPIOB,&gpio_init_struct);
}

uint8_t xunji_scan(void)
{
	if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_13)==0)
	{
		delay_ms(10);//Ïû¶¶ 	
		if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_13)==0)
		{	
			while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_13)==0)
				return 1;
		}
	}
	return 0;
}