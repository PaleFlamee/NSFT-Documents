#include <stdio.h>
#include <string.h>
#include <Arduino.h>

void setup() {
    Serial.begin(115200);  // start serial for output
    //定义引脚
    pinMode(2,INPUT);
    pinMode(3,INPUT);
    pinMode(4,INPUT);
    pinMode(5,INPUT);
    
    pinMode(6,INPUT);
    pinMode(7,INPUT);
    pinMode(8,INPUT);
    pinMode(9,INPUT);
 
}

uint8_t x1,x2,x3,x4,x5,x6,x7,x8;
char buf[50] = {'\0'};
void loop() {
  
    x1 = digitalRead(2);
    x2 = digitalRead(3);
    x3 = digitalRead(4);
    x4 = digitalRead(5);

    x5 = digitalRead(6);
    x6 = digitalRead(7);
    x7 = digitalRead(8);
    x8 = digitalRead(9);

    sprintf(buf,"x1:%d x2:%d x3:%d x4:%d x5:%d x6:%d x7:%d x8:%d",x1,x2,x3,x4,x5,x6,x7,x8);
    Serial.println(buf); 
   //delay(50);
}
