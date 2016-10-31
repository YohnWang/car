#ifndef MOTOR_H
#define MOTOR_H

#define STAY   (-1)
#define LEFT    0
#define RIGHT   1
#define FORWARD 1
#define BACKWARD 0

extern void init_motor();
extern void set_velocity(signed char left,signed char right);
extern void swerve(unsigned char direction,unsigned char angle);
extern void set_forward_or_backward(unsigned char left,unsigned char right);

#define run_full() set_velocity(100,100)


#endif // MOTOR_H
