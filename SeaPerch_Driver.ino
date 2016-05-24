/*
   Matthew Jackson
   4/13/2016
   For Team 5214's 2016 SeaPerch Competition and Beyond
   Left Motor Relay = 4
   Right Motor Relay = 7
   Vertical Motor Relay = 8
   Vertical Motor 2 Relay = 12
   Vertical Motor 2 PWM = 11
   Left Motor PWM = 6
   Right Motor PWM = 9
   Vertical Motor PWM = 10
   Serial:
    RX = 5
    TX = 3
*/
#include <SoftwareSerial.h>
int x;
int y;
int altitude;
int ind1; // , locations
int ind2;
int ind3;
const int verticalMotorTwoRelay = 12;
const int verticalMotorTwoPWM = 11;
const int leftMotorRelay = 4;
const int rightMotorRelay = 7;
const int verticalMotorRelay = 8;
const int leftMotorPWM = 6;
const int rightMotorPWM = 9;
const int verticalMotorPWM = 10;
unsigned long timeSinceLast = 0;
int altitudeDirection = 1;
String readString;
SoftwareSerial softwareSerial(5, 3);

void setup() {
  softwareSerial.begin(57600);
  //Serial.begin(9600);
  pinMode(verticalMotorTwoRelay, OUTPUT);
  pinMode(verticalMotorTwoPWM, OUTPUT);
  pinMode(leftMotorRelay, OUTPUT);
  pinMode(rightMotorRelay, OUTPUT);
  pinMode(verticalMotorRelay, OUTPUT);
  pinMode(leftMotorPWM, OUTPUT);
  pinMode(rightMotorPWM, OUTPUT);
  pinMode(verticalMotorPWM, OUTPUT);
  digitalWrite(verticalMotorTwoRelay, LOW);
  digitalWrite(leftMotorRelay, LOW);
  digitalWrite(rightMotorRelay, LOW);
  digitalWrite(verticalMotorRelay, LOW);
  delay(500);
  digitalWrite(verticalMotorTwoPWM, LOW);
  digitalWrite(leftMotorPWM, LOW);
  digitalWrite(rightMotorPWM, LOW);
  digitalWrite(verticalMotorPWM, LOW);
}

void loop() {
  if (softwareSerial.available()) {
    timeSinceLast = millis();
    char c = softwareSerial.read();
    if (c == '*') {
      x = readString.substring(0, readString.indexOf(",")).toInt();
      String remaining = readString.substring(readString.indexOf(",") + 1);
      y = remaining.substring(0, remaining.indexOf(",")).toInt();
      altitude = remaining.substring(remaining.indexOf(",") + 1).toInt();
      String xDec = (String(x, DEC));
      String yDec = (String(y, DEC));
      String altitudeDec = (String(altitude, DEC));
      //Serial.println(xDec + ", " + yDec + ", " + altitudeDec);
      int xDirection = abs(x) / x;
      int yDirection = abs(y) / y;
      if (altitude != 0)
      {
        altitudeDirection = abs(altitude) / altitude;
      }
      if (abs(x) > abs(y) && abs(x) > 10)
      {
        if (xDirection == 1)
        {
          digitalWrite(leftMotorRelay, HIGH);
          digitalWrite(rightMotorRelay, LOW);
        }
        else if (xDirection == -1)
        {
          digitalWrite(leftMotorRelay, LOW);
          digitalWrite(rightMotorRelay, HIGH);
        }
        analogWrite(leftMotorPWM, 255);
        analogWrite(rightMotorPWM, 255);
      }
      else if (abs(y) > abs(x) && abs(y) > 10)
      {
        if (yDirection == 1)
        {
          digitalWrite(leftMotorRelay, LOW);
          digitalWrite(rightMotorRelay, LOW);
        }
        else if (yDirection == -1)
        {
          digitalWrite(leftMotorRelay, HIGH);
          digitalWrite(rightMotorRelay, HIGH);
        }
        analogWrite(leftMotorPWM, 255);
        analogWrite(rightMotorPWM, 255);

      }
      else
      {
        digitalWrite(leftMotorPWM, LOW);
        digitalWrite(rightMotorPWM, LOW);
      }
      if (altitudeDirection == 1)
      {
        digitalWrite(verticalMotorTwoRelay, LOW);
        digitalWrite(verticalMotorRelay, LOW);
      }
      else if (altitudeDirection == -1)
      {
        digitalWrite(verticalMotorTwoRelay, HIGH);
        digitalWrite(verticalMotorRelay, HIGH);
      }
      if (abs(altitude) > 5)
      {
        digitalWrite(verticalMotorTwoPWM, HIGH);
        digitalWrite(verticalMotorPWM, HIGH);
      }
      else
      {
        digitalWrite(verticalMotorTwoPWM, LOW);
        digitalWrite(verticalMotorPWM, LOW);
      }
      readString = "";
    }
    else
    {
      readString += c;
    }
  }
  if (millis() - timeSinceLast > 200)
  {
    digitalWrite(leftMotorPWM, LOW);
    digitalWrite(rightMotorPWM, LOW);
    digitalWrite(verticalMotorPWM, LOW);
    digitalWrite(verticalMotorTwoPWM, LOW);
  }
}
