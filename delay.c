#include "p18cxxx.h"
#include "timer.h"
void delay(int time)
{
Timer1=time;
while(Timer1){}

}