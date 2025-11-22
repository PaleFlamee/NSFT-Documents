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
#ifndef	__GPS__H__
#define __GPS__H__

#include <Arduino.h>



class GPS_UBLOX
{
public:
	void Init_GPS();							//初始化GPS数据
	void Get_GPS();								//获取GPS数据并串口显示
	bool IsLeapYear(unsigned int uiYear);		//是否闰年
	unsigned char GetMaxDay(unsigned char Month_Value,unsigned int Year_Value);		//获得当月最大天数
	void UTCDate2LocalDate(void);				//UTC日期转换为北京日期
	void UTCTime2LocalTime(void);				//UTC时间转换为北京时间


	unsigned int UTC_Year;
	unsigned char UTC_Month;
	unsigned char UTC_Day;
	unsigned char UTC_Hour;
	unsigned char UTC_Min;
	unsigned char UTC_Sec;

	unsigned int Beijing_Year;
	unsigned char Beijing_Month;
	unsigned char Beijing_Day;
	unsigned char Beijing_Hour;
	unsigned char Beijing_Min;
	unsigned char Beijing_Sec;

	char Latitude[10];
	char Latitude_N_or_S;

	char Longitude[11];
	char Longitude_E_or_W;

	char Altitude[4];

	char Speed[5];

private:
	char Uart_Buffer;
	char GPS_COM[6];			//存放当前GPS指令名称,例如：$GPGGA
	char RX_GPGGA_Buffer[80];
	char RX_GPRMC_Buffer[80];
	
	unsigned char RX_Count;
	bool Flag_GPGGA_OK;
	bool Flag_GPRMC_OK;
	bool Flag_GPS_OK;
};






#endif
