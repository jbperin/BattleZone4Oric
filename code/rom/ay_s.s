
;; Author: Jean-Baptiste PERIN 

#include "rom/via.h"
#include "rom/score.h"


.zero

_ayReg0      .dsb 1    ; R0  : Chan A Tone Period Fine (LSB)
_ayReg1      .dsb 1    ; R1  : Chan A Tone Period Coarse (HSB)
_ayReg2      .dsb 1    ; R2  : Chan B Tone Period Fine (LSB)
_ayReg3      .dsb 1    ; R3  : Chan B Tone Period Coarse (HSB)
_ayReg4      .dsb 1    ; R4  : Chan C Tone Period Fine (LSB)
_ayReg5      .dsb 1    ; R5  : Chan C Tone Period Coarse (HSB)
_ayReg6      .dsb 1    ; R6  : Noise Period 
_ayReg7      .dsb 1    ; R7  : Mixer 
_ayReg10     .dsb 1    ; R10 : Chan A Amplitude 
_ayReg11     .dsb 1    ; R11 : Chan B Amplitude
_ayReg12     .dsb 1    ; R12 : Chan C Amplitude
_ayReg13     .dsb 1    ; R13 : Envelope Period Fine 
_ayReg14     .dsb 1    ; R14 : Envelope Period Coarse 
_ayReg15     .dsb 1    ; R15 : Envelope Shape / Cycle 

; store precalculated values to write in via PCR for latch sequence
ayLatch_N   .dsb 1
ayLatch_V   .dsb 1
ayUnlatch   .dsb 1

; temporary variable
ayTmp       .dsb 1

#ifdef USE_AY_LIGHT_UPDATE
_ayOldReg0      .dsb 1    ; R0  : Chan A Tone Period Fine (LSB)
_ayOldReg1      .dsb 1    ; R1  : Chan A Tone Period Coarse (HSB)
_ayOldReg2      .dsb 1    ; R2  : Chan B Tone Period Fine (LSB)
_ayOldReg3      .dsb 1    ; R3  : Chan B Tone Period Coarse (HSB)
_ayOldReg4      .dsb 1    ; R4  : Chan C Tone Period Fine (LSB)
_ayOldReg5      .dsb 1    ; R5  : Chan C Tone Period Coarse (HSB)
_ayOldReg6      .dsb 1    ; R6  : Noise Period 
_ayOldReg7      .dsb 1    ; R7  : Mixer 
_ayOldReg10     .dsb 1    ; R10 : Chan A Amplitude 
_ayOldReg11     .dsb 1    ; R11 : Chan B Amplitude
_ayOldReg12     .dsb 1    ; R12 : Chan C Amplitude
_ayOldReg13     .dsb 1    ; R13 : Envelope Period Fine 
_ayOldReg14     .dsb 1    ; R14 : Envelope Period Coarse 
_ayOldReg15     .dsb 1    ; R15 : Envelope Shape / Cycle 
#endif

.text

#define LATCH_REG_NUMBER     sta via_porta:lda ayLatch_N:sta via_pcr:lda ayUnlatch: sta via_pcr
#define LATCH_REG_VALUE      sta via_porta:lda ayLatch_V:sta via_pcr:lda ayUnlatch: sta via_pcr


_ayInit:
    lda #0 
    sta _ayReg0 
    sta _ayReg1 
    sta _ayReg2 
    sta _ayReg3 
    sta _ayReg4 
    sta _ayReg5 
    sta _ayReg6 
    sta _ayReg10 
    sta _ayReg11 
    sta _ayReg12
    sta _ayReg13
    sta _ayReg14
    sta _ayReg15

#ifdef USE_AY_LIGHT_UPDATE
    sta _ayOldReg0
    sta _ayOldReg1
    sta _ayOldReg2
    sta _ayOldReg3
    sta _ayOldReg4
    sta _ayOldReg5
    sta _ayOldReg6
    sta _ayOldReg7
    sta _ayOldReg10
    sta _ayOldReg11
    sta _ayOldReg12
    sta _ayOldReg13
    sta _ayOldReg14
    sta _ayOldReg15
#endif


    lda #$3F    
    sta _ayReg7 


_ayUpdate:
	LDX #<(_ayReg0)	; LL de l'adresse des 14 paramètres
    LDY #>(_ayReg0)	; HH de l'adresse des 14 paramètres
    JSR BlockToAY		
    rts

