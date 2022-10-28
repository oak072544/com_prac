/*
  #include <LiquidCrystal.h>
  LiquidCrystal LCD(A4,A5,0,1,2,3);
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C LCD(0x27, 16, 2); // LiquidCrystal_I2C lcd(0x3F, 16, 2);
/*
  A4  SDA
  A5  SCL
*/

//#define THERMISTORPIN A0
//#define THERMISTORVALUE 10000
//#define TEMPERATUREVALUE 25
//#define SAMPLESNUM 5
//#define BCOEFFICIENT 3950
//#define SERIESRESISTOR 10000
//int samples[SAMPLESNUM];
//int i;

#define R0 10000.0
#define RT0 10000   // Ω
#define B 3950     // K 3435p 3950m
float a = A5; //TherPIN

#define VCC 5    //Supply voltage
#define R 10000.0  //R=10KΩ

#define PWMpin 9

int MAX_temp = 40;


//Variables
float RT, VR, ln, Temp, T0, Read,ReadV;
float LMval,mv, cel;
float tempPin = A0;   //LM


void setup() {
  Serial.begin(9600);
//  analogReference(EXTERNAL);
  T0 = 25 + 273.15;                 //Temperature T0 from datasheet, conversion from Celsius to kelvin
  //LCD.begin(16,2);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  LCD.begin();
  LCD.backlight();
  LCD.print("Temp T : ");
}

void loop() {
  Read = analogRead(A1);
  LMval = analogRead(tempPin);
  VR = (Read*5.0)/1024.0;
  RT = ((5.0*R)/VR)-R;
  ln = log(RT/R0)/B;
  Temp = (1.0/(ln+(1.0/298.15)))-273.15;
  
  Serial.print("Temperature Ther:");
  Serial.println(Temp);
  LCD.setCursor(10, 0);
  LCD.print(Temp);
  delay(1000);
  
  Serial.print("TEMP lm = ");
  cel = analogRead(tempPin)*0.488;
  Serial.println(cel);
  LCD.setCursor(0, 1);
  LCD.print("Temp L : ");
  LCD.print(cel);
  delay(1000);

  
  
  if (Temp >= MAX_temp || cel >= MAX_temp)
  {
    analogWrite(PWMpin, 0);
  }
  else
  {
    analogWrite(PWMpin, 0); // analogWrite values from 0 to 255
  }
  
}
