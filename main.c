
#include <p18cxxx.h>
#include "delay.h"
#include "timer.h"
#include "canf8.h"

void main(void)
{
unsigned char k, p, k1, k2, k3;
unsigned char i,j,c;
unsigned char phase1, phase2, phase3, MODE, offset;
unsigned char comm;
unsigned int ident;
unsigned long Time, Time1 ;



unsigned char a, b;
unsigned long M[3][2];
unsigned long buf[2], s;
unsigned long MM;

unsigned char Pa;


////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

/*---------------инициализация портов таймера и CAN----------------------*/
initports();
timer2init();
Init_can ();

RXB0CONbits.RXFUL=0;
ident=0b0;

comm=0;
offset=72;
phase1=0;
phase2=0;
phase3=0;
Time=0;
MODE=0;

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

while(1)
{
ident=RXB0SIDH;

if(RXB0CONbits.RXFUL==1)
{
	ident=RXB0SIDH;

	if(ident==0b11011)
	{
	phase1=RXB0D0;
	phase2=RXB0D1;
	phase3=RXB0D2;
	Time=RXB0D3;
	MODE=RXB0D4;
	
	M[0][1]=0b001;
	M[0][0]=phase1;
	M[1][1]=0b010;
	M[1][0]=phase2;
	M[2][1]=0b100;
	M[2][0]=phase3;

	/*----------------------------------------*/
	for (a=1;a<3;a++)
	{												//sorting from the shortest phase to the longest

	buf[0]=M[a][0]; 
	buf[1]=M[a][1];

		for (b=a-1;(b>=0)&&(buf[0]<M[b][0]);b--)
		{
		M[b+1][0]=M[b][0];
		M[b+1][1]=M[b][1];

		M[b][0]=buf[0];
		M[b][1]=buf[1];
		}
	}

	/*----------------------------------------*/
	MM=M[1][0];										//counting of time gaps
	M[1][0]=MM-M[0][0];								//
	M[2][0]=M[2][0]-MM;								//
	/*----------------------------------------*/


	M[0][1]=M[0][1]+0b1000;
	M[1][1]=M[1][1]+M[0][1];
	M[2][1]=M[2][1]+M[1][1];
	
	Time1=Time*200-M[0][0]-M[1][0]-M[2][0];

	/*if(Time1!=0)
	{Time1=Time1-1;}*/


	RXB0CONbits.RXFUL=0;
	}
	if(ident==0b10101)
	{
	comm=RXB0D0;
	if(Time==0&&MODE==0xF0||phase1>200||phase2>200||phase3>200)
	{comm=0;}
		
	RXB0CONbits.RXFUL=0;
	}
}


///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
/*if(ident==0b11011&&phase1==202&&phase2==123&&phase3==52&&Time==111&&MODE==0xF0)
{
PORTA=0b111;
delay(500);
PORTA=0b000000;
delay(500);
ident=0b0;
phase1=0;
};*/
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////

if(comm==0xF0)
{
j=0;
c=0;
k=0;
for(i=0;i<2;i++)
{
k=PORTCbits. RC0;

	if(i==0)
	{
	j=k;
	k=0;
	}

	if(i==1)
	{
	c=k;
	k=0;
	}
}


if (j==0&&c==1)
{

delay(offset);
PORTA=0b00001000	;

/*------------------------------*/

/*for (a=0;a<3;a++)
	{
	delay(M[a][0]);
	if(M[a][1]==0b001)
	{
		
		PORTA=LATA+0b00000001;
	}

	if(M[a][1]==0b010)
	{
		
		PORTA=LATA+0b00000010;		
	}
	
	if(M[a][1]==0b100)
	{
		
		PORTA=LATA+0b00000100;
	}
	}
*/
/*----------*/
delay(M[0][0]);
PORTA=M[0][1];

delay(M[1][0]);
PORTA=M[1][1];

delay(M[2][0]);
PORTA=M[2][1];
/*----------*/
/*------------------------------*/

	if(MODE!=0x0F)
	{
	delay(Time1);
	PORTA=0b0;
	}
comm=0;

}
}

if(comm==0x0F)
{
PORTA=0b0;
comm=0;
}

}
}





