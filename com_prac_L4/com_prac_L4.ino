#define s1 11
#define s2 12
char n = 0;
char txt[3];
bool load = false;
char ID;
void setup()
{
    DDRC = 0x0F;
    DDRB = 0xE7;                   // PB3,PB4 for s1 , s2
    PORTB = PORTB | 0x18;          // internal pullup
    UCSR0B = 0x18;                 // enable receiver / transmitter
    UCSR0C = 0x06;                 // 8 bit data, 1 stop bit no parity
    UBRR0 = 103;                   // Baud rate = 9600
    mprintln("Serial Port Lab.1"); // send data via serial port to serial monitor
}
void sendchar(unsigned char ch)
{
    while ((UCSR0A & 0x20) == 0)
        ; // UDRE0 == 0 ? (1 for Empty)
    UDR0 = ch;
}
char chkbuffer()
{
    if ((UCSR0A & 0x80) != 0)
        return (1); // checking for USART receive complete
    else
        return (0);
}
void mprintln(char ch[])
{
    char k = 0;
    while (ch[k] != '\0')
    {
        while ((UCSR0A & 0x20) == 0)
            ;
        UDR0 = ch[k];
        k++;
    }
    sendchar(10); // ใĀเกิดการขึ้นบรรทัดใĀมกรณีแÿดงผล
    sendchar(13); // ที่ Serial monitor Āรือ Virtual Terminal
}
void loop()
{
    if (chkbuffer() == 1)
    { // เรยีกฟงกชัน chkbuffer( ) ตรวจÿอบวามีขอ มูลเขามาที่พอรตอนุกรม ?
        txt[n] = UDR0;
        if (n == 1)
        {
            if (txt[0] == 'O')
            {
                ID = txt[1] - '0';
                digitalWrite(A0 + ID, 1); // ON LED
            }
            else if (txt[0] == 'F')
            {
                ID = txt[1] - '0';
                digitalWrite(A0 + ID, 0); // OFF LED
            }
            else
            {
                mprintln("--Invalid command--");
            }
            n = -1;
        } // end of if(n==1)
        n = n + 1;
    } // end of if (chkbuffer()==1)
} // end of loop function
