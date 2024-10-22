
// #include "myRom.h" 
// #include "ddas.h" 
#include "ships.h"
#define NB_FRAME_EXPLODE 10


#define MAX_X               60
#define MAX_Y               64
#define COEFF_SPEED_STEPS   2

unsigned char shipX[MAX_SHIPS];
unsigned char shipY[MAX_SHIPS];
unsigned char shipZ[MAX_SHIPS];
unsigned char shipS[MAX_SHIPS];
unsigned char shipTRAJ[MAX_SHIPS];
unsigned char shipExploding[MAX_SHIPS];

unsigned char shipCurrentIndex;

unsigned char shipStartX, shipEndX, shipStartY, shipEndY; // startX/Y endX/Y

unsigned char ddaXStVal,ddaXNbVal, ddaXNbStps;
unsigned char ddaYStVal,ddaYNbVal, ddaYNbStps;

extern signed char explode_3[];

// gen with genH3to
signed char h3XtoglX[] = {-82, -80, -77, -74, -72, -69, -66, -63, -60, -58, -55, -52, -50, -47, -44, -41, -38, -36, -33, -30, 
-28, -25, -22, -19, -16, -14, -11, -8, -6, -3, 0, 3, 6, 8, 11, 14, 16, 19, 22, 25, 28, 30, 33, 36, 38, 41, 44, 47, 50, 52, 55, 58, 60, 63, 66, 69, 72, 74, 77, 80};
signed char h3YtoglY[] = {88, 85, 82, 80, 77, 74, 72, 69, 66, 63, 60, 58, 55, 52, 50, 47, 44, 41, 38, 36, 33, 30, 28, 25, 22, 
19, 16, 14, 11, 8, 6, 3, 0, -3, -6, -8, -11, -14, -16, -19, -22, -25, -28, -30, -33, -36, -38, -41, -44, -47, -50, -52, -55, -58, -60, -63, -66, -69, -72, -74, -77, -80, -82, -85};

/* Spawns a ship number shipCurrentIndex and instantiate 2 DDA at ddaCurrentIndex */
void spawnShip(void );

void initShips()
{

    h3SetFB(2);
    for (shipCurrentIndex = 0; shipCurrentIndex < MAX_SHIPS; ++shipCurrentIndex)
    {
        spawnShip();

        // shipX[shipCurrentIndex] = GETRAND() % MAX_X;
        // shipY[shipCurrentIndex] = GETRAND() % MAX_Y;
        // shipZ[shipCurrentIndex] = 0;
        // shipS[shipCurrentIndex] = GETRAND() % 3 + 1;
        h3Curset(shipX[shipCurrentIndex], shipY[shipCurrentIndex]);


    }

}





#define FACTOR_MUL 11
#define FACTOR_DIV 4



unsigned char shipTrajId;
unsigned char shipXdda, shipYdda;
unsigned char shipNextX, shipNextY;


signed char *shipGeom;
signed char shipDestX, shipDestY;
unsigned char shipOrientation;


