#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK miniSTM32������
//������������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   	 


//#define KEY0 PCin(5)   	
//#define KEY1 PAin(15)	 
//#define WK_UP  PAin(0)	 
 

#define KB_L1  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)//��ȡ��������1
#define KB_L2  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)//��ȡ��������2

 

#define KEY1Line_PRES	1		//KEY1Line ��һ�м����� 
#define KEY2Line_PRES	2		//KEY2Line �ڶ��м����� 


void KEY_Init(void);//IO��ʼ��
u8 KEY_Scan(u8 mode);  	//����ɨ�躯��					    
#endif
