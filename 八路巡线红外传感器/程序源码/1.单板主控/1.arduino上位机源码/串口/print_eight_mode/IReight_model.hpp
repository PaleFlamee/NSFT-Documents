#ifndef __IREIGHT_MODEL_H
#define __IREIGHT_MODEL_H


#include <stdio.h>
#include <string.h>
#include <Arduino.h>

#ifdef __cplusplus
extern "C" {
#endif


#define IR_Num 			8
extern uint8_t IR_Data_number[];
extern uint16_t IR_Data_Anglo[];
extern uint8_t g_Amode_Data ;//模拟型标志
extern uint8_t g_Dmode_Data ;//数字型标志
extern uint8_t g_new_package_flag;//接收到新的数据处理

void serial_init(void);
void recv_data(void);

void SET_Eight_Mode(uint8_t adjust,uint8_t ao,uint8_t num);
void Data_Deal(char RXdata);

void Deal_Usart_Data(void);
void Deal_Usart_AData(void);
void splitString(char* mystrArray[],char *str, const char *delimiter) ;

#ifdef __cplusplus
}
#endif

#endif

