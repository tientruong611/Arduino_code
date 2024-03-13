#include <Wire.h>
#include <LiquidCrystal_I2C.h>
const int trig = 8;     // chân trig của HC-SR04
const int echo = 7;     // chân echo của HC-SR04
int led = 13;
LiquidCrystal_I2C lcd(0x27, 16, 2);  //SCL 21 SDA 20
void setup()
{
    lcd.init();
    lcd.backlight();
    Serial.begin(9600);     // giao tiếp Serial với baudrate 9600
    pinMode(trig,OUTPUT);   // chân trig sẽ phát tín hiệu
    pinMode(echo,INPUT);    // chân echo sẽ nhận tín hiệu
    pinMode(led, OUTPUT);

}
 
void loop()
{
    unsigned long duration; // biến đo thời gian
    int distance;           // biến lưu khoảng cách
    
    /* Phát xung từ chân trig */
    digitalWrite(trig,0);   // tắt chân trig
    delayMicroseconds(2);
    digitalWrite(trig,1);   // phát xung từ chân trig
    delayMicroseconds(5);   // xung có độ dài 5 microSeconds
    digitalWrite(trig,0);   // tắt chân trig
    
    /* Tính toán thời gian */
    // Đo độ rộng xung HIGH ở chân echo. 
    duration = pulseIn(echo,HIGH);  
    // Tính khoảng cách đến vật.
    distance = int(duration/2/29.412);
    
    /* In kết quả ra Serial Monitor */
    if(distance>=20)
    {
      lcd.setCursor(0,0);
      lcd.print(" khoang cach la ");
    }
    lcd.setCursor(0,1);
    lcd.print("Don vi Cm:");
    lcd.setCursor(11,1);
    lcd.print(distance);
    Serial.print(distance);
    Serial.println("cm");
    if(distance <10)
    {
      lcd.setCursor(12,1);      
      lcd.print(" ");
      lcd.setCursor(13,1);      
      lcd.print(" ");
    }
    if(distance<20)
    {
      lcd.setCursor(0,0);      
      lcd.print("Canh Bao Va Cham");
      digitalWrite(led,HIGH);  
    }
    else {
    digitalWrite(led,LOW);
    }

}