#include"bsp_can.h"
#include"stm32f4xx_hal_can.h"

static CAN_TxHeaderTypeDef can_tx_message;
static CAN_RxHeaderTypeDef can_rx_message;