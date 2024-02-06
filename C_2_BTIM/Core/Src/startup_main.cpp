#include "startup_main.h"
#include "bsp_delay.h"
#include "tim.h"

void startup_main(void)
{

	
#if isRTOS==0    	//如果是裸机开发
	for(;;)  //等同于while(true)
	{
		bsp_delay.f1.ms(500);
		HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
	}
#endif
}