#include "startup_main.h"
#include "bsp_delay.h"
#include "tim.h"

void startup_main(void)
{

	
#if isRTOS==0    	//������������
	for(;;)  //��ͬ��while(true)
	{
		bsp_delay.f1.ms(500);
	}
#endif
}