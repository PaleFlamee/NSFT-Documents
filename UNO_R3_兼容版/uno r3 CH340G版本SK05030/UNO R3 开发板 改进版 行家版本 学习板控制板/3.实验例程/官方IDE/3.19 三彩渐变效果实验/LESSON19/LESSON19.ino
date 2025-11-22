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
#define LED_R 3
#define LED_G 5
#define LED_B 6

int PWMValue = 0;

void setup()
{
  analogWrite(LED_R,255);			//高电平255 = 占空比是100%，IO相当于输出高电平，红色LED熄灭
  analogWrite(LED_G,255);			//高电平255 = 占空比是100%，IO相当于输出高电平，绿色LED熄灭
  analogWrite(LED_B,255);			//高电平255 = 占空比是100%，IO相当于输出高电平，蓝色LED熄灭
}

void loop()
{
  int i = 0;
  PWMValue = 255;
  for(i = 0 ; i < 255 ; i++)		//红色逐渐变亮
  {
    analogWrite(LED_R,PWMValue--);
    analogWrite(LED_G,255);
    analogWrite(LED_B,255);
    delay(10);									
  }
  PWMValue = 0;
  for(i = 0 ; i < 255 ; i++)		//逐渐变暗
  {
    analogWrite(LED_R,PWMValue++);
    analogWrite(LED_G,255);
    analogWrite(LED_B,255);
    delay(10);
  }
  
   PWMValue = 255;
  for(i = 0 ; i < 255 ; i++)		//绿色逐渐变亮
  {
    analogWrite(LED_R,255);
    analogWrite(LED_G,PWMValue--);
    analogWrite(LED_B,255);
    delay(10);
  }
  PWMValue = 0;
  for(i = 0 ; i < 255 ; i++)		//逐渐变暗
  {
    analogWrite(LED_R,255);
    analogWrite(LED_G,PWMValue++);
    analogWrite(LED_B,255);
    delay(10);
  }
  
  PWMValue = 255;
  for(i = 0 ; i < 255 ; i++)		//蓝色逐渐变亮
  {
    analogWrite(LED_R,255);
    analogWrite(LED_G,255);
    analogWrite(LED_B,PWMValue--);
    delay(10);
  }
  PWMValue = 0;
  for(i = 0 ; i < 255 ; i++)		//逐渐变暗
  {
    analogWrite(LED_R,255);
    analogWrite(LED_G,255);
    analogWrite(LED_B,PWMValue++);
    delay(10);
  }
  
}
