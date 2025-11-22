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

#define Sensor A5
#define LED 13
#define Sensor_DO 2

unsigned int SensorValue = 0;


void setup()
{
	pinMode(Sensor_DO,INPUT);
	pinMode(Sensor,INPUT);
	pinMode(LED,OUTPUT);
	Serial.begin(9600);	//设置通讯的波特率为9600
	Serial.println("Welcome to use!");  //发送的内容
	Serial.println("Made by Beetle Electronic Technology!");  //发送的内容
}

void loop()
{
	SensorValue = analogRead(Sensor);		//读取Sensor引脚的模拟值，该值大小0-1023
	Serial.print("AD Value = ");
	Serial.println(SensorValue);			//将模拟值输出到串口
	if( digitalRead(Sensor_DO) == LOW )		//当DO引脚接收到低电平时候说明，模拟值超过比较器阀值
	{										//通过调节传感器上的电位器可以改变阀值
		Serial.println("Alarm!");		//报警
		digitalWrite(LED,HIGH);			//LED点亮
	}
	else
	{
		digitalWrite(LED,LOW);			//LED熄灭
	}
	delay(1000);
}
