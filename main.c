#include"route.h"
extern struct  SAngle 	 stcAngle;

extern u8 Interrupt_MODE;
extern u16 sp;
extern u8 Seesaw_flag;
extern u16 Interrupt_Counter;
extern u8 Bucket_Status[4];
float Standard_Angle;
RCC_ClocksTypeDef get_rcc_clock; 
int main(void)
{
	
	
	  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
		delay_init(168);
	  
	  uart_init(115200);
		UART4_Init(115200);
	  USART2_Init(9600); 
    JJ_GPIO_init();	
	  SPI_LCD_Init();
	  GM_Init();
	  LED_Init();
	  Motor_Init();
    BMQ_Init();
	  PID_init();
	  TIM7_Init();	
	  KEY_Init();
	  SERVO_Init();
	  BMQ_PID_Init();
	  Servo_Light_Init();
//	  BMQ_Start();
//	RCC_GetClocksFreq(&get_rcc_clock); 
//		LCD_ShowNum(50,80,get_rcc_clock.PCLK1_Frequency,10,16);
//		LCD_ShowNum(50,100,get_rcc_clock.PCLK2_Frequency,10,16);
	while(1)
	{
		u8 key;
		key=KEY_Scan(0);
		
		
//		  Show_BMQ();
  	show_IO_status();
//		show_mpu_angle();
//    MOTOR_CONTRAL(50,50);
// 		  show_value();
//   show_value_3ADC();
//		MOTOR_CONTRAL(100,0);		
  if(KEY2==key)  		//按键扫描函数
		{
			delay_ms(1500);
			From_1_TO_2();
			From_2_TO_3();
			From_3_TO_Scenic_Spots_2_TO_4();
			From_4_TO_5();
			From_5_TO_7();
			From_7_TO_8();	
			From_8_TO_1();	
		}
	if(KEY3==key)
	  {	
      delay_ms(1500);
      PID_realize(90,13,Middle,30600,2); 		//编码器巡线调整位置，准备加速
			//PID_realize(100,16,Middle,0,1);      	//调整位置，准备加速
			
			Set_Speed_And_Mode(0,200,1,0);	  	  //变换模式	
	    PID_realize(100,7,Middle,33000,1);  //编码器加速一段
			Set_Speed_And_Mode(0,220,0,0);	  	  //变换模式	
			
			PID_realize(100,2,Left,0,1);  //编码器加速一段
			
		  PID_realize(100,17,Middle,0,2);  //编码器加速一段
			
			MOTOR_CONTRAL(0,0);
	  }
		 
	if(KEY4==key)
	  {
			delay_ms(1500);
		  Set_Speed_And_Mode(0,220,0,0);	  		//变换模式
      PID_realize(100,8,Middle,0,1.5);	//
		  Set_Speed_And_Mode(0,220,3,0);	  		//变换模式
			PID_realize(50,22,Middle,0,1.5);     	//
			if(Interrupt_Counter>100)
				{
					Bucket_Status[3]=1;
					Go_Advance(-60,23);
					Interrupt_Counter=0;
					Standard_Angle=JY901_Yaw;     				//记录标准角度用于后面的陀螺仪走直线和转弯
		      MPU_Turnback(Left,110,180,20);    //平台陀螺仪转弯
				}
			else
				PID_realize(100,2,Middle,0,1.5);
					
			MOTOR_CONTRAL(0,0);
	  }
	if(KEY5==key)
		{
			delay_ms(1500);
			if(Bucket_Status[0]+Bucket_Status[1]+Bucket_Status[2]+Bucket_Status[3]==0)
				Get_Buckets_Statues();
		  else if(Bucket_Status[3]==1)
			{
				PID_realize(100,0,Middle,0,1);     	//
		    PID_realize(100,5,Middle,0,1);     	//
		    GM_Turnback(100,Left,4);       //光敏转弯
		    GM_Turnback(100,Left,5);       //光敏转弯
				
				PID_realize(100,10,Middle,0,2);	//
				Set_Speed_And_Mode(0,220,1,0);	  		//变换模式
				PID_realize(100,13,Middle,33000,1.5);     	//
				Set_Speed_And_Mode(0,220,2,0);	  		//变换模式
				PID_realize(sp,5,Middle,0,1);     	//		
			}
			else if(Bucket_Status[2]==1)
			{
				PID_realize(100,0,Middle,0,1);     	//
		    PID_realize(100,5,Middle,0,1);     	//

		    GM_Turnback(100,Left,5);       //光敏转弯
				
				PID_realize(100,10,Middle,0,2);	//
//				Set_Speed_And_Mode(0,220,1,0);	  		//变换模式
				PID_realize(100,5,Middle,33000,1.5);  
			}
			else if(Bucket_Status[0]==1)
			{
				Set_Speed_And_Mode(0,220,0,1);
				PID_realize(80,13,Middle,30600,2); 		//编码器巡线调整位置，准备加速
			  PID_realize(90,16,Middle,0,1.5);      	//调整位置，准备加速
			
			  Set_Speed_And_Mode(0,220,1,1);	  	  //变换模式	
	      PID_realize(90,7,Middle,36000,1);  //编码器加速一段
			  Set_Speed_And_Mode(0,220,0,0);	  	  //变换模式	
					
			  PID_realize(100,19,Middle,0,1.5);      	//调整位置，准备加速
					
				GM_Turnback(100,Left,6);
										
				PID_realize(100,10,Middle,0,2);	//
				Set_Speed_And_Mode(0,220,1,0);	  		//变换模式
				PID_realize(100,13,Middle,33000,1.5);     	//
				Set_Speed_And_Mode(0,220,2,0);	  		//变换模式
				PID_realize(sp,5,Middle,0,1);     	//			
			}
		 	MOTOR_CONTRAL(0,0);	
    }
  }

}
	

		
//		Move_Servos_Array(5,1000,0,1700,1,600,2,2000,3,700,4,1280);			


