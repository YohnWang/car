#include<reg51.h>
#include"timer.h"
#include"sensor.h"
static unsigned long _TimerClock=0;
unsigned long clock()
{
    return _TimerClock;
}
void sleep(clock_t time)
{
    clock_t start=clock();
    while(clock()-start<time){}
}
void initTimer()
{
    //TMOD=0x10;
    //PT1=1;
    TH1=(CYCLE_WHOLE-CYCLE_DELAY)/256;
    TL1=(CYCLE_WHOLE-CYCLE_DELAY)%256;
    ET1=1;
    TR1=1;
}


static void timer() interrupt 3
{
    TH1=(CYCLE_WHOLE-CYCLE_DELAY)/256;
    TL1=(CYCLE_WHOLE-CYCLE_DELAY)%256;
    _TimerClock+=TIME_INC;
}

