#ifndef _CHASSIS_H
#define _CHASSIS_H


 
#include <stdint.h>
#pragma once
//#include "includes.h"
//#include <main.h>
 
 
#ifdef   ROBOT_CTRL_MODULE
#define  ROBOT_CTRL_EXT
#else
#define  ROBOT_CTRL_EXT  extern
#endif
 
//****************************************************************           ???           ****************************************************************
#ifdef   CHASSIS_MODULE
#define  CHASSIS_EXT
#else
#define  CHASSIS_EXT  extern
#endif
#define PI 3.1415926
//#define PI2 2*3.1415926 
typedef struct
{
  float Vx;
  float Vy;
  float Vz;
  
}Velocity; // unit: mm/s, rad/s
 

// Position data structure
typedef struct
{
  float pos_x; // mm
  float pos_y; // mm
  float zangle; // degree
  float xangle; // degree
  float yangle; // degree
  float w_z;
  float theta; // rad
  
}POSE;
 
typedef struct
{
float L;//边长的一半，常数
float Vx;//输入，action坐标系下的速度
float Vy;//输入，action坐标系下的速度
float omega;//输入，action坐标系下的角速度
float alfa;//车头定位
float R;//总转向半径
float r[4];//轮半径
float theta[4];//轮方向
float V[4];//轮速度
int halt;//停止移动指令
}LUN;
 
	 
void Formula (float Vx,float Vy,float Vz);
void Formula_World2Robo (Velocity *world, Velocity *robo);//转角相反
float trans_PI(float n);

extern LUN   Wheel3;
extern POSE  RobotPos;

#endif