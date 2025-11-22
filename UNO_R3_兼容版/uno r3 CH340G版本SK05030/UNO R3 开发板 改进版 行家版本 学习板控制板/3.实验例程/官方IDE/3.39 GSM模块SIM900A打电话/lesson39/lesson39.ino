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
/*
//arduino uno
#include <Arduino.h>

#define KEY1 2
#define KEY2 3

void setup()
{
	pinMode(KEY1, INPUT_PULLUP); 
	pinMode(KEY2, INPUT_PULLUP); 
	Serial.begin(9600);	//设置通讯的波特率为9600
}

void loop()
{
	Scan_KEY();			
}

void Ring()
{
	Serial.print("ATD18067933376;\r\n");				//可从此条语句修改需要更换的手机号，将18067933376修改为您需要拨打的手机号
	delay(1000);
}

void HangUp()
{
	Serial.print("ATH\r\n");			//挂断指令
	delay(1000);
}


void Scan_KEY()						//按键扫描
{
	if( digitalRead(KEY1) == 0 )		//查看按键是否按下	
	{
		delay(20);					//延时20ms，去抖动	
		if( digitalRead(KEY1) == 0 ) //查看按键是否按下
		{			
			while(digitalRead(KEY1) == 0);		//松手检测
			Ring();
		}
	}

	if( digitalRead(KEY2) == 0 )		//查看按键是否按下	
	{
		delay(20);					//延时20ms，去抖动	
		if( digitalRead(KEY2) == 0 ) //查看按键是否按下
		{			
			while(digitalRead(KEY2) == 0);		//松手检测
			HangUp();
		}
	}
}
*/


//arduino leonardo
#include <Arduino.h>

#define KEY1 2
#define KEY2 3

void setup()
{
	pinMode(KEY1, INPUT_PULLUP); 
	pinMode(KEY2, INPUT_PULLUP); 
	Serial1.begin(9600);	//设置通讯的波特率为9600
}

void loop()
{
	Scan_KEY();			
}

void Ring()
{
	Serial1.print("ATD18067933376;\r\n");				//可从此条语句修改需要更换的手机号，将18067933376修改为您需要拨打的手机号
	delay(1000);
}

void HangUp()
{
	Serial1.print("ATH\r\n");			//挂断指令
	delay(1000);
}


void Scan_KEY()						//按键扫描
{
	if( digitalRead(KEY1) == 0 )		//查看按键是否按下	
	{
		delay(20);					//延时20ms，去抖动	
		if( digitalRead(KEY1) == 0 ) //查看按键是否按下
		{			
			while(digitalRead(KEY1) == 0);		//松手检测
			Ring();
		}
	}

	if( digitalRead(KEY2) == 0 )		//查看按键是否按下	
	{
		delay(20);					//延时20ms，去抖动	
		if( digitalRead(KEY2) == 0 ) //查看按键是否按下
		{			
			while(digitalRead(KEY2) == 0);		//松手检测
			HangUp();
		}
	}
}
