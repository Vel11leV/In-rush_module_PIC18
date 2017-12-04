/*500kBt*/


#include "p18cxxx.h"


void Init_can (void)
{
/*------------------------------настройка портов------------------------------*/
TRISBbits.TRISB3=1;
TRISBbits.TRISB2=0;

/*---------------------------вход в режим настройки---------------------------*/
CANCONbits.REQOP2=0b1;
CANCONbits.REQOP1=0b0;
CANCONbits.REQOP0=0b0;
while(!CANCONbits.REQOP2){};

/*-------------------------сброс всех масок и фильтров------------------------*/
RXM0SIDH=0;
RXM1SIDH=0;

RXM0SIDL=0;
RXM1SIDL=0;

RXM0EIDH=0;
RXM1EIDH=0;

RXM0EIDL=0;
RXM1EIDL=0;

/*--------------------------настройка приемных буферов-------------------------*/
RXB0CONbits.RXM1=0b0;
RXB0CONbits.RXM0=0b1;
RXB0CONbits.RXB0DBEN=0b0; //запрет на дублирование


CIOCONbits.CANCAP=0;


/*--------------------------настройка скорости передачи------------------------*/
BRGCON1bits.BRP5=0b0;
BRGCON1bits.BRP4=0b0;
BRGCON1bits.BRP3=0b0;
BRGCON1bits.BRP2=0b0;
BRGCON1bits.BRP1=0b1;
BRGCON1bits.BRP0=0b1;


/*----------------------свободное программирование второго фазового сегмента---*/
BRGCON2bits.SEG2PHTS=1;

/*---------------------------------выборка 1 раз-------------------------------*/
BRGCON2bits.SAM=0b0;

/*------------------------no wake up when bus is active------------------------*/
BRGCON3bits.WAKFIL=0;



/*----------------------------------PropSeg=2TQ--------------------------------*/
BRGCON2bits.PRSEG2=0b0;
BRGCON2bits.PRSEG1=0b1;    //
BRGCON2bits.PRSEG0=0b0;

/*------------------------------------PS1=8TQ-----------------------------------*/
BRGCON2bits.SEG1PH2=0b1;
BRGCON2bits.SEG1PH1=0b1;
BRGCON2bits.SEG1PH0=0b1;

/*------------------------------------PS2=2TQ-----------------------------------*/
BRGCON3bits.SEG2PH2=0b1;
BRGCON3bits.SEG2PH1=0b1;
BRGCON3bits.SEG2PH0=0b1;

/*------------------------------------SJW=1TQ-----------------------------------*/
BRGCON1bits.SJW1=0b0;
BRGCON1bits.SJW0=0b0;

/*-----------------выход из режима настройки в нормальный режим работы----------*/
CANCONbits.REQOP2=0b0;
CANCONbits.REQOP1=0b0;
CANCONbits.REQOP0=0b0;
while((CANCONbits.REQOP2)&&(CANCONbits.REQOP1)&&(CANCONbits.REQOP0=0b0));
}


/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////


void tr_can(unsigned char ident1, unsigned char ident2, unsigned char m)
{

TXB0SIDH=ident1;

TXB0SIDLbits.SID2=0b0;
TXB0SIDLbits.SID1=0b0;
TXB0SIDLbits.SID0=0b0;

TXB0SIDLbits.EXIDE=0b0;

TXB0SIDLbits.EID17=0b0;
TXB0SIDLbits.EID16=0b0;




TXB0D0=m;
TXB0D1=0;
TXB0D2=0;
TXB0D3=0;
TXB0D4=0;
TXB0D5=0;
TXB0D6=0;
TXB0D7=0;
TXB0DLC=8;
TXB0CONbits.TXREQ=0b1;
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

void resrb0_init()
{
RXB0CONbits.RXM1=0b1; //принимать 
RXB0CONbits.RXM0=0b1; //все сообщения
//RXB0CONbits.RXFUL=0;  //приемный буфер готов к приему сообщения
}