#include "startup_main.h"
#include "bsp_delay.h"
#include "can_receive.h"
#include "pid_user.h"
#include "tim.h"
#include "bsp_can.h"
void startup_main(void)
{
	//�δ�ʱ����ʼ��
  bsp_delay.f4.Init(168);
	
//PID��ʼ��
	pid_controller.All_Device_Init();
	
//CANͨ���˲���ʼ��
	can_bus.bsp.Filter_Init(&hcan1);
	can_bus.bsp.Filter_Init(&hcan2);
	
//CANͨ�ſ���
	can_bus.bsp.CAN_Start(&hcan1);
	can_bus.bsp.CAN_Start(&hcan2);

//������ʱ���ж�
	HAL_TIM_Base_Start_IT(&htim7);
	
	dbus_uart_init();
	
#if isRTOS==0    	//������������
	for(;;)  //��ͬ��while(true)
	{


	}
#endif
}