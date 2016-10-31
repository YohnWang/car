#ifndef SENSOR_H
#define SENSOR_H

#define BRIGHT 0
#define DARK   1



enum{NONE,STRAIGHT,DEVIATION_OF_LEFT,DEVIATION_OF_RIGHT,DEVIATION_OF_VERTICAL,
     NOSWERVE,SHOULDSWERVE,SWERVE_RIGHT,SWERVE_LEFT,
     SWERVE_BLOCK,SWERVE_BLOCK_STOP,SWERVE_BLOCK_CONTINUE,GO_BLOCK,
     HAVE_BLOCK,HAVE_LINE,
     };

extern char state_edge();
extern char should_swerve_left();
extern char should_swerve_right();
extern char should_swerve_block();
extern char right_sensor();
extern char right_sensor2();
extern char left_sensor();
extern char should_go_block();
extern char have_block1();
//extern char have_black_line();
extern void initInter0();
extern unsigned char get_black_line_cnt();
#endif // SENSOR_H
