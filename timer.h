#ifndef TIMER_H
#define TIMER_H
typedef unsigned long clock_t;

extern unsigned long clock();      //get the now time clock
extern void initTimer();           //initialize timer
extern void sleep(clock_t time);   //delay  单位ms 精度为 TIME_INC ms

//第一个参数为每次产生时钟中断的机器周期数
//第二个参数是时钟最大的机器周期数
//第三个参数是没发生一次中断的时间间隔 单位ms
//参数需要自己计算 //下列参数为24M晶振 12分频 中断间隔1ms
#define CYCLE_DELAY 2000
#define CYCLE_WHOLE 65536
#define TIME_INC    1


#endif
