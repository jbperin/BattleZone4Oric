
#include <lib.h>

#include "glOric.h"

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
#define USE_DOUBLE_SIZE_BLINKING_STANDARD_CHARSET   12		
#define USE_DOUBLE_SIZE_BLINKING_ALTERNATE_CHARSET  13		
#define USE_BLINKING_STANDARD_CHARSET	            14		
#define USE_BLINKING_ALTERNATE_CHARSET	            15		
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

// Shall match CLIP_TOP
#define FIRSTLINE 40
// Shale match CLIP_BOTTOM
#define LASTLINE 128

#define HORIZONLINE 88

/*
 * VISIBILITY LIMITS
 */
#define ANGLE_MAX 0xC0
#define ANGLE_VIEW 0xE0


#define abs(x)                 (((x)<0)?-(x):(x))

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


//
// ===== circle.s =====
//
extern unsigned int CentreX;			// Coordinate X of the circle centre
extern unsigned int CentreY;			// Coordinate Y of the circle centre
extern unsigned int Radius;				// Circle radius

extern void circleMidpoint();



// LANDSCAPE
extern unsigned int  tabPointsX[];
extern unsigned char tabPointsY[];
extern unsigned char tabSegPt1[];
extern unsigned char tabSegPt2[];
extern unsigned char tabIdxFirstSeg[];
extern unsigned char tabNbLeftClipSeg[];
extern unsigned char tabNbRightClipSeg[];
extern unsigned char tabNoClipSeg[];
extern unsigned int  tabOffset[];


char inGame = 1;
unsigned char debugOn = 0;
unsigned char enemyInRange = 0;
unsigned char enemyToLeft = 0;
unsigned char enemyToRight = 0;
unsigned int highScore = 9000;
unsigned int currentScore = 200;
unsigned char nbRemaingLife = 3;
unsigned char isLandscape2BeRedrawn = 1;
unsigned char isScene2BeRedrawn = 1;

void revertDebug(){
    debugOn = (debugOn==0)?1:0;
}
void player ();

#include "lrs.c"

#include "drawLandscape.c"

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
// #define ASM_ANGLE_MAX $C0
// #define ASM_ANGLE_VIEW $E0

// angle of FOV = 0.7854 radians

void drawRadar () {
    CentreX=126;
	CentreY=20;
    Radius=15;
    circleMidpoint();

    OtherPixelX=CentreX;
    OtherPixelY=CentreY;
    CurrentPixelX=OtherPixelX - 5;
    CurrentPixelY=OtherPixelY - 15;
    DrawLine8();

    OtherPixelX=CentreX;
    OtherPixelY=CentreY;
    CurrentPixelX=OtherPixelX + 5;
    CurrentPixelY=OtherPixelY - 15;
    DrawLine8();

}

void drawHorizonLine() {
    OtherPixelX=2;
    OtherPixelY=HORIZONLINE;
    CurrentPixelX=231;
    CurrentPixelY=HORIZONLINE;
    DrawLine8();
}

void prepare_graphics() {
    int ii, jj;
    
    memset(HIRES_SCREEN_ADDRESS, 64, 5120); // 5120 = 0xB400 (std char) - 0xA000 (hires screen)
    memset(LORES_SCREEN_ADDRESS, 32, 40*25);

    poke (LORES_SCREEN_ADDRESS,SWITCH_TO_TEXT_MODE_50HZ);
    poke (LORES_SCREEN_ADDRESS+1,CHANGE_INK_TO_RED);
    for (ii = 0; ii<=4 ; ii++){
        // poke (LORES_SCREEN_ADDRESS+(ii*SCREEN_WIDTH)+0,SWITCH_TO_TEXT_MODE_50HZ);
        // poke (LORES_SCREEN_ADDRESS+(ii*SCREEN_WIDTH)+0,CHANGE_PAPER_TO_GREEN);
        poke (LORES_SCREEN_ADDRESS+(ii*SCREEN_WIDTH)+0,CHANGE_INK_TO_RED);
        poke (LORES_SCREEN_ADDRESS+(ii*SCREEN_WIDTH)+16,USE_STANDARD_CHARSET);
        poke (LORES_SCREEN_ADDRESS+(ii*SCREEN_WIDTH)+17,SWITCH_TO_HIRES_MODE_50HZ);
        for (jj = 0; jj < 8; jj++) {
            poke (HIRES_SCREEN_ADDRESS+((ii*8+jj)*SCREEN_WIDTH)+24,SWITCH_TO_TEXT_MODE_50HZ);
        }
    }
    for (ii=5; ii<16 ; ii++){
        poke (LORES_SCREEN_ADDRESS+(ii*SCREEN_WIDTH)+0,CHANGE_INK_TO_GREEN);
        poke (LORES_SCREEN_ADDRESS+(ii*SCREEN_WIDTH)+1,SWITCH_TO_HIRES_MODE_50HZ);
        for (jj = 0; jj < 8; jj++) {
            poke (HIRES_SCREEN_ADDRESS+((ii*8+jj)*SCREEN_WIDTH)+39,SWITCH_TO_TEXT_MODE_50HZ);
        }
    }
    poke (LORES_SCREEN_ADDRESS+(24*SCREEN_WIDTH)+0,CHANGE_PAPER_TO_BLACK);
    poke (LORES_SCREEN_ADDRESS+(25*SCREEN_WIDTH)+0,CHANGE_PAPER_TO_BLACK);
    poke (LORES_SCREEN_ADDRESS+(26*SCREEN_WIDTH)+0,CHANGE_PAPER_TO_BLACK);
    poke (LORES_SCREEN_ADDRESS+(27*SCREEN_WIDTH)+0,CHANGE_PAPER_TO_BLACK);
}

