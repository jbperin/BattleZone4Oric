
// #ifndef __GNUC__
// // #include "glOric.h"
// #include "myRom.h"
// #include "ships.h"
// #endif

#define MAX_X 60
#define MAX_Y 64
#define NB_FRAME_EXPLODE 10
#define DISTANCE_TO_EXPLODE 5

extern void h3Curset(unsigned char x, unsigned char y);
extern unsigned char shipX[];
extern unsigned char shipY[];
extern unsigned char shipExploding[];
#define NB_MAX_MISSILE 4

unsigned char   missileActive   [NB_MAX_MISSILE];
int             missilePosX     [NB_MAX_MISSILE];
int             missilePosY     [NB_MAX_MISSILE];
int             missileIncX     [NB_MAX_MISSILE];
int             missileIncY     [NB_MAX_MISSILE];
signed char     missilePosZ     [NB_MAX_MISSILE];
unsigned char   missileOri      [NB_MAX_MISSILE];

unsigned char missileCurrentIdx;


#define MISSILE_SIZE 9
signed char geomMissile []= {                  
                                            
/* Nb Coords = */ 4,                        
/* Nb Faces = */ 0,                         
/* Nb Segments = */ 4,                      
/* Nb Particles = */ 0,                     
                                            
// Coord List : X, Y, Z, unused             
0,          0,          0,              0,  
MISSILE_SIZE,          0,         MISSILE_SIZE,   1,  
0,          0,          2*MISSILE_SIZE,   2,  
-MISSILE_SIZE,          0, MISSILE_SIZE,   3,  
                                            
// Face List : idxPoint1, idxPoint2, idxPoint3, character 
// Segment List : idxPoint1, idxPoint2, character , unused
0, 1, '/', 0,
1, 2, '/', 1,
3, 2, '/', 0,
0, 3, '/', 1,
// Particle List : idxPoint1, character 
};




#define FACTOR_MUL 11
#define FACTOR_DIV 4
extern unsigned char shipCurrentIndex;
void missilePulse() {
    signed char destX, destY;
    int highX, highY;
    // unsigned char ii;

    for (missileCurrentIdx = 0; missileCurrentIdx < NB_MAX_MISSILE; missileCurrentIdx++) {
        if (missileActive[missileCurrentIdx]!=0) {
            missilePosX [missileCurrentIdx] += missileIncX[missileCurrentIdx];
            missilePosY [missileCurrentIdx] -= missileIncY[missileCurrentIdx];

            highX = missilePosX [missileCurrentIdx] / 256;
            highY = missilePosY [missileCurrentIdx] / 256;
            if ((highX <=0) || (highX >= MAX_X) || (highY <=0 )|| (highY >= MAX_Y )){
                missileActive[missileCurrentIdx]=0;
            } else {
                // lprintf ("missile %d is at [%d, %d] ",missileCurrentIdx, highX, highY );
                for (shipCurrentIndex = 0 ; shipCurrentIndex < MAX_SHIPS; shipCurrentIndex++){
                    // lprintf("ship %d, is at [%d, %d]", shipCurrentIndex, shipX[shipCurrentIndex]);
                    // TODO: create myNorm function and reactivate following lines
                    // if (myNorm(highX-shipX[shipCurrentIndex], highY-shipY[shipCurrentIndex]) < DISTANCE_TO_EXPLODE) {
                    //     PRINTS(22,26,"EXPLOSION");
                    //     // PRINTN(32,26,shipCurrentIndex);
                    //     // PRINTN(35,26,missileCurrentIdx);
                    //     shipExploding[shipCurrentIndex] = NB_FRAME_EXPLODE;
                    //     missileActive[missileCurrentIdx]=0;
                    // }
                }
                if (missileActive[missileCurrentIdx]!=0){
                    h3Curset((unsigned char)highX, (unsigned char)highY);
                    destX = (signed char)highX - (signed char)(MAX_X / 2);
                    destY = (signed char)(MAX_Y / 2) -(signed char)highY;
                    destX = (signed char)((((int)(destX)*FACTOR_MUL)/FACTOR_DIV)&0x00FF);
                    destY = (signed char)((((int)(destY)*FACTOR_MUL)/FACTOR_DIV)&0x00FF);
                    glLoadShape(destX, destY, 0, missileOri[missileCurrentIdx], geomMissile);
                }
            }
        }
    }
}


// unsigned char computeRelativeOrientation (signed char direction, signed char rayCamRotZ);


