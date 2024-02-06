#include "./BSP/LED/led.h"


//��ʼ��
void led_init (void)
{

    GPIO_InitTypeDef gpio_init_struct={0};
    
    __HAL_RCC_GPIOC_CLK_ENABLE();
    
    gpio_init_struct.Pin=GPIO_PIN_13;
    gpio_init_struct.Mode=GPIO_MODE_OUTPUT_PP;
    gpio_init_struct.Speed=GPIO_SPEED_FREQ_LOW;
    
    HAL_GPIO_Init(GPIOC, &gpio_init_struct);


    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_SET);
}
