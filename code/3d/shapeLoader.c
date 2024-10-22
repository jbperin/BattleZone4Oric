
extern unsigned char sl_ori;
extern signed char          *sl_geom;
extern signed char sl_X, sl_Y, sl_Z;

// 0 : rz(0) : newX = x; newY = y
// 1 : rz(-pi/2) : newX = -y; newY = x
// 2 : rz(pi) : newX = -x; newY = -y
// 3 : rz(pi/2) : newX = y; newY = -x
// unsigned char sl_kk=0;
// unsigned char sl_npt,sl_nfa, sl_nseg, sl_npart;
// unsigned char sl_ii;
// unsigned char sl_ori;
// signed char          *sl_geom;
// signed char sl_X, sl_Y, sl_Z;

void glLoadShape(
    signed char   X,
    signed char   Y,
    signed char   Z,
    unsigned char orientation,
    signed char          geom[]) {

    sl_X = X;
    sl_Y = Y;
    sl_Z = Z;
    sl_geom = geom;
    sl_ori = orientation;

    loadShape();
}
