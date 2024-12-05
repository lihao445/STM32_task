#include "timer_user.h"

#define THETA (double)(8191.00/(2*PI))

extern "C"
/*
 * @brief       回调函数，定时器中断服务函数调用
 * @param       htim：触发中断的定时器句柄
 * @retval      void
 * @note        该函数由中断公共服务函数调用，不用用户去调用。且为一个弱函数，所以在C++中要在该函数前面加上extern "C"，或直接用extern "C"{}括起来
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM7)  //周期为1ms
	{
		robot_chassis();
	}
}


void robot_chassis()
{
	Formula(rc.ch0,rc.ch1,rc.ch2);
	double theta6020[3]={THETA*Wheel3.theta[0],THETA*Wheel3.theta[1],THETA*Wheel3.theta[2]};
	can_bus.cmd.CAN1_6020( 
		pid_controller.can_motor.CAN1_VP_Dual_Loop_Realize_6020(theta6020[2],0),
		pid_controller.can_motor.CAN1_VP_Dual_Loop_Realize_6020(theta6020[0],1),
		pid_controller.can_motor.CAN1_VP_Dual_Loop_Realize_6020(theta6020[1],2),
		0); 
	can_bus.cmd.CAN1_3508(
		pid_controller.can_motor.CAN1_Velocity_Realize_3508(Wheel3.V[0]*3,0),
		pid_controller.can_motor.CAN1_Velocity_Realize_3508(Wheel3.V[1]*3,1),
		pid_controller.can_motor.CAN1_Velocity_Realize_3508(Wheel3.V[2]*3,2),
		0);
}
