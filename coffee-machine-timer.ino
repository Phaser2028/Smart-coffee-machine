#include <LiquidCrystal.h>
#include <iarduino_RTC.h>                     
iarduino_RTC watch(RTC_DS1307);
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
#define BTN_UP   1
#define BTN_DOWN 2
#define BTN_LEFT 3
#define BTN_RIGHT 4
#define BTN_SELECT 5
#define BTN_NONE 10
#define PIN_RELAY 13
byte H=7,M=0;
byte p=1;
byte q=1;

uint8_t c_H,c_M;





int detectButton() {
  int keyAnalog =  analogRead(A0);
  if (keyAnalog < 100) {
    delay(300);
    return BTN_RIGHT;
  } else if (keyAnalog < 200) {
    delay(500);
    return BTN_UP;
  } else if (keyAnalog < 400) {
    delay(500);
    return BTN_DOWN;
  } else if (keyAnalog < 600) {
    delay(300);
    return BTN_LEFT;
  } else if (keyAnalog < 800) {
    delay(300);
    return BTN_SELECT;
  } else {
    // Все остальные значения (до 1023) будут означать, что нажатий не было
    return BTN_NONE;
  }
}


void hour_up(){
  ++H;
  if (H==25 ){ //|| или
    lcd.setCursor(1,0);
    lcd.print(" ");
    H=0;
      }
     
  lcd.setCursor(0,0);
  lcd.print(H);}
  
void hour_down(){
  if (H == 10){
    lcd.setCursor(1,0);
    lcd.print(" ");
    }
      --H;
  if (H==255){
    H=24;
    }
  lcd.setCursor(0,0);
  lcd.print(H);
    }
void minute_up(){
  ++M;
  if (M==61){
    lcd.setCursor(1,0);
    lcd.print(" ");
    M=0;
      }
     
  lcd.setCursor(0,0);
  lcd.print(H);   
  }
void minute_down(){
  if (M == 10){
    lcd.setCursor(1,0);
    lcd.print(" ");
    }
      --M;
  if (M==255){
    M=59;
    }
  lcd.setCursor(0,0);
  lcd.print(M);
 }  




void current_time(){
     watch.gettime();
     lcd.setCursor(0,0);
     lcd.print("current time:");
     lcd.setCursor(0,1);
     if ((watch.Hours / 10) <= 0){
      lcd.setCursor(0,1);
      lcd.print("0");
      lcd.setCursor(1,1);
      }
     lcd.print(watch.Hours);
     lcd.setCursor(2,1);
     lcd.print(":");
     lcd.setCursor(3,1);
     if ((watch.minutes / 10) <= 0){
      lcd.setCursor(3,1);
      lcd.print("0");
      lcd.setCursor(4,1);
      }
     lcd.print(watch.minutes);  
  }



void switch_on_time(){
     lcd.setCursor(0,0);
     lcd.print("switch-on time:");
     lcd.setCursor(0,1);
     if ((H / 10) <= 0){
     lcd.setCursor(0,1);
     lcd.print("0");
     lcd.setCursor(1,1);
      }
     lcd.print(H);
     lcd.setCursor(2,1);
     lcd.print(":");
     lcd.setCursor(3,1);
     if ((M / 10) <= 0){
      lcd.setCursor(3,1);
      lcd.print("0");
      lcd.setCursor(4,1);}
     lcd.print(M);
     //delay(5000);
     //lcd.clear();  
  }




void setup() {
  Serial.begin(9600);
  watch.begin();
  lcd.begin(16,2);
  pinMode(PIN_RELAY, OUTPUT); // Объявляем пин реле как выход
  digitalWrite(PIN_RELAY, HIGH); // Выключаем реле - посылаем высокий сигнал
  
}


void loop(){
  int button = detectButton();






  

  switch (button) {
    case BTN_UP:
    if (q%2==1){
     hour_up();}
    else{
      minute_up();
    }
      break;
    case BTN_DOWN:
    if (q%2==1){
     hour_down();}
    else{
      minute_down();
    }
      break;
    case BTN_LEFT:
      --q;

     
      break;
    case BTN_RIGHT:
       ++q;  

    
      break;
    case BTN_SELECT:
      lcd.clear();
      ++p;
      break;


      
     case BTN_NONE:
     if ((p%2)==1){
      current_time();
     }
     else{
      switch_on_time();
      
     }  
    break;
  }

    
       if(watch.Hours==H && watch.minutes==M && watch.seconds==0) {
         lcd.clear();
          lcd.print("rabotaet"); 
          digitalWrite(PIN_RELAY, LOW); 
         delay(900000);
         digitalWrite(PIN_RELAY, HIGH ); 
          lcd.clear();    

                                         
    }



  }














    
