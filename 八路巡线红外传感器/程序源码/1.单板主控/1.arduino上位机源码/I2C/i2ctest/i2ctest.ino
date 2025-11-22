#include <Wire.h>

void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(115200);  // start serial for output


 // 进入校准模式
  // Wire.beginTransmission(0x12); 
  // Wire.write(1);
  // Wire.write(1);
  // Wire.endTransmission();    // stop transmitting
  // delay(500);



}
uint8_t x1,x2,x3,x4,x5,x6,x7,x8;
char bufbuf[50]={'\0'};
void loop() {
  
 byte data = 0; // 用于存储读取的数据
 
  Wire.beginTransmission(0x12); // I2C设备的地址
  Wire.write(0x30); // 寄存器地址
  Wire.endTransmission();
 
  delay(10); // 给设备足够的时间来处理请求
 
  Wire.requestFrom(0x12, 1); // 请求1个字节的数据
  while (Wire.available()) {
    data = Wire.read(); // 读取数据
  }
 
  x1 = (data>>7)&0x01;
  x2 = (data>>6)&0x01;
  x3 = (data>>5)&0x01;
  x4 = (data>>4)&0x01;
  x5 = (data>>3)&0x01;
  x6 = (data>>2)&0x01;
  x7 = (data>>1)&0x01;
  x8 = (data>>0)&0x01;
  sprintf(bufbuf,"x1:%d,x2:%d,x3:%d,x4:%d,x5:%d,x6:%d,x7:%d,x8:%d\r\n",x1,x2,x3,x4,x5,x6,x7,x8);
  Serial.println(bufbuf);
  // Serial.println(data, HEX); // 在串行监视器上打印数据（十六进制）
  delay(500);


}

