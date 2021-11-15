sbit LCD_RS at RB0_bit;
sbit LCD_EN at RB1_bit;
sbit LCD_D4 at RB2_bit;
sbit LCD_D5 at RB3_bit;
sbit LCD_D6 at RB4_bit;
sbit LCD_D7 at RB5_bit;
sbit LCD_RS_Direction at TRISB0_bit;
sbit LCD_EN_Direction at TRISB1_bit;
sbit LCD_D4_Direction at TRISB2_bit;
sbit LCD_D5_Direction at TRISB3_bit;
sbit LCD_D6_Direction at TRISB4_bit;
sbit LCD_D7_Direction at TRISB5_bit;

#define gazesik 300
#define ag�rl�kesik 100

unsigned int GazDeger;         //mq4 metan gaz� sens�r�nden gelen de�er
unsigned int AgirlikDeger;    //potansiyometreden gelen de�er

int bayrak = 0;

void kesme()
{
if(INTCON.INTF == 1 )
  {
    bayrak = 1;
    INTCON.INTF = 0;       // kesme bayra�� temizlendi
  }
}
void main() {
trisc=0x00;    //c0 ve c1 de led   c2 de  buzzzer
portc=0x00;

INTCON.GIE=1;    //programda kesme kullan�ca��m�z�n bilgisini verdik
INTCON.INTE=1; //B0 kesme butonu olarak tan�mland�

ansel=0b000000110; //a1 ve a2 pinler ans1 ve ans2 de
anselh=0b00000000;


Lcd_Init();                //lcd ba�latt�k
Lcd_Cmd(_LCD_CURSOR_OFF); // LCD display ekran�ndaki imleci kald�rd�k
Lcd_Cmd(_LCD_CLEAR);      //LCD ekran�n� temizledik

if (bayrak == 1)
 {
if(GazDeger>=300 || AgirlikDeger<=100 )
{
portc.b0=1;   //k�rm�z� led yand�
portc.b2=1;   //buzzer �al�st�
Lcd_Out(1,1,"gaz"); //1 sat�r ve 1.S�tundan itibaren yazma
Lcd_Out(2,1,GazDeger); //2.sat�r ve 1.s�tundan itibaren yazma
}
if(GazDeger<=300 || AgirlikDeger>=100 )
{
portc.b0=1;   //k�rm�z� led yand�
portc.b2=1;   //buzzer �al�st�
Lcd_Out(1,1,"agirlik"); //1 sat�r ve 1.S�tundan itibaren yazma
Lcd_Out(2,1,AgirlikDeger); //2.sat�r ve 1.s�tundan itibaren yazma
}
if(GazDeger>=300 && AgirlikDeger>=100 )
{
portc.b0=1;   //k�rm�z� led yand�
portc.b2=1;   //buzzer �al�st�
Lcd_Out(1,1,"agirlik ");     //1 sat�r ve 1.S�tundan itibaren yazma
Lcd_Out(2,1,AgirlikDeger);  //2.sat�r ve 1.s�tundan itibaren yazma
Delay_ms(2000);
Lcd_Cmd(_LCD_CLEAR);
Lcd_Out(1,1,"gaz "); //1 sat�r ve 1.S�tundan itibaren yazma
Lcd_Out(2,1,GazDeger); //2.sat�r ve 1.s�tundan itibaren yazma
}
       bayrak = 0;    // bayrak 0 land� ve yeni kesme i�in haz�rland�
       portc.b0=0;   //k�rm�z� led sondu
       portc.b2=0;   //buzzer durdu
 }

while(1)
{
 GazDeger=adc_read(1);
 AgirlikDeger=adc_read(2);

 if(GazDeger>=300 || AgirlikDeger>=100 )  //ikisinden biri e�ik degerini geciyorsa kesmeye git
 {
  portb.b0=1;
 }
 else
 {
  portc.b1=1;
 }
}
}
