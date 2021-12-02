#include <avr/io.h>
#include <string.h>
#include <avr/eeprom.h>
#include <avr/interrupt.h>
#include "remote.h"

unsigned char u8_data;

//LCD connections 

#define E   PD7
#define RS   PB0

#define Relay PB3  //Relay1
#define Relay1 PB4  //Relay1

//Decleration
void display(char string[16]);
void displaybyte(char D);
void dispinit(void);
void cleardisplay(void);
void line1(void);
void line2(void);
void epulse(void);
void delay_ms(unsigned int de);
void PasswordNotOK();
void PasswordNotOK1();
char KeyCheck();

char mystr[6];
char Password[3];

int main(void)
{ 
 DDRB = 0b00011011; //LCD port direction
 DDRD = 0b11011001; //LCD port direction
 DDRC = 0b00011010;  

 PORTC= 0b11111111;  //Activate internal pullups for keypad
 PORTD |=(1<<PD1); 

// PORTB |=(1<<Relay); 
 
  delay_ms(500);  //Initiaize LCD
  dispinit();
  delay_ms(200);


 line1();
 uint8_t cmd=0;
 RemoteInit();

 display("    Password    ");
 line2(); 
 display("     Access     ");
 cleardisplay();
 line1();
 char Key,cnt;
 cnt=0;
 Key=KeyCheck();
 if(Key==11)
 {
//Get Old Password
line1();
display("Enter Old Pass: ");
line2();
cnt=0;
   while(1)
   {

    Key = KeyCheck();
    //cmd=GetRemoteCmd(0);
    //displaybyte(cmd+48);
        

     delay_ms(100);

     if((Key != 15) && (cnt<4) && (Key !=11) && (Key !=12))
     {
    //line1();
    //displaybyte(Key+48); //Display Passsword
     displaybyte(0x2A); //"*" Display '*' Instead of password

    Password[cnt]=Key;
    cnt++;
     }
     
     if(Key==11) //Cancel Key
     {
      cnt=0;
    PasswordNotOK1();
     }
     if(((Key !=15)) && (cnt==4))
     {
       if(Key==12) //OK Key
     {
      //Verify password
     if(eeprom_read_byte((uint8_t*)4)==Password[0])
       {
          if(eeprom_read_byte((uint8_t*)5)==Password[1])
       {
       if(eeprom_read_byte((uint8_t*)6)==Password[2])
       {
        if(eeprom_read_byte((uint8_t*)7)==Password[3])
        {
         //PasswordOK
           cleardisplay();
           line1();
           display("  Enter New   ");
           line2();
           display("Password:");

            while(1)
            {
             Key = KeyCheck();
             delay_ms(100);
              if((Key != 15) && (cnt<4))
              {
             //line1();
             displaybyte(Key+48);
             Password[cnt]=Key;
             cnt++;
              }
              if((Key !=15) && (cnt==4))
              {
                if(Key==12) //OK Key
              {
               cleardisplay();
              line1();
              display("Password Changed");
              eeprom_write_byte((uint8_t*)4,Password[0]);
              eeprom_write_byte((uint8_t*)5,Password[1]);
              eeprom_write_byte((uint8_t*)6,Password[2]);
              eeprom_write_byte((uint8_t*)7,Password[3]);
              delay_ms(2000);
              cleardisplay();
              break;
              }
                 if(Key==11) //Cancel Key
              {
               cleardisplay();
              break;
              }

              }
            }

          //}
         //=========
          cleardisplay();
          line1();
          display("Enter Password:");
          line2();
          cnt=0;
        }
        else
        {
         cnt=0;
         //PORTB |= (1<<Relay1);
         PasswordNotOK1();
        }
       }
       else
       {
        cnt=0;
        //PORTB |= (1<<Relay1);
        PasswordNotOK1();
       }
       }
       else
       {
        cnt=0;
       //PORTB |= (1<<Relay1);
        PasswordNotOK1();
       }
       }
       else
       {
        cnt=0;
      //PORTB |= (1<<Relay1);
         PasswordNotOK1();
       }

     }
        if(Key==11) //Cancel Key
     {
      cleardisplay();
     line1();
     display("Enter Old Pass: ");
     line2();
     cnt=0;
     }

     }
   }
   }

//----------------


line1();
display("Enter Password:");
line2();
cnt=0;
   while(1)
   {

    Key = KeyCheck();
    cmd=GetRemoteCmd(0);
    //displaybyte(cmd+48);
        

    delay_ms(100);
     if((cnt<4) && (cmd !=10) && (cmd !=25) && (cmd !=255))
     {
    //line1();
    //displaybyte(cmd+48);
    displaybyte(0x2A); //"*"
    Password[cnt]=cmd;
    cnt++;
     }

     if((Key != 15) && (cnt<4) && (Key !=11) && (Key !=12))
     {
    //line1();
    //displaybyte(Key+48);
     displaybyte(0x2A); //"*"

    Password[cnt]=Key;
    cnt++;
     }
     if(Key==11 || cmd==10) //Cancel Key
     {
      cnt=0;
    PasswordNotOK();
     }
     if(((Key !=15) || (cmd==25)) && (cnt==4))
     {
       if(Key==12 || cmd==25) //OK Key
     {
      //Verify password
     if(eeprom_read_byte((uint8_t*)4)==Password[0])
       {
          if(eeprom_read_byte((uint8_t*)5)==Password[1])
       {
       if(eeprom_read_byte((uint8_t*)6)==Password[2])
       {
        if(eeprom_read_byte((uint8_t*)7)==Password[3])
        {
         //PasswordOK
          cleardisplay();
          PORTB |=(1<<Relay);
          line1();
          display("Open The Door");
          delay_ms(4000);
          cleardisplay();
          //Operate Relay
          PORTB &=~(1<<Relay);
          line1();
          display("Enter Password:");
          line2();
          cnt=0;
        }
        else
        {
         cnt=0;
         PORTB |= (1<<Relay1);
         PasswordNotOK();
        }
       }
       else
       {
        cnt=0;
        PORTB |= (1<<Relay1);
        PasswordNotOK();
       }
       }
       else
       {
        cnt=0;
       PORTB |= (1<<Relay1);
        PasswordNotOK();
       }
       }
       else
       {
        cnt=0;
      PORTB |= (1<<Relay1);
         PasswordNotOK();
       }

     }
        if(Key==11) //Cancel Key
     {
      cleardisplay();
     line1();
     display("Enter Password:");
     line2();
     cnt=0;
     }

     }
   }
}

