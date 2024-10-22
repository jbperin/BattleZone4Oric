/*
 * VISIBILITY LIMITS
 */
#define ANGLE_MAX 0xC0
#define ANGLE_VIEW 0xE0

void drawSegments () {
    unsigned char ii;
    unsigned char idxPt1, idxPt2;
    // signed char aH1, aV1, aH2, aV2;
    signed char aH1, aH2;
    // signed char   tmpH, tmpV;
    signed char   tmpH;
    unsigned char m1, m2;
    unsigned char v1, v2;

    unsigned char isSegment2BeDrawn;

    for (ii = 0; ii < glNbSegments; ii++) {
        idxPt1    = glSegmentsPt1[ii];
        idxPt2    = glSegmentsPt2[ii];
        aH1 = points2aH[idxPt1];
        // aV1 = points2aV[idxPt1];
        aH2 = points2aH[idxPt2];
        // aV2 = points2aV[idxPt2];

        if (abs(aH2) < abs(aH1)) {
            tmpH = aH1;
            // tmpV = aV1;
            aH1 = aH2;
            // aV1 = aV2;
            aH2 = tmpH;
            // aV2 = tmpV;
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
			LargeX0= ptXScreen[idxPt1];
			LargeY0= ptYScreen[idxPt1];
			LargeX1= ptXScreen[idxPt2];
			LargeY1= ptYScreen[idxPt2];
			DrawClippedLine();
		}    
    }
}
