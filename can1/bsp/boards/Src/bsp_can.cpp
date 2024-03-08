#include"bsp_can.h"

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

void can_cmd_send(int motor1,int motor2,int motor3,int motor4)
{
	
}



















