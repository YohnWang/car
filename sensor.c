#include<reg51.h>
#include"sensor.h"
#include"timer.h"
sbit sensor1=P0^1;
sbit sensor2=P0^2;
sbit sensor3=P0^3;
sbit sensor4=P0^4;
sbit sensor5=P0^5;
sbit sensor6=P0^6;
sbit sensor7=P0^7;
sbit sensor8=P2^7;
sbit sensor9=P2^6;
sbit sensor10=P2^5;//test black line

char state_edge()
{
    if(sensor1==DARK && sensor2==BRIGHT)
        return STRAIGHT;
    else if(sensor1==DARK && sensor2==DARK)
        return DEVIATION_OF_LEFT;
    else if(sensor1==BRIGHT && sensor2==BRIGHT)
        return DEVIATION_OF_RIGHT;
    else
        return DEVIATION_OF_VERTICAL;
}

char should_swerve_left()
{
    if(sensor3==DARK)
        return NOSWERVE;
    else
        return SWERVE_LEFT;
}

char should_swerve_right()
{
    if(sensor4==DARK)
        return SWERVE_RIGHT;
    else
        return NOSWERVE;
}
#define NO_USING
#ifndef NO_USING
char should_swerve_block()
{
    if(sensor5==BRIGHT&&sensor7==BRIGHT&&sensor9==BRIGHT)
        return SWERVE_BLOCK;
    else if(sensor5==DARK&&sensor7==DARK)
        return SWERVE_BLOCK_STOP;
    else if(sensor5==BRIGHT&&sensor7==DARK)
        return SWERVE_BLOCK_CONTINUE;
    else
        return NONE;
}
#endif // NO_USING
char right_sensor()
{
    if(sensor7==BRIGHT)
        return HAVE_BLOCK;
    else
        return NONE;
}
char right_sensor2()
{
    if(sensor9==BRIGHT)
        return HAVE_BLOCK;
    else
        return NONE;
}

char left_sensor()
{
    /*
    if(sensor5==BRIGHT)
    {
        sleep(5);
        if(sensor5==BRIGHT)
            return HAVE_BLOCK;
        else
            return NONE;
    }
    else
        return NONE;*/
    char i,cnt=0,max=0;
    for(i=0;i<10;i++)
    {
        if(sensor5==BRIGHT)
            cnt++;
        else
            cnt=0;
        if(cnt>max)
            max=cnt;
        sleep(1);
    }
    if(max<4)
        return NONE;
    else
        return HAVE_BLOCK;

}

char should_go_block()
{
    if(sensor6==BRIGHT)
        return GO_BLOCK;
    else
        return SWERVE_BLOCK;
}

char have_block1()
{
    if(sensor8==BRIGHT)
        return HAVE_BLOCK;
    else
        return NONE;
}

#if 0
char have_black_line()
{
    static unsigned char flag=0;
    static clock_t time=0;
    if(sensor10==1&&flag==0&&clock()-time>3)
    {
        flag=1;
        time=clock();
        return HAVE_LINE;
    }
    else if(sensor10==0)
    {
        flag=0;
    }
    return NONE;
}
#endif // 0
static unsigned char BLACK_LINE_CNT=0;
void initInter0()
{
    IT0=1;  //interrupt
    PX0=1;
    EX0=1;
}
static void inter0() interrupt 0
{
    static clock_t time=0;
    static clock_t before=0;
    static unsigned char flag=0;
    //static unsigned char cnt=0;
    clock_t now=clock();
    if(flag==0 && now-time >300)
    {
        //insert code
        //flag=1;
        BLACK_LINE_CNT++;
        //end
    }
    time=now;
    before=now;
}
unsigned char get_black_line_cnt()
{
    return BLACK_LINE_CNT;
}
