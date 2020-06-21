
#define CUBE_SIZE	4
#define NB_POINTS_CUBE		8

char ptsCube3D[]={
	 -CUBE_SIZE, -CUBE_SIZE, +CUBE_SIZE, 0 // P0
	,-CUBE_SIZE, -CUBE_SIZE, -CUBE_SIZE, 0 // P1
	,+CUBE_SIZE, -CUBE_SIZE, -CUBE_SIZE, 0 // P2
	,+CUBE_SIZE, -CUBE_SIZE, +CUBE_SIZE, 0 // P3
	,-CUBE_SIZE, +CUBE_SIZE, +CUBE_SIZE, 0 // P4
	,-CUBE_SIZE, +CUBE_SIZE, -CUBE_SIZE, 0 // P5
	,+CUBE_SIZE, +CUBE_SIZE, -CUBE_SIZE, 0 // P6
	,+CUBE_SIZE, +CUBE_SIZE, +CUBE_SIZE, 0 // P7
};
char ptsCube2D [NB_POINTS_CUBE	* SIZEOF_2DPOINT];

void lineBetweenPoints (idxPt1, idxPt2 ){

	LargeX0= 120  + (int)(ptsCube2D[idxPt1*SIZEOF_2DPOINT+0])*4;
	LargeY0= HORIZONLINE - (int)(ptsCube2D[idxPt1*SIZEOF_2DPOINT+1])*4;
	LargeX1= 120  + (int)(ptsCube2D[idxPt2*SIZEOF_2DPOINT+0])*4;
	LargeY1= HORIZONLINE - (int)(ptsCube2D[idxPt2*SIZEOF_2DPOINT+1])*4;
	DrawClippedLine();

}
void drawCube () {
	lineBetweenPoints (0, 1);
	lineBetweenPoints (1, 2);
	lineBetweenPoints (2, 3);
	lineBetweenPoints (3, 0);
	lineBetweenPoints (4, 5);
	lineBetweenPoints (5, 6);
	lineBetweenPoints (6, 7);
	lineBetweenPoints (7, 4);
	lineBetweenPoints (0, 4);
	lineBetweenPoints (1, 5);
	lineBetweenPoints (2, 6);
	lineBetweenPoints (3, 7);
}