void PasswordNotOK()
{
 cleardisplay();
 line1();
 display("   Incorrect  ");
 line2();
 display("   Password   ");
 delay_ms(2000);
 cleardisplay();
 line1();
 display("Enter Password:");
 line2();
 PORTB &=~ (1<<Relay1);
}

void PasswordNotOK1()
{
 cleardisplay();
 line1();
 display("   Incorrect  ");
 line2();
 display("   Password   ");
 delay_ms(2000);
 cleardisplay();
 line1();
 display("Enter Old Pass: ");
 line2();
}

char KeyCheck()
{
char KeyCode;
 KeyCode=15;

//Scan 1
 PORTC &=~(1<<PC1);
 PORTC |=(1<<PC3);
 PORTC |=(1<<PC4);
 PORTD |=(1<<PD0);
   
    if((PIND & 0x02)==0x00)
  {
   KeyCode=3;
      while((PIND & 0x02)==0x00);
  } 
    if((PINC & 0x04)==0x00)
  {
   KeyCode=2;
   while((PINC & 0x04)==0x00);
  } 
    if((PINC & 0x20)==0x00)
  {
   KeyCode=1;
   while((PINC & 0x20)==0x00);
  } 
//Scan 2
 PORTC |=(1<<PC1);
 PORTC &=~(1<<PC3);
 PORTC |=(1<<PC4);
 PORTD |=(1<<PD0);
   
    if((PIND & 0x02)==0x00)
  {
   KeyCode=6;
   while((PIND & 0x02)==0x00);
  } 
    if((PINC & 0x04)==0x00)
  {
   KeyCode=5;
   while((PINC & 0x04)==0x00);
  } 
    if((PINC & 0x20)==0x00)
  {
   KeyCode=4;
   while((PINC & 0x20)==0x00);
  } 
//Scan 3
 PORTC |=(1<<PC1);
 PORTC |=(1<<PC3);
 PORTC &=~(1<<PC4);
 PORTD |=(1<<PD0);
   
    if((PIND & 0x02)==0x00)
  {
   KeyCode=9;
   while((PIND & 0x02)==0x00);
  } 
    if((PINC & 0x04)==0x00)
  {
   KeyCode=8;
   while((PINC & 0x04)==0x00);
  } 
    if((PINC & 0x20)==0x00)
  {
   KeyCode=7;
   while((PINC & 0x20)==0x00);
  } 
//Scan 4
 PORTC |=(1<<PC1);
 PORTC |=(1<<PC3);
 PORTC |=(1<<PC4);
 PORTD &=~(1<<PD0);
   
    if((PIND & 0x02)==0x00)
  {
   KeyCode=12;
   while((PIND & 0x02)==0x00);
  } 
    if((PINC & 0x04)==0x00)
  {
   KeyCode=0;
   while((PINC & 0x04)==0x00);
  } 
    if((PINC & 0x20)==0x00)
  {
   KeyCode=11;
   while((PINC & 0x20)==0x00);
  } 

 return KeyCode;
}

