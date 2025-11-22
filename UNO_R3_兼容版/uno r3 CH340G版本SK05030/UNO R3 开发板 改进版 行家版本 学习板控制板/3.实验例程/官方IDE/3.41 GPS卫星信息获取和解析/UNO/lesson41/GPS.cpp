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
#include "GPS.h"

//****************************************************
//UTC日期与当地日期转换
//****************************************************
void GPS_UBLOX::UTCDate2LocalDate(void)
{
	unsigned char MaxDay;
	Beijing_Day = UTC_Day + 1;		//日  加一
	
	MaxDay = GetMaxDay(Beijing_Month,Beijing_Year);				//获取当月 天数 最大值
	if(Beijing_Day > MaxDay)		//溢出
	{
		Beijing_Day = 1;
		Beijing_Month += 1;
		if(Beijing_Month > 12)
		{
			Beijing_Year+=1;
		}
	}		
}

//****************************************************
//UTC时间与当地时间转换
//****************************************************
void GPS_UBLOX::UTCTime2LocalTime(void)
{
	unsigned char MaxDay;
	Beijing_Min = UTC_Min;
	Beijing_Sec = UTC_Sec;
	Beijing_Hour = UTC_Hour + 8;

	Beijing_Year = UTC_Year + 2000;
	Beijing_Month = UTC_Month;
	Beijing_Day = UTC_Day;

	if(Beijing_Hour >= 24)
	{
		Beijing_Hour %= 24;
		UTCDate2LocalDate();
	}
}

//****************************************************
//获取当月日期最大值
//****************************************************
unsigned char GPS_UBLOX::GetMaxDay(unsigned char Month_Value,unsigned int Year_Value)
{
	unsigned char iDays;
	switch(Month_Value)
	{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			{
				iDays = 31;
			}
			break;
		case 2:
			{
				//2月份比较特殊，需要根据是不是闰年来判断当月是28天还29天
				iDays = IsLeapYear(Year_Value)?29:28;
			}
			break;
		case 4:
		case 6:
		case 9:
		case 11:
			{
				iDays = 30;
			}
			break;
		default : break;
	}
	return(iDays);						
}

//****************************************************
//闰年检测
//****************************************************
bool GPS_UBLOX::IsLeapYear(unsigned int uiYear)
{
	return (((uiYear%4)==0)&&((uiYear%100)!=0))||((uiYear%400)==0);
}


