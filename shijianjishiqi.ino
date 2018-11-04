#include <Wire.h>
#include <RTClib.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
void printDateTime(DateTime dateTime);
int Y=18;
int M=10;
int D=04;
int H=11;
int F=12;
int S=00;
int x=00;
int y=00;
int z=00;
int m=00;
int n=00;
#define BUTTON 12    //定义按钮开关引脚为12

int val = 0;        //变量val用来储存按钮状态

int old_val = 0;    //暂存val变量的上一个时间单位

int state = 0;       //0
//创建实例
RTC_DS1307 RTC;

const int buttonPin2 = 9;   
const int buttonPin3 = 10; 

int buttonState1= 0; 
int buttonState2= 0; 
int buttonState3= 0;     
void setup (void){
  pinMode (BUTTON,INPUT); 

pinMode(buttonPin2, INPUT);
pinMode(buttonPin3, INPUT);
   Serial.begin(9600);
   //初始化总线
   Wire.begin();
   //初始化实时时钟
   RTC.begin(); 
   lcd.init();                      // initialize the lcd

  // Print a message to the LCD.
  lcd.backlight();

}

void loop() {
  val = digitalRead(BUTTON); //读取按钮状态并储存
  if (val==0){
    z=z+1;
    if(z>4){
      z=1;
    }
  }
  buttonState2 = digitalRead(buttonPin2);
  buttonState3 = digitalRead(buttonPin3);
  if((val == HIGH)&&(old_val == LOW)){

    state =1-state;

    delay(40);              //延时简单抗抖动

  }

  old_val = val;            //val下载已经是旧的了，让我们暂存一下
  DateTime now = RTC.now();
       //通过串口传送当前的日期和时间      
       printDateTime(now);
       delay(100);
       
   if (Serial.available() > 0) {

    int instruct = Serial.read();

    switch (instruct) {
      
     case 'S':
       RTC.set(RTC_YEAR,18);  //设置成17年
       RTC.set(RTC_MONTH, M);  //设置成4月
       RTC.set(RTC_DAY, D);  //设置成18日
       RTC.set(RTC_HOUR, H);  //设置成9时
       RTC.set(RTC_MINUTE, F);  //设置成39分
       RTC.set(RTC_SECOND, S);  //设置成01秒
       break;
     }
   }
   
}

void printDateTime(DateTime dateTime) {
     //传送年份
     Serial.print(dateTime.year(), DEC);
     Serial.print('/');
     //传送月份
     Serial.print(dateTime.month(), DEC);
     Serial.print('/');
     //传送月份中的第几天
     Serial.print(dateTime.day(), DEC);
     Serial.print(' ');
     //传送小时
     Serial.print(dateTime.hour(), DEC);
     Serial.print(':');
     //传送分钟
     Serial.print(dateTime.minute(), DEC);
     Serial.print(':');
     //传送秒
     Serial.print(dateTime.second(), DEC) ;Serial.print('/');Serial.print( x);Serial.print('/');Serial.print( y);Serial.print('/');Serial.print(state);Serial.print(z);Serial.print('/');Serial.print( buttonState2);Serial.print('/');Serial.print( buttonState3);
     Serial.println();
     buttonState1 = digitalRead(buttonPin2);
  buttonState2 = digitalRead(buttonPin2);
  buttonState3 = digitalRead(buttonPin3);
     if ((z == 1)&&(buttonState2==0))
       {
        x=x+1;
         delay(40); 
       }
       if ((z == 1)&&(buttonState3==0))
       {
        y=y+1;
         delay(40); 
       }
       if ((z == 2)&&( buttonState2==0))
       {
         x=x-1;
          delay(40); 
       }
       if ((z == 2 )&&(buttonState3==0))
       {
        y=y-1; delay(40); 
       }
      
     if (dateTime.hour()==x & dateTime.minute()==y){
       digitalWrite(6, HIGH);
     }
     else {

    digitalWrite(6, LOW);

  }
if ((z== 3)&&(buttonState2==0))
       {
        m=m+1;
         delay(40); 
       }
       if ((z==3)&&(buttonState3==0))
       {
        n=n+1;
         delay(40); 
       }
       if ((z == 4)&&( buttonState2==0))
       {
         m=m-1;
          delay(40); 
       }
       if ((z== 4 )&&(buttonState3==0))
       {
        n=n-1; delay(40); 
       }
      
     if (dateTime.hour()==m & dateTime.minute()==n){
       digitalWrite(6, HIGH);
     }
     else {

    digitalWrite(6, LOW);

  }

lcd.setCursor(2,0);
lcd.print(dateTime.month());
lcd.setCursor(4,0);
lcd.print("-");
lcd.setCursor(6,0);
lcd.print(dateTime.day());
lcd.setCursor(0,1);

lcd.print(dateTime.hour());
lcd.setCursor(2,1);
lcd.print(":");

lcd.setCursor(3,1);
lcd.print(dateTime.minute());
lcd.setCursor(5,1);
lcd.print(":");
lcd.setCursor(6,1);
lcd.print(dateTime.second());

lcd.setCursor(10,1);
lcd.print(x);
lcd.setCursor(12,1);
lcd.print(":");
lcd.setCursor(14,1);
lcd.print(y);
lcd.setCursor(10,0);
lcd.print(m);
lcd.setCursor(12,0);
lcd.print(":");
lcd.setCursor(14,0);
lcd.print(n);
}
