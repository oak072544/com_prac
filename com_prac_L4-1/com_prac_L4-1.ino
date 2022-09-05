#define s1 11
#define s2 12

#define led1 A0
#define led2 A1
#define led3 A2
#define led4 A3

void setup() {
  // put your setup code here, to run once:
  DDRC = 0x0F;
  Serial.begin(9600);
  
  
  DDRB = 0xE7;                   // PB3,PB4 for s1 , s2
  PORTB = PORTB | 0x18;          // internal pullup
  Serial.println("Serial Port Lab.2"); // send data via serial port to serial monitor
  
}

String x = "";

void loop() 
{
  // put your main code here, to run repeatedly:
  while(Serial.available())
  {
     x += char(Serial.read());
     Serial.println(x+" "+x.length());
     
  }
}
