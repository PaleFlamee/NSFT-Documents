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
#define LED 13
#define KEY 2
#define Buzzer 3

int KEY_NUM = 0;			//按键键值变量

void setup()
{
  pinMode(LED,OUTPUT);			//LED为IO输出
  pinMode(KEY,INPUT_PULLUP);//按键为IO带上拉输入
  pinMode(Buzzer,OUTPUT);		//蜂鸣器为IO输出
  digitalWrite(Buzzer,LOW);	//蜂鸣器初始为不鸣叫
}

void loop()
{
  ScanKey();							//按键扫描
  if(KEY_NUM == 1)				//当有按键按下时
  {   
    digitalWrite(LED,!digitalRead(LED));	//LED状态翻转
  }
}

void ScanKey()
{
  KEY_NUM = 0;
  if(digitalRead(KEY) == LOW)
  {
    delay(20);							//延时去抖动
    if(digitalRead(KEY) == LOW)
    {
      BuzzerDi();					//滴一声
      KEY_NUM = 1;				//设置键值
      while(digitalRead(KEY) == LOW);	//松手检测
    }
  }
}

void BuzzerDi()
{
  digitalWrite(Buzzer,HIGH);			//蜂鸣器响
  delay(20);											//延时20ms
  digitalWrite(Buzzer,LOW);				//蜂鸣器关闭
}
