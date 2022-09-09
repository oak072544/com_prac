#define s1 11
#define s2 12

#define led1 A0
#define led2 A1
#define led3 A2
#define led4 A3

//String led[] = {"A0","A1","A2","A3"} ;
char txt[3];
int n = 0;
char ID; 

void setup() {
  // put your setup code here, to run once:
  DDRC = 0x0F;
  Serial.begin(9600);
  
  
  DDRB = 0xE7;                   // PB3,PB4 for s1 , s2
  PORTB = PORTB | 0x18;          // internal pullup
  Serial.println("Serial Port Lab.2"); // send data via serial port to serial monitor
  
}

//String x = "";

void loop() 
{
  // put your main code here, to run repeatedly:
  while(Serial.available())
  {
     txt[n] = char(Serial.read());
     //Serial.println(x+" "+x.length());

     if(n==1)
     { 
        if(txt[0]=='O' && txt[1]!='A' && txt[1]-'0'< 4 ){ 
        ID = txt[1]-'0'; 
        digitalWrite(A0+ID,1);
      } 
      else if(txt[0]=='F' && txt[1]!='A' && txt[1]-'0'< 4 ) 
      { 
        ID = txt[1]-'0'; 
        digitalWrite(A0+ID,0);  
      }
      else if(txt[0]=='O' && txt[1]=='A'){ digitalWrite(A0,1); digitalWrite(A1,1); digitalWrite(A2,1); digitalWrite(A3,1); }
      //else if(txt[0]=='F' && txt[1]=='A'){ digitalWrite(A0,0); digitalWrite(A1,0); digitalWrite(A2,0); digitalWrite(A3,0); }
      else if(txt[0]=='F' && txt[1]=='A'){ PORTC = 0x00;}
      else{ Serial.println("--Invalid command--"); } 
      n=-1; 
    }  
    
    n=n+1;
  }
  if(digitalRead(s1)==0){
     digitalWrite(A0,1);
     digitalWrite(A1,1);
     digitalWrite(A2,1);
     digitalWrite(A3,1);
     while(digitalRead(s1)==0){delay(50);}
     Serial.println("On all of LEDS");
   }
   if(digitalRead(s2)==0){
     digitalWrite(A0,0);
     digitalWrite(A1,0);
     digitalWrite(A2,0);
     digitalWrite(A3,0);
     while(digitalRead(s2)==0){delay(50);}
     Serial.println("Off all of LEDS");
   }
}