void display(char string[16])
{
 int len,count;
  len = strlen(string);

   for (count=0;count<len;count++)
  {
    displaybyte(string[count]);
 }
}


void displaybyte(char D)
{
  char D1;
  D1=D;
  D1=D1 & 0xF0;
  D1=D1 >> 4;  //Send MSB
  
  PORTD = PORTD & (0b10100011);
  PORTB = PORTB & (0b11111101);

  PORTD |= ((D1 & 0x01) << 6);
  //PORTD |= ((D1 & 0x02) << 1);
  PORTB |= ((D1 & 0x02)); 
  PORTD |= ((D1 & 0x04) << 2);
  PORTD |= (D1 & 0x08);
  
 epulse();

  D1=D;
  D1=D1 & 0x0F;  //Send LSB

  PORTD = PORTD & (0b10100011);
  PORTB = PORTB & (0b11111101);

  PORTD |= ((D1 & 0x01) << 6);
  //PORTD |= ((D1 & 0x02) << 1);
  PORTB |= ((D1 & 0x02));
  PORTD |= ((D1 & 0x04) << 2);
  PORTD |= (D1 & 0x08);
 
 epulse();
}


void dispinit(void)
{
 int count;
 char init[]={0x43,0x03,0x03,0x02,0x28,0x01,0x0C,0x06,0x02,0x02};
  
 PORTB &= ~(1<<RS);           // RS=0
 for (count = 0; count <= 9; count++)
  {
 displaybyte(init[count]);
  }
 PORTB |= 1<<RS;    //RS=1
}


void cleardisplay(void)
{
 PORTB &= ~(1<<RS);           // RS=0
    displaybyte(0x01);
 PORTB |= 1<<RS;    //RS=1
}

void line1(void)
{
 PORTB &= ~(1<<RS);           // RS=0
    displaybyte(0x80);
 PORTB |= 1<<RS;    //RS=1
}

void line2(void)
{
 PORTB &= ~(1<<RS);           // RS=0
    displaybyte(0xC0);
 PORTB |= 1<<RS;    //RS=1
}

void epulse(void)
{
 PORTD |= 1<<E;
  delay_ms(1);
 PORTD &= ~(1<<E);
 delay_ms(1);
}

void delay_ms(unsigned int de)
{
unsigned int rr,rr1;
   for (rr=0;rr<de;rr++)
   {
  
  for(rr1=0;rr1<700;rr1++)   //395
  {
   asm("nop");
  }
   
   }
}