void moveShips() {

    for (shipCurrentIndex = 0; shipCurrentIndex < MAX_SHIPS; ++shipCurrentIndex)
    {
        if (shipExploding[shipCurrentIndex] == 0) {
            // shipXdda = shipCurrentIndex*2;
            // shipYdda = shipXdda+1;
            // // X coord
            // ddaCurrentIndex = shipXdda; ddaStep();
            // // Y coord
            // ddaCurrentIndex = shipYdda; ddaStep();

            {asm("lda _shipCurrentIndex: asl :sta _shipXdda: sta _ddaCurrentIndex:");}
            {asm (
                "lda #<(_ddaStepFunction) : sta tmp0 : lda #>(_ddaStepFunction) : sta tmp0+1:"
                "lda _ddaCurrentIndex: asl: tay: lda (tmp0),y : tax : iny : lda (tmp0),y : stx tmp0 : sta tmp0+1 :"
                ".( : lda tmp0 : sta call+1: lda tmp0+1 : sta call+2 : ldy #0 :call : jsr 0000 : .) :"
            );}
            {asm("lda _shipXdda: clc: adc #1 :sta _shipYdda: sta _ddaCurrentIndex:");}
            {asm (
                "lda #<(_ddaStepFunction) : sta tmp0 : lda #>(_ddaStepFunction) : sta tmp0+1:"
                "lda _ddaCurrentIndex: asl: tay: lda (tmp0),y : tax : iny : lda (tmp0),y : stx tmp0 : sta tmp0+1 :"
                ".( : lda tmp0 : sta call+1: lda tmp0+1 : sta call+2 : ldy #0 :call : jsr 0000 : .) :"
            );}

            
            // shipNextX            = ddaCurrentValue[shipXdda];
            // shipNextY            = ddaCurrentValue[shipYdda];
            {
                asm (
                    "ldy _shipXdda: lda _ddaCurrentValue,y: sta _shipNextX:"
                    "ldy _shipYdda: lda _ddaCurrentValue,y: sta _shipNextY:"
                );
            }
            if((ddaCurrentValue[shipXdda] == ddaEndValue[shipXdda]) &&
                (ddaCurrentValue[shipYdda] == ddaEndValue[shipYdda])) {
                spawnShip();
            } else {
                
                // shipTrajId = shipTRAJ[shipCurrentIndex];
                {asm(
                    "ldy _shipCurrentIndex: lda _shipTRAJ,y: sta _shipTrajId:"
                );}
                switch (shipTrajId){
                    case 0:
                        // shipX[shipCurrentIndex]     = shipNextX;
                        // shipY[shipCurrentIndex]     = shipNextY;
                        // shipOrientation = 0;
                        {asm(
                            "ldy _shipCurrentIndex: lda _shipNextX: sta _shipX,Y:lda _shipNextY: sta _shipY,Y:"
                            "lda #0: sta _shipOrientation:"
                        );}
                        break;
                    case 1:
                        // shipX[shipCurrentIndex]     = MAX_X - 1 - shipNextX;
                        // shipY[shipCurrentIndex]     = shipNextY;
                        // shipOrientation = 0;
                        {asm(
                            "lda #59: sec: sbc _shipNextX:"
                            "ldy _shipCurrentIndex: sta _shipX,Y:lda _shipNextY: sta _shipY,Y:"
                            "lda #0: sta _shipOrientation:"
                        );}
                        break;
                    case 2:
                        // shipX[shipCurrentIndex]     = shipNextX;
                        // shipY[shipCurrentIndex]     = shipNextY;
                        // shipOrientation = 1;
                        {asm(
                            "ldy _shipCurrentIndex: lda _shipNextX: sta _shipX,Y:lda _shipNextY: sta _shipY,Y:"
                            "lda #1: sta _shipOrientation:"
                        );}
                        break;
                    case 3:
                        // shipX[shipCurrentIndex]     = shipNextX;
                        // shipY[shipCurrentIndex]     = MAX_Y - 1 - shipNextY;
                        // shipOrientation = 1;
                        {asm(
                            "lda #63: sec: sbc _shipNextY:"
                            "ldy _shipCurrentIndex: sta _shipY,Y:lda _shipNextX: sta _shipX,Y:"
                            "lda #1: sta _shipOrientation:"
                        );}
                        break;
                    case 4:
                        // shipX[shipCurrentIndex]     = shipNextX;
                        // shipY[shipCurrentIndex]     = MAX_Y - 1 - shipNextY;
                        // shipOrientation = 2;
                        {asm(
                            "lda #63: sec: sbc _shipNextY:"
                            "ldy _shipCurrentIndex: sta _shipY,Y:lda _shipNextX: sta _shipX,Y:"
                            "lda #2: sta _shipOrientation:"
                        );}
                        break;
                    case 5:
                        // shipX[shipCurrentIndex]     = MAX_X - 1 - shipNextX;
                        // shipY[shipCurrentIndex]     = MAX_Y - 1 - shipNextY;
                        // shipOrientation = 2;
                        {asm(
                            "lda #59: sec: sbc _shipNextX:"
                            "ldy _shipCurrentIndex: sta _shipX,Y:"
                            "lda #63: sec: sbc _shipNextY:sta _shipY,Y:"
                            "lda #2: sta _shipOrientation:"
                        );}
                        break;
                    case 6:
                        // shipX[shipCurrentIndex]     = MAX_X - 1 - shipNextX;
                        // shipY[shipCurrentIndex]     = shipNextY;
                        // shipOrientation = 3;
                        {asm(
                            "lda #59: sec: sbc _shipNextX:"
                            "ldy _shipCurrentIndex: sta _shipX,Y:lda _shipNextY: sta _shipY,Y:"
                            "lda #3: sta _shipOrientation:"
                        );}
                        break;
                    case 7:
                        // shipX[shipCurrentIndex]     = MAX_X - 1 - shipNextX;
                        // shipY[shipCurrentIndex]     = MAX_Y - 1 - shipNextY;
                        // shipOrientation = 3;
                        {asm(
                            "lda #59: sec: sbc _shipNextX:"
                            "ldy _shipCurrentIndex: sta _shipX,Y:"
                            "lda #63: sec: sbc _shipNextY:sta _shipY,Y:"
                            "lda #3: sta _shipOrientation:"
                        );}
                        break;
                }
            }
            h3Curset(shipX[shipCurrentIndex], shipY[shipCurrentIndex]);

            // TODO: create myNorm function and reactivate following lines
            // if (myNorm(shipX[shipCurrentIndex]- (MAX_X / 2), (MAX_Y / 2) -shipY[shipCurrentIndex]) < 6){
            //     PRINTS(10,26,"COLLISION");
            // }
            // shipDestX = (signed char)(((((int)(((signed char)shipX[shipCurrentIndex])- (MAX_X / 2)))*FACTOR_MUL)/FACTOR_DIV)&0x00FF);
            shipDestX = h3XtoglX[shipX[shipCurrentIndex]];

            // shipDestY = (signed char)(((((int)((MAX_Y / 2) -((signed char)shipY[shipCurrentIndex]) ))*FACTOR_MUL)/FACTOR_DIV)&0x00FF);
            shipDestY = h3YtoglY[shipY[shipCurrentIndex]];

            // if (norm(shipDestX, shipDestY) < 14){
            //     PRINTS(10,26,"COLLISION");
            // }
            // switch (shipS[shipCurrentIndex]){
            //     case 1:
            //         shipGeom = geomShip;
            //         break;
            //     case 2:
            //         shipGeom = geomTriangle;
            //         break;
            //     case 3:
            //         shipGeom = geomSquare;
            //         break;
            // }

            {asm(
                ":.(:ldy _shipCurrentIndex: lda _shipS,y:"
                "cmp #1: bne case2: lda #<(_geomShip): sta _shipGeom: lda #>(_geomShip):sta _shipGeom+1:jmp endswitch:"
                "case2: cmp #2: bne case3: lda #<(_geomTriangle): sta _shipGeom: lda #>(_geomTriangle):sta _shipGeom+1:jmp endswitch:"
                "case3: cmp #3: bne endswitch: lda #<(_geomSquare): sta _shipGeom: lda #>(_geomSquare):sta _shipGeom+1:"
                ":endswitch:.):"

            );}


            glLoadShape(shipDestX, shipDestY, 0, shipOrientation, shipGeom);
        } else {
            // shipDestX = (signed char)(((((int)(((signed char)shipX[shipCurrentIndex])- (MAX_X / 2)))*FACTOR_MUL)/FACTOR_DIV)&0x00FF);
            shipDestX = h3XtoglX[shipX[shipCurrentIndex]];
            // shipDestY = (signed char)(((((int)((MAX_Y / 2) -((signed char)shipY[shipCurrentIndex]) ))*FACTOR_MUL)/FACTOR_DIV)&0x00FF);
            shipDestY = h3YtoglY[shipY[shipCurrentIndex]];
            
            shipExploding[shipCurrentIndex]     -= 1;
            if (shipExploding[shipCurrentIndex] == 0){
                spawnShip();
            } else {
                // glLoadShape(shipDestX, shipDestY, 4, shipOrientation, explode_frame[NB_FRAME_EXPLODE - shipExploding[shipCurrentIndex]]);
            }

        }
    }
}


