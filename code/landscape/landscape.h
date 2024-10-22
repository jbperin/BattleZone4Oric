#ifndef LANDSCAPE_H
#define LANDSCAPE_H
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

void drawLandscape ();
#endif