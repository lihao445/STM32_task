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
float L;//�߳���һ�룬����
float Vx;//���룬action����ϵ�µ��ٶ�
float Vy;//���룬action����ϵ�µ��ٶ�
float omega;//���룬action����ϵ�µĽ��ٶ�
float alfa;//��ͷ��λ
float R;//��ת��뾶
float r[4];//�ְ뾶
float theta[4];//�ַ���
float V[4];//���ٶ�
int halt;//ֹͣ�ƶ�ָ��
}LUN;
 
	 
void Formula (float Vx,float Vy,float Vz);
void Formula_World2Robo (Velocity *world, Velocity *robo);//ת���෴
float trans_PI(float n);

extern LUN   Wheel3;
extern POSE  RobotPos;

#endif