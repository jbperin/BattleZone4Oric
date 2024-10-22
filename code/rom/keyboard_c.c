#include "keyboard.h"


char keyForward         = KEY_UP;
char keyBackward        = KEY_DOWN;
char keyTurnLeft        = KEY_LEFT;
char keyTurnRight       = KEY_RIGHT;
char keyStraffeLeft     = KEY_X;
char keyStraffeRight    = KEY_C;
char keyQuit            = KEY_ESCAPE;

unsigned char keybconfig        = 0; // 0 : ArrowKeys + XC,  1: AZEQSD , 2 : TYUGHJ
unsigned char soundenabled      = 0; // 0 : No Sound, 1 = Sound Enabled


void setKeyboardConfig(){
    if (keybconfig == 0) {
        keyForward         = KEY_UP;
        keyBackward        = KEY_DOWN;
        keyTurnLeft        = KEY_LEFT;
        keyTurnRight       = KEY_RIGHT;
        keyStraffeLeft     = KEY_X;
        keyStraffeRight    = KEY_C;
        keyQuit            = KEY_ESCAPE;
    } else if (keybconfig == 1) {
        keyForward         = KEY_Z;
        keyBackward        = KEY_S;
        keyTurnLeft        = KEY_A;
        keyTurnRight       = KEY_E;
        keyStraffeLeft     = KEY_Q;
        keyStraffeRight    = KEY_D;
        keyQuit            = KEY_ESCAPE;
    } else if (keybconfig == 2) {
        keyForward         = KEY_Y;
        keyBackward        = KEY_H;
        keyTurnLeft        = KEY_T;
        keyTurnRight       = KEY_U;
        keyStraffeLeft     = KEY_G;
        keyStraffeRight    = KEY_J;
        keyQuit            = KEY_ESCAPE;
    }
}
