

void drawLandscape () {
    
    unsigned char glCamRotZdiv4;
    unsigned char idxSeg, nbLeftClipSeg, nbRightClipSeg, nbNoClipSeg, idxPt1, idxPt2;

    glCamRotZdiv4 = ((unsigned char)-glCamRotZ) >> 2;

    idxSeg = tabIdxFirstSeg [glCamRotZdiv4];
    nbLeftClipSeg = tabNbLeftClipSeg [glCamRotZdiv4];
    nbRightClipSeg = tabNbRightClipSeg [glCamRotZdiv4];
    nbNoClipSeg = tabNoClipSeg [glCamRotZdiv4];

    while (nbLeftClipSeg > 0){
        idxPt1 = tabSegPt1[idxSeg];
        idxPt2 = tabSegPt2[idxSeg];
        LargeX0 = tabPointsX[idxPt1]-tabOffset[glCamRotZdiv4];
        LargeY0 = tabPointsY[idxPt1];
        LargeX1 = tabPointsX[idxPt2]-tabOffset[glCamRotZdiv4];
        LargeY1 = tabPointsY[idxPt2];
        DrawClippedLine();
        idxSeg = idxSeg + 1;
        nbLeftClipSeg --;
    }

    while (nbNoClipSeg > 0) {
        idxPt1 = tabSegPt1[idxSeg];
        idxPt2 = tabSegPt2[idxSeg];
        CurrentPixelX = tabPointsX[idxPt1]-tabOffset[glCamRotZdiv4];
        CurrentPixelY = tabPointsY[idxPt1];
        OtherPixelX = tabPointsX[idxPt2]-tabOffset[glCamRotZdiv4];
        OtherPixelY = tabPointsY[idxPt2];
        DrawLine8();
        idxSeg = idxSeg + 1;
        nbNoClipSeg --;
    }
    while (nbRightClipSeg > 0){
        idxPt1 = tabSegPt1[idxSeg];
        idxPt2 = tabSegPt2[idxSeg];
        LargeX0 = tabPointsX[idxPt1]-tabOffset[glCamRotZdiv4];
        LargeY0 = tabPointsY[idxPt1];
        LargeX1 = tabPointsX[idxPt2]-tabOffset[glCamRotZdiv4];
        LargeY1 = tabPointsY[idxPt2];
        DrawClippedLine();
        idxSeg = idxSeg + 1;
        nbRightClipSeg --;
    }

}
