#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK miniSTM32开发板
//按键驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/3
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   	 


//#define KEY0 PCin(5)   	
//#define KEY1 PAin(15)	 
//#define WK_UP  PAin(0)	 
 

#define KB_L1  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)//读取按键行数1
#define KB_L2  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)//读取按键行数2

 

#define KEY1Line_PRES	1		//KEY1Line 第一行键按下 
#define KEY2Line_PRES	2		//KEY2Line 第二行键按下 


void KEY_Init(void);//IO初始化
u8 KEY_Scan(u8 mode);  	//按键扫描函数					    
#endif
