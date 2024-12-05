#include "pid_user.h"
#include "encoder.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "mpu6050.h"
#include "motor.h"
#include "sr04.h"

#define SPEED_Y 50//������ǰ������趨�ٶ�
#define SPEED_Z 200//ƫ�������ң�����趨�ٶ�


//���������ݱ���
int Encoder_Left,Encoder_Right;//���ҵ�����������ֵ
float pitch,roll,yaw;//�����ǣ�����ǣ�ƫ����
short gyrox,gyroy,gyroz;//���ٶ�
short	aacx,aacy,aacz;//���ٶ�
  
//�ջ������м����
int Vertical_out,Velocity_out,Turn_out,Target_Speed,Target_turn,MOTO1,MOTO2;
float Med_Angle=-4.5;//ƽ��ʱ�Ƕ�ֵƫ��������е��ֵ��
   
float Vertical_Kp=200,Vertical_Kd=2;  //
float Velocity_Kp=-0.5,Velocity_Ki=-0.0025;		// 
float Turn_Kp=10,Turn_Kd=0.4;											//ת�� 

extern uint8_t Fore,Back,Left,Right;
extern float distance;
/*****************  
ֱ����PD��������Kp*Ek+Kd*Ek_D
��ڣ�Med:��е��ֵ(�����Ƕ�)��Angle:��ʵ�Ƕȣ�gyro_Y:��ʵ���ٶ�
���ڣ�ֱ�������
******************/

int Vertical(float Med,float Angle,float gyro_Y) 
{
  int PWM_out;
  
  PWM_out = Vertical_Kp*(Angle-Med)+Vertical_Kd*(gyro_Y-0);
  
  return PWM_out;
} 

uint8_t stop;
/*****************  
�ٶȻ�PI��������Kp*Ek+Ki*Ek_S(Ek_S��ƫ��Ļ���)
******************/

int Velocity(int Target,int encoder_left,int encoder_right)
{
  // ����ɾ�̬�����������ھ�̬�洢����ʹ�ñ���������
  static int Encoder_S,EnC_Err_Lowout_last;
  static float a=0.7;
	int EnC_Err_Lowout,Encoder_Err,PWM_out;
	
  
  // 1.�����ٶ�ƫ��
  //��ȥ���--�ҵ���⣺�ܹ����ٶ�Ϊ"0"�ĽǶȣ����ǻ�е��ֵ��
  Encoder_Err = ((encoder_left+encoder_right)-Target);
  
  // 2.���ٶ�ƫ����е�ͨ�˲�
  EnC_Err_Lowout=(1-a)*Encoder_Err + a*EnC_Err_Lowout_last; // ʹ�ò��θ���ƽ�����˳���Ƶ���ţ������ٶ�ͻ��
  EnC_Err_Lowout_last=EnC_Err_Lowout;   // ��ֹ�ٶȹ���Ӱ��ֱ��������������
  
  // 3.���ٶ�ƫ����ֳ�λ��
  Encoder_S+=EnC_Err_Lowout;
  
  // 4.�����޷�
	Encoder_S=Encoder_S>20000?20000:(Encoder_S<(-20000)?(-20000):Encoder_S);
  
  // 5.�ٶȻ��������
  PWM_out = Velocity_Kp*EnC_Err_Lowout+Velocity_Ki*Encoder_S;
  if(stop==1)Encoder_S=0,stop=0;
  return PWM_out;
}

//ת��PD������
//���룺���ٶȡ��Ƕ�ֵ
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
	// 1.�ɼ�����������&MPU6050�Ƕ���Ϣ
  // �������԰�װ���պ����180�ȣ�Ϊ�˱������������һ�£�����Ҫ������һ��ȡ��
      Encoder_Left=-Read_Speed(&htim2); 
      Encoder_Right=Read_Speed(&htim4);
	   
      mpu_dmp_get_data(&pitch,&roll,&yaw);	    // ��ȡ�Ƕ�
      MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);  // ��ȡ���ٶ�
      MPU_Get_Accelerometer(&aacx,&aacy,&aacz); // ��ȡ���ٶ�
	
	/*ң��*/
	//ǰ��
	if((Fore==0)&&(Back==0))Target_Speed=0;
	if(Fore==1)Target_Speed-=5;
	if(Back==1)Target_Speed+=5;
	Target_Speed=Target_Speed>SPEED_Y?SPEED_Y:(Target_Speed<-SPEED_Y?(-SPEED_Y):Target_Speed);  // �޷�
	//����
	if((Left==0)&&(Right==0)) Target_turn=0;
	if(Left==1)Target_turn+=10;//��ת
	if(Right==1)Target_turn-=10;//��ת
	Target_turn=Target_turn>SPEED_Z?SPEED_Z:(Target_turn<-SPEED_Z?(-SPEED_Z):Target_turn);  // �޷�
	
	/*ת��Լ��*/
	if((Left==0)&&(Right==0))Turn_Kd=0.6;    // ��������ת��ָ�����ת��Լ��
  else if((Left==1)||(Right==1))Turn_Kd=0;  // ������ת��ָ����յ�����ȥ��ת��Լ��
	
	/*����*/
		
	
      // 2.������ѹ��ջ������У���������������
			Velocity_out=Velocity(Target_Speed,Encoder_Left,Encoder_Right); // �ٶȻ�
      Vertical_out=Vertical(Velocity_out+Med_Angle,roll,gyrox);			  // ֱ����
			Turn_out=Turn(gyroz,Target_turn);	
      PWM_out=Vertical_out;//�������

      // 3.�ѿ�����������ص�����ϣ�������տ���
      MOTO1 = PWM_out-Turn_out; // ����  ����ת��
      MOTO2 = PWM_out+Turn_out; // �ҵ��
      Limit(&MOTO1,&MOTO2);     // PWM�޷�
      Load(MOTO1,MOTO2);        // ���ص������ 
			//Load(1000,1000);
}
      