;; #TODO Remove function below and all its resources
_ayUpdateOld:

    ; sei

    ;; Save bits 
    lda     via_pcr
    and     #$11
    sta     ayTmp

    ;; Prepare values used in latch sequence of VIA 6522
    ora     #$EE     
    sta     ayLatch_N
    lda     ayTmp
    ora     #$EC
    sta     ayLatch_V
    lda     ayTmp
    ora     #$CC
    sta     ayUnlatch

    ;; Tranfert registers one by one

;    lda     #0
;    LATCH_REG_NUMBER
;    sta     via_porta 
;    lda     ayLatch_N
;    sta     via_pcr 
;    lda     ayUnlatch
;    sta     via_pcr
;    lda     _ayReg0
;    LATCH_REG_VALUE
;    sta     via_porta 
;    lda     ayLatch_V
;    sta     via_pcr 
;    lda     ayUnlatch
;    sta     via_pcr

    lda #0 : LATCH_REG_NUMBER: lda _ayReg0 : LATCH_REG_VALUE
    lda #1 : LATCH_REG_NUMBER: lda _ayReg1 : LATCH_REG_VALUE
    lda #2 : LATCH_REG_NUMBER: lda _ayReg2 : LATCH_REG_VALUE
    lda #3 : LATCH_REG_NUMBER: lda _ayReg3 : LATCH_REG_VALUE
    lda #4 : LATCH_REG_NUMBER: lda _ayReg4 : LATCH_REG_VALUE
    lda #5 : LATCH_REG_NUMBER: lda _ayReg5 : LATCH_REG_VALUE
    lda #6 : LATCH_REG_NUMBER: lda _ayReg6 : LATCH_REG_VALUE
    lda #7 : LATCH_REG_NUMBER: lda _ayReg7 : ORA #$40: LATCH_REG_VALUE
    lda #8 : LATCH_REG_NUMBER: lda _ayReg10 : LATCH_REG_VALUE
    lda #9 : LATCH_REG_NUMBER: lda _ayReg11 : LATCH_REG_VALUE
    lda #10: LATCH_REG_NUMBER: lda _ayReg12: LATCH_REG_VALUE
    lda #11: LATCH_REG_NUMBER: lda _ayReg13: LATCH_REG_VALUE
    lda #12: LATCH_REG_NUMBER: lda _ayReg14: LATCH_REG_VALUE
    lda #13: LATCH_REG_NUMBER: lda _ayReg15: LATCH_REG_VALUE    


;    lda #0 : ldx _ayReg0 : jsr ayWriteRegister
;    lda #1 : ldx _ayReg1 : jsr ayWriteRegister
;    lda #2 : ldx _ayReg2 : jsr ayWriteRegister
;    lda #3 : ldx _ayReg3 : jsr ayWriteRegister
;    lda #4 : ldx _ayReg4 : jsr ayWriteRegister
;    lda #5 : ldx _ayReg5 : jsr ayWriteRegister
;    lda #6 : ldx _ayReg6 : jsr ayWriteRegister
;    lda #7 : ldx _ayReg7 : jsr ayWriteRegister
;    lda #8 : ldx _ayReg10: jsr ayWriteRegister
;    lda #9 : ldx _ayReg11: jsr ayWriteRegister
;    lda #10: ldx _ayReg12: jsr ayWriteRegister
;    lda #11: ldx _ayReg13: jsr ayWriteRegister
;    lda #12: ldx _ayReg14: jsr ayWriteRegister
;    lda #13: ldx _ayReg15: jsr ayWriteRegister
    

    ; cli
    rts

#ifdef USE_AY_LIGHT_UPDATE
_ayLightUpdate:
    lda     _ayReg0
    cmp     _ayOldReg0
    beq     ayReg0Updated
    sta     _ayOldReg0
    tax
    lda     #0
    jsr     ayWriteRegister
ayReg0Updated:
    lda     _ayReg1
    cmp     _ayOldReg1
    beq     ayReg1Updated
    sta     _ayOldReg1
    tax
    lda     #1
    jsr     ayWriteRegister
ayReg1Updated:
    lda     _ayReg2
    cmp     _ayOldReg2
    beq     ayReg2Updated
    sta     _ayOldReg2
    tax
    lda     #2
    jsr     ayWriteRegister
ayReg2Updated:
    lda     _ayReg3
    cmp     _ayOldReg3
    beq     ayReg3Updated
    sta     _ayOldReg3
    tax
    lda     #3
    jsr     ayWriteRegister
ayReg3Updated:
    lda     _ayReg4
    cmp     _ayOldReg4
    beq     ayReg4Updated
    sta     _ayOldReg4
    tax
    lda     #4
    jsr     ayWriteRegister
ayReg4Updated:
    lda     _ayReg5
    cmp     _ayOldReg5
    beq     ayReg5Updated
    sta     _ayOldReg5
    tax
    lda     #5
    jsr     ayWriteRegister
