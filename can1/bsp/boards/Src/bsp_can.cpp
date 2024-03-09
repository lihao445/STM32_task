#include "bsp_can.h"

static CAN_TxHeaderTypeDef can_tx_message;
static CAN_RxHeaderTypeDef can_rx_message;

static uint8_t can_send_data[8];
static uint8_t can_receive_data[8];


void can_filter_init()
{
	CAN_FilterTypeDef can_filter_st;
	can_filter_st.FilterActivation=ENABLE;//������ʹ�ܣ�
	can_filter_st.FilterMode=CAN_FILTERMODE_IDMASK;//������ģʽ��
	can_filter_st.FilterScale=CAN_FILTERSCALE_32BIT;//������λ��
	can_filter_st.FilterIdHigh=0x0000;//ID���ֽڣ�
	can_filter_st.FilterIdLow=0x0000;//ID���ֽڣ�
	can_filter_st.FilterMaskIdHigh=0x0000;//������ֽڣ�
	can_filter_st.FilterMaskIdLow=0x0000;//������ֽڣ�
	can_filter_st.FilterBank=0;//ѡ��������飻
	can_filter_st.FilterFIFOAssignment=CAN_RX_FIFO0;//����������FIFO��
	HAL_CAN_ConfigFilter(&hcan1,&can_filter_st);//����CANͨ�Ź�������
}

void can_start(CAN_HandleTypeDef *hcan)
{
	HAL_CAN_Start(hcan);//����canͨѶ��
	if(HAL_CAN_ActivateNotification(hcan,CAN_IT_RX_FIFO0_MSG_PENDING)!=HAL_OK)//ʹ���жϣ�
	{
		Error_Handler();
	}
}

void can_cmd_send(int motor1,int motor2,int motor3,int motor4)//���ͺ���
{
	uint32_t send_mail_box;
	can_tx_message.StdId=0x200;//ID��׼��ʶ����
	can_tx_message.IDE=CAN_ID_STD;//֡��ʽ��
	can_tx_message.RTR=CAN_RTR_DATA;//֡���ͣ�
	can_tx_message.DLC=0x08;//���ݳ��ȣ�
	
	can_send_data[0]=motor1>>8;
	can_send_data[1]=motor1;
	can_send_data[2]=motor2>>8;
	can_send_data[3]=motor2;
	can_send_data[4]=motor3>>8;
	can_send_data[5] = motor3;
	can_send_data[6] = motor4 >> 8;
	can_send_data[7] = motor4;
	
	HAL_CAN_AddTxMessage(&hcan1,&can_tx_message,can_send_data,&send_mail_box);
	//��Tx����������һ����Ϣ�����Ҽ����Ӧ�Ĵ�������

}
  /*�˺����ǽ�����ֵ���͸���CAN1ͨ�ŵ����
CAN1ͨ��ÿ��ֻ�ܷ���8���ص����ݣ�����ֵ��16���ص����ݣ�
���԰ѵ���ֵ������8λ��Ȼ���ٷ��͸������
������յ�����ֵ�Ϳ�ʼת������ڲ����ǵ��IDΪ1-4�ĵ������ֵ��*/

void can_cmd_receive()
{
	uint32_t receive_mail_box;
	can_rx_message.StdId=0x200;//ID��׼֡
	can_rx_message.IDE=CAN_ID_STD;//֡��ʽ
	can_rx_message.RTR=CAN_RTR_DATA;//֡����
	can_rx_message.DLC=0x08;//���ݳ���
	
}



















