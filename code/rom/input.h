#ifndef INPUT_H
#define INPUT_H

#define NB_MAX_ENTER_TEXT   40



// Cursor Line and Column
extern unsigned char           cursorL;
extern unsigned char           cursorC; 
// Flag indicating if user is entering text
extern unsigned char           enteringText; 
// Flag indicating that user is asked to hit a key
extern unsigned char           waitingKey ; 

// String containing user entered text
extern char                    enteredText[NB_MAX_ENTER_TEXT];
extern unsigned char           nbEnteredChar;
extern unsigned char           enteredTextMaxlen;

extern unsigned char           lastKey;

extern unsigned char getKey();
extern void inputText(unsigned char l, unsigned char c, unsigned char maxlen, char *target);

#endif INPUT_H
