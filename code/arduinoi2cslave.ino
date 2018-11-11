// SCL A5
// SDA A4
// A0~3 read analog input
// 共12个uint_8数据，高低位为一组数据，共有6组 20181022
#include <Wire.h>
uint8_t i2cData[13];//高低位一组
const int analogInPin0=A0;
const int analogInPin1=A1;
const int analogInPin2=A2;
const int analogInPin3=A3;
const int analogInPin4=A6;
const int analogInPin5=A7;
static int i=0;
void setup() {
  // put your setup code here, to run once:
  Wire.begin(0x08);
  pinMode(LED_BUILTIN, OUTPUT);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  Serial.begin(115200);
}
void receiveEvent(int howMany){
  while (1 < Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
  Serial.println("i am 0x08");
}
void requestEvent(){
  digitalWrite(LED_BUILTIN, HIGH);
  Wire.write(i2cData[i]);
  Serial.println(i2cData[i]);
  i++;
  if(i==12)i=0;
  digitalWrite(LED_BUILTIN, LOW);
}
void loop() {
  // put your main code here, to run repeatedly:
  if(i==0){
    uint16_t sensor0=analogRead(analogInPin0);
    uint16_t sensor1=analogRead(analogInPin1);
    uint16_t sensor2=analogRead(analogInPin2);
    uint16_t sensor3=analogRead(analogInPin3);
    uint16_t sensor4=analogRead(analogInPin4);
    uint16_t sensor5=analogRead(analogInPin5);
    i2cData[0]=(sensor0>>8)&0xff;
    i2cData[1]=(sensor0)&0xff;
    i2cData[2]=(sensor1>>8)&0xff;
    i2cData[3]=(sensor1)&0xff;
    i2cData[4]=(sensor2>>8)&0xff;
    i2cData[5]=(sensor2)&0xff;
    i2cData[6]=(sensor3>>8)&0xff;
    i2cData[7]=(sensor3)&0xff;
    i2cData[8]=(sensor4>>8)&0xff;
    i2cData[9]=(sensor4)&0xff;
    i2cData[10]=(sensor5>>8)&0xff;
    i2cData[11]=(sensor5)&0xff;
    i2cData[12]='\0';
  }
//   Wire.write((const uint8_t*)i2cData,13);
  delay(5);
}
