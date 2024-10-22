#ifndef RASTER_H
#define RASTER_H
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
extern void ScreenCopyHires();
extern void HiresClear();
extern void drawSegments ();
#endif