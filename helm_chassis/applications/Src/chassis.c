#include "chassis.h"
#include <math.h>



LUN   Wheel3;
POSE  RobotPos;

/*
*********************************************************************************************************
* Brief    : World frame to robot frame transform formula.
*
* Param(s) : world - velocity vector(Vx,Vy,Vz) in inertia frame. (mm/s, rad/s)
*      robo  - velocity vector(Vx,Vy,Vz) in robot frame. (mm/s, rad/s)
*
* Return(s): none.
*
*********************************************************************************************************
*/

void Formula_World2Robo (Velocity *world, Velocity *robo)//转角相反
{
  
   // 计算机器人当前位姿的正弦和余弦值
  float sinTheta = sin(RobotPos.theta);
  float cosTheta = cos(RobotPos.theta);

    // 将世界坐标系下的速度向量转换到机器人坐标系下
  robo->Vx = world->Vx * cosTheta + world->Vy * sinTheta;
  robo->Vy = world->Vy * cosTheta - world->Vx * sinTheta;
  // 机器人坐标系下的角速度与世界坐标系下的角速度相同
  robo->Vz = world->Vz;

}
  
/*
*********************************************************************************************************
* Brief    : robot frame to wheel frame transform formula.
*
* Param(s) : wheel - velocity vector(Vx,Vy,Vz) in wheel frame. (0.1 enc counts/s)
*      robo  - velocity vector(Vx,Vy,Vz) in robot frame. (mm/s, rad/s)
*
* Return(s): none.
*·
*********************************************************************************************************
*/

//float theta_angle[3];//转向以角度形式展示
void Formula (float Vx,float Vy,float Vz)
{
  int flag;
  float V;
  float Vx_part[3]={0,0,0},Vy_part[3]={0,0,0},theta_temp[3]={0,0,0};
  Wheel3.L = 273;//车轮到三角中心的距离
 
  //输入Vx_in,Vy_in
  //输入Wheel3.omega
    Wheel3.Vx = Vx;
    Wheel3.Vy = Vy;
    Wheel3.omega = Vz * PI/180 * Wheel3.L;
  V = sqrt(Wheel3.Vx * Wheel3.Vx + Wheel3.Vy * Wheel3.Vy);
  if (V==0&Vz==0)//驻停
  {
    Wheel3.theta[0] = 0;
    Wheel3.theta[1] = Wheel3.theta[0];
    Wheel3.theta[2] = Wheel3.theta[0];
    
    Wheel3.V[0] = 0;
    Wheel3.V[1] = Wheel3.V[0];
    Wheel3.V[2] = Wheel3.V[0];
  }

  else if (V || Wheel3.omega)
  {
      if (Wheel3.Vx >= 0)
        flag = 1;
      else 
        flag = -1;
 
        //反三角计算角度
      if (Wheel3.Vy != 0)
        {
          theta_temp[0] = flag*acos(Wheel3.Vy / V);
          theta_temp[1] = theta_temp[0];
          theta_temp[2] = theta_temp[0];
        }
      else
        {
          if (flag==1)
          {
            theta_temp[0] = PI/2;
            theta_temp[1] = theta_temp[0];
            theta_temp[2] = theta_temp[0];
          }
          else
          {
            theta_temp[0] = -PI/2;
            theta_temp[1] = theta_temp[0];
            theta_temp[2] = theta_temp[0];
          }
        }//反三角计算角度
        
        //平移旋转速度正交分解叠加
        Vx_part[0] = V * sin(theta_temp[0]);
        Vx_part[1] = V * sin(theta_temp[1]);
        Vx_part[2] = V * sin(theta_temp[2]);
        Vy_part[0] = V * cos(theta_temp[0]);
        Vy_part[1] = V * cos(theta_temp[1]);
        Vy_part[2] = V * cos(theta_temp[2]);
        Vx_part[0] += Wheel3.omega;
        Vx_part[1] -= Wheel3.omega / 2;
        Vy_part[1] += Wheel3.omega * sqrt(3)/2;
        Vx_part[2] -= Wheel3.omega /2;
        Vy_part[2] -= Wheel3.omega * sqrt(3)/ 2;
        Wheel3.V[0] = sqrt(Vx_part[0]*Vx_part[0] + Vy_part[0]*Vy_part[0]);
        Wheel3.V[1] = sqrt(Vx_part[1]*Vx_part[1] + Vy_part[1]*Vy_part[1]);
        Wheel3.V[2] = sqrt(Vx_part[2]*Vx_part[2] + Vy_part[2]*Vy_part[2]);
        
        //叠加后重新计算角度
        for (int i=0;i<3;i++)
        {
          if (Vy_part[i] != 0)
          {
            if (Vx_part[i] >= 0)
            {
              Wheel3.theta[i] =  acos(Vy_part[i] / Wheel3.V[i]);
            }
            else
            {
              Wheel3.theta[i] = -acos(Vy_part[i] / Wheel3.V[i]);
            }
          }
          else
          {
            if (Vx_part[i] == 0)
            {
              Wheel3.theta[i] = 0;
            }
            if (Vx_part[i] > 0)
            {
              Wheel3.theta[i] = PI/2;
            }
            else
            {
              Wheel3.theta[i] = -PI/2;
            }
          }
        }//叠加后重新计算角度
        //基准位置修正，编码器向后到编码器向里
        //Wheel3.theta[1] -= 2*PI/3;
        //Wheel3.theta[2] += 2*PI/3;
      }//平移旋转
  else//其他情况:仅停止，不转轮
    {
      Wheel3.V[0] = 0;
      Wheel3.V[1] = Wheel3.V[0];
      Wheel3.V[2] = Wheel3.V[0];
    }
  
  //限制角度范围
  Wheel3.theta[0] = trans_PI(trans_PI(Wheel3.theta[0]));
  Wheel3.theta[1] = trans_PI(trans_PI(Wheel3.theta[1]));
  Wheel3.theta[2] = trans_PI(trans_PI(Wheel3.theta[2]));

}//Formula_4Omni末尾
 
float trans_PI(float n)//[-2PI,2PI]->[-PI,PI]
{
  if (n > PI) n -= 2*PI;
  else if (n < -PI) n += 2*PI;
  return n;
}