unsigned char isAllowedPosition(signed char X, signed char Y, signed char Z) {
    return 1;
}

void forward() {
    signed int X, Y;
    X = glCamPosX; Y = glCamPosY;
    if (-112 >= glCamRotZ) {
        glCamPosX--;
    } else if ((-112 < glCamRotZ) && (-80 >= glCamRotZ)) {
        glCamPosX--; glCamPosY--;
    } else if ((-80 < glCamRotZ) && (-48 >= glCamRotZ)) {
        glCamPosY--;
    } else if ((-48 < glCamRotZ) && (-16 >= glCamRotZ)) {
        glCamPosX++; glCamPosY--;
    } else if ((-16 < glCamRotZ) && (16 >= glCamRotZ)) {
        glCamPosX++;
    } else if ((16 < glCamRotZ) && (48 >= glCamRotZ)) {
        glCamPosX++; glCamPosY++;
    } else if ((48 < glCamRotZ) && (80 >= glCamRotZ)) {
        glCamPosY++;
    } else if ((80 < glCamRotZ) && (112 >= glCamRotZ)) {
        glCamPosX--; glCamPosY++;
    } else {
        glCamPosX--;
    }
    if (!isAllowedPosition(glCamPosX, glCamPosY, glCamPosZ)) {
        glCamPosX = X; glCamPosY = Y;
    }
}
void backward() {
    signed int X, Y;
    X = glCamPosX; Y = glCamPosY;
    if (-112 >= glCamRotZ) {
        glCamPosX++;
    } else if ((-112 < glCamRotZ) && (-80 >= glCamRotZ)) {
        glCamPosX++; glCamPosY++;
    } else if ((-80 < glCamRotZ) && (-48 >= glCamRotZ)) {
        glCamPosY++;
    } else if ((-48 < glCamRotZ) && (-16 >= glCamRotZ)) {
        glCamPosX--; glCamPosY++;
    } else if ((-16 < glCamRotZ) && (16 >= glCamRotZ)) {
        glCamPosX--;
    } else if ((16 < glCamRotZ) && (48 >= glCamRotZ)) {
        glCamPosX--; glCamPosY--;
    } else if ((48 < glCamRotZ) && (80 >= glCamRotZ)) {
        glCamPosY--;
    } else if ((80 < glCamRotZ) && (112 >= glCamRotZ)) {
        glCamPosX++; glCamPosY--;
    } else {
        glCamPosX++;
    }
    if (!isAllowedPosition(glCamPosX, glCamPosY, glCamPosZ)) {
        glCamPosX = X; glCamPosY = Y;
    }
}