// void soldierUpdate()
// {
//     // unsigned char ldist;
//     unsigned char displaystate;
//     signed char direction;
//     signed char sex, sey;
// 	signed char ex = objPosX[missileCurrentIdx];
//     signed char ey = objPosY[missileCurrentIdx];
//     sex = ex;
//     sey = ey;
//     direction = *(objData[missileCurrentIdx]);
//     if (-112 >= direction) {
//         ex--;
//     } else if ((-112 < direction) && (-80 >= direction)) {
//         ex--; ey--;
//     } else if ((-80 < direction) && (-48 >= direction)) {
//         ey--;
//     } else if ((-48 < direction) && (-16 >= direction)) {
//         ex++; ey--;
//     } else if ((-16 < direction) && (16 >= direction)) {
//         ex++;
//     } else if ((16 < direction) && (48 >= direction)) {
//         ex++; ey++;
//     } else if ((48 < direction) && (80 >= direction)) {
//         ey++;
//     } else if ((80 < direction) && (112 >= direction)) {
//         ex--; ey++;
//     } else {
//         ex--;
//     }
//     if (isInWall(ex, ey)) {
//          direction += 16;
//          *(objData[missileCurrentIdx]) = direction;
//          ex = sex;
//          ey = sey;
//     }
//     objPosX[missileCurrentIdx] = ex;
//     objPosY[missileCurrentIdx] = ey;
//     // ldist = computeLogDist (ex, ey);
//     computeLogDistance();
//     dichoInsert (missileCurrentIdx, objLogDistance[missileCurrentIdx]);

//     // computeRelativeOrientation (*(objData[missileCurrentIdx]));
// #ifdef USE_SPRITE    
//     displaystate = computeRelativeOrientation (direction, rayCamRotZ);
//     switch (displaystate) {
//         case 0:
//             objTexture[missileCurrentIdx] = texture_smily_back; // ptrTextureSoldierBack;
//             break;
//         case 1:
//             objTexture[missileCurrentIdx] = texture_smily_left; // ptrTextureSoldierRight;
//             break;
//         case 2:
//             objTexture[missileCurrentIdx] = texture_smily_front; // ptrTextureSoldierFront;
//             break;
//         case 3:
//             objTexture[missileCurrentIdx] = texture_smily_right; // ptrTextureSoldierLeft;
//             break;
//     }
// #endif
//     refreshNeeded = 1;
// }

void missileInit()
{
    for (missileCurrentIdx = 0; missileCurrentIdx < NB_MAX_MISSILE; missileCurrentIdx++) missileActive[missileCurrentIdx] = 0;
}

int tabIncX[]={384, 382, 377, 367, 355, 339, 319, 297, 272, 244, 213, 181, 147, 111, 75, 38, 0, -38, -75, -111, -147, -181, -213, -244, -272, -297, -319, -339, -355, -367, -377, -382, -384, -382, -377, -367, -355, -339, -319, -297, -272, -244, -213, -181, -147, -111, -75, -38, 0, 38, 75, 111, 147, 181, 213, 244, 272, 297, 319, 
339, 355, 367, 377, 382};
int tabIncY[]={0, 38, 75, 111, 147, 181, 213, 244, 272, 297, 319, 339, 355, 367, 377, 382, 384, 382, 377, 367, 355, 339, 319, 297, 272, 244, 213, 181, 147, 111, 75, 38, 0, -38, -75, -111, -147, -181, -213, -244, -272, -297, 
-319, -339, -355, -367, -377, -382, -384, -382, -377, -367, -355, -339, -319, -297, -272, -244, -213, -181, -147, -111, -75, -38};

void missileNew(){
    unsigned char idxAngle;
    for (missileCurrentIdx = 0; missileCurrentIdx < NB_MAX_MISSILE; missileCurrentIdx++)
    {
        if (missileActive[missileCurrentIdx] == 0) break;
    }
    if (missileCurrentIdx != NB_MAX_MISSILE) {
        missileActive[missileCurrentIdx] = 1;
        missilePosX[missileCurrentIdx] = 30*256;
        missilePosY[missileCurrentIdx] = 32*256;
        missilePosZ[missileCurrentIdx] = 9; // TODO: 
        idxAngle = (((signed char)glCamRotZ) >> 2) & 0x3F;
        missileIncX[missileCurrentIdx] = tabIncX[idxAngle]; // TODO: 
        missileIncY[missileCurrentIdx] = tabIncY[idxAngle]; // TODO: 
        missileOri[missileCurrentIdx] = 3 - (idxAngle>>4);

    };

}

// void engDeleteObject(unsigned char objectNumber) {
//     objActive[objectNumber] = 0;
// }

// void engDeleteAllObjects(unsigned char objectType) {
//     unsigned char i;
//     for (i = 0; i < NB_MAX_MISSILE; i++)
//         if (1 == objActive[i] && objectType == objType[i])
//             objActive[i] = 0;
// }


// void main () {
//     int ii;
//     printf ("coucou\n");
//     engInitObjects();
//     engAddObject(OBJ_KEY, 3, 3, 0);
//     engAddObject(OBJ_SOLDIER, 3, -3, soldier_data);
//     for (ii=0 ; ii < 4; ii++){
//         engPulse();
//     }
// }

#ifdef __GNUC__
void main (){

    printf ("hello\n");
    ddaCurrentIndex = 0;
    ddaStartValue[ddaCurrentIndex]       = 0x13;
    ddaNbStep[ddaCurrentIndex]           = 3;
    ddaNbVal[ddaCurrentIndex]            = 0x14-0x13;

    ddaInit();
    printf ("0x%x\n", ddaCurrentValue[ddaCurrentIndex]);
    while (ddaCurrentValue[ddaCurrentIndex] < ddaEndValue[ddaCurrentIndex]) {
        (*ddaStepFunction[ddaCurrentIndex])(); 
        printf ("0x%x\n", ddaCurrentValue[ddaCurrentIndex]);
    }
}
#endif //__GNUC__