#ifndef DDAS_H
#define DDAS_H

#define NB_MAX_DDAS 10

typedef void ddastepfct(void);

extern unsigned char   ddaNbVal[NB_MAX_DDAS];
extern unsigned char   ddaNbStep[NB_MAX_DDAS];
extern unsigned char   ddaStartValue[NB_MAX_DDAS];
extern unsigned char   ddaEndValue[NB_MAX_DDAS];
extern unsigned char   ddaCurrentValue[NB_MAX_DDAS];

extern unsigned char   ddaCurrentIndex;

extern ddastepfct      *ddaStepFunction[NB_MAX_DDAS]; 

void ddaInit();
void ddaStep();
#endif
