// Digital Differential Analyzer Algorithm
// Incremental error algorithm
#include "ddas.h"

unsigned char   ddaNbVal[NB_MAX_DDAS];
unsigned char   ddaNbStep[NB_MAX_DDAS];
unsigned char   ddaStartValue[NB_MAX_DDAS];

unsigned char   ddaCurrentValue[NB_MAX_DDAS];
unsigned char   ddaEndValue[NB_MAX_DDAS];

signed char     ddaCurrentError[NB_MAX_DDAS];

unsigned char   ddaCurrentIndex;

ddastepfct      *ddaStepFunction[NB_MAX_DDAS]; 

#ifdef USE_C_DDAS
void ddaStep0(){

    ddaCurrentValue[ddaCurrentIndex]         += 1;
    // {asm (
    //     "lda #<(_ddaCurrentValue) : sta tmp0 : lda #>(_ddaCurrentValue) : sta tmp0+1 :"
    //     "ldy _ddaCurrentIndex: lda (tmp0),y :clc : adc #1: sta (tmp0),y"
    // );}
    
}

void ddaStep1(){

    while ((ddaCurrentError[ddaCurrentIndex]<<1) >= ddaNbStep[ddaCurrentIndex]) {

        // ddaCurrentError[ddaCurrentIndex]         -= ddaNbStep[ddaCurrentIndex];
        {asm (
            "lda #<(_ddaCurrentError) : sta tmp0 : lda #>(_ddaCurrentError) : sta tmp0+1 :"
            "ldy _ddaCurrentIndex: lda (tmp0),y : sta tmp1 :  "
            "lda #<(_ddaNbStep) : sta tmp0 : lda #>(_ddaNbStep) : sta tmp0+1 :"
            "sec: lda tmp1: sbc (tmp0),y : sta tmp1 :"
            "lda #<(_ddaCurrentError) : sta tmp0 : lda #>(_ddaCurrentError) : sta tmp0+1 :"
            "lda tmp1: sta(tmp0),y"
        );}

        // ddaCurrentValue[ddaCurrentIndex]         += 1;
        {asm (
            "lda #<(_ddaCurrentValue) : sta tmp0 : lda #>(_ddaCurrentValue) : sta tmp0+1 :"
            "ldy _ddaCurrentIndex: lda (tmp0),y :clc : adc #1: sta (tmp0),y"
        );}
    }
    // ddaCurrentError[ddaCurrentIndex]     += ddaNbVal[ddaCurrentIndex];
    {asm (
        "lda #<(_ddaCurrentError) : sta tmp0 : lda #>(_ddaCurrentError) : sta tmp0+1 :"
        "ldy _ddaCurrentIndex: lda (tmp0),y : sta tmp1 :  "
        "lda #<(_ddaNbVal) : sta tmp0 : lda #>(_ddaNbVal) : sta tmp0+1 :"
        "clc: lda tmp1: adc (tmp0),y : sta tmp1 :"
        "lda #<(_ddaCurrentError) : sta tmp0 : lda #>(_ddaCurrentError) : sta tmp0+1 :"
        "lda tmp1: sta(tmp0),y"
    );}
  
}


