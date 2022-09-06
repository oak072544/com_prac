#define s1 11 
#define s2 12 
char n=0; 
char txt[3]; 
bool load=false; 
char ID; 
void setup( ) {
  DDRC = 0x0F; 
  DDRB = 0xE7; 
  PORTB = PORTB | 0x18; 
  UCSR0B = 0x18; 
  UCSR0C = 0x06;
  UBRR0 = 103; 
  mprintln("Serial Port Lab.1");
}

void sendchar(unsigned char ch) 
{ while((UCSR0A&0x20) ==0); 
  UDR0 = ch; 
} 

char chkbuffer() 
{ if((UCSR0A&0x80)!=0) return(1); 
  else return(0); 
} 

void mprintln(char ch[ ]) 
{char k=0; 
  while(ch[k]!='\0') { 
    while((UCSR0A&0x20) ==0); 
    UDR0 = ch[k]; 
    k++ ; 
  } 
  sendchar(10); 
  sendchar(13); 
} 

void loop() {
  if (chkbuffer()==1){
    txt[n] = UDR0; 
    if(n==1){ 
      if(txt[0]=='O' && txt[1]!='A' && txt[1]<'4' && txt[1]!='S'){ 
        ID = txt[1]-'0'; 
        digitalWrite(A0+ID,1);
      } 
      else if(txt[0]=='F' && txt[1]!='A' && txt[1]<'4' && txt[1]!='S') 
      { ID = txt[1]-'0'; 
        digitalWrite(A0+ID,0);  
      }
      else if(txt[0]=='O' && txt[1]=='A'){ digitalWrite(A0,1); digitalWrite(A1,1); digitalWrite(A2,1); digitalWrite(A3,1); }
      else if(txt[0]=='F' && txt[1]=='A'){ digitalWrite(A0,0); digitalWrite(A1,0); digitalWrite(A2,0); digitalWrite(A3,0); }
      else{ mprintln("--Invalid command--"); } 
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
     mprintln("On all of LEDS");
   }
   if(digitalRead(s2)==0){
     digitalWrite(A0,0);
     digitalWrite(A1,0);
     digitalWrite(A2,0);
     digitalWrite(A3,0);
     while(digitalRead(s2)==0){delay(50);}
     mprintln("Off all of LEDS");
   }
} 
