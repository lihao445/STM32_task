#include"bsp_can.h"

static CAN_TxHeaderTypeDef can_tx_message;
static CAN_RxHeaderTypeDef can_rx_message;

static uint8_t can_send_data[8];
static uint8_t can_receive_data[8];


void can_filter_init()
{
	CAN_FilterTypeDef can_filter_st;
	can_filter_st.FilterActivation=ENABLE;//
	can_filter_st.FilterMode=CAN_FILTERMODE_IDMASK;
	can_filter_st.FilterScale=CAN_FILTERSCALE_32BIT;
	can_filter_st.FilterIdHigh=0x0000;
	can_filter_st.FilterIdLow=0x0000;
	can_filter_st.FilterMaskIdHigh=0x0000;
	can_filter_st.FilterMaskIdLow=0x0000;
	can_filter_st.FilterBank=0;
	can_filter_st.FilterFIFOAssignment=CAN_RX_FIFO0;
	HAL_CAN_ConfigFilter(&hcan1,&can_filter_st);
}