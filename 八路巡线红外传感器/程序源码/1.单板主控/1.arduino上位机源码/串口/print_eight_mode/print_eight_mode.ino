#include <stdio.h>
#include "IReight_model.hpp"



extern uint8_t g_new_package_flag ;
void setup()
{
    serial_init();//串口初始化
    //等待模块正常 
    SET_Eight_Mode(0,0,1);//设置只接收数值型数据


}



void loop() 
{
  //主要处理在串口中断
  recv_data(); //接收
  if(g_new_package_flag ==1)
  {
    g_new_package_flag = 0; 
    Deal_Usart_Data();//数据解析
   }
}


