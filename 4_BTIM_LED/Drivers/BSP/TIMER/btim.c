#include "./BSP/TIMER/btim.h"
#include "./BSP/LED/led.h"

TIM_HandleTypeDef g_timx_handle;

void bit_timx_int_init(uint16_t psc,uint16_t arr)								//定时器中断初始化函数
{
	g_timx_handle.Instance=TIM6;																	//外设寄存器基地址
	g_timx_handle.Init.Prescaler=psc;															//定时器初始化结构体
	g_timx_handle.Init.Period=arr;															  //定时器初始化结构体
	g_timx_handle.Init.CounterMode=TIM_COUNTERMODE_UP;
	HAL_TIM_Base_Init(&g_timx_handle);														//初始化定时器基础参数
	
	HAL_TIM_Base_Start_IT(&g_timx_handle);//使能更新中断并启动计数器
	
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)//定时器msp初始化
{
	if(htim->Instance==TIM6)																			//判断寄存器基地址是否是TIM6
	{
		__HAL_RCC_TIM6_CLK_ENABLE();//打开定时器6的时钟
		HAL_NVIC_SetPriority(TIM6_IRQn,1,1);//配置NVIC
		HAL_NVIC_EnableIRQ(TIM6_IRQn);
		
	}
}

void TIM6_IRQHandler(void)//定时器6中断服务函数
{
	HAL_TIM_IRQHandler(&g_timx_handle);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{   if(htim->Instance == TIM6)
    {
        HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
    }
}














