void ddaStep2(){

    // ddaCurrentError[ddaCurrentIndex]         -= ddaNbVal[ddaCurrentIndex];
    {asm (
        "lda #<(_ddaCurrentError) : sta tmp0 : lda #>(_ddaCurrentError) : sta tmp0+1 :"
        "ldy _ddaCurrentIndex: lda (tmp0),y : sta tmp1 :  "
        "lda #<(_ddaNbVal) : sta tmp0 : lda #>(_ddaNbVal) : sta tmp0+1 :"
        "sec: lda tmp1: sbc (tmp0),y : sta tmp1 :"
        "lda #<(_ddaCurrentError) : sta tmp0 : lda #>(_ddaCurrentError) : sta tmp0+1 :"
        "lda tmp1: sta(tmp0),y"
    );}


    if ((ddaCurrentError[ddaCurrentIndex]<<1) < ddaNbStep[ddaCurrentIndex]) {

        // ddaCurrentError[ddaCurrentIndex]     += ddaNbStep[ddaCurrentIndex];
        {asm (
            "lda #<(_ddaCurrentError) : sta tmp0 : lda #>(_ddaCurrentError) : sta tmp0+1 :"
            "ldy _ddaCurrentIndex: lda (tmp0),y : sta tmp1 :  "
            "lda #<(_ddaNbStep) : sta tmp0 : lda #>(_ddaNbStep) : sta tmp0+1 :"
            "clc: lda tmp1: adc (tmp0),y : sta tmp1 :"
            "lda #<(_ddaCurrentError) : sta tmp0 : lda #>(_ddaCurrentError) : sta tmp0+1 :"
            "lda tmp1: sta(tmp0),y"
        );}

        // ddaCurrentValue[ddaCurrentIndex]     += 1;
        {asm (
            "lda #<(_ddaCurrentValue) : sta tmp0 : lda #>(_ddaCurrentValue) : sta tmp0+1 :"
            "ldy _ddaCurrentIndex: lda (tmp0),y :clc : adc #1: sta (tmp0),y"
        );}
    }
}

void ddaInit(){

    ddaCurrentValue[ddaCurrentIndex]         = ddaStartValue[ddaCurrentIndex];
    ddaEndValue[ddaCurrentIndex]             = ddaStartValue[ddaCurrentIndex] + ddaNbVal[ddaCurrentIndex];

    if          (ddaNbVal[ddaCurrentIndex] > ddaNbStep[ddaCurrentIndex]) {
        ddaCurrentError[ddaCurrentIndex]     = ddaNbVal[ddaCurrentIndex];
        ddaStepFunction[ddaCurrentIndex]     = &ddaStep1;
    } else if   (ddaNbVal[ddaCurrentIndex] < ddaNbStep[ddaCurrentIndex]) {
        ddaCurrentError[ddaCurrentIndex]     = ddaNbStep[ddaCurrentIndex];
        ddaStepFunction[ddaCurrentIndex]     = &ddaStep2;
    } else {
        ddaCurrentError[ddaCurrentIndex]     = ddaEndValue[ddaCurrentIndex];
        ddaStepFunction[ddaCurrentIndex]     = &ddaStep0;
    }

}


#else
extern void ddaStep0(void);
extern void ddaStep1(void);
extern void ddaStep2(void);
extern void ddaInit(void);
#endif  // USE_C_DDAS




void ddaStep(){
    // (*ddaStepFunction[ddaCurrentIndex])();
    {asm (
        "lda #<(_ddaStepFunction) : sta tmp0 : lda #>(_ddaStepFunction) : sta tmp0+1:"
        "lda _ddaCurrentIndex: asl: tay: lda (tmp0),y : tax : iny : lda (tmp0),y : stx tmp0 : sta tmp0+1 :"
        ".( : lda tmp0 : sta call+1: lda tmp0+1 : sta call+2 : ldy #0 :call : jsr 0000 : .) :"
    );}
 
}

#ifdef __GNUC__
void main (){

    printf ("hello\n");
    ddaCurrentIndex = 0;
    ddaStartValue[ddaCurrentIndex]       = 0x13;
    ddaNbStep[ddaCurrentIndex]           = 3;
    ddaNbVal[ddaCurrentIndex]            = 0x14-0x13;

    ddaInit();
    printf ("0x%x\n", ddaCurrentValue[ddaCurrentIndex]);
    while (ddaCurrentValue[ddaCurrentIndex] < ddaEndValue[ddaCurrentIndex]) {
        (*ddaStepFunction[ddaCurrentIndex])(); 
        printf ("0x%x\n", ddaCurrentValue[ddaCurrentIndex]);
    }
}
#endif //__GNUC__