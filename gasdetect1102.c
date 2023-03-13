#include<reg52.h>
#define lcd P1
sbit led= P0^3;
sbit rs= P2^5;
sbit rw= P2^6;
sbit e= P2^7;
sbit gas_sensor=P0^7;

void cmd(unsigned char);
void ldata(unsigned char);
void delay(unsigned int);

void delay(unsigned int t)
{
  int i,j;
  for(i=0;i<t;i++)
    for(j=0;j<500;j++);
}
void  cmd(unsigned char c)
{
	lcd=c;
	rs=0;
	rw=0;
	e=1;
	delay(5);
	e=0;
}
void ldata(unsigned char c)
{
	 lcd=c;
	 rs=1;
	 rw=0;
	 e=1;
	 delay(5);
	 e=0;
}
	
void main()
{
	int i;
	unsigned char msg1[16]="GAS DETECTED";
	unsigned char msg2[16]="GAS NOT DETECTED";
	cmd(0x38);
	cmd(0x0c);
	cmd(0x01);
	cmd(0x80);
	while(1)
	{
		delay(10);
		cmd(0x80);
		if(gas_sensor==1){
			for(i=0;i<5;i++){
				led=1;
				delay(5);
				led=0;
			}
			delay(10);
			for(i=0;i<sizeof(msg1);i++)
			{
				ldata(msg1[i]);
			}
		}
		if(gas_sensor==0)
		{
			led=0;
			delay(10);
			for(i=0;i<sizeof(msg1);i++)
			{
			 ldata(msg2[i]);
			}
		}
	}
}