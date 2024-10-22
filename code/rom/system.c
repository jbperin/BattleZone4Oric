#include "system.h"
#include "input.h"
#include "keyboard.h"

#include "myRom.h"
#define USE_OSME 


extern unsigned char ScreenAdressLow[28];
extern unsigned char ScreenAdressHigh[28];
#define SCREEN_ADDRESS(lin,col) (char *)(ScreenAdressHigh[(lin)]<<8|ScreenAdressLow[(lin)]+col)
// extern void onKey(unsigned char c);
extern void onIT();
extern void onUserInput(char *);
extern unsigned char 	nbE_keybuf;

// Callback for when user has just entered a text
extern strcallbackfct          *txtinputcallback;
static char last_cursor_char = ' '; // Last char under cursor
static unsigned char last_beat=0;
#ifdef COUNTFPS
static unsigned char last_second=0;
static unsigned char current_fps=0;
static unsigned char counter_fps=0;
#endif


void onKeyPressed(unsigned char c){
	// printf ("kp: %x, ", c);
    pressKey(c);
    
    if (waitingKey){ 
        lastKey = c;
        waitingKey = 0;
    } else if (enteringText){
        if (c == KEY_RETURN) {
            *(SCREEN_ADDRESS(cursorL,cursorC)) = last_cursor_char;
            enteringText =0;
            //onUserInput(enteredText);
            if (txtinputcallback!=0)
                (*txtinputcallback)(enteredText);
                // FIXME: txtinputcallback=0;
            nbEnteredChar=0;
            enteredText[0]=0;
            //AdvancedPrint(10,26,enteredText);
        } else if (c == KEY_DELETE){
            if (nbEnteredChar > 0) {
                enteredText[--nbEnteredChar]=0;
                *(SCREEN_ADDRESS(cursorL,cursorC)) = ' ';
                cursorC--;
            }
        } else if ((c >= 32) && (c<125)){
            *(SCREEN_ADDRESS(cursorL,cursorC)) = c;
            enteredText[nbEnteredChar]=c;
            if (nbEnteredChar < enteredTextMaxlen) {
                nbEnteredChar++;
                cursorC++;
            }
        }
        onKey(c);
    } else {
        onKey(c);
    }

}

void onKeyReleased(unsigned char c){
    releaseKey(c);
}

void lsys(){
	unsigned char c;
//     PRINTN(9,17,kernel_s);
//     PRINTN(12,17,kernel_cs);
// #ifdef USE_OSME    
//     PRINTN(3,17,kernel_beat);
//     PRINTN(6,17,kernel_fraction);
// #endif // USE_OSME    
#ifdef COUNTFPS
    if (last_second != kernel_s){
        last_second = kernel_s;
        current_fps=counter_fps;
        counter_fps=0;
    } else {
        counter_fps+=1;
    }
    PRINTS(31,0, "      FPS");
    PRINTN(33,0,current_fps);
#endif
    if (last_beat != kernel_beat){
        last_beat = kernel_beat;
        onIT();
        // ((voidfct *)ptronIT)();*((int*)0x4c1)
    }
	while (nbE_keybuf != 0) {
		if ((c=get_keyevent()) & 0x80){
			onKeyReleased (c & 0x7F);
		} else {
			onKeyPressed (c);
		}
	}
    if (enteringText){
        if (kernel_cs>50) {
            *(SCREEN_ADDRESS(cursorL,cursorC)) = last_cursor_char;
        } else {
            *(SCREEN_ADDRESS(cursorL,cursorC)) = 0xA0;
        }
    }
    scanKey();

}
