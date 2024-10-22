

_ddaStep0:
.(
    ;; ddaCurrentValue[ddaCurrentIndex]         += 1;
    ldy _ddaCurrentIndex: lda _ddaCurrentValue,y :clc : adc #1: sta _ddaCurrentValue,y
.)
    rts


_ddaStep1:
.(
loop:
    ;; while ((ddaCurrentError[ddaCurrentIndex]<<1) >= ddaNbStep[ddaCurrentIndex]) {
    ldy         _ddaCurrentIndex
    lda         _ddaCurrentError,y
    bmi         end_loop
    asl
    cmp         _ddaNbStep,y
    bcc         end_loop

        ;; ddaCurrentError[ddaCurrentIndex]         -= ddaNbStep[ddaCurrentIndex];
        ldy _ddaCurrentIndex: lda _ddaCurrentError,y : sec: sbc _ddaNbStep,y : sta _ddaCurrentError,y

        ;; ddaCurrentValue[ddaCurrentIndex]         += 1;
        ldy _ddaCurrentIndex: lda _ddaCurrentValue,y :clc : adc #1: sta _ddaCurrentValue,y

    
    jmp         loop
end_loop:
    ;; ddaCurrentError[ddaCurrentIndex]     += ddaNbVal[ddaCurrentIndex];
    ldy _ddaCurrentIndex: lda _ddaCurrentError,y: clc: adc _ddaNbVal,y: sta _ddaCurrentError,y
.)
    rts

_ddaStep2:
.(

    ;; ddaCurrentError[ddaCurrentIndex]         -= ddaNbVal[ddaCurrentIndex];
    ldy _ddaCurrentIndex: lda _ddaCurrentError,y : sec : sbc _ddaNbVal,y: sta _ddaCurrentError,y

    ;; if ((ddaCurrentError[ddaCurrentIndex]<<1) < ddaNbStep[ddaCurrentIndex]) {
    ldy         _ddaCurrentIndex
    lda         _ddaCurrentError,y
    bmi         updateError
    asl
    cmp         _ddaNbStep,y
    bcc         updateError
    rts
updateError    
        ;; ddaCurrentError[ddaCurrentIndex]     += ddaNbStep[ddaCurrentIndex];
        ldy _ddaCurrentIndex: lda _ddaCurrentError,y : clc: adc _ddaNbStep,y: sta _ddaCurrentError,y

        ;; ddaCurrentValue[ddaCurrentIndex]     += 1;
        ldy _ddaCurrentIndex: lda _ddaCurrentValue,y :clc : adc #1: sta _ddaCurrentValue,y
.)
    rts

_ddaInit:
.(
    ;;ddaCurrentValue[ddaCurrentIndex]         = ddaStartValue[ddaCurrentIndex];
    ldy     _ddaCurrentIndex: lda _ddaStartValue,y: sta _ddaCurrentValue,y

    ;;ddaEndValue[ddaCurrentIndex]             = ddaStartValue[ddaCurrentIndex] + ddaNbVal[ddaCurrentIndex];
    clc: adc _ddaNbVal,y: sta _ddaEndValue,y

    ldy     _ddaCurrentIndex: lda _ddaNbVal,y : cmp _ddaNbStep,y: beq case_equal: bcc case_NbValLowerNbStep
    ;;if          (ddaNbVal[ddaCurrentIndex] > ddaNbStep[ddaCurrentIndex]) {
case_NbStepLowerNbVal:     
    ;;    ddaCurrentError[ddaCurrentIndex]     = ddaNbVal[ddaCurrentIndex];
        lda _ddaNbVal,y: sta _ddaCurrentError,y
    ;;    ddaStepFunction[ddaCurrentIndex]     = &ddaStep1;
        lda #0 : sta tmp0+1 : lda _ddaCurrentIndex : asl : sta tmp0 : lda tmp0+1 : rol : sta tmp0+1 :
  	    clc : lda #<(_ddaStepFunction) : adc tmp0 : sta tmp0 : lda #>(_ddaStepFunction) : adc tmp0+1 : sta tmp0+1 :
	    ldy #0 : lda #<(_ddaStep1) : sta (tmp0),y : iny : lda #>(_ddaStep1) : sta (tmp0),y :
    rts
    ;;} else if   (ddaNbVal[ddaCurrentIndex] < ddaNbStep[ddaCurrentIndex]) {
case_NbValLowerNbStep:        
    ;;    ddaCurrentError[ddaCurrentIndex]     = ddaNbStep[ddaCurrentIndex];
        lda _ddaNbStep,y: sta _ddaCurrentError,y
    ;;    ddaStepFunction[ddaCurrentIndex]     = &ddaStep2;
        lda #0 : sta tmp0+1 : lda _ddaCurrentIndex : asl : sta tmp0 : lda tmp0+1 : rol : sta tmp0+1 :
  	    clc : lda #<(_ddaStepFunction) : adc tmp0 : sta tmp0 : lda #>(_ddaStepFunction) : adc tmp0+1 : sta tmp0+1 :
	    ldy #0 : lda #<(_ddaStep2) : sta (tmp0),y : iny : lda #>(_ddaStep2) : sta (tmp0),y :
    rts 
    ;;} else {
case_equal:        
    ;;    ddaCurrentError[ddaCurrentIndex]     = ddaEndValue[ddaCurrentIndex];
        lda _ddaEndValue,y: sta _ddaCurrentError,y
    ;;    ddaStepFunction[ddaCurrentIndex]     = &ddaStep0;
        lda #0 : sta tmp0+1 : lda _ddaCurrentIndex : asl : sta tmp0 : lda tmp0+1 : rol : sta tmp0+1 :
  	    clc : lda #<(_ddaStepFunction) : adc tmp0 : sta tmp0 : lda #>(_ddaStepFunction) : adc tmp0+1 : sta tmp0+1 :
	    ldy #0 : lda #<(_ddaStep0) : sta (tmp0),y : iny : lda #>(_ddaStep0) : sta (tmp0),y :

    ;;}
.)
    rts