#include "IReight_model.hpp"
#include <stdio.h>
#include <SoftwareSerial.h>


#define  printSerial Serial  //printSerial

SoftwareSerial IRMODELSerial(2, 3); //rx2 tx3 IRMODELSerial

#define Package_size 100

char send_buf[35]={0}; //发送命令的buf

uint8_t rx_buff[Package_size];
uint8_t new_package[Package_size];
uint8_t g_new_package_flag = 0;//接收到新的一包数据标志

uint8_t IR_Data_number[IR_Num];//数字值
uint16_t IR_Data_Anglo[IR_Num];//模拟值
uint8_t g_Amode_Data = 0;//模拟型标志
uint8_t g_Dmode_Data = 0;//数字型标志

void serial_init(void)
{
  IRMODELSerial.begin(115200);
  printSerial.begin(115200);

}

void recv_data(void)
{
    char strr;
    if (IRMODELSerial.available()) 
    {
      strr = char(IRMODELSerial.read());
      Data_Deal(strr);
     }
  
}

//设置接收的数据模式
void SET_Eight_Mode(uint8_t adjust,uint8_t ao,uint8_t num)
{
  //$0,0,1# 只接收数字型数据
  sprintf(send_buf,"$%d,%d,%d#",adjust,ao,num);
  IRMODELSerial.print(send_buf);
  memset(send_buf,0,sizeof(send_buf));
  delay(300);  
}


uint8_t end_falg = 0;
uint8_t i_index= 0; //数组索引

//处理串口接收到的信息
void Data_Deal(char rxtemp)
{
  static u8 g_start = 0;
  static u8 step = 0;
  if(rxtemp == '$')
  {  
    g_start = 1;//开始接收标志
    rx_buff[step] = rxtemp;
    step++;
  }
  else
  {
    if(g_start == 0)
    {
      return;
    }
    else
    {
      rx_buff[step] = rxtemp;
      step ++;
      if(rxtemp == '#')//结束
      {
        g_start = 0;
        step = 0;
        memcpy(new_package,rx_buff,Package_size);//赋值
        g_new_package_flag = 1;
        memset(rx_buff,0,Package_size);//清空数据

      }
      
      if(step >= Package_size)//数据异常
      {
        g_start = 0;
        step = 0;
        memset(rx_buff,0,Package_size);//清空数据
      }
    }
  }
}



//数据例子：$D,x1:0,x2:0,x3:0,x4:0,x5:0,x6:0,x7:0,x8:0#
void Deal_Usart_Data(void) //处理数字型数据
{
	if(new_package[1]!='D')
	{
		return; //此包数据不是数字型数据
	}
	for(u8 i = 0;i<IR_Num;i++)
	{
		IR_Data_number[i] = (new_package[6+i*5]-'0');//把字符转成数字 //6 11 16 21 26 
	}

  sprintf(send_buf,"x1:%d\t x2:%d\t x3:%d\t x4:%d\t x5:%d\t x6:%d\t x7:%d\t x8:%d\t \r\n",IR_Data_number[0],IR_Data_number[1],IR_Data_number[2],IR_Data_number[3],IR_Data_number[4],IR_Data_number[5],IR_Data_number[6],IR_Data_number[7]);
  printSerial.println(send_buf); 
	memset(new_package,0,Package_size);//清除旧数据
  
}





//---------------------------模拟值处理相关的---------------------------

//传入参数：保留的字符串(指针数组)  原始字符串  分隔符号
void splitString(char* mystrArray[],char *str, const char *delimiter) 
{
    char *token = strtok(str, delimiter); //这是第一次分割,不会保留第一个字符值
    int i =0;
    while (token != NULL) 
    {
        token = strtok(NULL, delimiter);
        mystrArray[i] = token;
        i++;
    }
}

void Deal_Usart_AData(void) //处理模拟值数据
{
	//$A,x1:1000,x2:3450,x3:40,x4:450,x5:110,x6:4096,x7:780,x8:80#
	
	char* strArray[10];//指针数组 长度根据分割号定义  char 1字节   char* 4字节
	char* strArraytemp[2];
	char str_temp[Package_size] = {'\0'};
	char mystr_temp[8][10] = {'\0'}; //临时备份
	
	
	if(new_package[1]!='A')
	{
		return; //此包数据不是模拟值数据
	}
	strncpy(str_temp,(char*)new_package,strlen((char*)new_package)-1);
	
	splitString(strArray,str_temp, ", ");//以逗号切割
	
	 //遍历数组
    for (int i = 0; i < IR_Num; i++)
    {
    	  strcpy(mystr_temp[i],strArray[i]);
    	  splitString(strArraytemp,mystr_temp[i], ": ");
				IR_Data_Anglo[i] = atoi(strArraytemp[0]);
    }
		memset(new_package,0,Package_size);//清除旧数据
		
		memset(strArray,0,sizeof(strArray)); //数组指针清0
		memset(strArraytemp,0,sizeof(strArraytemp));//数组指针清0
  
}




