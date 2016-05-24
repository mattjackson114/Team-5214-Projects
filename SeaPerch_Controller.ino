/*
   Matthew Jackson
   4/13/2016
   For Team 5214's 2016 SeaPerch Competition and Beyond
   Accelerometer:
    SCL = 13
    SDA = 11
    SDO = 12
    CS = 6
   Barometric Pressure Sensor:
    SDA = A4
    SCL = A5
   Serial:
    RX = 3
    TX = 5
   Start Button = 2
   Stop Button = 4
   Calibrate Button = 7
*/
#include <SoftwareSerial.h>
#include <SPI.h>
int CS = 6;
char POWER_CTL = 0x2D;  //Power Control Register
char DATA_FORMAT = 0x31;
char DATAX0 = 0x32; //X-Axis Data 0
char DATAX1 = 0x33; //X-Axis Data 1
char DATAY0 = 0x34; //Y-Axis Data 0
char DATAY1 = 0x35; //Y-Axis Data 1
char DATAZ0 = 0x36; //Z-Axis Data 0
char DATAZ1 = 0x37; //Z-Axis Data 1
char values[10]; //Used for storing normal acceleration values
char calValues[10]; //Used for calibration
int x;
int y;
unsigned long timeRunning = 0;
int altitude;
int xCal = 0;
int yCal = 0;
int distance = A0;
int altitudeCal = 0;
bool runProgram = false;
const int startButtonPin = 2;
const int stopButtonPin = 4;
const int calibrateButtonPin = 7;
SoftwareSerial softwareSerial(3, 5); // RX, TX
void setup() {
  SPI.begin();
  SPI.setDataMode(SPI_MODE3);
  softwareSerial.begin(57600);
  //Serial.begin(9600);
  pinMode(CS, OUTPUT);
  pinMode(startButtonPin, INPUT);
  pinMode(stopButtonPin, INPUT);
  pinMode(calibrateButtonPin, INPUT);
  digitalWrite(CS, HIGH);
  delay(100);
  writeRegister(DATA_FORMAT, 0x01);
  writeRegister(POWER_CTL, 0x08);
}

void loop() {
  checkButtons();
  if (runProgram == true)
  {
    altitude = analogRead(distance);
    readRegister(DATAX0, 6, values);
    x = ((int)values[1] << 8) | (int)values[0];
    y = ((int)values[3] << 8) | (int)values[2];
    x = x - xCal;
    y = y - yCal;
    altitude = altitude + altitudeCal;
    x = constrain(x, -200, 200);
    y = constrain(y, -200, 200);
    altitude = map(altitude, 35, -35, -3, 3);
    x = map(x, -200, 200, -100, 100);
    y = map(y, -200, 200, -100, 100);
    String xDec = (String(x, DEC));
    String yDec = (String(y, DEC));
    String altitudeDec = (String(altitude, DEC));
    //Serial.println(altitudeDec);
    //Serial.println(String("X Acceleratiion: " + xDec + "," + "Y Acceleration : " + yDec + "," + "Altitude (ft): " + altitude));
    softwareSerial.println(String(xDec + "," + yDec + "," + altitudeDec + '*'));
    checkButtons();
    delay(115);
    checkButtons();
  }
}

void readRegister(char registerAddress, int numBytes, char * values) {
  char address = 0x80 | registerAddress;
  if (numBytes > 1)address = address | 0x40;
  digitalWrite(CS, LOW);
  SPI.transfer(address);
  for (int i = 0; i < numBytes; i++) {
    values[i] = SPI.transfer(0x00);
  }
  digitalWrite(CS, HIGH);
}

void writeRegister(char registerAddress, char value) {
  digitalWrite(CS, LOW);
  SPI.transfer(registerAddress);
  SPI.transfer(value);
  digitalWrite(CS, HIGH);
}

void checkButtons()
{
  if (digitalRead(startButtonPin) == HIGH)
  {
    runProgram = true;
    delay(500);
  }
  if (digitalRead(stopButtonPin) == HIGH)
  {
    runProgram = false;
    delay(500);
  }
  if (digitalRead(calibrateButtonPin) == HIGH)
  {
    timeRunning = millis();
    runProgram = false;
    delay(2000);
    readRegister(DATAX0, 6, calValues);
    //Calculates how far from zero the current acceleration and barometric pressure is
    xCal = 0 - ((int)calValues[1] << 8) | (int)calValues[0];
    yCal = 0 - ((int)calValues[3] << 8) | (int)calValues[2];
    altitudeCal = 0 - analogRead(distance);
    Serial.println(altitudeCal);
    delay(2000);
  }
}
