char index = 0;
char load[]={0,0,0,0};

void setup() 
{
  // put your setup code here, to run once:
  DDRC = 0b11111111;
  DDRB = 0b11100111;
  PORTB = PORTB | 0x18;
}

void loop() 
{
  // put your main code here, to run repeatedly:

  
  if(digitalRead(11)==0)
  {
    while(digitalRead(11)==0){}
    index++;
    if(index > 3) index = 3;
  }
  
  if(digitalRead(12)==0)
  {
    while(digitalRead(12)==0){}
    
    index = 0;
  }
  
  for(int j = 0;j < 4;j++)
      {
        load[j] = 0;
      }
      
  load[index] = 1;
  
  for(int i = 0;i < 4;i++)
      {
        digitalWrite(A0+i,load[i]);
      }   
   
}
