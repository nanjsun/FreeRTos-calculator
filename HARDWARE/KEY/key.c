#include "key.h"
#include "delay.h"
/************************************************************************************************** 
               �������� ��������		   
**************************************************************************************************/							   
	 
 	    
//������ʼ������ 
//extern 	u8 Press_Count;
void KEY_Init(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//ʹ��PORTBʱ��

	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//�ر�jtag��ʹ��SWD��������SWDģʽ����
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_8|GPIO_Pin_9;;//PB8��PB9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOB8-9;
	

	
} 
//����������
//���ذ���ֵ
//mode:0,��֧��������;1,֧��������;
//����ֵ��
//0��û���κΰ�������
//KEY1Line_PRES����һ�м�����
//KEY2Line_PRES���ڶ��м�����

//ע��˺�������Ӧ���ȼ�,KEY0>KEY1>WK_UP!!
	u8 KEY_Scan(u8 mode)
	{	 
		static u8 key_up=1;//�������ɿ���־
			if(mode)key_up=1;  //֧������		  
		if(key_up&&(KB_L1==0||KB_L2==0))
		{
		 //delay_ms(10);//ȥ���� 
			key_up=0;
			//Press_Count++;
			if(KB_L1==0)
				return KEY1Line_PRES;
			else if(KB_L2==0)
						return KEY2Line_PRES;
		}else if(KB_L1==1&&KB_L2==1)
		        key_up=1; 	     
			return 0;// �ް�������
	}
//u8 KEY_Scan()
//{	 
//	
//	if(KB_L1==0||KB_L2==0)
//	{
//	  //delay_ms(10);//ȥ���� 
//		
//		if(KB_L1==0)
//			return KEY1Line_PRES;
//		else if(KB_L2==0)
//			    return KEY2Line_PRES;
//	}else if(KB_L1==1&&KB_L2==1)	     
//	  return 0;// �ް�������
//}
