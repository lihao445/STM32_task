#include "pid_user.h"
#include "encoder.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "mpu6050.h"
#include "motor.h"
#include "sr04.h"

#define SPEED_Y 50//俯仰（前后）最大设定速度
#define SPEED_Z 200//偏航（左右）最大设定速度


//传感器数据变量
int Encoder_Left,Encoder_Right;//左右电机编码器输出值
float pitch,roll,yaw;//俯仰角，横滚角，偏航角
short gyrox,gyroy,gyroz;//角速度
short	aacx,aacy,aacz;//加速度
  
//闭环控制中间变量
int Vertical_out,Velocity_out,Turn_out,Target_Speed,Target_turn,MOTO1,MOTO2;
float Med_Angle=-4.5;//平衡时角度值偏移量（机械中值）
   
float Vertical_Kp=200,Vertical_Kd=2;  //
float Velocity_Kp=-0.5,Velocity_Ki=-0.0025;		// 
float Turn_Kp=10,Turn_Kd=0.4;											//转向环 

extern uint8_t Fore,Back,Left,Right;
extern float distance;
/*****************  
直立环PD控制器：Kp*Ek+Kd*Ek_D
入口：Med:机械中值(期望角度)，Angle:真实角度，gyro_Y:真实角速度
出口：直立环输出
******************/

int Vertical(float Med,float Angle,float gyro_Y) 
{
  int PWM_out;
  
  PWM_out = Vertical_Kp*(Angle-Med)+Vertical_Kd*(gyro_Y-0);
  
  return PWM_out;
} 

uint8_t stop;
/*****************  
速度环PI控制器：Kp*Ek+Ki*Ek_S(Ek_S：偏差的积分)
******************/

int Velocity(int Target,int encoder_left,int encoder_right)
{
  // 定义成静态变量，保存在静态存储器，使得变量不丢掉
  static int Encoder_S,EnC_Err_Lowout_last;
  static float a=0.7;
	int EnC_Err_Lowout,Encoder_Err,PWM_out;
	
  
  // 1.计算速度偏差
  //舍去误差--我的理解：能够让速度为"0"的角度，就是机械中值。
  Encoder_Err = ((encoder_left+encoder_right)-Target);
  
  // 2.对速度偏差进行低通滤波
  EnC_Err_Lowout=(1-a)*Encoder_Err + a*EnC_Err_Lowout_last; // 使得波形更加平滑，滤除高频干扰，放置速度突变
  EnC_Err_Lowout_last=EnC_Err_Lowout;   // 防止速度过大影响直立环的正常工作
  
  // 3.对速度偏差积分出位移
  Encoder_S+=EnC_Err_Lowout;
  
  // 4.积分限幅
	Encoder_S=Encoder_S>20000?20000:(Encoder_S<(-20000)?(-20000):Encoder_S);
  
  // 5.速度环控制输出
  PWM_out = Velocity_Kp*EnC_Err_Lowout+Velocity_Ki*Encoder_S;
  if(stop==1)Encoder_S=0,stop=0;
  return PWM_out;
}

//转向环PD控制器
//输入：角速度、角度值
int Turn(float gyro_Z,int Target_turn)
{
	int temp;
	temp=Turn_Kp*Target_turn+Turn_Kd*gyro_Z;
	return temp;
}

extern TIM_HandleTypeDef htim2,htim4;



void Control(void)
{
	
	int PWM_out;
	// 1.采集编码器数据&MPU6050角度信息
  // 电机是相对安装，刚好相差180度，为了编码器输出极性一致，就需要对其中一个取反
      Encoder_Left=-Read_Speed(&htim2); 
      Encoder_Right=Read_Speed(&htim4);
	   
      mpu_dmp_get_data(&pitch,&roll,&yaw);	    // 读取角度
      MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);  // 读取角速度
      MPU_Get_Accelerometer(&aacx,&aacy,&aacz); // 读取加速度
	
	/*遥控*/
	//前后
	if((Fore==0)&&(Back==0))Target_Speed=0;
	if(Fore==1)Target_Speed-=5;
	if(Back==1)Target_Speed+=5;
	Target_Speed=Target_Speed>SPEED_Y?SPEED_Y:(Target_Speed<-SPEED_Y?(-SPEED_Y):Target_Speed);  // 限幅
	//左右
	if((Left==0)&&(Right==0)) Target_turn=0;
	if(Left==1)Target_turn+=10;//左转
	if(Right==1)Target_turn-=10;//右转
	Target_turn=Target_turn>SPEED_Z?SPEED_Z:(Target_turn<-SPEED_Z?(-SPEED_Z):Target_turn);  // 限幅
	
	/*转向约束*/
	if((Left==0)&&(Right==0))Turn_Kd=0.6;    // 若无左右转向指令，则开启转向约束
  else if((Left==1)||(Right==1))Turn_Kd=0;  // 若左右转向指令接收到，则去掉转向约束
	
	/*避障*/
		
	
      // 2.将数据压入闭环控制中，计算出控制输出量
			Velocity_out=Velocity(Target_Speed,Encoder_Left,Encoder_Right); // 速度环
      Vertical_out=Vertical(Velocity_out+Med_Angle,roll,gyrox);			  // 直立环
			Turn_out=Turn(gyroz,Target_turn);	
      PWM_out=Vertical_out;//最终输出

      // 3.把控制输出量加载到电机上，完成最终控制
      MOTO1 = PWM_out-Turn_out; // 左电机  可以转向
      MOTO2 = PWM_out+Turn_out; // 右电机
      Limit(&MOTO1,&MOTO2);     // PWM限幅
      Load(MOTO1,MOTO2);        // 加载到电机上 
			//Load(1000,1000);
}
      