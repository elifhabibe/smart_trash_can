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
#define agýrlýkesik 100

unsigned int GazDeger;         //mq4 metan gazý sensöründen gelen deðer
unsigned int AgirlikDeger;    //potansiyometreden gelen deðer

int bayrak = 0;

void kesme()
{
if(INTCON.INTF == 1 )
  {
    bayrak = 1;
    INTCON.INTF = 0;       // kesme bayraðý temizlendi
  }
}
void main() {
trisc=0x00;    //c0 ve c1 de led   c2 de  buzzzer
portc=0x00;

INTCON.GIE=1;    //programda kesme kullanýcaðýmýzýn bilgisini verdik
INTCON.INTE=1; //B0 kesme butonu olarak tanýmlandý

ansel=0b000000110; //a1 ve a2 pinler ans1 ve ans2 de
anselh=0b00000000;


Lcd_Init();                //lcd baþlattýk
Lcd_Cmd(_LCD_CURSOR_OFF); // LCD display ekranýndaki imleci kaldýrdýk
Lcd_Cmd(_LCD_CLEAR);      //LCD ekranýný temizledik

if (bayrak == 1)
 {
if(GazDeger>=300 || AgirlikDeger<=100 )
{
portc.b0=1;   //kýrmýzý led yandý
portc.b2=1;   //buzzer çalýstý
Lcd_Out(1,1,"gaz"); //1 satýr ve 1.Sütundan itibaren yazma
Lcd_Out(2,1,GazDeger); //2.satýr ve 1.sütundan itibaren yazma
}
if(GazDeger<=300 || AgirlikDeger>=100 )
{
portc.b0=1;   //kýrmýzý led yandý
portc.b2=1;   //buzzer çalýstý
Lcd_Out(1,1,"agirlik"); //1 satýr ve 1.Sütundan itibaren yazma
Lcd_Out(2,1,AgirlikDeger); //2.satýr ve 1.sütundan itibaren yazma
}
if(GazDeger>=300 && AgirlikDeger>=100 )
{
portc.b0=1;   //kýrmýzý led yandý
portc.b2=1;   //buzzer çalýstý
Lcd_Out(1,1,"agirlik ");     //1 satýr ve 1.Sütundan itibaren yazma
Lcd_Out(2,1,AgirlikDeger);  //2.satýr ve 1.sütundan itibaren yazma
Delay_ms(2000);
Lcd_Cmd(_LCD_CLEAR);
Lcd_Out(1,1,"gaz "); //1 satýr ve 1.Sütundan itibaren yazma
Lcd_Out(2,1,GazDeger); //2.satýr ve 1.sütundan itibaren yazma
}
       bayrak = 0;    // bayrak 0 landý ve yeni kesme için hazýrlandý
       portc.b0=0;   //kýrmýzý led sondu
       portc.b2=0;   //buzzer durdu
 }

while(1)
{
 GazDeger=adc_read(1);
 AgirlikDeger=adc_read(2);

 if(GazDeger>=300 || AgirlikDeger>=100 )  //ikisinden biri eþik degerini geciyorsa kesmeye git
 {
  portb.b0=1;
 }
 else
 {
  portc.b1=1;
 }
}
}