void gameLoop() {
    signed char pX, pY, pZ, sX, sY, aH, aV;
    
    unsigned char ii, jj;
    while (inGame) {

        player ();


        if (isLandscape2BeRedrawn || isScene2BeRedrawn) {
            // clear Hires Body part
            memset(HIRES_SCREEN_ADDRESS+(FIRSTLINE*SCREEN_WIDTH), 64, (8*12)*SCREEN_WIDTH); // FIXME .. should be 8*11*SCREEN_WIDTH
            for (ii=5; ii<16 ; ii++){
                for (jj = 0; jj < 8; jj++) poke (HIRES_SCREEN_ADDRESS+((ii*8+jj)*SCREEN_WIDTH)+39,SWITCH_TO_TEXT_MODE_50HZ);
            }

            drawLandscape ();
            drawHorizonLine();
            isLandscape2BeRedrawn = 0;
            
            glProject (ptsCube2D, ptsCube3D, NB_POINTS_CUBE, 0);
            //drawCube ();
            drawSegments (segCube3D, ptsCube2D, NB_SEGMENTS_CUBE );

            isScene2BeRedrawn = 0;
        }
        

        if (enemyInRange) {sprintf (LORES_SCREEN_ADDRESS+(1*SCREEN_WIDTH)+1 , "\14ENEMY IN RANGE");}
        if (enemyToLeft) {sprintf (LORES_SCREEN_ADDRESS+(2*SCREEN_WIDTH)+1 , "\14ENEMY TO LEFT");}
        if (enemyToRight) {sprintf (LORES_SCREEN_ADDRESS+(2*SCREEN_WIDTH)+1 , "\14ENEMY TO RIDHT");}
        if (nbRemaingLife==3) 
            sprintf (LORES_SCREEN_ADDRESS+(2*SCREEN_WIDTH)+26 , "abcd");
        else 
            sprintf (LORES_SCREEN_ADDRESS+(2*SCREEN_WIDTH)+26 , "abcd");

        if (nbRemaingLife>=2) 
        
            sprintf (LORES_SCREEN_ADDRESS+(2*SCREEN_WIDTH)+30 , "abcd");
        else 
            sprintf (LORES_SCREEN_ADDRESS+(2*SCREEN_WIDTH)+30 , "abcd");

        if (nbRemaingLife>=1) 
            sprintf (LORES_SCREEN_ADDRESS+(2*SCREEN_WIDTH)+34 , "abcd");
        else 
            sprintf (LORES_SCREEN_ADDRESS+(2*SCREEN_WIDTH)+34 , "abcd");

        sprintf (LORES_SCREEN_ADDRESS+(1*SCREEN_WIDTH)+28 , "HI SCR  %d",highScore);
        sprintf (LORES_SCREEN_ADDRESS+(3*SCREEN_WIDTH)+28 , "SCORE   %d",currentScore);

        if (debugOn) sprintf(ADR_BASE_SCREEN, "(X=%d Y=%d Z=%d) [%d %d]", glCamPosX, glCamPosY, glCamPosZ, glCamRotZ, glCamRotX);
    }
}

/*    ___  _                           
 *   / _ \| |  __ _  _   _   ___  _ __ 
 *  / /_)/| | / _` || | | | / _ \| '__|
 * / ___/ | || (_| || |_| ||  __/| |   
 * \/     |_| \__,_| \__, | \___||_|   
 *                   |___/             
 */
void forward();
void shiftLeft();
void backward();
void shiftRight();

void player () {
    switch (key()) {
    case 8:  // left 
        glCamRotZ -= 4; isScene2BeRedrawn = 1;isLandscape2BeRedrawn = 1;break;
    case 9:  // right 
        glCamRotZ += 4; isScene2BeRedrawn = 1;isLandscape2BeRedrawn = 1;break;
    case 10:  // down
        backward(); isScene2BeRedrawn = 1;break;
    case 11:  // up
        forward(); isScene2BeRedrawn = 1;break;
    case 68:  // D
        revertDebug(); break;
    case 81:  // Q
        inGame = 0; break;
    default:
        break;
    }
}
#define B(x) S_to_binary_(#x)

