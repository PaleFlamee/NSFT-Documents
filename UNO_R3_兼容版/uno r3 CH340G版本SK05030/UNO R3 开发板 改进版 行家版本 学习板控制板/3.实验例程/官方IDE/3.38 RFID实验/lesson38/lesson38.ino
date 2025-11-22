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
#include "RC522.h"
#include <SPI.h>

#define Relay 2

//4 bytes Serial number of card, the 5 bytes is verfiy bytes
unsigned char serNum[5];


void setup() 
{ 
    Serial.begin(9600); 
    Serial.print("Ilovemcu.taobao.com");
    pinMode(Relay,OUTPUT);
    SPI.begin();   
    pinMode(chipSelectPin,OUTPUT); // Set digital pin 10 as OUTPUT to connect it to the RFID /ENABLE pin 
    digitalWrite(chipSelectPin, LOW); // Activate the RFID reader
    pinMode(NRSTPD,OUTPUT); // Set digital Reset , Not Reset and Power-down
    
    MFRC522_Init();						//初始化RFID
}


void loop()
{
    unsigned char status;
    unsigned char str[MAX_LEN];
    
    // Search card, return card types
    status = MFRC522_Request(PICC_REQIDL, str); 
    if (status == MI_OK)			//读取到ID卡时候
    {   
		// Show card type
		//ShowCardType(str);
    
		//Prevent conflict, return the 4 bytes Serial number of the card
		status = MFRC522_Anticoll(str);
    
		// str[0..3]: serial number of the card
		// str[4]: XOR checksum of the SN.
		if (status == MI_OK)
		{
			memcpy(serNum, str, 5);
			Serial.print("ID:");
			ShowCardID(serNum);
    
			// Check people associated with card ID
			unsigned char* id = serNum;
			if( id[0]==0xed && id[1]==0x34 && id[2]==0xfa && id[3]==0x95 ) 
			{
				digitalWrite(Relay,HIGH);		//打开继电器
                                Serial.println("The Host 1!");
			} 
			else if(id[0]==0x4C && id[1]==0xB3 && id[2]==0x74 && id[3]==0x19) 
			{
				digitalWrite(Relay,LOW);		//继电器
                                Serial.println("The Host 2!");
			}
                        else
                        {
                                Serial.println("Stranger!");
                        }
			
		}
		
    }
   
    MFRC522_Halt(); //command the card into sleep mode 
    delay(100);
}
