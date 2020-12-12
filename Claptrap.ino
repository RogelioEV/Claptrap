#include "SD.h"
#include "TMRpcm.h"
#include "SPI.h"
#include <TimerEvent.h>

#define SD_ChipSelectPin 10
#define M1 12
#define M2 11
#define RIGHT 2
#define LEFT 3
#define TRIGGER_PIN 6
#define ECHO_PIN 7
#define MAX_DISTANCE 100

TMRpcm tmrpcm;
TimerEvent tEvt;
float distance;
const int interval 9000;
char *audios[] = ["1.wav", "2.wav", "3.wav", "4.wav"];
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(M1, OUTPUT);
  digitalWrite(M1, HIGH);
  pinMode(M2, OUTPUT);
  digitalWrite(M2, HIGH);
  pinMode(RIGHT, INPUT);
  pinMode(LEFT, INPUT);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  tmrpcm.speakerPin=9;
  if(!SD.begin(SD_ChipSelectPin))
  {
    Serial.println("SD fail");
    return;
  }
  tmrpcm.setVolume(6);
  tEvt.set(iterval, tEvtFunc);
  randomSeed(analogRead(0));
}

void tEvtFunc(){
  int x = random(4);
  tmrpcm.play(audios[x]);
}
float checkDistance(){
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(5);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  float time = pulseIn(ECHO_PIN, HIGH);
  return time/58; 
}
void loop() {
  // put your main code here, to run repeatedly:
  delay(300);
  distance = checkDistance();
  Serial.print("distance");
  Serial.println(distance);
  int Right_Value = digitalRead(RIGHT);
  Serial.print("RIGHT");
  Serial.println(Right_Value);
  
  int Left_Value = digitalRead(LEFT);
  Serial.print("LEFT");
  Serial.println(Left_Value);

  if((distance<10)){
    digitalWrite(M2, HIGH);
    digitalWrite(M1, HIGH);
  }
  if((distance>=10 && distance<=30)){
    digitalWrite(M2, LOW);
    digitalWrite(M1, LOW);
  } else if((Right_Value==0) && (Left_Value==1)){
    digitalWrite(M2, LOW);
    digitalWrite(M1, HIGH);
  } else if(Right_Value == 1 && Left_Value == 0){
    digitalWrite(M2, HIGH);
    digitalWrite(M1, LOW);
  } else {
    digitalWrite(M2, HIGH);
    digitalWrite(M1, HIGH);
  }
}
