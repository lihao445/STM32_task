#include"bsp_can.h"

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

void can_cmd_send(int motor1,int motor2,int motor3,int motor4)
{
	
}



















