
#include "input.h"
#include "myRom.h"

// Cursor Line and Column
unsigned char           cursorL=26;
unsigned char           cursorC=4; 
// Flag indicating if user is entering text
unsigned char           enteringText = 0; 
// Flag indicating that user is asked to hit a key
unsigned char           waitingKey = 0; 

// String containing user entered text
char                    enteredText[NB_MAX_ENTER_TEXT];
unsigned char           nbEnteredChar = 0;
unsigned char           enteredTextMaxlen = NB_MAX_ENTER_TEXT;
unsigned char           lastKey = 0;

// Callback for when user has just entered a text
strcallbackfct          *txtinputcallback = 0;

#define min(a,b)            (((a) < (b)) ? (a) : (b))

void inputText(unsigned char l, unsigned char c, unsigned char maxlen, char *target){
    cursorL = l;
    cursorC = c;
    enteredTextMaxlen = min(maxlen, NB_MAX_ENTER_TEXT);
    MEMSET((unsigned char*)enteredText, 0, NB_MAX_ENTER_TEXT);
    nbEnteredChar = 0;
    enteringText = 1;
    while (enteringText){
        lsys();
    }
    MEMCPY((unsigned char*)target, (unsigned char*)enteredText, maxlen);
}
void asyncInputText(unsigned char l, unsigned char c, unsigned char maxlen, strcallbackfct *callback){
    cursorL = l;
    cursorC = c;
    enteredTextMaxlen = min(maxlen, NB_MAX_ENTER_TEXT);
    MEMSET((unsigned char*)enteredText, 0, NB_MAX_ENTER_TEXT);
    nbEnteredChar = 0;
    enteringText = 1;
    txtinputcallback = callback;
}
unsigned char getKey(){
    waitingKey = 1;
    while (waitingKey){
        lsys();
    }
    return (lastKey);
}