#ifndef __BSP_CAN_H_    //头文件防止引用重复的条件编译
#define __BSP_CAN_H_   //头文件防止引用重复的条件编译

#ifdef __cplusplus    //混合编译的条件编译
extern "C"           //混合编译的条件编译
{                   //混合编译的条件编译
#endif             //混合编译的条件编译
/*  头文件内容开始   */
#include "main.h"
extern CAN_HandleTypeDef hcan1;
	
	
//头文件内容：预处理、函数声明、变量声明


/*   头文件内容结束  */
#ifdef __cplusplus     //混合编译的条件编译
}                      //混合编译的条件编译
#endif                 //混合编译的条件编译

#endif   //头文件防止引用重复的条件编译
