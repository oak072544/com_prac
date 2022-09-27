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

#define RT0 10000   // Ω
#define B 3950      // K 3435p 3950m
float a = A0; //TherPIN

#define VCC 5    //Supply voltage
#define R 10000  //R=10KΩ

#define PWMpin 9 

//Variables
float RT, VR, ln, Temp, T0, Read;

float LMval;
float tempPin = A2;   //LM

void setup() {
  Serial.begin(9600);
  pinMode(a,INPUT);
  T0 = 25 + 273.15;                 //Temperature T0 from datasheet, conversion from Celsius to kelvin

  
  //LCD.begin(16,2);

  LCD.begin();
  LCD.backlight();
  
  LCD.print("Temp T : ");
}

void loop() {
  Read = analogRead(a);              //Acquisition analog value Read
  Read = (5.00 / 1023.00) * Read;      //Conversion to voltage
  VR = VCC - Read;
  RT = Read / (VR / R);               //Resistance of RT

  ln = log(RT / RT0);
  Temp = (1 / ((ln / B) + (1 / T0))); //Temperature from sensor

  Temp = Temp - 273.15;                 //Conversion to Celsius


  Serial.print("Temperature Ther:");
  Serial.print("\t");
  Serial.print(Temp);       //Conversion to c
  Serial.print("C\t\t");
  Serial.print(Temp + 273.15);        //Conversion to Kelvin
  Serial.print("K\t\t");
  Serial.print((Temp * 1.8) + 32);    //Conversion to Fahrenheit
  Serial.println("F");

  LCD.setCursor(10,0);
  LCD.print(Temp);

  LMval = analogRead(tempPin);
  float mv = ( LMval / 1024.0) * 5000;
  float cel = mv / 10;

  Serial.print("TEMP lm = ");
  Serial.print(cel);
  Serial.print("*C");
  Serial.println();
  LCD.setCursor(0,1);
  LCD.print("Temp L : ");
  LCD.print(cel);
  
  analogWrite(PWMpin,200); // analogWrite values from 0 to 255
  delay(1000);

  

}
