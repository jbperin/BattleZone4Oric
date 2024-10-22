#ifndef L3D_H
#define L3D_H

// Camera 
extern unsigned char glCamRotZ;
extern unsigned char glCamPosX, glCamPosY, glCamPosZ ;

 // Geometry size
extern unsigned char    glNbVertices;
extern unsigned char    glNbSegments;
extern unsigned char    glNbParticles;
extern unsigned char    glNbFaces;

 // Geometry buffers
extern signed char      glVerticesX[];
extern signed char      glVerticesY[];
extern signed char      glVerticesZ[];

extern signed char      points2aH[];

extern unsigned char    glSegmentsPt1[];
extern unsigned char    glSegmentsPt2[];

extern void glProjectArrays();
extern void glLoadShape(
    signed char   X,
    signed char   Y,
    signed char   Z,
    unsigned char orientation,
    signed char          geom[]);

extern signed char geomCube [];
extern signed char geomShip [];
extern signed char geomTriangle [];
extern signed char geomSquare [];


#endif