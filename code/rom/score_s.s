#include "rom/score.h"
;;
;; Circular Buffer 
;;
;; Author :  Jean-Baptiste PERIN
;;
.zero

_ptr_Read__Reg0      .dsb 2    ; R0  : Chan A Tone Period Fine (LSB)
_ptr_Read__Reg1      .dsb 2    ; R1  : Chan A Tone Period Coarse (HSB)
_ptr_Read__Reg2      .dsb 2    ; R2  : Chan B Tone Period Fine (LSB)
_ptr_Read__Reg3      .dsb 2    ; R3  : Chan B Tone Period Coarse (HSB)
_ptr_Read__Reg4      .dsb 2    ; R4  : Chan C Tone Period Fine (LSB)
_ptr_Read__Reg5      .dsb 2    ; R5  : Chan C Tone Period Coarse (HSB)
_ptr_Read__Reg6      .dsb 2    ; R6  : Noise Period 
_ptr_Read__Reg7      .dsb 2    ; R7  : Mixer 
_ptr_Read__Reg10     .dsb 2    ; R10 : Chan A Amplitude 
_ptr_Read__Reg11     .dsb 2    ; R11 : Chan B Amplitude
_ptr_Read__Reg12     .dsb 2    ; R12 : Chan C Amplitude
_ptr_Read__Reg13     .dsb 2    ; R13 : Envelope Period Fine 
_ptr_Read__Reg14     .dsb 2    ; R14 : Envelope Period Coarse 
_ptr_Read__Reg15     .dsb 2    ; R15 : Envelope Shape / Cycle 


_ptr_Write_Reg0      .dsb 2    ; R0  : Chan A Tone Period Fine (LSB)
_ptr_Write_Reg1      .dsb 2    ; R1  : Chan A Tone Period Coarse (HSB)
_ptr_Write_Reg2      .dsb 2    ; R2  : Chan B Tone Period Fine (LSB)
_ptr_Write_Reg3      .dsb 2    ; R3  : Chan B Tone Period Coarse (HSB)
_ptr_Write_Reg4      .dsb 2    ; R4  : Chan C Tone Period Fine (LSB)
_ptr_Write_Reg5      .dsb 2    ; R5  : Chan C Tone Period Coarse (HSB)
_ptr_Write_Reg6      .dsb 2    ; R6  : Noise Period 
_ptr_Write_Reg7      .dsb 2    ; R7  : Mixer 
_ptr_Write_Reg10     .dsb 2    ; R10 : Chan A Amplitude 
_ptr_Write_Reg11     .dsb 2    ; R11 : Chan B Amplitude
_ptr_Write_Reg12     .dsb 2    ; R12 : Chan C Amplitude
_ptr_Write_Reg13     .dsb 2    ; R13 : Envelope Period Fine 
_ptr_Write_Reg14     .dsb 2    ; R14 : Envelope Period Coarse 
_ptr_Write_Reg15     .dsb 2    ; R15 : Envelope Shape / Cycle 

.text

_ay_score            .dsb NB_REGISTER*NB_SAMPLE

_current_frame_read  .dsb 1
_current_frame_write .dsb 1
_current_end_write .dsb 1

