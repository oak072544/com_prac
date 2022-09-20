/*
  วัดอุณหภูมิ ด้วย LM35 Arduino
  https://www.9arduino.com/article/34/
*/

float LMval;
float tempPin = A2;   //ต่อ Sensor ที่ ขา A3

void setup() {
  Serial.begin(9600);
}

void loop() {
  LMval = analogRead(tempPin);
  float mv = ( LMval / 1024.0) * 5000;
  float cel = mv / 10;

  Serial.print("TEMP = ");
  Serial.print(cel);
  Serial.print("*C");
  Serial.println();
  delay(1000);

}
