#include <reg51.h> 
#include "lcd.h"  	 
#include "ds1307.h" 
#include "i2c.h"
#include "delay.h"
#include<stdio.h>
unsigned int i;
char EEPROM_DATA[20];
char Read_Data[20];
void EepromWriteByte( unsigned char Data,unsigned char Address, unsigned char Page)
{
    i2c_Start(); 
   	i2c_Write(0xA0|(Page<<1));	
   	i2c_Write(Address); 
   	i2c_Write(Data);    
    i2c_Stop();           	 
	  delay_ms(5);        
}



unsigned char EepromReadByte(unsigned char Address,unsigned char Page)
{
  unsigned char Data;

    i2c_Start();            
   	i2c_Write(0xA0|(Page<<1));	  
   	i2c_Write(Address); 
    i2c_Start();		   
    i2c_Write(0xA1|(Page<<1));           
	  Data = i2c_Read(); 
	  i2c_NoAck();
    i2c_Stop();		        
	  delay_us(10);
    return Data;          
}


	void EepromWriteNBytes(unsigned char Location, unsigned char *Pointer, char N, unsigned char Page)
	 {
		while(N !=  0)
		 {
		EepromWriteByte(Location,*Pointer,Page);
		Location++;Pointer++;N--;		
		 }
	 }



	void EepromReadNBytes(unsigned char Location, unsigned char *Pointer, char N,unsigned char Page)
	 {
		 while(N !=  0)
		{
		 *Pointer = EepromReadByte(Location,Page);
			Location++;Pointer++;N--;
		 }
	 }

   void EepromErasePage(unsigned char Page)
   {
		unsigned char i;
		for(i=0;i<255;i++)
		EepromWriteByte(0x00,i,Page);	
   }



  void EepromEraseAll()
   {
		unsigned char i;
		for(i=0;i<255;i++){
		EepromWriteByte(0x00,i,0);
		EepromWriteByte(0x00,i,1);}	
   }



void main() 
{
   
	 char Name[]="TANGENT TECHNO LABS"; //Char data saved in EEPROM
	 unsigned char sec,min,hour,day,month,year;
	 
    lcd_Init();
    ds1307_Init();
    ds1307_SetTime(0x23,0x59,0x30);  
    ds1307_SetDate(0x31,0x12,0x20); 
    lcd_DisplayString("WELCOME");
    lcd_Line_posnY();
    lcd_DisplayString("NANDISH");
	  delay_ms(1000);
	  lcd_Clear();
	 	for(i =0; i<14; i++){
	  EepromWriteByte(Name[i],i,0);
		}
		for(i =0; i<14; i++)
	  {	
		Read_Data[15] = EepromReadByte(i,0xA0);//Read Store Data on EEPROM
		}
		delay_ms(500);
    while(1)
    {
		lcd_DisplayString(" Time:");
	  lcd_Line_posnY();
    lcd_DisplayString(" Date:");
	  ds1307_GetTime(&hour,&min,&sec);        
	  lcd_curser_posn(0,6); 		 
    lcd_DisplayRtcTime(hour,min,sec);
    ds1307_GetDate(&day,&month,&year);        
    lcd_curser_posn(1,6); 		 
    lcd_DisplayRtcDate(day,month,year);
    delay_ms(1000);
    lcd_Clear();			
	  lcd_DisplayString("EEPROM READING");
		lcd_Line_posnY();	 
    lcd_DisplayString(Read_Data); // Display Data from EEPROM on LCD
	  delay_ms(2000);
		 lcd_Clear();	
    }
}
