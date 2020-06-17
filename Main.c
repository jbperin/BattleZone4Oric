
#include <lib.h>

#define SCREEN_WIDTH                    40
#define SCREEN_HEIGHT                   26
#define LORES_SCREEN_ADDRESS            0xBB80 
#define HIRES_SCREEN_ADDRESS            0xA000
#define STANDARD_CHARSET_ADDRESS        0xB400
#define aLTERNATE_CHARSET_ADDRESS       0xB800
#define NB_LESS_LINES_4_COLOR           4

#define CHANGE_INK_TO_BLACK	            0		
#define CHANGE_INK_TO_RED	            1		
#define CHANGE_INK_TO_GREEN	            2		
#define CHANGE_INK_TO_YELLOW	        3		
#define CHANGE_INK_TO_BLUE	            4		
#define CHANGE_INK_TO_MAGENTA           5			
#define CHANGE_INK_TO_CYAN	            6		
#define CHANGE_INK_TO_WHITE	            7	

#define USE_STANDARD_CHARSET    	                    8		
#define USE_ALTERNATE_CHARSET	                    9		
#define USE_DOUBLE_SIZE_STANDARD_CHARSET	    10		
#define USE_DOUBLE_SIZE_ALTERNATE_CHARSET	    11		
#define USE_BLINKING_STANDARD_CHARSET	            12		
#define USE_BLINKING_ALTERNATE_CHARSET	            13		
#define USE_DOUBLE_SIZE_BLINKING_STANDARD_CHARSET   14		
#define USE_DOUBLE_SIZE_BLINKING_ALTERNATE_CHARSET  15		
// Change Paper (background) color	
#define CHANGE_PAPER_TO_BLACK			    16		
#define CHANGE_PAPER_TO_RED	                    17		
#define CHANGE_PAPER_TO_GREEN	                    18		
#define CHANGE_PAPER_TO_YELLOW	                    19		
#define CHANGE_PAPER_TO_BLUE	                    20		
#define CHANGE_PAPER_TO_MAGENTA	                    21		
#define CHANGE_PAPER_TO_CYAN	                    22		
#define CHANGE_PAPER_TO_WHITE	                    23		
// Video control attributes	
#define SWITCH_TO_TEXT_MODE_60HZ		    24		
#define SWITCH_TO_TEXT_MODE_50HZ		    26		
#define SWITCH_TO_HIRES_MODE_60HZ	            28		
#define SWITCH_TO_HIRES_MODE_50HZ                   30		



extern int LargeX0;
extern int LargeY0;
extern int LargeX1;
extern int LargeY1;
extern void DrawClippedLine();

extern char CurrentPixelX;
extern char CurrentPixelY;
extern char OtherPixelX;
extern char OtherPixelY;
extern void DrawLine8();

void change_char(char c, unsigned char patt01, unsigned char patt02, unsigned char patt03, unsigned char patt04, unsigned char patt05, unsigned char patt06, unsigned char patt07, unsigned char patt08) {
    unsigned char* adr;
    adr      = (unsigned char*)(0xB400 + c * 8);
    *(adr++) = patt01;
    *(adr++) = patt02;
    *(adr++) = patt03;
    *(adr++) = patt04;
    *(adr++) = patt05;
    *(adr++) = patt06;
    *(adr++) = patt07;
    *(adr++) = patt08;
}