unsigned char S_to_binary_(const char *s)
{
        unsigned char i = 0;
        while (*s) {
                i <<= 1;
                i += *s++ - '0';
        }
        return i;
}
void initGame(){

        GenerateTables();

        glCamPosX = -20;
        glCamPosY = 17;
        glCamPosZ = 2;

        // Camera Orientation
        glCamRotZ = -68;  // -128 -> 127 unit : 2PI/(2^8 - 1)
        glCamRotX = 0;

        prepare_graphics();

// 000001100000000000000000
// 00000011000000000000000000
// 000000011100000000000000
// 000000000111111100000000
// 000000000100000100000000
// 000001111111111111100000
// 000010010000000010010000
// 000001111111111111100000
        change_char('a', 
            B(00000001), 
            B(00000000), 
            B(00000000), 
            B(00000000), 
            B(00000001), 
            B(00000010), 
            B(00000001),
            B(00000000) 
        );
        change_char('b', 
            B(00110000), 
            B(00011100), 
            B(00000111), 
            B(00000100), 
            B(00111111), 
            B(00010000), 
            B(00111111),
            B(00000000) 
        );
        change_char('c', 
            B(00000000), 
            B(00000000), 
            B(00111100), 
            B(00000100), 
            B(00111111), 
            B(00000010), 
            B(00111111),
            B(00000000) 
        );
        change_char('d', 
            B(00000000), 
            B(00000000), 
            B(00000000), 
            B(00000000), 
            B(00100000), 
            B(00010000), 
            B(00100000),
            B(00000000) 
        );

        drawHorizonLine();

        drawRadar ();
}
#ifdef AUTOTEST
void test() {

    int ii, jj;
    signed char aH, aV;
    signed char aH1, aV1, aH2, aV2;
    unsigned char idxPt1, idxPt2;
    signed char   tmpH, tmpV;
    unsigned char m1, m2;
    unsigned char v1, v2;
    unsigned char isSegment2BeDrawn;

    text();
    cls();

    glCamPosX = 16;
    glCamPosY = 2;
    glCamPosZ = 2;

    // Camera Orientation
    glCamRotZ = 0;  // -128 -> 127 unit : 2PI/(2^8 - 1)
    glCamRotX = 0;

    glProject (ptsCube2D, ptsCube3D, NB_POINTS_CUBE, 0);

    for (ii=0; ii < NB_POINTS_CUBE; ii++) {

        aH=ptsCube2D[ii*SIZEOF_2DPOINT+0];
        aV=ptsCube2D[ii*SIZEOF_2DPOINT+1];

        LargeX0= 120  + (int)(aH)*4;
        LargeY0= HORIZONLINE - (int)(aV)*4;

        printf ("[%d %d %d]=> (%d %d)=> [%d %d]\n",
            ptsCube3D[ii*SIZEOF_3DPOINT+0], ptsCube3D[ii*SIZEOF_3DPOINT+1], ptsCube3D[ii*SIZEOF_3DPOINT+2], 
            aH, aV, 
            LargeX0, LargeY0
        );
    }
    get ();
    // cls();

    for (jj=0; jj < NB_SEGMENTS_CUBE; jj++) {

        idxPt1 = segCube3D[jj*2+0];
        idxPt2 = segCube3D[jj*2+1];

        aH1=ptsCube2D[idxPt1*SIZEOF_2DPOINT+0];
        aV1=ptsCube2D[idxPt1*SIZEOF_2DPOINT+1];
        aH2=ptsCube2D[idxPt2*SIZEOF_2DPOINT+0];
        aV2=ptsCube2D[idxPt2*SIZEOF_2DPOINT+1];


        if (abs(aH2) < abs(aH1)) {
            tmpH = aH1;
            tmpV = aV1;
            aH1 = aH2;
            aV1 = aV2;
            aH2 = tmpH;
            aV2 = tmpV;
        }

        m1 = aH1 & ANGLE_MAX;
        m2 = aH2 & ANGLE_MAX;
        v1 = aH1 & ANGLE_VIEW;
        v2 = aH2 & ANGLE_VIEW;

        isSegment2BeDrawn = 0;
        if ((m1 == 0x00) || (m1 == ANGLE_MAX)) {
            if ((v1 == 0x00) || (v1 == ANGLE_VIEW)) {
                if((aH1 & 0x80) != (aH2 & 0x80)) {
                    if ((abs(aH2) < 127 - abs(aH1))) {
                        isSegment2BeDrawn = 1;
                    }
                }else {
                    isSegment2BeDrawn = 1;
                }
            }else{
                // P1 FRONT
                if ((m2 == 0x00) || (m2 == ANGLE_MAX)) {
                    // P2 FRONT
                    isSegment2BeDrawn = 1;
                } else {
                    // P2 BACK
                    if ((aH1 & 0x80) != (aH2 & 0x80)) {
                        if (abs(aH2) < 127 - abs(aH1)) {
                            isSegment2BeDrawn=1;
                        }
                    }
                }

            }
        }

        LargeX0= 120  + (int)(aH1)*4;
        LargeY0= HORIZONLINE - (int)(aV1)*4;
        LargeX1= 120  + (int)(aH2)*4;
        LargeY1= HORIZONLINE - (int)(aV2)*4;

        printf ("%d=>%d, [%d %d]=>[%d %d] %d\n",
             idxPt1, idxPt2
            ,LargeX0, LargeY0
            ,LargeX1, LargeY1
            ,isSegment2BeDrawn
        );  
    }
    get();
}
#endif

void main()
{
#ifdef AUTOTEST
    test();
#endif
    initGame();
    gameLoop();
}


