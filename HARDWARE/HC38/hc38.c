#include "hc38.h"
#include "delay.h"

/***********************************************************************************************************************
           74HC38�������������	   
***********************************************************************************************************************/  

//��ʼ��PA15��PC10-12Ϊ�����.    

void HC38_Init(void)
{
 
	 GPIO_InitTypeDef  GPIO_InitStructure;
		
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC, ENABLE);	 //ʹ��PA,PC�˿�ʱ��
		
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;				 //LED_En-->PA.15 �˿�����
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	 GPIO_Init(GPIOA, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOA.15
	 GPIO_SetBits(GPIOA,GPIO_Pin_15);						 //PA.15 �����

	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12;	//LED_SA-->PC.10  LED_SB-->PC.11 LED_SC-->PC.12 �˿�����,                                                                   // LED_SA-->PC.10                                                                   	
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;         //IO���ٶ�Ϊ50MHz
	 GPIO_Init(GPIOC, &GPIO_InitStructure); 				     //�����趨������ʼ��GPIOC.10-C.12
	}

 void HC38_Enter_Value(u16 Value)
	{
		GPIOC->ODR&=0xe3ff;
	  GPIOC->ODR|=Value<<10;
		
	 }
