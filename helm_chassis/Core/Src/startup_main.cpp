#include "startup_main.h"
#include "bsp_delay.h"
#include "can_receive.h"
#include "pid_user.h"
#include "tim.h"
#include "bsp_can.h"
void startup_main(void)
{
	//滴答定时器初始化
  bsp_delay.f4.Init(168);
	
//PID初始化
	pid_controller.All_Device_Init();
	
//CAN通信滤波初始化
	can_bus.bsp.Filter_Init(&hcan1);
	can_bus.bsp.Filter_Init(&hcan2);
	
//CAN通信开启
	can_bus.bsp.CAN_Start(&hcan1);
	can_bus.bsp.CAN_Start(&hcan2);

//开启定时器中断
	HAL_TIM_Base_Start_IT(&htim7);
	
	dbus_uart_init();
	
#if isRTOS==0    	//如果是裸机开发
	for(;;)  //等同于while(true)
	{


	}
#endif
}