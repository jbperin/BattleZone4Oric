

// 0,          0,          0,   0,  
// 0,          0,          0,   1,  
// 0,          0,          0,   2,  
// 0,          0,          0,   3,  
// 0,          0,          0,   4,  
// 0,          0,          0,   5,  
// 0,          0,          0,   6,  
// 0,          0,          0,   7,  
                                           


#define CUBE_SIZE 9
signed char geomCube []= {                  
                                            
/* Nb Coords = */ 8,                        
/* Nb Faces = */ 0,                         
/* Nb Segments = */ 12,                      
/* Nb Particles = */ 0, 
                                            
// Coord List : X, Y, Z, unused             
CUBE_SIZE,          CUBE_SIZE,          0,   0,  
-CUBE_SIZE,          CUBE_SIZE,          0,   1,  
-CUBE_SIZE,          -CUBE_SIZE,          0,   2,  
CUBE_SIZE,          -CUBE_SIZE,          0,   3,  
CUBE_SIZE,          CUBE_SIZE,          CUBE_SIZE*2,   4,  
-CUBE_SIZE,          CUBE_SIZE,          CUBE_SIZE*2,   5,  
-CUBE_SIZE,          -CUBE_SIZE,          CUBE_SIZE*2,   6,  
CUBE_SIZE,          -CUBE_SIZE,          CUBE_SIZE*2,   7,  
                                           
// Face List : idxPoint1, idxPoint2, idxPoint3, character 
// Segment List : idxPoint1, idxPoint2, character , unused
0, 1, ' ', 0,
1, 2, ' ', 1,
2, 3, ' ', 2,
3, 0, ' ', 3,
4, 5, ' ', 4,
5, 6, ' ', 5,
6, 7, ' ', 6,
7, 4, ' ', 7,
0, 4, ' ', 8,
1, 5, ' ', 9,
2, 6, ' ', 10,
3, 7, ' ', 11,
// Particle List : idxPoint1, character 

};



#define SHIP_SIZE 9
signed char geomShip []= {                  
                                            
/* Nb Coords = */ 10,                        
/* Nb Faces = */ 0,                         
/* Nb Segments = */ 6,                      
/* Nb Particles = */ 0,                     
                                            
// Coord List : X, Y, Z, unused             
-SHIP_SIZE,          0,          0,   0,  
SHIP_SIZE,          0,          0,   1,  
-SHIP_SIZE, 0,          2*SHIP_SIZE,   2,  
SHIP_SIZE,          0, 2*SHIP_SIZE,   3,  

-SHIP_SIZE,          -SHIP_SIZE,          0,   4,  
SHIP_SIZE,          -SHIP_SIZE,          0,   5,  
-SHIP_SIZE, -SHIP_SIZE,          2*SHIP_SIZE,   6,  
SHIP_SIZE,          -SHIP_SIZE, 2*SHIP_SIZE,   7,  

-SHIP_SIZE,          SHIP_SIZE,          0,   8,  
SHIP_SIZE,          SHIP_SIZE,          0,   9,  

// Face List : idxPoint1, idxPoint2, idxPoint3, character 
// Segment List : idxPoint1, idxPoint2, character , unused
0, 3, '/', 0,
1, 2, '/', 1,
4, 8, '-', 2,
5, 9, '-', 3,
6, 2, '-', 4,
7, 3, '-', 5,
// Particle List : idxPoint1, character 
};


#define CROSS_SIZE 9
signed char geomCross []= {                  
                                            
/* Nb Coords = */ 4,                        
/* Nb Faces = */ 0,                         
/* Nb Segments = */ 2,                      
/* Nb Particles = */ 0,                     
                                            
// Coord List : X, Y, Z, unused             
-CROSS_SIZE,          0,          0,   0,  
CROSS_SIZE,          0,          0,   1,  
-CROSS_SIZE, 0,          2*CROSS_SIZE,   2,  
CROSS_SIZE,          0, 2*CROSS_SIZE,   3,  
                                            
// Face List : idxPoint1, idxPoint2, idxPoint3, character 
// Segment List : idxPoint1, idxPoint2, character , unused
0, 3, '/', 0,
1, 2, '/', 1,
// Particle List : idxPoint1, character 
};

#define SQUARE_SIZE 9
signed char geomSquare []= {                  
                                            
/* Nb Coords = */ 4,                        
/* Nb Faces = */ 2,                         
/* Nb Segments = */ 4,                      
/* Nb Particles = */ 0,                     
                                            
// Coord List : X, Y, Z, unused             
-SQUARE_SIZE,          0,          0,   0,  
SQUARE_SIZE,          0,          0,   1,  
-SQUARE_SIZE, 0,          2*SQUARE_SIZE,   2,  
SQUARE_SIZE,          0, 2*SQUARE_SIZE,   3,  
                                            
// Face List : idxPoint1, idxPoint2, idxPoint3, character 
0, 1, 2, ')',
1, 2, 3, ')',
// Segment List : idxPoint1, idxPoint2, character , unused
0, 1, '-', 0,
1, 3, '|', 1,
3, 2, '-', 0,
2, 0, '|', 1,
// Particle List : idxPoint1, character 

};


#define TRIANGLE_SIZE 9
signed char geomTriangle []= {                  
                                            
/* Nb Coords = */ 3,                        
/* Nb Faces = */ 1,                         
/* Nb Segments = */ 3,                      
/* Nb Particles = */ 3, 
                                            
// Coord List : X, Y, Z, unused             
-TRIANGLE_SIZE,          0,          0,   0,  
TRIANGLE_SIZE,          0,          0,   1,  
0, 0,          2*TRIANGLE_SIZE,   2,  
                                            
// Face List : idxPoint1, idxPoint2, idxPoint3, character 
0, 1, 2, '$',
// Segment List : idxPoint1, idxPoint2, character , unused
0, 1, '-', 0,
 1, 2, '$', 1,
 0, 2, '$', 3,
// Particle List : idxPoint1, character 
0, '$',
1, '$',
2, '$',
};

