
#include "loader_api.h"
#include "rom/keyboard.h"
#include "rom/myRom.h"
#include "util.h"

#include "params.h"
#include "h3/h3.h"
#include "3d/3d.h"
#include "raster/raster.h"

#define HORIZONLINE 68
void drawHorizonLine() {
    OtherPixelX=8;
    OtherPixelY=HORIZONLINE;
    CurrentPixelX=231;
    CurrentPixelY=HORIZONLINE;
    DrawLine8();
}




void onKey(unsigned char c){
    if (c == KEY_ESCAPE) {
        // localGameData->running = 0;
    } else if (c == KEY_LEFT){
        // {asm (
        //     ":stop_here:"
        // );}
        glCamRotZ += 8; 
    } else if (c == KEY_RIGHT){
        glCamRotZ -= 8;
    } else if (c == KEY_SPACE) {
        missileNew();
    }    
}
void onIT(){
    // PRINTN(16,17,glCamPosX);
    // PRINTN(20,17,glCamPosY);
    // PRINTN(24,17,glCamRotZ);
    
}

void gameInit(void){

	LoadFileAt(HIRES_SCREEN, 0xA000);
    GenerateTables();

    // initCamera
    glCamPosX   = 0;
    glCamPosY   = 0;
    glCamPosZ   = 9;
    glCamRotZ   = 0;

    h3Save();

    initShips();
    missileInit();

}
signed char deltaXs[]={6, 6, 6, 6, 6, 5, 5, 5, 4, 4, 3, 3, 2, 2, 1, 1, 0, -1, -1, -2, -2, -3, -3, -4, -4, -5, -5, -5, -6, -6, -6, -6, -6, -6, -6, -6, -6, -5, -5, -5, -4, -4, -3, -3, -2, -2, -1, -1, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 5, 6, 6, 6, 6};
signed char deltaYs[]={0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 5, 5, 5, 4, 4, 3, 3, 2, 2, 1, 1, 0, -1, -1, -2, -2, -3, -3, -4, -4, -5, -5, -5, -6, -6, -6, -6, -6, -6, -6, -6, -6, -5, -5, -5, -4, -4, -3, -3, -2, -2, -1, -1};

void updateH3Canvas(){
    signed char deltaX, deltaY;
    unsigned char idxAngle;

    idxAngle = (((signed char)glCamRotZ) >> 2) & 0x3F;
    // PRINTN(22,0, idxAngle);
    deltaX=deltaXs[idxAngle];
    deltaY=-deltaYs[idxAngle];
    h3Line(MAX_X / 2, MAX_Y / 2, (MAX_X / 2)+deltaX, (MAX_Y / 2)+deltaY);
}
#define CHANGE_INK_TO_GREEN	            2
void gamePulse(void){
    int ii;
    // init Shapes
    glNbVertices     = 0;
    glNbSegments   = 0;
    glNbFaces      = 0;
    glNbParticles = 0;

    glLoadShape(
        40, 12, 0, 
        0, 
        geomCube
    );


    h3Restore();
    updateH3Canvas();
    moveShips();        
    missilePulse();
    glProjectArrays();
    HiresClear();
    for (ii=0; ii < 17*8; ii ++ ) {
        pk(ADR_DRAWING+ii*40,CHANGE_INK_TO_GREEN);
    }

    drawLandscape ();
    drawHorizonLine();
    drawSegments ();

#ifdef USE_BUFFERED_SCREEN
    ScreenCopyHires();
#endif

}
