/******************************************************************************
----------------本例程仅供学习使用，未经作者允许，不得用于其他用途。-----------
------------------------版权所有，仿冒必究！-----------------------------------
----------------1.开发环境:Arduino IDE-----------------------------------------
----------------2.测试使用开发板型号：Arduino Leonardo or Arduino UNO R3-------
----------------3.单片机使用晶振：16M------------------------------------------
----------------4.淘宝网址：Ilovemcu.taobao.com--------------------------------
----------------------------epic-mcu.taobao.com--------------------------------
----------------5.作者：神秘藏宝室---------------------------------------------
******************************************************************************/
#include <Arduino.h>
#include "DS1302.h"

#define KEY1 5
#define KEY2 6
#define KEY3 7
#define KEY4 8

unsigned char KEY_NUM = 0;
bool Flag_KEY_Set = 0;
unsigned char KEY2_Count = 0;

void setup()
{
	pinMode(KEY1,INPUT_PULLUP);
	pinMode(KEY2,INPUT_PULLUP);
	pinMode(KEY3,INPUT_PULLUP);
	pinMode(KEY4,INPUT_PULLUP);

	DS1302_Init();
	Serial.begin(9600);	//设置通讯的波特率为9600
	Serial.println("Welcome to use!");  //发送的内容
	Serial.println("Made by Beetle Electronic Technology!");  //发送的内容	
}

void loop()
{
	DS1302_GetTime(&DS1302Buffer);			//获取当前RTCC值
	if(Flag_Time_Refresh == 1 && Flag_KEY_Set == 0 )
	{
		Flag_Time_Refresh = 0;
		Display_RTCC();
	}
	Scan_KEY();
	switch( KEY_NUM )
	{
		case 1:						//按键1执行程序
				KEY_NUM = 0;		//清空按键标志
				Flag_KEY_Set =!Flag_KEY_Set;	//设置按键标志位翻转
				if(Flag_KEY_Set)
				{						
					Serial.println("Set Mode!");
					Serial.println("Set Year!");	//设置年
					KEY2_Count = 0;
					DS1302_ON_OFF(0);			//关闭振荡
				}
				else
				{
					Serial.println("Quit Set!");
					DS1302_ON_OFF(1);			//打开振荡
				}
				break;
		case 2:						//按键2执行程序
				KEY_NUM = 0;		//清空按键标志
				if(Flag_KEY_Set)			//在设置状态时运行
				{
					KEY2_Count++;
					if(KEY2_Count == 7)
						KEY2_Count = 0;
					switch(KEY2_Count)
					{
						case 0:
								Serial.println("Set Year!");	//年
								break;
						case 1:
								Serial.println("Set Month!");	//月
								break;
						case 2:
								Serial.println("Set Day!");	//日
								break;
						case 3:
								Serial.println("Set Week!");		//星期
								break;
						case 4:
								Serial.println("Set Hour!");		//小时
								break;
						case 5:
								Serial.println("Set Minute!");		//分钟
								break;
						case 6:
								Serial.println("Set Second!");		//秒钟
								break;
						default : break;
					}	
				}					
				break;
		case 3:						//按键3执行程序
				KEY_NUM = 0;		//清空按键标志
				if(Flag_KEY_Set)			//在设置状态时运行
				{
					switch(KEY2_Count)
					{
						case 0:
								DS1302Buffer.Year++;
								if(DS1302Buffer.Year >= 100)
								{
									DS1302Buffer.Year = 0;
								}
								DS1302_SetTime( DS1302_YEAR , DS1302Buffer.Year );
								Serial.println("*******************************************");
								Serial.println("Setting Year+1:");
								Display_RTCC();
								break;
						case 1:
								DS1302Buffer.Month++;
								if(DS1302Buffer.Month >= 13)
								{
									DS1302Buffer.Month = 1;
								}
								DS1302_SetTime( DS1302_MONTH , DS1302Buffer.Month );
								Serial.println("*******************************************");
								Serial.println("Setting Month+1:");
								Display_RTCC();
								break;
						case 2:
								DS1302Buffer.Day++;
								if(DS1302Buffer.Day >= 32)
								{
									DS1302Buffer.Day = 1;
								}
								DS1302_SetTime( DS1302_DAY , DS1302Buffer.Day );
								Serial.println("*******************************************");
								Serial.println("Setting Day+1:");
								Display_RTCC();
								break;
						case 3:
								DS1302Buffer.Week++;
								if(DS1302Buffer.Week >= 8)
								{
									DS1302Buffer.Week = 1;
								}
								DS1302_SetTime( DS1302_WEEK , DS1302Buffer.Week );
								Serial.println("*******************************************");
								Serial.println("Setting Week+1:");
								Display_RTCC();
								break;
						case 4:
								DS1302Buffer.Hour++;
								if(DS1302Buffer.Hour >= 24)
								{
									DS1302Buffer.Hour = 0;
								}
								DS1302_SetTime( DS1302_HOUR , DS1302Buffer.Hour );
								Serial.println("*******************************************");
								Serial.println("Setting Hour+1:");
								Display_RTCC();
								break;
						case 5:
								DS1302Buffer.Minute++;
								if(DS1302Buffer.Minute >= 60)
								{
									DS1302Buffer.Minute = 0;
								}
								DS1302_SetTime( DS1302_MINUTE , DS1302Buffer.Minute );
								Serial.println("*******************************************");
								Serial.println("Setting Minute+1:");
								Display_RTCC();
								break;
						case 6:
								DS1302Buffer.Second++;
								if(DS1302Buffer.Second >= 60)
								{
									DS1302Buffer.Second = 0;
								}
								DS1302_SetTime( DS1302_SECOND , DS1302Buffer.Second);
								DS1302_ON_OFF(0);			//设置秒会使DS1302振荡，再次关闭振荡
								Serial.println("*******************************************");
								Serial.println("Setting Second+1:");
								Display_RTCC();
								break;
						default : break;
					}
				}
				break;
		case 4:						//按键4执行程序
				KEY_NUM = 0;		//清空按键标志
				if(Flag_KEY_Set)			//在设置状态时运行
				{
					switch(KEY2_Count)
					{
						case 0:
								DS1302Buffer.Year--;
								if(DS1302Buffer.Year == 255)
								{
									DS1302Buffer.Year = 99;
								}
								DS1302_SetTime( DS1302_YEAR , DS1302Buffer.Year );
								Serial.println("*******************************************");
								Serial.println("Setting Year-1:");
								Display_RTCC();
								break;
						case 1:
								DS1302Buffer.Month--;
								if(DS1302Buffer.Month == 0)
								{
									DS1302Buffer.Month = 12;
								}
								DS1302_SetTime( DS1302_MONTH , DS1302Buffer.Month );
								Serial.println("*******************************************");
								Serial.println("Setting Month-1:");
								Display_RTCC();
								break;
						case 2:
								DS1302Buffer.Day--;
								if(DS1302Buffer.Day == 0)
								{
									DS1302Buffer.Day = 31;
								}
								DS1302_SetTime( DS1302_DAY , DS1302Buffer.Day );
								Serial.println("*******************************************");
								Serial.println("Setting Day-1:");
								Display_RTCC();
								break;
						case 3:
								DS1302Buffer.Week--;
								if(DS1302Buffer.Week == 0)
								{
									DS1302Buffer.Week = 7;
								}
								DS1302_SetTime( DS1302_WEEK , DS1302Buffer.Week );
								Serial.println("*******************************************");
								Serial.println("Setting Week-1:");
								Display_RTCC();
								break;
						case 4:
								DS1302Buffer.Hour--;
								if(DS1302Buffer.Hour == 255)
								{
									DS1302Buffer.Hour = 23;
								}
								DS1302_SetTime( DS1302_HOUR , DS1302Buffer.Hour );
								Serial.println("*******************************************");
								Serial.println("Setting Hour-1:");
								Display_RTCC();
								break;
						case 5:
								DS1302Buffer.Minute--;
								if(DS1302Buffer.Minute == 255)
								{
									DS1302Buffer.Minute = 59;
								}
								DS1302_SetTime( DS1302_MINUTE , DS1302Buffer.Minute );
								Serial.println("*******************************************");
								Serial.println("Setting Minute-1:");
								Display_RTCC();
								break;
						case 6:
								DS1302Buffer.Second--;
								if(DS1302Buffer.Second == 255)
								{
									DS1302Buffer.Second = 59;
								}
								DS1302_SetTime( DS1302_SECOND , DS1302Buffer.Second);
								DS1302_ON_OFF(0);			//设置秒会使DS1302振荡，再次关闭振荡
								Serial.println("*******************************************");
								Serial.println("Setting Second-1:");
								Display_RTCC();
								break;
						default : break;
					}
				}
				break;
		default : break;
	}				
}

