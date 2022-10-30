void P1_GreenBlk(); // P1_GREEN_LED 를 3초 간격으로 키고 끄는 것을 7번 반복
void P1_GreenOn();  // P1_GREEN_LED 를 키고 BuzSound 를 1회 실행하는 함수
void P1_GreenOff(); // P1_GREEN_LED 를 키고 1.5초 후에 끄는 함수 
void P1_RedOn();    // P1_RED_LED 를 키고 BuzSound 를 2회 실행하는 함수
void P1_RedOff();   // P1_RED_LED 를 끄는 함수
void BuzSound(int cnt);// buz 를 0.6초 간격으로 키고 끄는 함수
void P2_GreenOn();  // P2_GREEN_LED 와 C1_RED_LED 를 켜고 C1_YELLOW_LED 와 C1_GREEN_LED 를 끄고
                    // BuzSound를 1회 실행하는 함수
void P2_GreenBlk(); // P2_GREEN_LED 를 3초 간격으로 키고 끄는 것을 7번 반복하는 함수
void P2_GreenOff(); // P2_GREEN_LED 를 키고 1.5초 후에 끄고 C1_RED_LED 를 끄는 함수
void P2_RedOn();    // P2_RED_LED 와 C1_GREEN_LED 를 키고 C1_YELLOW_LED 를 끄고
                    // BuzSound 를 2회 실행하는 함수
void P2_RedOff();   // P2_RED_LED 를 끄는 함수
void C1_YellowOn(); // C1_GREEN_LED 를 끄고 C1_YELLOW_LED 를 켜는 함수



int P1_RED_LED=3;
int P1_GREEN_LED=4;
int P2_RED_LED=8;
int P2_GREEN_LED=9;
int C1_RED_LED=7;
int C1_YELLOW_LED=6;
int C1_GREEN_LED=5;
int P1_GreenOnTime=6000;
int P1_GreenBlkTime=300;
int P1_RedOffTime=8000;
int P2_GreenOnTime=7000;
int P2_GreenBlkTime=300;
int P2_RedOffTime=9100;
int BlkCount=7;
int Blkinterval=150;
int P1_G=0;
int P1_R=0;
int P2_G=0;
int P2_R=0;
int BUZ=A2;
int Irpin=2;
int i=0;

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3f, 16, 2);
SimpleTimer _timerP1_G; 
SimpleTimer _timerP1_R;
SimpleTimer _timerP2_G;
SimpleTimer _timerP2_R;
SimpleTimer _timerC1_Y;

/**********************************************************/
//BUZ 를 제어하는 함수
/*********************************************************/

void BuzSound(int cnt){
    for(int i=0;i<cnt;i++){
        digitalWrite (BUZ,HIGH); delay(60);
        digitalWrite (BUZ,LOW); delay(60);    
    }
}

/**********************************************************/
//P1_GREEN_LED 를 제어하는 함수
/*********************************************************/

void P1_GreenOn(){
    digitalWrite (P1_GREEN_LED,HIGH);
    _timerP1_G.setTimeout(6000,P1_GreenBlk);
    BuzSound(1);
}
 
void P1_GreenBlk(){
    _timerP1_G.setTimer(P1_GreenBlkTime,P1_GreenOff,BlkCount);
}

void P1_GreenOff(){
    digitalWrite (P1_GREEN_LED,HIGH); delay(Blkinterval);
    digitalWrite (P1_GREEN_LED,LOW); delay(Blkinterval);
}

/**********************************************************/
//P1_RED_LED 를 제어하는 함수
/*********************************************************/
void P1_RedOn(){
    digitalWrite (P1_RED_LED,HIGH);
    digitalWrite (BUZ,HIGH);
    BuzSound(2);
    P1_G=0;
    P1_R=1;
 }

 void P1_RedOff(){
    digitalWrite (P1_RED_LED,LOW);
    _timerP1_R.setTimeout(8000,P1_RedOn);
    P1_G=1;
    P1_R=0;
}
 

/**********************************************************/
//P2_GREEN_LED 를 제어하는 함수
/*********************************************************/
void P2_GreenOn(){
    digitalWrite (P2_GREEN_LED,HIGH);
    digitalWrite (C1_RED_LED,HIGH);
    digitalWrite (C1_GREEN_LED,LOW);
    digitalWrite (C1_YELLOW_LED,LOW);
    _timerP2_G.setTimeout(P2_GreenOnTime,P2_GreenBlk);
    BuzSound(1);
    _timerP1_R.setTimeout(17500,C1_YellowOn);
}

void P2_GreenBlk(){
    _timerP2_G.setTimer(P2_GreenBlkTime,P2_GreenOff,BlkCount);
}

void P2_GreenOff(){
    digitalWrite (P2_GREEN_LED,HIGH);delay(Blkinterval);
    digitalWrite (P2_GREEN_LED,LOW);delay(Blkinterval);
}

/**********************************************************/
//P2_RED_LED 를 제어하는 함수
/*********************************************************/

void P2_RedOn(){
    digitalWrite (P2_RED_LED,HIGH);
    digitalWrite (C1_GREEN_LED,HIGH);
    digitalWrite (C1_RED_LED,LOW);
    digitalWrite (BUZ,HIGH);
    BuzSound(2);
    P2_G=0;
    P2_R=1;
}

void P2_RedOff(){
    digitalWrite (P2_RED_LED,LOW);
    P2_G=1;
    P2_R=0;
    _timerP2_R.setTimeout(P2_RedOffTime,P2_RedOn);
}

/**********************************************************/
//C1_YELLOW_LED 를 제어하는 함수
/*********************************************************/

void C1_YellowOn(){
    digitalWrite (C1_GREEN_LED,LOW);
    digitalWrite (C1_YELLOW_LED,HIGH);
}

