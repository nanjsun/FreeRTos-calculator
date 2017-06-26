#include "shuma.h"
#include "delay.h"
#include "hc38.h"
/*********************************************************************************************************
       数码管驱动文件
*********************************************************************************************************/
u8 shuma_table[]={
0xc0,0xf9,0xa4,0xb0,
0x99,0x92,0x82,0xf8,
0x80,0x90,0x88,0x83,
0xc6,0xa1,0x86,0x8e};

void Shuma_Init(void)
{
 
	 GPIO_InitTypeDef  GPIO_InitStructure;
		
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 //使能PC端口时钟
		
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;	
	//数码管a b c d e f g 和小数点位dp 端口配置,                                                                   // LED_SA-->PC.10                                                                   	
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;         //IO口速度为50MHz
	 GPIO_Init(GPIOC, &GPIO_InitStructure); 				     //根据设定参数初始化GPIOC.0-C.6
	}
 void Shuma_Display(u8 Display_Value)
 { 
	GPIOC->ODR&=0xff80;
  GPIOC->ODR|=shuma_table[Display_Value];
	
   }
