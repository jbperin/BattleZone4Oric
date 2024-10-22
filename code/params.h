#ifndef PARAM_H
#define PARAM_H

//
// --- SECTION for RASTERISATION ---
// 
#define CLIP_BORDER	1


#define CLIP_LEFT	8
#define CLIP_RIGHT	220
#define CLIP_TOP	1
#define CLIP_BOTTOM	136

#define USE_ACCURATE_CLIPPING
#define USE_BUFFERED_SCREEN

#define SCREEN_WIDTH                    40
#define SCREEN_HEIGHT                   26

#define _ADR_SCREEN_BUFFER C000
#define _ADR_SCREEN_MEMORY a000

#ifdef USE_BUFFERED_SCREEN
#define _ADR_DRAWING _ADR_SCREEN_BUFFER
#define ADR_DRAWING 0xC000
#else
#define _ADR_DRAWING _ADR_SCREEN_MEMORY
#define ADR_DRAWING 0xa000
#endif

//
// --- SECTION for SHAPES GEOMETRIES ---
//
#define NB_MAX_VERTICES 64
#define NB_MAX_SEGMENTS 64
#define NB_MAX_FACES 64
#define NB_MAX_PARTICLES 64


#endif