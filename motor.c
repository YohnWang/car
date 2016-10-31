#include<reg51.h>


static signed char velocity_left=0;
static signed char velocity_right=0;

sbit motor_left=P1^0; //need changing
sbit motor_right=P1^1;//need changing
sbit motor_left_in1=P1^2;
sbit motor_left_in2=P1^3;
sbit motor_right_in1=P1^4;
sbit motor_right_in2=P1^5;

sbit debug_flag=P2^0;

#define CYCLE_DELAY 200
#define CYCLE_WHOLE 65536
#define TIME_INC    1
#define RUN     1
#define STOP    0
#define STAY   (-1)
#define LEFT    0
#define RIGHT   1
#define FORWARD 1
#define BACKWARD 0

void init_motor()
{
    //TMOD=1;
    //PT0=1;
    TH0=(CYCLE_WHOLE-CYCLE_DELAY)/256;
    TL0=(CYCLE_WHOLE-CYCLE_DELAY)%256;
    ET0=1;
    TR0=1;
}
#if 0
void set_forward_or_backward(unsigned char left_or_right,unsigned char forward_or_backward)
{
    if(left_or_right==LEFT)
    {
        if(forward_or_backward==FORWARD)
        {
            motor_left_in1=1;
            motor_left_in2=0;
        }
        else if(forward_or_backward==BACKWARD)
        {
            motor_left_in1=0;
            motor_left_in2=1;
        }
        else//exception
        {

        }
    }
    else if(left_or_right==RIGHT)
    {
        if(forward_or_backward==FORWARD)
        {
            motor_right_in1=1;
            motor_right_in2=0;
        }
        else if(forward_or_backward==BACKWARD)
        {
            motor_right_in1=0;
            motor_right_in2=1;
        }
        else//exception
        {

        }
    }
    else //exception
    {

    }
}
#endif // 0
void set_forward_or_backward(unsigned char left,unsigned char right)
{
    if(left==FORWARD)
    {
        motor_left_in1=1;
        motor_left_in2=0;
    }
    else if(left==BACKWARD)
    {
        motor_left_in1=0;
        motor_left_in2=1;
    }
    else
    {

    }

    if(right==FORWARD)
    {
        motor_right_in1=1;
        motor_right_in2=0;
    }
    else if(right==BACKWARD)
    {
        motor_right_in1=0;
        motor_right_in2=1;
    }
    else
    {

    }
}


void set_velocity(signed char left,signed char right)
{
    if(debug_flag==0)
    {
        left/=2;
        right/=2;
    }
    if(left!=STAY)
    {
        if(right>80)
            velocity_left=(char)((int)left*3/4);
        else if(right>60)
            velocity_left=(char)((int)left*4/5);
        else if(right>40)
            velocity_left=(char)((int)left*7/8);
        else if(right>20)
            velocity_left=(char)((int)left*9/10);
        else
            velocity_left=left;
        //velocity_left=left;
    }
    if(left!=STAY)
    {
        velocity_right=right;
    }
}
/*
void delayms(unsigned char t)
{
    unsigned char i,j;
    for(;--t;)
        for(i=30;i;--i)
            for(j=30;j;--j){}
}
void swerve(unsigned char direction,unsigned char angle)
{
    signed char tmp_left,tmp_right;
    tmp_left=velocity_left;
    tmp_right=velocity_right;
    //set_velocity(0,0);
    if(direction==LEFT)
    {
        //set_velocity(velocity_left/4,velocity_right);
        set_velocity(0,velocity_right);
    }
    else if(direction==RIGHT)
    {
        //set_velocity(velocity_left,velocity_right/4);
        set_velocity(velocity_left,0);
    }
    else //if direction is wrong,it will happen
    {
        set_velocity(0,0);
        for(;;){}
    }
    delayms(angle);
    velocity_left=tmp_left;
    velocity_right=tmp_right;
}*/

static void motor_driver() interrupt 1
{
    static signed char left_times=0;
    static signed char right_times=0;
    TH0=(CYCLE_WHOLE-CYCLE_DELAY)/256;
    TL0=(CYCLE_WHOLE-CYCLE_DELAY)%256;
    ++left_times;
    ++right_times;
    if(left_times>99)
        left_times=0;
    if(right_times>99)
        right_times=0;
    if(left_times<velocity_left)
    {
        motor_left=RUN;
    }
    else
    {
        motor_left=STOP;
    }
    if(right_times<velocity_right)
    {
        motor_right=RUN;
    }
    else
    {
        motor_right=STOP;
    }
}