void prepare_graphics() {
    int ii, jj;
    
    memset(HIRES_SCREEN_ADDRESS, 64, 5500);
    memset(LORES_SCREEN_ADDRESS, 32, 40*25);
    // cls();
    poke (LORES_SCREEN_ADDRESS,SWITCH_TO_TEXT_MODE_50HZ);
    poke (LORES_SCREEN_ADDRESS+1,CHANGE_INK_TO_RED);
    for (ii = 0; ii<=4 ; ii++){
        // poke (LORES_SCREEN_ADDRESS+(ii*SCREEN_WIDTH)+0,SWITCH_TO_TEXT_MODE_50HZ);
        // poke (LORES_SCREEN_ADDRESS+(ii*SCREEN_WIDTH)+0,CHANGE_PAPER_TO_GREEN);
        poke (LORES_SCREEN_ADDRESS+(ii*SCREEN_WIDTH)+0,CHANGE_INK_TO_RED);
        poke (LORES_SCREEN_ADDRESS+(ii*SCREEN_WIDTH)+17,SWITCH_TO_HIRES_MODE_50HZ);
        for (jj = 0; jj < 8; jj++) {
            poke (HIRES_SCREEN_ADDRESS+((ii*8+jj)*SCREEN_WIDTH)+24,SWITCH_TO_TEXT_MODE_50HZ);
        }
    }
    for (ii=5; ii<=16 ; ii++){
        poke (LORES_SCREEN_ADDRESS+(ii*SCREEN_WIDTH)+0,CHANGE_INK_TO_GREEN);
        poke (LORES_SCREEN_ADDRESS+(ii*SCREEN_WIDTH)+1,SWITCH_TO_HIRES_MODE_50HZ);
        for (jj = 0; jj < 8; jj++) poke (HIRES_SCREEN_ADDRESS+((ii*8+jj)*SCREEN_WIDTH)+39,SWITCH_TO_TEXT_MODE_50HZ);
    }
    // for (jj = 0; jj < 8; jj++) poke (HIRES_SCREEN_ADDRESS+((15*8+jj)*SCREEN_WIDTH)+0,CHANGE_INK_TO_GREEN);

    // for (jj = 0; jj < 8; jj++) poke (HIRES_SCREEN_ADDRESS+((15*8+jj)*SCREEN_WIDTH)+1,SWITCH_TO_TEXT_MODE_50HZ);
    // for (ii=5; ii<=SCREEN_HEIGHT-NB_LESS_LINES_4_COLOR ; ii++){
    //     poke (LORES_SCREEN_ADDRESS+(ii*SCREEN_WIDTH)+0,CHANGE_INK_TO_GREEN);
    // }

    // for (ii=5; ii<=SCREEN_HEIGHT-NB_LESS_LINES_4_COLOR ; ii++){
    //     poke (LORES_SCREEN_ADDRESS+(ii*SCREEN_WIDTH)+0,SWITCH_TO_HIRES_MODE_50HZ);
    //     for (jj = 0; jj < 8; jj++) {
    //         poke (HIRES_SCREEN_ADDRESS+((ii*8+jj)*SCREEN_WIDTH)+1,CHANGE_INK_TO_GREEN);
    //         poke (HIRES_SCREEN_ADDRESS+((ii*8+jj)*SCREEN_WIDTH)+2,SWITCH_TO_TEXT_MODE_50HZ);
    //     }
    // }
        // poke (LORES_SCREEN_ADDRESS+(ii*SCREEN_WIDTH)+0,CHANGE_INK_TO_GREEN);
        // poke (LORES_SCREEN_ADDRESS+(ii*SCREEN_WIDTH)+1,SWITCH_TO_HIRES_MODE_50HZ);
    //for (; ii<=20 ; ii++)
        
    // ii++;
    // poke (HIRES_SCREEN_ADDRESS+(((SCREEN_HEIGHT-NB_LESS_LINES_4_COLOR)*8)*SCREEN_WIDTH)+0, SWITCH_TO_TEXT_MODE_50HZ);
//     for (; ii<=SCREEN_HEIGHT-NB_LESS_LINES_4_COLOR ; ii++){
//         for (jj = 0; jj < 8; jj++) {
//             poke (HIRES_SCREEN_ADDRESS+((ii*8+jj)*SCREEN_WIDTH)+24,CHANGE_INK_TO_GREEN);
//         }
// //         poke (LORES_SCREEN_ADDRESS+(ii*SCREEN_WIDTH)+0,SWITCH_TO_HIRES_MODE_50HZ);
// //         // fbuffer[ii*SCREEN_WIDTH]=HIRES_50Hz;
// //         // for (jj = 0; jj < 8; jj++) {
// //         //     poke (HIRES_SCREEN_ADDRESS+((ii*8+jj)*SCREEN_WIDTH)+1, tab_color[jj]);
// //         //     poke (HIRES_SCREEN_ADDRESS+((ii*8+jj)*SCREEN_WIDTH)+2, SWITCH_TO_TEXT_MODE_50HZ);
// //         // }
// //     }
// //     for (; ii<=SCREEN_HEIGHT-NB_LESS_LINES_4_COLOR ; ii++){
            
//     }
    // poke (HIRES_SCREEN_ADDRESS+(((SCREEN_HEIGHT-NB_LESS_LINES_4_COLOR)*8+0)*SCREEN_WIDTH)+0,SWITCH_TO_TEXT_MODE_50HZ);
}
#define LASTLINE 135
void main()
{
        printf ("debut \n");
        // get();
        GenerateTables();
        prepare_graphics();
        sprintf (LORES_SCREEN_ADDRESS+(1*SCREEN_WIDTH)+2 , "ENEMY IN RANGE");
        sprintf (LORES_SCREEN_ADDRESS+(2*SCREEN_WIDTH)+2 , "ENEMY TO LEFT");
        sprintf (LORES_SCREEN_ADDRESS+(1*SCREEN_WIDTH)+26 , "HI SCR    9000");
        sprintf (LORES_SCREEN_ADDRESS+(3*SCREEN_WIDTH)+26 , "SCORE     2000");

        OtherPixelX=120;
        OtherPixelY=0;
        CurrentPixelX=120;
        CurrentPixelY=3*8;
        DrawLine8();

        LargeX0=3;
        LargeY0=LASTLINE;
        LargeX1=239;
        LargeY1=LASTLINE;
        DrawClippedLine();

        get();
        printf ("fin \n");
        

}