void spawnShip(void ){
    unsigned char tborder;

    tborder = GETRAND()%4;
    shipS[shipCurrentIndex]             = GETRAND() % 3 + 1;
    shipExploding[shipCurrentIndex]     = 0;
    switch (tborder){
        case 0:
            shipStartX      = GETRAND()%MAX_X;
            shipStartY      = 0;
            shipEndX        = GETRAND()%MAX_X; // FIXME Make sure not equal to shipStartX
            shipEndY        = MAX_Y-1;
            if (shipEndX > shipStartX){
                ddaXStVal                   = shipStartX; 
                ddaXNbVal                   = shipEndX - shipStartX;
                ddaXNbStps                  = NB_STEPS - shipS[shipCurrentIndex]*COEFF_SPEED_STEPS;
                ddaYStVal                   = shipStartY; 
                ddaYNbVal                   = shipEndY - shipStartY;
                ddaYNbStps                  = NB_STEPS - shipS[shipCurrentIndex]*COEFF_SPEED_STEPS;
                shipTRAJ[shipCurrentIndex]  = 0;
            } else {
                ddaXStVal                   = MAX_X - 1 - shipStartX; 
                ddaXNbVal                   = shipStartX - shipEndX;
                ddaXNbStps                  = NB_STEPS - shipS[shipCurrentIndex]*COEFF_SPEED_STEPS;
                ddaYStVal                   = shipStartY; 
                ddaYNbVal                   = shipEndY - shipStartY;
                ddaYNbStps                  = NB_STEPS - shipS[shipCurrentIndex]*COEFF_SPEED_STEPS;
                shipTRAJ[shipCurrentIndex]  = 1;
            }
            break;
        case 1:
            shipStartX      = 0;
            shipEndX        = MAX_X-1;
            shipStartY      = GETRAND()%MAX_Y;
            shipEndY        = GETRAND()%MAX_Y;
            if (shipEndY > shipStartY){
                ddaXStVal                   = shipStartX; 
                ddaXNbVal                   = shipEndX - shipStartX;
                ddaXNbStps                  = NB_STEPS - shipS[shipCurrentIndex]*COEFF_SPEED_STEPS;
                ddaYStVal                   = shipStartY; 
                ddaYNbVal                   = shipEndY - shipStartY;
                ddaYNbStps                  = NB_STEPS - shipS[shipCurrentIndex]*COEFF_SPEED_STEPS;
                shipTRAJ[shipCurrentIndex]  = 2;
            } else {
                ddaXStVal                   = shipStartX; 
                ddaXNbVal                   = shipEndX - shipStartX;
                ddaXNbStps                  = NB_STEPS - shipS[shipCurrentIndex]*COEFF_SPEED_STEPS;
                ddaYStVal                   = MAX_Y - 1 - shipStartY; 
                ddaYNbVal                   = shipStartY - shipEndY;
                ddaYNbStps                  = NB_STEPS - shipS[shipCurrentIndex]*COEFF_SPEED_STEPS;
                shipTRAJ[shipCurrentIndex]  = 3;
            }
            break;
        case 2:
            shipStartX      = GETRAND()%MAX_X;
            shipEndX        = GETRAND()%MAX_Y;
            shipStartY      = MAX_Y-1;
            shipEndY        = 0;
            if (shipEndX > shipStartX){
                ddaXStVal                   = shipStartX; 
                ddaXNbVal                   = shipEndX - shipStartX;
                ddaXNbStps                  = NB_STEPS - shipS[shipCurrentIndex]*COEFF_SPEED_STEPS;
                ddaYStVal                   = MAX_Y- 1 -shipStartY; 
                ddaYNbVal                   = shipStartY - shipEndY;
                ddaYNbStps                  = NB_STEPS - shipS[shipCurrentIndex]*COEFF_SPEED_STEPS;
                shipTRAJ[shipCurrentIndex]  = 4;
                {asm("breakhere");}
            } else {
                ddaXStVal                   = MAX_X - 1 - shipStartX; 
                ddaXNbVal                   = shipStartX - shipEndX;
                ddaXNbStps                  = NB_STEPS - shipS[shipCurrentIndex]*COEFF_SPEED_STEPS;
                ddaYStVal                   = MAX_Y - 1 - shipStartY; 
                ddaYNbVal                   = shipStartY - shipEndY;
                ddaYNbStps                  = NB_STEPS - shipS[shipCurrentIndex]*COEFF_SPEED_STEPS;
                shipTRAJ[shipCurrentIndex]  = 5;
            }
            break;
        case 3:
            shipStartX      = MAX_X-1;
            shipEndX        = 0;
            shipStartY      = GETRAND()%MAX_Y;
            shipEndY        = GETRAND()%MAX_Y;
            if (shipEndY > shipStartY){
                ddaXStVal                   = MAX_X - 1 - shipStartX; 
                ddaXNbVal                   = shipStartX - shipEndX;
                ddaXNbStps                  = NB_STEPS - shipS[shipCurrentIndex]*COEFF_SPEED_STEPS;
                ddaYStVal                   = shipStartY; 
                ddaYNbVal                   = shipEndY - shipStartY;
                ddaYNbStps                  = NB_STEPS - shipS[shipCurrentIndex]*COEFF_SPEED_STEPS;
                shipTRAJ[shipCurrentIndex]  = 6;
            } else {
                ddaXStVal                   = MAX_X - 1 - shipStartX; 
                ddaXNbVal                   = shipStartX - shipEndX;
                ddaXNbStps                  = NB_STEPS - shipS[shipCurrentIndex]*COEFF_SPEED_STEPS;
                ddaYStVal                   = MAX_Y - 1 - shipStartY; 
                ddaYNbVal                   = shipStartY - shipEndY;
                ddaYNbStps                  = NB_STEPS - shipS[shipCurrentIndex]*COEFF_SPEED_STEPS;
                shipTRAJ[shipCurrentIndex]  = 7;
            }
            break;
    }
        // INIT DDA for X Coordinate
    ddaCurrentIndex = shipCurrentIndex*2;

    ddaStartValue[ddaCurrentIndex]       = ddaXStVal;
    ddaNbVal[ddaCurrentIndex]            = ddaXNbVal;
    ddaNbStep[ddaCurrentIndex]           = ddaXNbStps;

    ddaInit();

    // INIT DDA for Y Coordinate
    ddaCurrentIndex = shipCurrentIndex*2 + 1;

    ddaStartValue[ddaCurrentIndex]       = ddaYStVal;
    ddaNbStep[ddaCurrentIndex]           = ddaYNbStps;
    ddaNbVal[ddaCurrentIndex]            = ddaYNbVal;

    ddaInit();

    // place ship
    shipX[shipCurrentIndex]             = shipStartX;
    shipY[shipCurrentIndex]             = shipStartY;
    
    // PRINTN(10,25,shipTRAJ[shipCurrentIndex]);
}


