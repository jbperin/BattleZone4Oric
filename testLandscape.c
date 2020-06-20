#include <stdio.h>

#include "landscape_c.c"
// extern unsigned int  tabPointsX[];
// extern unsigned char tabPointsY[];

// extern unsigned char tabSegPt1[];
// extern unsigned char tabSegPt2[];

// extern unsigned char tabIdxFirstSeg[];
// extern unsigned char tabNbLeftClipSeg[];
// extern unsigned char tabNbRightClipSeg[];
// extern unsigned char tabNoClipSeg[];
// extern unsigned int  tabOffset[];


signed char glCamRotZ=12;
unsigned char CurrentPixelX, CurrentPixelY, OtherPixelX, OtherPixelY;
int LargeX0, LargeY0, LargeX1, LargeY1;

void DrawClippedLine () {
    printf ("drawClippedLine from (%d, %d) to (%d, %d)\n",LargeX0, LargeY0, LargeX1, LargeY1 );
}

void DrawLine8 (){
    printf ("drawLine8 from (%d, %d) to (%d, %d)\n", CurrentPixelX, CurrentPixelY, OtherPixelX, OtherPixelY);
}

#include "drawLandscape.c"

void main () {
    drawLandscape();
}
