#include <LiquidCrystal.h>
LiquidCrystal LCD(A4,A5,0,1,2,3);

#define RT0 10000   // Ω
#define B 3435      // K
float a=A0;

#define VCC 5    //Supply voltage
#define R 10000  //R=10KΩ

//Variables
float RT, VR, ln, Temp, T0, Read;

void setup() {
  Serial.begin(9600);
  pinMode(A0,INPUT);
  T0 = 25 + 273.15;                 //Temperature T0 from datasheet, conversion from Celsius to kelvin
  
  LCD.begin(16,2);
  LCD.print("Temp : ");
}

void loop() {
  Read = analogRead(A0);              //Acquisition analog value Read
  Read = (5.00 / 1023.00) * Read;      //Conversion to voltage
  VR = VCC - Read;
  RT = Read / (VR / R);               //Resistance of RT

  ln = log(RT / RT0);
  Temp = (1 / ((ln / B) + (1 / T0))); //Temperature from sensor

  Temp = Temp - 273.15;                 //Conversion to Celsius


  Serial.print("Temperature:");
  Serial.print("\t");
  Serial.print(Temp);       //Conversion to c
  Serial.print("C\t\t");
  Serial.print(Temp + 273.15);        //Conversion to Kelvin
  Serial.print("K\t\t");
  Serial.print((Temp * 1.8) + 32);    //Conversion to Fahrenheit
  Serial.println("F");

  LCD.setCursor(10,0);
  LCD.print(Temp);
  delay(1000);

}