void Display_RTCC()
{
	
	if(DS1302Buffer.Year < 10)
	{
		Serial.print("200");
	}
	else
	{
		Serial.print("20");
	}
	Serial.print(DS1302Buffer.Year);
	Serial.print('-');
	Serial.print(DS1302Buffer.Month);
	Serial.print('-');
	Serial.print(DS1302Buffer.Day);

	Serial.print("   ");

	switch(DS1302Buffer.Week)
	{
		case 1:
				Serial.println("Mon");				 //显示星期一
				break;
		case 2:
				Serial.println("Tue");				 //显示星期二
				break;
		case 3:
				Serial.println("Wed");				 //显示星期三
				break;
		case 4:
				Serial.println("Thu");				 //显示星期四
				break;
		case 5:
				Serial.println("Fri");				 //显示星期五
				break;
		case 6:
				Serial.println("Sat");				 //显示星期六
				break;
		case 7:
				Serial.println("Sun");				 //显示星期日
				break;
		default : break;						
	}

	Serial.print(DS1302Buffer.Hour);
	Serial.print(':');
	Serial.print(DS1302Buffer.Minute);
	Serial.print(':');
	Serial.println(DS1302Buffer.Second);
}

void Scan_KEY()
{
	if( digitalRead(KEY1) == LOW )	 					//按键1扫描
	{
		delay(20);					//延时去抖
		if( digitalRead(KEY1) == LOW )
		{
			while(digitalRead(KEY1) == LOW);			//等待松手
			KEY_NUM = 1;
		}
	}

	if( digitalRead(KEY2) == LOW )						//按键2扫描
	{
		delay(20);					//延时去抖
		if( digitalRead(KEY2) == LOW )
		{
			while(digitalRead(KEY2) == LOW);			//等待松手
			KEY_NUM = 2;
		}
	}

	if( digitalRead(KEY3) == LOW )						//按键3扫描
	{
		delay(20);					//延时去抖
		if( digitalRead(KEY3) == LOW )
		{
			while(digitalRead(KEY3) == LOW);			//等待松手
			KEY_NUM = 3;
		}
	}

	if( digitalRead(KEY4) == LOW )						//按键4扫描
	{
		delay(20);					//延时去抖
		if( digitalRead(KEY4) == LOW )
		{
			while(digitalRead(KEY4) == LOW);			//等待松手
			KEY_NUM = 4;
		}
	}
}
