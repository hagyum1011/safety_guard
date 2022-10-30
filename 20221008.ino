/*
 제목 : 2023학년도 디미고 자기추천 실적물
        우회전 차량 사고방지를 위한 신호표시 장치
 작성자 : 정천중학교 3학년 김하겸
 개발기간 : 2022.06.30~2022.09.30
 하드웨어 : MCU(아두이노 나노), LCD, IR센서, BUZ, LED*9
 */


#include <SimpleTimer.h>
#include <Wire.h>
#include "func.h"


void setup(){
    lcd.begin();
    lcd.backlight();
    pinMode (Irpin,INPUT);
    pinMode (P1_RED_LED,OUTPUT);
    pinMode (P1_GREEN_LED,OUTPUT);
    pinMode (P2_RED_LED,OUTPUT);
    pinMode (P2_GREEN_LED,OUTPUT);
    pinMode (C1_RED_LED,OUTPUT);
    pinMode (C1_YELLOW_LED,OUTPUT);
    pinMode (C1_GREEN_LED,OUTPUT);
    pinMode (BUZ,OUTPUT);
    _timerP1_G.setInterval(18000,P1_GreenOn);
    _timerP1_R.setInterval(18000,P1_RedOff);
    _timerP2_G.setInterval(20000,P2_GreenOn);
    _timerP2_R.setInterval(20000,P2_RedOff);
    _timerC1_Y.setInterval(20000,C1_YellowOn);
    P1_RedOff();
    P1_GreenOn();
    P2_RedOff();
    P2_GreenOn();
    Serial.begin(9600);
}


void loop(){
    _timerP1_G.run();
    _timerP1_R.run();
    _timerP2_G.run();
    _timerP2_R.run();

    if (P1_R==1 && P2_R==1){
        boolean irdata=digitalRead(Irpin);
        if (irdata==0){
            lcd.setCursor(0,0);lcd.print("     STOP"); 
            BuzSound(3);
        }
        else {
            lcd.setCursor(0,0);lcd.print("       GO");
        }
    }
    else if (P2_G==1){
        lcd.setCursor(0,0);lcd.print("     STOP");
    }
    else if (P1_G==1 && P2_R==1){
        boolean irdata=digitalRead(Irpin);
        if (irdata==0){
            lcd.setCursor(0,0);lcd.print("     STOP"); 
            BuzSound(3);
        }
        else {
            lcd.setCursor(0,0);lcd.print("SLOWLY GO");
        }
    } 
}




