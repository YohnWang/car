#include<reg51.h>
#include"motor.h"
#include"sensor.h"
#include"timer.h"

//static clock_t time_flag=0;//warning only in left and block


void run()
{
    static clock_t time_right;
    static clock_t time_left;
    static clock_t time_tmp;
    static unsigned char flag_right=1;
    static unsigned char flag_left=1;
    static unsigned char state=0;
    static char v_left=100,v_right=100;
    static unsigned int cnt_left=10,cnt_right=10;

    switch(state_edge())
    {
    case STRAIGHT:
        state=1;
        if(should_swerve_left()==SWERVE_LEFT)
        {
            v_left-=50;
            v_left-=50;
        }
        set_velocity(v_left,v_right);
        break;
    case DEVIATION_OF_LEFT:
        state=2;

        set_velocity(100,20);
        if(flag_left==1)
        {
            flag_left=0;cnt_left++;
            time_left=clock();
        }
        break;
    case DEVIATION_OF_RIGHT:
        state=3;

        set_velocity(20,100);
        if(flag_right==1)
        {
            flag_right=0;cnt_right++;
            time_right=clock();
        }
        break;
    case DEVIATION_OF_VERTICAL:
        state=4;
        set_velocity(100,100);
        //sleep(60);
        break;
    default:
        state=5;
        set_velocity(30,30);
    }
    /*调整*/
    if(flag_left==0&&state!=2)
    {
        flag_left=1;
        set_velocity(20,100);
        sleep(((clock()-time_left)>>2)&0x3f);
    }
    if(flag_right==0&&state!=3)
    {
        flag_right=1;
        set_velocity(100,20);
        sleep(((clock()-time_right)>>2)&0x3f);
    }
    /**/
    /*急调*/

    if(flag_right==0&&should_swerve_left()!=SWERVE_LEFT&&clock()-time_right>300)
    {
        time_tmp=clock();
        set_forward_or_backward(BACKWARD,FORWARD);
        while(state_edge()==DEVIATION_OF_RIGHT&&clock()-time_tmp<100)
            set_velocity(20,80);
        set_forward_or_backward(FORWARD,FORWARD);
    }

    if(flag_left==0&&should_swerve_right()!=SWERVE_RIGHT&&clock()-time_left>300)
    {
        time_tmp=clock();
        set_forward_or_backward(FORWARD,BACKWARD);
        while(state_edge()==DEVIATION_OF_LEFT&&clock()-time_tmp<100)
            set_velocity(80,20);
        set_forward_or_backward(FORWARD,FORWARD);
    }
    /**/

    if(cnt_left>cnt_right)
    {
        v_left=100;
        v_right=100*cnt_right/cnt_left;
    }
    else
    {
        v_right=100;
        v_left=100*cnt_left/cnt_right;
    }
}

void run_swerve_left()
{
    //static clock_t time=0;
    //static unsigned char flag=1;
    if(should_swerve_left()==SWERVE_LEFT&&should_swerve_right()==NOSWERVE/*&&flag==1*/)
    {
        //flag=0;
        //time=clock();
        set_velocity(80,80);
        set_forward_or_backward(BACKWARD,FORWARD);
        while(state_edge()==DEVIATION_OF_RIGHT&&/*should_swerve_left()==SWERVE_LEFT&&*/
                should_swerve_right()==NOSWERVE)
        {}
        set_forward_or_backward(FORWARD,FORWARD);
    }
    /*
    if(clock()-time>0)//不可关闭
    {
        flag=1;
    }*/
}

