#include<reg51.h>
#include "delay.h" 
 
void delay_us(unsigned int us_count)
 {  
    while(us_count!=0)
      {
         us_count--;
       }
   }
 
	 void Delay_ms(long int k)
{
		int i;
	TMOD=0X02;
	TH0=0x00;
	while(k!=0)
	{
		for(i=0;i<4;i++){
		TR0=1;
		while(!TF0);
		TF0=0;}
		k--;
	}
}  