_initAyScore:
.(
    lda #<(_ay_score+ 0 * NB_SAMPLE): sta _ptr_Read__Reg0:  sta _ptr_Write_Reg0:   lda #>(_ay_score+ 0 * NB_SAMPLE): sta _ptr_Read__Reg0+1:  sta _ptr_Write_Reg0+1
    lda #<(_ay_score+ 1 * NB_SAMPLE): sta _ptr_Read__Reg1:  sta _ptr_Write_Reg1:   lda #>(_ay_score+ 1 * NB_SAMPLE): sta _ptr_Read__Reg1+1:  sta _ptr_Write_Reg1+1
    lda #<(_ay_score+ 2 * NB_SAMPLE): sta _ptr_Read__Reg2:  sta _ptr_Write_Reg2:   lda #>(_ay_score+ 2 * NB_SAMPLE): sta _ptr_Read__Reg2+1:  sta _ptr_Write_Reg2+1
    lda #<(_ay_score+ 3 * NB_SAMPLE): sta _ptr_Read__Reg3:  sta _ptr_Write_Reg3:   lda #>(_ay_score+ 3 * NB_SAMPLE): sta _ptr_Read__Reg3+1:  sta _ptr_Write_Reg3+1
    lda #<(_ay_score+ 4 * NB_SAMPLE): sta _ptr_Read__Reg4:  sta _ptr_Write_Reg4:   lda #>(_ay_score+ 4 * NB_SAMPLE): sta _ptr_Read__Reg4+1:  sta _ptr_Write_Reg4+1
    lda #<(_ay_score+ 5 * NB_SAMPLE): sta _ptr_Read__Reg5:  sta _ptr_Write_Reg5:   lda #>(_ay_score+ 5 * NB_SAMPLE): sta _ptr_Read__Reg5+1:  sta _ptr_Write_Reg5+1
    lda #<(_ay_score+ 6 * NB_SAMPLE): sta _ptr_Read__Reg6:  sta _ptr_Write_Reg6:   lda #>(_ay_score+ 6 * NB_SAMPLE): sta _ptr_Read__Reg6+1:  sta _ptr_Write_Reg6+1
    lda #<(_ay_score+ 7 * NB_SAMPLE): sta _ptr_Read__Reg7:  sta _ptr_Write_Reg7:   lda #>(_ay_score+ 7 * NB_SAMPLE): sta _ptr_Read__Reg7+1:  sta _ptr_Write_Reg7+1
    lda #<(_ay_score+ 8 * NB_SAMPLE): sta _ptr_Read__Reg10: sta _ptr_Write_Reg10:  lda #>(_ay_score+ 8 * NB_SAMPLE): sta _ptr_Read__Reg10+1: sta _ptr_Write_Reg10+1
    lda #<(_ay_score+ 9 * NB_SAMPLE): sta _ptr_Read__Reg11: sta _ptr_Write_Reg11:  lda #>(_ay_score+ 9 * NB_SAMPLE): sta _ptr_Read__Reg11+1: sta _ptr_Write_Reg11+1
    lda #<(_ay_score+ 10* NB_SAMPLE): sta _ptr_Read__Reg12: sta _ptr_Write_Reg12:  lda #>(_ay_score+ 10* NB_SAMPLE): sta _ptr_Read__Reg12+1: sta _ptr_Write_Reg12+1
    lda #<(_ay_score+ 11* NB_SAMPLE): sta _ptr_Read__Reg13: sta _ptr_Write_Reg13:  lda #>(_ay_score+ 11* NB_SAMPLE): sta _ptr_Read__Reg13+1: sta _ptr_Write_Reg13+1
    lda #<(_ay_score+ 12* NB_SAMPLE): sta _ptr_Read__Reg14: sta _ptr_Write_Reg14:  lda #>(_ay_score+ 12* NB_SAMPLE): sta _ptr_Read__Reg14+1: sta _ptr_Write_Reg14+1
    lda #<(_ay_score+ 13* NB_SAMPLE): sta _ptr_Read__Reg15: sta _ptr_Write_Reg15:  lda #>(_ay_score+ 13* NB_SAMPLE): sta _ptr_Read__Reg15+1: sta _ptr_Write_Reg15+1
    lda #0 : sta _current_frame_read: : sta _current_frame_write 
.)
    rts



