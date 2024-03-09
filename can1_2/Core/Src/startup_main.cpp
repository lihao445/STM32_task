#include "startup_main.h"
#include "bsp_can.h"


void startup_main(void)
{
	
#if isRTOS==0    	//如果是裸机开发
	for(;;)  //等同于while(true)
	{
can_filter_init();
can_start(&hcan1);
while (1)
  { 
	  can_cmd_send(1500,1500,1500,1500);
	}
	
	}
#endif
}