void run_swerve_right()
{
    if(should_swerve_right()==SWERVE_RIGHT)
    {
        while(should_swerve_right()==SWERVE_RIGHT/*&&state_edge()!=DEVIATION_OF_RIGHT*/)
        {
            if(should_swerve_left()==SWERVE_LEFT)
            {
                goto here;
            }

            if(state_edge()==DEVIATION_OF_RIGHT)
                break;
            here:
            set_forward_or_backward(FORWARD,BACKWARD);
            //while(state_edge()!=DEVIATION_OF_RIGHT)
            set_velocity(80,80);
        }
        set_forward_or_backward(FORWARD,FORWARD);
    }
}
void run_swerve_block()
{
    //static unsigned char flag=1;
    //static clock_t time;
    static clock_t time_open=0;
    if(right_sensor()==HAVE_BLOCK||right_sensor2()==HAVE_BLOCK)
    {
        if(clock()-time_open<1400)
            return;
        set_velocity(50,50);
        sleep(50);
        if(right_sensor()!=HAVE_BLOCK&&right_sensor2()!=HAVE_BLOCK)
            return ;
        set_forward_or_backward(FORWARD,BACKWARD);
        while(right_sensor()==HAVE_BLOCK||right_sensor2()==HAVE_BLOCK)
            set_velocity(100,100);
        while(left_sensor()==NONE)
            set_velocity(100,100);
        //set_forward_or_backward(FORWARD,FORWARD);
        while(left_sensor()==HAVE_BLOCK)
            set_velocity(100,100);
        //sleep(10);
        set_forward_or_backward(FORWARD,FORWARD);

        while(should_go_block()==SWERVE_BLOCK&&
              should_swerve_right()!=SWERVE_RIGHT)
            set_velocity(100,100);

        while(/*should_swerve_right()!=SWERVE_RIGHT&&*/
              state_edge()==DEVIATION_OF_RIGHT)
        {
            while(should_go_block()==GO_BLOCK&&should_swerve_right()!=SWERVE_RIGHT&&
                  state_edge()==DEVIATION_OF_RIGHT)
                set_velocity(70,70);
            //time=clock();
            while(should_go_block()==SWERVE_BLOCK&&/*should_swerve_right()!=SWERVE_RIGHT&&*/
                  state_edge()==DEVIATION_OF_RIGHT)
            {
                set_forward_or_backward(BACKWARD,FORWARD);
                set_velocity(50,60);
            }
            set_forward_or_backward(FORWARD,FORWARD);

        }/*
        set_forward_or_backward(BACKWARD,BACKWARD);
        set_velocity(50,100);
        sleep(100);
        set_forward_or_backward(FORWARD,FORWARD);
        time=clock();
        while(should_swerve_right()==SWERVE_RIGHT)
        {
            set_forward_or_backward(FORWARD,BACKWARD);
            set_velocity(50,50);
        }
        //set_forward_or_backward(FORWARD,FORWARD);
        time=clock()-time;
        set_forward_or_backward(FORWARD,BACKWARD);
        set_velocity(50,50);
        sleep(time>>2);
        set_forward_or_backward(FORWARD,FORWARD);
        set_velocity(40,100);
        sleep(time>>2);*/

        time_open=clock();
    }
    return ;

}
void run_swerve_small_block()
{
    if(have_block1()==HAVE_BLOCK/*&&should_swerve_left()==SWERVE_LEFT*/)
    {
        set_velocity(80,80);
        sleep(20);
        if(have_block1()!=HAVE_BLOCK)
            return ;
        set_forward_or_backward(FORWARD,BACKWARD);
        while(have_block1()==HAVE_BLOCK)
            set_velocity(100,50);
        set_forward_or_backward(FORWARD,FORWARD);
        while(should_go_block()!=GO_BLOCK)
            set_velocity(100,100);

        while(/*should_swerve_right()!=SWERVE_RIGHT&&*/
              state_edge()==DEVIATION_OF_RIGHT)
        {
            while(should_go_block()==GO_BLOCK&&/*should_swerve_right()!=SWERVE_RIGHT&&*/
                  state_edge()==DEVIATION_OF_RIGHT)
                set_velocity(70,70);
            //time=clock();
            while(should_go_block()==SWERVE_BLOCK&&/*should_swerve_right()!=SWERVE_RIGHT&&*/
                  state_edge()==DEVIATION_OF_RIGHT)
            {
                set_forward_or_backward(BACKWARD,FORWARD);
                set_velocity(50,60);
            }
            set_forward_or_backward(FORWARD,FORWARD);
            /*
            while(state_edge()==DEVIATION_OF_VERTICAL)
            {
                set_forward_or_backward(FORWARD,BACKWARD);
                set_velocity(50,50);
            }
            set_forward_or_backward(FORWARD,FORWARD);*/
        }
    }
}

int main()
{
    unsigned char line_cnt;

    set_velocity(0,0);
    TMOD=0x10|0x01;
    init_motor();
    initTimer();

    set_forward_or_backward(FORWARD,FORWARD);
    EA=1;
    sleep(500);
    initInter0();
    line_cnt=get_black_line_cnt();
    for(;get_black_line_cnt()-line_cnt<2;)
    {
        run_swerve_small_block();
        run_swerve_right();
        run_swerve_left();
        run();
        run_swerve_block();
        run_swerve_right();
        run_swerve_left();
    }
    set_velocity(0,0);
    for(;;){}

    return 0;
}
