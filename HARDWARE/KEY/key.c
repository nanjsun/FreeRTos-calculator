#include "key.h"
#include "delay.h"
/************************************************************************************************** 
               按键输入 驱动代码		   
**************************************************************************************************/							   
	 
 	    
//按键初始化函数 
//extern 	u8 Press_Count;
void KEY_Init(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//使能PORTB时钟

	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//关闭jtag，使能SWD，可以用SWD模式调试
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_8|GPIO_Pin_9;;//PB8和PB9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOB8-9;
	

	
} 
//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//返回值：
//0，没有任何按键按下
//KEY1Line_PRES，第一行键按下
//KEY2Line_PRES，第二行键按下

//注意此函数有响应优先级,KEY0>KEY1>WK_UP!!
	u8 KEY_Scan(u8 mode)
	{	 
		static u8 key_up=1;//按键按松开标志
			if(mode)key_up=1;  //支持连按		  
		if(key_up&&(KB_L1==0||KB_L2==0))
		{
		 //delay_ms(10);//去抖动 
			key_up=0;
			//Press_Count++;
			if(KB_L1==0)
				return KEY1Line_PRES;
			else if(KB_L2==0)
						return KEY2Line_PRES;
		}else if(KB_L1==1&&KB_L2==1)
		        key_up=1; 	     
			return 0;// 无按键按下
	}
//u8 KEY_Scan()
//{	 
//	
//	if(KB_L1==0||KB_L2==0)
//	{
//	  //delay_ms(10);//去抖动 
//		
//		if(KB_L1==0)
//			return KEY1Line_PRES;
//		else if(KB_L2==0)
//			    return KEY2Line_PRES;
//	}else if(KB_L1==1&&KB_L2==1)	     
//	  return 0;// 无按键按下
//}