//********************************************************
//获取GPS信息
//********************************************************
void GPS_UBLOX::Get_GPS()
{
	unsigned char i = 0;
	while(Serial.available() > 0) 
	{		
		Uart_Buffer = Serial.read();	//获取GPS信息
		Serial.write(Uart_Buffer);			//测试使用

		if(Uart_Buffer == '$')
		{
			RX_Count = 0;
			//Flag_GPS_OK = 0;
		}
		
		if(RX_Count < 6)
		{
			GPS_COM[RX_Count++] = Uart_Buffer;
		}
		else if( GPS_COM[0] == '$' && GPS_COM[1] == 'G'&& GPS_COM[2] == 'P'&& GPS_COM[3] == 'G'&& GPS_COM[4] == 'G'&& GPS_COM[5] == 'A' )	//获取GPGGA数据
		{
			RX_GPGGA_Buffer[RX_Count] = Uart_Buffer;
			if(RX_GPGGA_Buffer[RX_Count] == '\n')
			{
				Flag_GPGGA_OK = 1;
				
			}
			else
			{
				RX_Count++;
			}			
		}
		else if( GPS_COM[0] == '$' && GPS_COM[1] == 'G'&& GPS_COM[2] == 'P'&& GPS_COM[3] == 'R'&& GPS_COM[4] == 'M'&& GPS_COM[5] == 'C' )	//获取GPRMC数据
		{
			RX_GPRMC_Buffer[RX_Count] = Uart_Buffer;
			if(RX_GPRMC_Buffer[RX_Count] == '\n')
			{
				Flag_GPRMC_OK = 1;
				
			}
			else
			{
				RX_Count++;
			}			
		}
		else if( GPS_COM[0] == '$' && GPS_COM[1] == 'G'&& GPS_COM[2] == 'P'&& GPS_COM[3] == 'G'&& GPS_COM[4] == 'L'&& GPS_COM[5] == 'L' )	//获取GPGLL数据
		{
			if(Uart_Buffer == '\n')
			{
				Flag_GPS_OK = 1;							//一组数据都是最后一帧是GPGLL，接收完GPGLL说明接收数据完成		
			}
		}
		

	}

	if(Flag_GPS_OK == 1)
	{
		Flag_GPS_OK = 0;
		Serial.print("**************************************************\n");
		if(Flag_GPGGA_OK == 1)
		{
			Serial.print("UTC_Time:");
			Flag_GPGGA_OK = 0;

			UTC_Hour = (RX_GPGGA_Buffer[7]-0x30)*10+(RX_GPGGA_Buffer[8]-0x30);			//获取UTC时间
			UTC_Min = (RX_GPGGA_Buffer[9]-0x30)*10+(RX_GPGGA_Buffer[10]-0x30);
			UTC_Sec = (RX_GPGGA_Buffer[11]-0x30)*10+(RX_GPGGA_Buffer[12]-0x30);

			Serial.print(UTC_Hour);
			Serial.print(':');
			Serial.print(UTC_Min);
			Serial.print(':');
			Serial.print(UTC_Sec);
			Serial.print("\n");

			Serial.print("Altitude: ");					//海拔
			for(i = 0 ; i < 4 ; i++)
			{
				Altitude[i]=RX_GPGGA_Buffer[54+i];
				Serial.print(Altitude[i]);
			}
			Serial.print(" m");
			Serial.print("\n");

		}

		if(Flag_GPRMC_OK == 1)
		{
			Serial.print("UTC_Date:");
			Flag_GPRMC_OK = 0;

			UTC_Year = (RX_GPRMC_Buffer[57]-0x30)*10+(RX_GPRMC_Buffer[58]-0x30);			//获取UTC日期
			UTC_Month = (RX_GPRMC_Buffer[55]-0x30)*10+(RX_GPRMC_Buffer[56]-0x30);
			UTC_Day = (RX_GPRMC_Buffer[53]-0x30)*10+(RX_GPRMC_Buffer[54]-0x30);

			Serial.print("20");
			Serial.print(UTC_Year);
			Serial.print('-');
			Serial.print(UTC_Month);
			Serial.print('-');
			Serial.print(UTC_Day);			
			Serial.print("\n");

			Serial.print("Latitude: ");
			Latitude_N_or_S = RX_GPRMC_Buffer[30];					//纬度
			Serial.print(Latitude_N_or_S);
			Serial.print(" ");
			for(i = 0;i<10;i++)
			{
				Latitude[i]=RX_GPRMC_Buffer[19+i];
				Serial.print(Latitude[i]);
			}
			Serial.print("\n");



			Serial.print("Longitude: ");
			Longitude_E_or_W = RX_GPRMC_Buffer[44];					//经度
			Serial.print(Longitude_E_or_W);
			Serial.print(" ");
			for(i = 0;i<11;i++)
			{
				Longitude[i]=RX_GPRMC_Buffer[32+i];
				Serial.print(Longitude[i]);
			}
			Serial.print("\n");

							
			Serial.print("Speed: ");	//速度
			for(i=0;i<5;i++)
			{
				Speed[i]=RX_GPRMC_Buffer[46+i];
				Serial.print(Speed[i]);
			}
			Serial.print("\n");			
		}

		UTCTime2LocalTime();

		Serial.print("Beijing_Time:");
		Serial.print(Beijing_Hour);
		Serial.print(':');
		Serial.print(Beijing_Min);
		Serial.print(':');
		Serial.print(Beijing_Sec);
		Serial.print("\n");

		Serial.print("Beijing_Date:");
		Serial.print(Beijing_Year);
		Serial.print('-');
		Serial.print(Beijing_Month);
		Serial.print('-');
		Serial.print(Beijing_Day);			
		Serial.print("\n");
		Serial.print("**************************************************\n");
		Serial.print("\n");

	}
}

//********************************************************
//初始化GPS用到的变量
//********************************************************
void GPS_UBLOX::Init_GPS()
{
	Flag_GPGGA_OK = 0;
	RX_Count = 0;
	Uart_Buffer = 0;
}
