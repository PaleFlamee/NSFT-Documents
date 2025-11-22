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
#define H1 2
#define H2 7 
#define H3 A5
#define H4 5
#define H5 13
#define H6 A4
#define H7 12
#define H8 A2

#define L1 6
#define L2 11
#define L3 10
#define L4 3
#define L5 A3
#define L6 4
#define L7 8
#define L8 9

unsigned char table1[8][8] = 			//大“心型”的数据
{
  0,0,0,0,0,0,0,0,
  0,1,1,0,0,1,1,0,
  1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,
  0,1,1,1,1,1,1,0,
  0,0,1,1,1,1,0,0,
  0,0,0,1,1,0,0,0,
};

unsigned char table2[8][8] = 			//小“心型”的数据
{
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,1,0,0,1,0,0,
  0,1,1,1,1,1,1,0,
  0,1,1,1,1,1,1,0,
  0,0,1,1,1,1,0,0,
  0,0,0,1,1,0,0,0,
  0,0,0,0,0,0,0,0,
};

void setup()
{
  pinMode(H1,OUTPUT);
  pinMode(H2,OUTPUT);
  pinMode(H3,OUTPUT);
  pinMode(H4,OUTPUT);
  pinMode(H5,OUTPUT);
  pinMode(H6,OUTPUT);
  pinMode(H7,OUTPUT);
  pinMode(H8,OUTPUT);
  
  pinMode(L1,OUTPUT);
  pinMode(L2,OUTPUT);
  pinMode(L3,OUTPUT);
  pinMode(L4,OUTPUT);
  pinMode(L5,OUTPUT);
  pinMode(L6,OUTPUT);
  pinMode(L7,OUTPUT);
  pinMode(L8,OUTPUT);
}

void loop()
{
  for(int i = 0 ; i < 100 ; i++)				//循环显示100次
  {
    Display(table1);										//显示大”心形“
  }
  for(int i = 0 ; i < 50 ; i++)					//循环显示50次
  {		
    Display(table2);										//显示小“心形”
  }
}

void Display(unsigned char dat[8][8])		//显示函数
{
  digitalWrite(L1,LOW);									//选通第一列
  digitalWrite(H1,dat[0][0]);
  digitalWrite(H2,dat[1][0]);
  digitalWrite(H3,dat[2][0]);
  digitalWrite(H4,dat[3][0]);
  digitalWrite(H5,dat[4][0]);
  digitalWrite(H6,dat[5][0]);
  digitalWrite(H7,dat[6][0]);
  digitalWrite(H8,dat[7][0]); 
  delay(1);	//延时一小段时间，等待LED被点亮
  Clear();	//清空显示去除余晖
  
  digitalWrite(L2,LOW);									//选通第二列
  digitalWrite(H1,dat[0][1]);
  digitalWrite(H2,dat[1][1]);
  digitalWrite(H3,dat[2][1]);
  digitalWrite(H4,dat[3][1]);
  digitalWrite(H5,dat[4][1]);
  digitalWrite(H6,dat[5][1]);
  digitalWrite(H7,dat[6][1]);
  digitalWrite(H8,dat[7][1]);
  delay(1);
  Clear();
  
  digitalWrite(L3,LOW);									//选通第三列
  digitalWrite(H1,dat[0][2]);
  digitalWrite(H2,dat[1][2]);
  digitalWrite(H3,dat[2][2]);
  digitalWrite(H4,dat[3][2]);
  digitalWrite(H5,dat[4][2]);
  digitalWrite(H6,dat[5][2]);
  digitalWrite(H7,dat[6][2]);
  digitalWrite(H8,dat[7][2]);
  delay(1);
  Clear();
  
  digitalWrite(L4,LOW);									//选通第四列
  digitalWrite(H1,dat[0][3]);
  digitalWrite(H2,dat[1][3]);
  digitalWrite(H3,dat[2][3]);
  digitalWrite(H4,dat[3][3]);
  digitalWrite(H5,dat[4][3]);
  digitalWrite(H6,dat[5][3]);
  digitalWrite(H7,dat[6][3]);
  digitalWrite(H8,dat[7][3]);
  delay(1);
  Clear();
  
  digitalWrite(L5,LOW);									//选通第五列
  digitalWrite(H1,dat[0][4]);
  digitalWrite(H2,dat[1][4]);
  digitalWrite(H3,dat[2][4]);
  digitalWrite(H4,dat[3][4]);
  digitalWrite(H5,dat[4][4]);
  digitalWrite(H6,dat[5][4]);
  digitalWrite(H7,dat[6][4]);
  digitalWrite(H8,dat[7][4]);
  delay(1);
  Clear();
  
  digitalWrite(L6,LOW);									//选通第六列
  digitalWrite(H1,dat[0][5]);
  digitalWrite(H2,dat[1][5]);
  digitalWrite(H3,dat[2][5]);
  digitalWrite(H4,dat[3][5]);
  digitalWrite(H5,dat[4][5]);
  digitalWrite(H6,dat[5][5]);
  digitalWrite(H7,dat[6][5]);
  digitalWrite(H8,dat[7][5]);
  delay(1);
  Clear();
  
  digitalWrite(L7,LOW);									//选通第七列
  digitalWrite(H1,dat[0][6]);
  digitalWrite(H2,dat[1][6]);
  digitalWrite(H3,dat[2][6]);
  digitalWrite(H4,dat[3][6]);
  digitalWrite(H5,dat[4][6]);
  digitalWrite(H6,dat[5][6]);
  digitalWrite(H7,dat[6][6]);
  digitalWrite(H8,dat[7][6]);
  delay(1);
  Clear();
  
  digitalWrite(L8,LOW);									//选通第八列
  digitalWrite(H1,dat[0][7]);
  digitalWrite(H2,dat[1][7]);
  digitalWrite(H3,dat[2][7]);
  digitalWrite(H4,dat[3][7]);
  digitalWrite(H5,dat[4][7]);
  digitalWrite(H6,dat[5][7]);
  digitalWrite(H7,dat[6][7]);
  digitalWrite(H8,dat[7][7]);
  delay(1);  
  Clear();
}

void Clear()													//清空显示
{
  digitalWrite(H1,LOW);
  digitalWrite(H2,LOW);
  digitalWrite(H3,LOW);
  digitalWrite(H4,LOW);
  digitalWrite(H5,LOW);
  digitalWrite(H6,LOW);
  digitalWrite(H7,LOW);
  digitalWrite(H8,LOW);
  
  digitalWrite(L1,HIGH);
  digitalWrite(L2,HIGH);
  digitalWrite(L3,HIGH);
  digitalWrite(L4,HIGH);
  digitalWrite(L5,HIGH);
  digitalWrite(L6,HIGH);
  digitalWrite(L7,HIGH);
  digitalWrite(L8,HIGH);
}

