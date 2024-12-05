#include "sr04.h"
#include "pid.h"
uint16_t count;
float distance;
extern TIM_HandleTypeDef htim3;
extern int Target_turn;

//延迟函数，网上复制的，单位微秒
void RCCdelay_us(uint32_t udelay)
{
  __IO uint32_t Delay = udelay * 72 / 8;//(SystemCoreClock / 8U / 1000000U)
    //见stm32f1xx_hal_rcc.c -- static void RCC_Delay(uint32_t mdelay)
  do
  {
    __NOP();
  }
  while (Delay --);
}


//让超声波飞一会，10微秒
void GET_Distance(void)
{
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_SET);
	RCCdelay_us(10);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_RESET);
}


//中断回调函数
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin==GPIO_PIN_2)//如果ding'si'qi是pa2
	{
		if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_2)==GPIO_PIN_SET)//如果PA2是高电平，既上升沿中断
		{
			__HAL_TIM_SetCounter(&htim3,0);//定时器计数值清零
			HAL_TIM_Base_Start(&htim3);//开启计数
		}
		else
		{
			HAL_TIM_Base_Stop(&htim3);//停止计数
			count=__HAL_TIM_GetCounter(&htim3);//读取时间（定时器的计数值），并赋值
			//distance=count/1000000*340*100/2;
			distance=count*0.017;//单位厘米
		}
//		if((distance>=0)&&(distance<=30))
//	{
//		Target_turn-=30;
//	}
	}
	if(GPIO_Pin==GPIO_PIN_5)
		Control();
}






