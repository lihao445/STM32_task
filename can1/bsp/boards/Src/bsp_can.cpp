#include "bsp_can.h"

static CAN_TxHeaderTypeDef can_tx_message;
static CAN_RxHeaderTypeDef can_rx_message;

static uint8_t can_send_data[8];
static uint8_t can_receive_data[8];


void can_filter_init()
{
	CAN_FilterTypeDef can_filter_st;
	can_filter_st.FilterActivation=ENABLE;//过滤器使能；
	can_filter_st.FilterMode=CAN_FILTERMODE_IDMASK;//过滤器模式；
	can_filter_st.FilterScale=CAN_FILTERSCALE_32BIT;//过滤器位宽；
	can_filter_st.FilterIdHigh=0x0000;//ID高字节；
	can_filter_st.FilterIdLow=0x0000;//ID低字节；
	can_filter_st.FilterMaskIdHigh=0x0000;//掩码高字节；
	can_filter_st.FilterMaskIdLow=0x0000;//掩码低字节；
	can_filter_st.FilterBank=0;//选择过滤器组；
	can_filter_st.FilterFIFOAssignment=CAN_RX_FIFO0;//过滤器关联FIFO；
	HAL_CAN_ConfigFilter(&hcan1,&can_filter_st);//配置CAN通信过滤器；
}

void can_start(CAN_HandleTypeDef *hcan)
{
	HAL_CAN_Start(hcan);//开启can通讯；
	if(HAL_CAN_ActivateNotification(hcan,CAN_IT_RX_FIFO0_MSG_PENDING)!=HAL_OK)//使能中断；
	{
		Error_Handler();
	}
}

void can_cmd_send(int motor1,int motor2,int motor3,int motor4)//发送函数
{
	uint32_t send_mail_box;
	can_tx_message.StdId=0x200;//ID标准标识符；
	can_tx_message.IDE=CAN_ID_STD;//帧格式；
	can_tx_message.RTR=CAN_RTR_DATA;//帧类型；
	can_tx_message.DLC=0x08;//数据长度；
	
	can_send_data[0]=motor1>>8;
	can_send_data[1]=motor1;
	can_send_data[2]=motor2>>8;
	can_send_data[3]=motor2;
	can_send_data[4]=motor3>>8;
	can_send_data[5] = motor3;
	can_send_data[6] = motor4 >> 8;
	can_send_data[7] = motor4;
	
	HAL_CAN_AddTxMessage(&hcan1,&can_tx_message,can_send_data,&send_mail_box);
	//向Tx邮箱中增加一个消息，并且激活对应的传输请求；

}
  /*此函数是将电流值发送给大疆CAN1通信电机，
CAN1通信每次只能发送8比特的数据，电流值是16比特的数据，
所以把电流值向右移8位，然后再发送给电机。
电机接收到电流值就开始转动（入口参数是电调ID为1-4的电机电流值）*/

void can_cmd_receive()
{
	uint32_t receive_mail_box;
	can_rx_message.StdId=0x200;//ID标准帧
	can_rx_message.IDE=CAN_ID_STD;//帧格式
	can_rx_message.RTR=CAN_RTR_DATA;//帧类型
	can_rx_message.DLC=0x08;//数据长度
	
}



















