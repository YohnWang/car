#ifndef TIMER_H
#define TIMER_H
typedef unsigned long clock_t;

extern unsigned long clock();      //get the now time clock
extern void initTimer();           //initialize timer
extern void sleep(clock_t time);   //delay  ��λms ����Ϊ TIME_INC ms

//��һ������Ϊÿ�β���ʱ���жϵĻ���������
//�ڶ���������ʱ�����Ļ���������
//������������û����һ���жϵ�ʱ���� ��λms
//������Ҫ�Լ����� //���в���Ϊ12M���� 12��Ƶ �жϼ��1ms
#define CYCLE_DELAY 2000
#define CYCLE_WHOLE 65536
#define TIME_INC    1


#endif
