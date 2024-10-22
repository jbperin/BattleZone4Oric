
#ifndef KEYBOARD_H
#define KEYBOARD_H

#define KEY_Q       0x41
#define KEY_C       0x43
#define KEY_D       0x44
#define KEY_E       0x45
#define KEY_O       0x4F
#define KEY_A       0x51
#define KEY_S       0x53
#define KEY_W       0x5A
#define KEY_Z       0x57
#define KEY_X       0x58

#define KEY_Y       0x59
#define KEY_H       0x48
#define KEY_T       0x54
#define KEY_U       0x55
#define KEY_G       0x47
#define KEY_J       0x4A
#define KEY_L       0x4C

#define KEY_UP      0x01
#define KEY_DOWN    0x03
#define KEY_LEFT    0x02
#define KEY_RIGHT   0x04

#define KEY_ESCAPE  0x1B
#define KEY_RETURN  0x0D
#define KEY_SPACE   0x20
#define KEY_DELETE  0x7F

extern char keyForward;
extern char keyBackward;
extern char keyTurnLeft;
extern char keyTurnRight;
extern char keyStraffeLeft;
extern char keyStraffeRight;
extern char keyQuit;



#endif KEYBOARD_H