ayReg5Updated:
    lda     _ayReg6
    cmp     _ayOldReg6
    beq     ayReg6Updated
    sta     _ayOldReg6
    tax
    lda     #6
    jsr     ayWriteRegister
ayReg6Updated:
    lda     _ayReg7
    cmp     _ayOldReg7
    beq     ayReg7Updated
    sta     _ayOldReg7
    tax
    lda     #7
    jsr     ayWriteRegister
ayReg7Updated:
    lda     _ayReg10
    cmp     _ayOldReg10
    beq     ayReg10Updated
    sta     _ayOldReg10
    tax
    lda     #8
    jsr     ayWriteRegister
ayReg10Updated:
    lda     _ayReg11
    cmp     _ayOldReg11
    beq     ayReg11Updated
    sta     _ayOldReg11
    tax
    lda     #9
    jsr     ayWriteRegister
ayReg11Updated:
    lda     _ayReg12
    cmp     _ayOldReg12
    beq     ayReg12Updated
    sta     _ayOldReg12
    tax
    lda     #10
    jsr     ayWriteRegister
ayReg12Updated:
    lda     _ayReg13
    cmp     _ayOldReg13
    beq     ayReg13Updated
    sta     _ayOldReg13
    tax
    lda     #11
    jsr     ayWriteRegister
ayReg13Updated:
    lda     _ayReg14
    cmp     _ayOldReg14
    beq     ayReg14Updated
    sta     _ayOldReg14
    tax
    lda     #12
    jsr     ayWriteRegister
ayReg14Updated:
    lda     _ayReg15
    cmp     _ayOldReg15
    beq     ayReg15Updated
    sta     _ayOldReg15
    tax
    lda     #13
    jsr     ayWriteRegister
ayReg15Updated:

    rts  
#endif


; parametre A = register number of 8912
; parametre X = donnée à transférer
ayWriteRegister:
.(
    PHP              
    SEI              
    STA via_porta    
    TAY              
    TXA              
    CPY #$07         
    BNE WriteToAY_F59D        
    ORA #$40         
WriteToAY_F59D:
    PHA              
    LDA via_pcr      
    ORA #$EE         
    STA via_pcr      
    AND #$11         
    ORA #$CC         
    STA via_pcr      
    TAX              
    PLA              
    STA via_porta    
    TXA              
    ORA #$EC         
    STA via_pcr      
    AND #$11         
    ORA #$CC         
    STA via_pcr      
    plp
.)              
    rts              


;; Compute amplitude command to store in PSG register based on:
;;  the required volume in register X and consigne in register A
;; INPUTS :
;; Consigne in 4 LSB of register A
;; Volume  in 4 MSB of register X
;; OUTPUT :
;; Command in 4 LSB of register A
;; Destroys registers A and X

compensate:
.(
    stx     ayTmp
    and     ayTmp
    tax
    lda     compensAY,x
.)
    rts

compensAY 	.byt 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	.byt 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1
	.byt 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2
	.byt 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 2, 2, 2, 3, 3, 3
	.byt 0, 0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 3, 3, 4, 4, 4
	.byt 0, 0, 0, 0, 1, 2, 2, 3, 3, 4, 4, 4, 4, 5, 5, 5
	.byt 0, 0, 0, 1, 2, 3, 3, 4, 4, 5, 5, 5, 5, 6, 6, 6
	.byt 0, 0, 1, 2, 3, 4, 4, 5, 5, 6, 6, 6, 6, 7, 7, 7
	.byt 0, 0, 2, 3, 4, 5, 5, 6, 6, 7, 7, 7, 7, 8, 8, 8
	.byt 0, 1, 3, 4, 5, 6, 6, 7, 7, 8, 8, 8, 8, 9, 9, 9
	.byt 0, 2, 4, 5, 6, 7, 7, 8, 8, 9, 9, 9, 9, 10, 10, 10
	.byt 0, 3, 5, 6, 7, 8, 8, 9, 9, 10, 10, 10, 10, 11, 11, 11
	.byt 0, 4, 6, 7, 8, 9, 9, 10, 10, 11, 11, 11, 11, 12, 12, 12
	.byt 0, 5, 7, 8, 9, 10, 10, 11, 11, 12, 12, 12, 12, 13, 13, 13
	.byt 0, 6, 8, 9, 10, 11, 11, 12, 12, 13, 13, 13, 13, 14, 14, 14
	.byt 0, 7, 9, 10, 11, 12, 12, 13, 13, 14, 14, 14, 14, 15, 15, 15

