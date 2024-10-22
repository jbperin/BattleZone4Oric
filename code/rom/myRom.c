
#include "myRom.h"


char IsHires=0;

void initRomFct(void){
    ptrRomFct[0]=    (voidfct*)AdvancedPrint;    // 0
    ptrRomFct[1]=    (voidfct*)DecimalPrint;     // 1
    ptrRomFct[2]=    (voidfct*)SwitchToText;     // 2
    ptrRomFct[3]=    (voidfct*)SwitchToHires;    // 3
    ptrRomFct[4]=    (voidfct*)inputText;        // 4
    ptrRomFct[5]=    (voidfct*)getKey;           // 5
    ptrRomFct[6]=    (voidfct*)getRand;          // 6
    ptrRomFct[7]=    (voidfct*)sndMusic;         // 7
    ptrRomFct[8]=    (voidfct*)sndSound;         // 8
    ptrRomFct[9]=    (voidfct*)sndPlay;          // 9
    ptrRomFct[10]=    (voidfct*)sndZap;           // 10
    ptrRomFct[11]=    (voidfct*)sndPing;          // 11
    ptrRomFct[12]=    (voidfct*)sndShoot;         // 12
    ptrRomFct[13]=    (voidfct*)sndExplode;       // 13
    ptrRomFct[14]=    (voidfct*)sndHKeyClick;     // 14
    ptrRomFct[15]=    (voidfct*)memorycpy;     // 15
    ptrRomFct[16]=    (voidfct*)memoryset;     // 16
    ptrRomFct[17]=    (voidfct*)asyncInputText;     // 17
}

void SwitchToText()
{
    // LoadFileAt(LOADER_FONT_6x8, 0xb500);
	if (IsHires)
	{
		// If not in TEXT; we need to switch from HIRES to TEXT
        // Clear the entire HIRES area with black ink
		memoryset((unsigned char*)0xa000,0,40*200);	
		// Move the charsets from BOTTOM to TOP
        memorycpy((unsigned char*)0xb400,(unsigned char*)0x9800,0xbb80-0xb400);		
        // Fill the entire TEXT area with spaces
		memoryset((unsigned char*)0xbb80,32,40*25);	
	}
    // 50hz Text attribute
    *((char*)0xbfdf) = 26;														
    *((char*)0xbbd0) = 0x10;
    *((char*)0xbbd1) = 0x07;
    *((char*)0xbbf8) = 0x10;
    *((char*)0xbbf9) = 0x07;
    *((char*)0xbf68) = 0x10;
    *((char*)0xbf69) = 0x07;
    *((char*)0xbf90) = 0x10;
    *((char*)0xbf91) = 0x07;

    //*((unsigned char *)LORES_SCREEN_ADDRESS+3*40+3)=33;


	IsHires=0;
}
void SwitchToHires()
{
	if (!IsHires)
	{
		// If not in HIRES; we need to switch from TEXT to HIRES
		memorycpy((unsigned char*)0x9800,(unsigned char*)0xb400,0xbb80-0xb400);		// Move the charsets from TOP to BOTTOM
		memoryset((unsigned char*)0xa000,0,40*200);									// Clear the entire HIRES area with black ink
		*((char*)0xbfdf)=30;														// 50hz Graphics attribute

		memoryset((unsigned char*)0xa000,64,40*200);									// Fill the entire HIRES area with neutral 64 value
	}
	IsHires=1;
    // memset((unsigned char*)0xbf40,0x20,40*4);
	
    // *((char*)0xbf40)=0x17;	
    // *((char*)0xbf41)=0x00;	
    // *((char*)0xbf68)=0x17;	
    // *((char*)0xbf69)=0x00;	
    // *((char*)0xbf90)=0x17;	
    // *((char*)0xbf91)=0x00;	
    // *((char*)0xbfb8)=0x17;	
    // *((char*)0xbfb9)=0x00;	
}