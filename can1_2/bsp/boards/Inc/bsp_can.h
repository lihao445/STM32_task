#ifndef __BSP_CAN_H_    //ͷ�ļ���ֹ�����ظ�����������
#define __BSP_CAN_H_   //ͷ�ļ���ֹ�����ظ�����������

#ifdef __cplusplus    //��ϱ������������

extern "C"           //��ϱ������������
{                   //��ϱ������������
#endif             //��ϱ������������
/*  ͷ�ļ����ݿ�ʼ   */
#include "main.h"
extern CAN_HandleTypeDef hcan1;
void can_filter_init(void);
void can_cmd_send(int motor1,int motor2,int motor3,int motor4);	
void can_start(CAN_HandleTypeDef *hcan);	
void can_cmd_receive();	
//ͷ�ļ����ݣ�Ԥ����������������������


/*   ͷ�ļ����ݽ���  */
#ifdef __cplusplus     //��ϱ������������
}                      //��ϱ������������
#endif                 //��ϱ������������

#endif   //ͷ�ļ���ֹ�����ظ�����������