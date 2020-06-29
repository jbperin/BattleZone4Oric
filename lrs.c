
#define CUBE_SIZE				4
#define NB_POINTS_CUBE			8
#define NB_SEGMENTS_CUBE		12

char ptsCube3D[]={
	 -CUBE_SIZE, -CUBE_SIZE, CUBE_SIZE*2, 0// +CUBE_SIZE, 0 // P0
	,-CUBE_SIZE, -CUBE_SIZE,           0, 0// -CUBE_SIZE, 0 // P1
	,+CUBE_SIZE, -CUBE_SIZE,           0, 0// -CUBE_SIZE, 0 // P2
	,+CUBE_SIZE, -CUBE_SIZE, CUBE_SIZE*2, 0// +CUBE_SIZE, 0 // P3
	,-CUBE_SIZE, +CUBE_SIZE, CUBE_SIZE*2, 0// +CUBE_SIZE, 0 // P4
	,-CUBE_SIZE, +CUBE_SIZE,           0, 0// -CUBE_SIZE, 0 // P5
	,+CUBE_SIZE, +CUBE_SIZE,           0, 0// -CUBE_SIZE, 0 // P6
	,+CUBE_SIZE, +CUBE_SIZE, CUBE_SIZE*2, 0// +CUBE_SIZE, 0 // P7
};

unsigned char segCube3D[]={
	0, 1,
	1, 2,
	2, 3,
	3, 0,
	4, 5,
	5, 6,
	6, 7,
	7, 4,
	0, 4,
	1, 5,
	2, 6,
	3, 7,
};

char ptsCube2D [NB_POINTS_CUBE	* SIZEOF_2DPOINT];


#define NB_POINTS_PYRAMID		5
#define NB_SEGMENTS_PYRAMID		8

char ptsPyramid3D[]={
	 -CUBE_SIZE+30, -CUBE_SIZE+30,           0, 0// -CUBE_SIZE, 0 // P1
	,+CUBE_SIZE+30, -CUBE_SIZE+30,           0, 0// -CUBE_SIZE, 0 // P2
	,-CUBE_SIZE+30, +CUBE_SIZE+30,           0, 0// -CUBE_SIZE, 0 // P5
	,+CUBE_SIZE+30, +CUBE_SIZE+30,           0, 0// -CUBE_SIZE, 0 // P6
	,         0+30,          0+30, CUBE_SIZE*2, 0// +CUBE_SIZE, 0 // P7
};

unsigned char segPyramid3D[]={
	0, 4,
	1, 4,
	2, 4,
	3, 4,
	0, 1,
	1, 3,
	3, 2,
	2, 0,
};

char ptsPyramid2D [NB_POINTS_PYRAMID	* SIZEOF_2DPOINT];

void drawSegments (unsigned char segments[], char pts2d[], unsigned char nbSeg ) {
	unsigned char ii;
    signed char aH1, aV1, aH2, aV2;
    unsigned char idxPt1, idxPt2;
    signed char   tmpH, tmpV;
    unsigned char m1, m2;
    unsigned char v1, v2;
    unsigned char isSegment2BeDrawn;

	for (ii=0; ii< nbSeg; ii++) {
		idxPt1 = segments[ii*2+0];
        idxPt2 = segments[ii*2+1];

        aH1=pts2d[idxPt1*SIZEOF_2DPOINT+0];
        aV1=pts2d[idxPt1*SIZEOF_2DPOINT+1];
        aH2=pts2d[idxPt2*SIZEOF_2DPOINT+0];
        aV2=pts2d[idxPt2*SIZEOF_2DPOINT+1];


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

		if (isSegment2BeDrawn) {
			LargeX0= 120  + (int)(aH1)*4;
			LargeY0= HORIZONLINE - (int)(aV1)*4;
			LargeX1= 120  + (int)(aH2)*4;
			LargeY1= HORIZONLINE - (int)(aV2)*4;
			DrawClippedLine();
		}
	}
}

