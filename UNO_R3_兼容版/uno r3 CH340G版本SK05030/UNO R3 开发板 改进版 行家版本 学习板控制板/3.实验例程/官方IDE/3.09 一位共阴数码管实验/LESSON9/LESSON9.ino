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

#define SEG_a 2				//IO命名
#define SEG_b 3
#define SEG_c 4
#define SEG_d 5
#define SEG_e 6
#define SEG_f 7
#define SEG_g 8
#define SEG_h 9

//数码管0-9数字码值
unsigned char table[10][8] =
{
	{0,	0,	1,	1,	1,	1,	1,	1},			//0
	{0,	0,	0,	0,	0,	1,	1,	0},			//1
	{0,	1,	0,	1,	1,	0,	1,	1},			//2
	{0,	1,	0,	0,	1,	1,	1,	1},			//3
	{0,	1,	1,	0,	0,	1,	1,	0},			//4
	{0,	1,	1,	0,	1,	1,	0,	1},			//5
	{0,	1,	1,	1,	1,	1,	0,	1},			//6
	{0,	0,	0,	0,	0,	1,	1,	1},			//7
	{0,	1,	1,	1,	1,	1,	1,	1},			//8
	{0,	1,	1,	0,	1,	1,	1,	1}			//9
};

void setup()
{
	pinMode(SEG_a,OUTPUT);				//设置引脚为输出
	pinMode(SEG_b,OUTPUT);
	pinMode(SEG_c,OUTPUT);
	pinMode(SEG_d,OUTPUT);
	pinMode(SEG_e,OUTPUT);
	pinMode(SEG_f,OUTPUT);
	pinMode(SEG_g,OUTPUT);
	pinMode(SEG_h,OUTPUT);
}

void loop()
{
	unsigned char i;

	for( i = 0 ; i < 10 ; i++)				//循环显示0-9
	{
		digitalWrite(SEG_a,table[i][7]);	//设置a引脚的电平
		digitalWrite(SEG_b,table[i][6]);
		digitalWrite(SEG_c,table[i][5]);
		digitalWrite(SEG_d,table[i][4]);
		digitalWrite(SEG_e,table[i][3]);
		digitalWrite(SEG_f,table[i][2]);
		digitalWrite(SEG_g,table[i][1]);
		digitalWrite(SEG_h,table[i][0]);

		delay(1000);						//延迟1s
	}
}
