#include "startup_main.h"
#include "bsp_can.h"


void startup_main(void)
{
	
#if isRTOS==0    	//������������
	for(;;)  //��ͬ��while(true)
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