stepReadScore:
.(
    lda     _current_frame_read
    cmp     _current_end_write
    bne     ScoreNotEmpty
    jmp     stepReadDone
ScoreNotEmpty

    ldy     _current_frame_read
    lda     (_ptr_Read__Reg0 ), Y: sta     _ayReg0
    lda     (_ptr_Read__Reg1 ), Y: sta     _ayReg1 
    lda     (_ptr_Read__Reg2 ), Y: sta     _ayReg2 
    lda     (_ptr_Read__Reg3 ), Y: sta     _ayReg3 
    lda     (_ptr_Read__Reg4 ), Y: sta     _ayReg4 
    lda     (_ptr_Read__Reg5 ), Y: sta     _ayReg5 
    lda     (_ptr_Read__Reg6 ), Y: sta     _ayReg6 
    lda     (_ptr_Read__Reg7 ), Y: sta     _ayReg7 
    lda     (_ptr_Read__Reg10), Y: sta     _ayReg10 
    lda     (_ptr_Read__Reg11), Y: sta     _ayReg11 
    lda     (_ptr_Read__Reg12), Y: sta     _ayReg12
    lda     (_ptr_Read__Reg13), Y: sta     _ayReg13
    lda     (_ptr_Read__Reg14), Y: sta     _ayReg14
    lda     (_ptr_Read__Reg15), Y: sta     _ayReg15


#ifdef USE_AY_LIGHT_UPDATE
    jsr     _ayLightUpdate
#else
    jsr     _ayUpdate
#endif

    ;; current_frame_read = (current_frame_read + 1) % NB_SAMPLE
    inc     _current_frame_read
    lda     _current_frame_read
    cmp     #NB_SAMPLE
    bne     NoRollOver
    lda     #0
    sta     _current_frame_read
NoRollOver    

    
;     inc     _current_idx_read
;     lda     _current_idx_read
;     cmp     #NB_SAMPLE
;     bne     skip_modulo_18
;         lda     #0
;         sta     _current_idx_read
;         inc     _ptr_Read__Reg0+1
;         lda     _ptr_Read__Reg0+1
;         cmp     #>(_ay_score+NB_GROUP*256)
;         bne     endif_rewind
;             lda #>(_ay_score + 0 * NB_SAMPLE): sta _ptr_Read__Reg0+1
;             lda #>(_ay_score + 1 * NB_SAMPLE): sta _ptr_Read__Reg1+1
;             lda #>(_ay_score + 2 * NB_SAMPLE): sta _ptr_Read__Reg2+1
;             lda #>(_ay_score + 3 * NB_SAMPLE): sta _ptr_Read__Reg3+1
;             lda #>(_ay_score + 4 * NB_SAMPLE): sta _ptr_Read__Reg4+1
;             lda #>(_ay_score + 5 * NB_SAMPLE): sta _ptr_Read__Reg5+1
;             lda #>(_ay_score + 6 * NB_SAMPLE): sta _ptr_Read__Reg6+1
;             lda #>(_ay_score + 7 * NB_SAMPLE): sta _ptr_Read__Reg7+1
;             lda #>(_ay_score + 8 * NB_SAMPLE): sta _ptr_Read__Reg10+1
;             lda #>(_ay_score + 9 * NB_SAMPLE): sta _ptr_Read__Reg11+1
;             lda #>(_ay_score + 10* NB_SAMPLE): sta _ptr_Read__Reg12+1
;             lda #>(_ay_score + 11* NB_SAMPLE): sta _ptr_Read__Reg13+1
;             lda #>(_ay_score + 12* NB_SAMPLE): sta _ptr_Read__Reg14+1
;             lda #>(_ay_score + 13* NB_SAMPLE): sta _ptr_Read__Reg15+1
; endif_rewind 
; skip_modulo_18

;;     inc     _current_idx_read
;;     lda     _current_idx_read
;;     eor     #18
;;     bne     skip_modulo18
;;     sta     _current_idx_read
;;     inc     _ptr_Read__Reg0+1
;; 
;;     lda     _ptr_Read__Reg0 +1
;;     eor     #>_ay_score+
;;     bne     skip_rewind
;; 
;;         lda #>_ay_score: sta _ptr_Read__Reg0+1
;;         lda #>_ay_score: sta _ptr_Read__Reg1+1
;;         lda #>_ay_score: sta _ptr_Read__Reg2+1
;;         lda #>_ay_score: sta _ptr_Read__Reg3+1
;;         lda #>_ay_score: sta _ptr_Read__Reg4+1
;;         lda #>_ay_score: sta _ptr_Read__Reg5+1
;;         lda #>_ay_score: sta _ptr_Read__Reg6+1
;;         lda #>_ay_score: sta _ptr_Read__Reg7+1
;;         lda #>_ay_score: sta _ptr_Read__Reg10+1
;;         lda #>_ay_score: sta _ptr_Read__Reg11+1
;;         lda #>_ay_score: sta _ptr_Read__Reg12+1
;;         lda #>_ay_score: sta _ptr_Read__Reg13+1
;;         lda #>_ay_score: sta _ptr_Read__Reg14+1
;;         lda #>_ay_score: sta _ptr_Read__Reg15+1
;;         jmp endif_rewind
;; skip_rewind
;;         inc     _ptr_Read__Reg1 +1
;;         inc     _ptr_Read__Reg2 +1
;;         inc     _ptr_Read__Reg3 +1
;;         inc     _ptr_Read__Reg4 +1
;;         inc     _ptr_Read__Reg5 +1
;;         inc     _ptr_Read__Reg6 +1
;;         inc     _ptr_Read__Reg7 +1
;;         inc     _ptr_Read__Reg10 +1
;;         inc     _ptr_Read__Reg11 +1
;;         inc     _ptr_Read__Reg12+1
;;         inc     _ptr_Read__Reg13+1
;;         inc     _ptr_Read__Reg14+1
;;         inc     _ptr_Read__Reg15+1
;; 
;; endif_rewind
;; 
;; skip_modulo18
    
stepReadDone
.)
    rts


