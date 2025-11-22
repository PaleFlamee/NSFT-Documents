/******************************************************************************
----------------本例程仅供学习使用，未经作者允许，不得用于其他用途。-----------
------------------------版权所有，仿冒必究！-----------------------------------
----------------1.开发环境:Arduino IDE,代码仅适合windows电脑-------------------
----------------2.测试使用开发板型号：Arduino Leonardo-------------------------
----------------3.单片机使用晶振：16M------------------------------------------
----------------4.淘宝网址：Ilovemcu.taobao.com--------------------------------
----------------------------epic-mcu.taobao.com--------------------------------
----------------5.作者：神秘藏宝室---------------------------------------------
******************************************************************************/
#define KEY1 2			//向左按键
#define KEY2 3			//向右按键

int Flag_up = 1;

void setup() 
{
  pinMode(KEY1, INPUT_PULLUP);
  pinMode(KEY2, INPUT_PULLUP);
  Keyboard.begin();
}
 
void loop() 
{
  if( ScanKey(1) == 1)			//向左按键按下
  {
    Keyboard.press(KEY_LEFT_ARROW);		//向电脑发送向左按键按下的指令
    delay(50);		
    Keyboard.releaseAll();						//向电脑发送按键释放的指令
  }
  else if(ScanKey(1) == 2)	//向右按键按下
  {
    Keyboard.press(KEY_RIGHT_ARROW);	//向电脑发送向右按键按下的指令
    delay(50);
    Keyboard.releaseAll();						//向电脑发送按键释放的指令
  }
}

unsigned char ScanKey(int mode)			//按键扫描程序，返回键值
{
  if(mode)							//mode = 1时候，该代码支持长按。mode = 0时候，不支持长按
  {
    Flag_up = 1;
  }
  
  if(Flag_up  && (digitalRead(KEY1) == LOW || digitalRead(KEY2) == LOW) )		//当Flag_up = 1并且按键按下时
  {
    Flag_up = 0;										//清空Flag_up
    delay(10);											//延时去抖动
    if(digitalRead(KEY1) == LOW)			//按键按下
    {
      return 1;											//返回键值1
    }
    if(digitalRead(KEY2) == LOW)			//按键按下
    {
      return 2;											//返回键值1
    }
  }
  if(digitalRead(KEY1) == HIGH && digitalRead(KEY2) == HIGH)			//按键松开时候
  {
    Flag_up = 1;										//置位Flag_up
  }
  return 0;													//返回键值0
}








