#include "led.h"
#include "delay.h"
#include "sys.h"
#include "FreeRTOS.h"
#include "task.h"
#include "usart.h"
#include "oled.h"
#include "hc38.h"
#include "shuma.h"
#include "key.h"
#include "semphr.h"
#include "timer.h"
/************************************************
 ALIENTEK Mini STM32F103开发板 FreeRTOS实验2-1
 FreeRTOS移植实验-库函数版本
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/

//任务优先级
#define START_TASK_PRIO		1
//任务堆栈大小	
#define START_STK_SIZE 		128  
//任务句柄
TaskHandle_t StartTask_Handler;
//任务函数
void start_task(void *pvParameters);

//任务优先级
#define LED_TASK_PRIO		2
//任务堆栈大小	
#define LED_STK_SIZE 		50  
//任务句柄
TaskHandle_t LEDTask_Handler;
//任务函数
void led_task(void *pvParameters);

//任务优先级
#define OLED_TASK_PRIO     3
//任务堆栈大小
#define OLED_STK_SIZE      50
//任务句柄
TaskHandle_t OLEDTask_Handler;
//任务函数
void oled_task(void *pvParameters);

//任务优先级
#define SHUMA_TASK_PRIO     4
//任务堆栈大小
#define SHUMA_STK_SIZE      50
//任务句柄
TaskHandle_t SHUMATask_Handler;
//任务函数
void shuma_task(void *pvParameters);

////任务优先级
//#define KEY_TASK_PRIO     4
////任务堆栈大小
//#define KEY_STK_SIZE      50
////任务句柄
//TaskHandle_t KEYTask_Handler;
////任务函数
//void key_task(void *pvParameters);
void xy_fenjie(u8 x,u8 y);
void snack_show(u8 px,u8 py,u8 len);
SemaphoreHandle_t BinarySemaphore;	//二值信号量句柄

u8 Count=0;
u8 LineNum=0;
u8 RowNum=0;
u8 Key_Num=0;
u8 LED_Num=1;
u8 Button_Num;
u8 plus=5;
u8 position_x=5;
u8 position_y=3;
u8 position[8]={0,5,0,3,1,0,5,0};
u8 px,py,len=1;
int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//设置系统中断优先级分组4	 	 
	delay_init();	    				//延时函数初始化	  
	uart_init(115200);					//初始化串口
	LED_Init();		  					//初始化LED
	OLED_Init();
	OLED_Clear();
	HC38_Init();
	Shuma_Init();
	KEY_Init();
	TIM5_Int_Init(2000-1,72-1);
	OLED_ShowString(position_x*10,position_y,"*",8);
	//OLED_ShowString(0,3,"**",16);
	//printf("cc");
	 
	//创建开始任务
    xTaskCreate((TaskFunction_t )start_task,            //任务函数
                (const char*    )"start_task",          //任务名称
                (uint16_t       )START_STK_SIZE,        //任务堆栈大小
                (void*          )NULL,                  //传递给任务函数的参数
                (UBaseType_t    )START_TASK_PRIO,       //任务优先级
                (TaskHandle_t*  )&StartTask_Handler);   //任务句柄              
    vTaskStartScheduler();          //开启任务调度
}

//开始任务任务函数
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           //进入临界区
		BinarySemaphore=xSemaphoreCreateBinary();	
   
    //创建LED任务
    xTaskCreate((TaskFunction_t )led_task,     
                (const char*    )"led_task",   
                (uint16_t       )LED_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )LED_TASK_PRIO,
                (TaskHandle_t*  )&LEDTask_Handler);  
		//创建OLED任务
    xTaskCreate((TaskFunction_t )oled_task,     
                (const char*    )"oled_task",   
                (uint16_t       )OLED_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )OLED_TASK_PRIO,
                (TaskHandle_t*  )&OLEDTask_Handler); 
	//创建SHUMA任务
    xTaskCreate((TaskFunction_t )shuma_task,     
                (const char*    )"shuma_task",   
                (uint16_t       )SHUMA_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )SHUMA_TASK_PRIO,
                (TaskHandle_t*  )&SHUMATask_Handler); 
								
    vTaskDelete(StartTask_Handler); //删除开始任务
    taskEXIT_CRITICAL();            //退出临界区
}

//LED任务函数 
void led_task(void *pvParameters)
{
	
    while(1)
    {   	
        LED1=0;
       vTaskDelay(10*plus);
        LED2=0;
        vTaskDelay(10*plus);
			  LED3=0;
      vTaskDelay(10*plus);
        LED4=0;
        vTaskDelay(10*plus);
			   LED1=1;
       vTaskDelay(10*plus);
        LED2=1;
       vTaskDelay(10*plus);
			  LED3=1;
      vTaskDelay(10*plus);
        LED4=1;
       vTaskDelay(10*plus);
		
    }
}   


//OLED任务函数
void oled_task(void *pvParameters)
{
	u8 j=0;
	u8 i=0;
	BaseType_t err=pdFALSE;
    while(1)
    {
			err=xSemaphoreTake(BinarySemaphore,portMAX_DELAY);	//获取信号量
			if(err==pdTRUE)										//获取信号量成功
			{		//if(Key_Num==11)
					printf("time is over");
			}
//			 xy_fenjie(position_x,position_y);
//		    if(len-position_x==2)
//				{
//					position_x++;
//				 }
//					for(i=0;i<len;i++)
//				{
//					OLED_ShowString((position_x-i)*10,position_y,"*",8);
//				 }
    }
}
 
void shuma_task(void *pvParameters)
{  
	u8 Num=0;
	u8 t=0;
	u8 m=0;
	u8 n=0;
	u8 flag1=0;
	u8 flag2=0;
	u8 Key_Num_past=0;
	u8 i=0;
	u8 add=1;
	//u8 position_x_last=0;
	//BaseType_t err=pdFALSE;
    while(1)
    {
			
			 if(Count==8)
				  Count=0;
			 if(Num==8)
				  Num=0;  
			    HC38_Enter_Value(Count);
		      RowNum=Count;
			    Count++;
			    //Key_Num=LineNum*10+RowNum;
			    t=LineNum;
			    LineNum=KEY_Scan(0);
			      if(LineNum!=t)
				    {
					    flag1=1;
				     }
								if(flag1==1)
								{
									//printf("Key_Num = %d\n",Key_Num);
									m++;
									 if(m==7)
									{
												 if(LineNum!=0)
											 {
												 m=0;
												 flag1=0;
												 Key_Num=LineNum*10+Count;
												 if(Key_Num!=Key_Num_past)
													{
														printf("Key_Num = %d\n",Key_Num);
														OLED_Clear();
														Key_Num_past=Key_Num;
															 switch(Key_Num)
															 { 
																 case 11:
																	 if(plus<20)
																		 plus++;
																	 else
																			plus=20;
																			//printf("plus = %d\n",plus);
																	 break;
																 case 21:
																	 if(plus>1)
																	    plus--;
																	 else
																			plus=1;
																		break;
																 case 12:
																	    if(add<4)
																	    add++;
																	 else
																			add=4;
																	 len=add;
																	 break;
																 case 22:
																	 if(add>1)
																	    add--;
																	 else
																			add=1;
																	 len=add;
																	 break;
																 case 13:
																	 if(position_x<12)
																		position_x++;
																	    else
																		position_x=12;																				
																	 break;
																 case 23:
																	 if(position_x>0)
																		 position_x--;
																	 else
																		 position_x=0;
																	 break;
																 case 14:
																	 if(position_y<7)
																		position_y++;
																	    else
																		position_y=7;	
																	 break;
																 case 24:
																	 if(position_y>0)
																		position_y--;
																	    else
																		position_y=0;	
																	 break;
																	case 15:                                       																
																	 break;
																 case 25:
																 default:
																		 break;
															 }
															 xy_fenjie(position_x,position_y);
															 if(len-position_x==2)
															 {
																 position_x++;
															 }
															 for(i=0;i<len;i++)
															 {
															 OLED_ShowString((position_x-i)*10,position_y,"*",8);
															 }
													   }
												   }									
											   else 
													 {
												   m=0;
												 }
												
											}
										 }	
                  if(LineNum==0&&t!=0)
									{ 
										flag2=1;
									}		
                    if(flag2==1)
										{
											n++;
											if(n==20)
											{ 
												
												if(LineNum==0)
												{ 
													n=0;
												  flag2=0;
													Key_Num_past=0;
												}
												else
													n=0;
											}
												
										}											
              if(Num<8)										
			   Shuma_Display(position[Num]);
			         Num++;
	       vTaskDelay(3);	
    }
 }

void xy_fenjie(u8 x,u8 y)
{
	 if(x<10)
	 {
		 position[0]=0;
		 position[1]=x;
	 }
	 else
	 {
		 position[0]=x/10;
		 position[1]=x%10;
	 }
	 
		 position[2]=0;
		 position[3]=y;
	   position[4]=len;
	   position[5]=10*plus/100;
	   position[6]=10*plus%100/10;
	   position[7]=10*plus%10;
	 
}

