

int ptXScreen [NB_MAX_VERTICES];
int ptYScreen [NB_MAX_VERTICES];

#ifndef __GNUC__
extern signed char PointX;
extern signed char PointY;
extern signed char PointZ;
extern signed int xScreen;
extern signed int yScreen;
extern signed char AngleH;
extern void sproject();
#endif

void glProjectArrays(){

    unsigned char ii;
    int c;

#ifdef __GNUC__
    signed char     x, y, z;
    signed char     Angle;
    signed int      lxScreen, lyScreen;
#endif
    for (ii = 0; ii < glNbVertices; ii++){
#ifdef __GNUC__
        x = glVerticesX[ii];
        y = glVerticesY[ii];
        z = glVerticesZ[ii];

        // glProjectPoint(x, y, z, options, &ah, &av, &dist);
        project (x, y, z, &Angle, &lxScreen, &lyScreen );
        ptXScreen[ii] = lxScreen;
        ptYScreen[ii] = lyScreen;
        points2aH[ii] = Angle;

#else
        PointX = glVerticesX[ii];
        PointY = glVerticesY[ii];
        PointZ = glVerticesZ[ii];
        sproject();
        ptXScreen[ii] = xScreen;
        ptYScreen[ii] = yScreen;
        points2aH[ii] = AngleH;
#endif

    }
}
