#include "startup_main.h"
#include "usart.h"
#include "bsp_delay.h"


extern uint8_t g_rx_buffer[1]; 
void startup_main(void)
{

	
#if isRTOS==0    	//如果是裸机开发
	for(;;)  //等同于while(true)
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
#endif
}