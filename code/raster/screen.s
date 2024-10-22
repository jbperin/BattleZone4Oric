#include "params.h"

#ifdef USE_BUFFERED_SCREEN
    .bss
* = $_ADR_SCREEN_BUFFER    
hires_screen_buffer .dsb 5480
    .text
; 5439 ~= 135*40+39
; memcpy((void *) (HIRES_SCREEN_ADDRESS+(FIRSTLINE*SCREEN_WIDTH)),(void *)(ADR_DRAWING+(FIRSTLINE*SCREEN_WIDTH)),(8*12)*SCREEN_WIDTH);// FIXME .. should be 8*11*SCREEN_WIDTH
_ScreenCopyHires
.(
	ldx #0
loop_x	
	lda $_ADR_DRAWING+256*0,x
	sta $_ADR_SCREEN_MEMORY+256*0,x
	lda $_ADR_DRAWING+256*1,x
	sta $_ADR_SCREEN_MEMORY+256*1,x
	lda $_ADR_DRAWING+256*2,x
	sta $_ADR_SCREEN_MEMORY+256*2,x
	lda $_ADR_DRAWING+256*3,x
	sta $_ADR_SCREEN_MEMORY+256*3,x
	lda $_ADR_DRAWING+256*4,x
	sta $_ADR_SCREEN_MEMORY+256*4,x
	lda $_ADR_DRAWING+256*5,x
	sta $_ADR_SCREEN_MEMORY+256*5,x
	lda $_ADR_DRAWING+256*6,x
	sta $_ADR_SCREEN_MEMORY+256*6,x
	lda $_ADR_DRAWING+256*7,x
	sta $_ADR_SCREEN_MEMORY+256*7,x
	lda $_ADR_DRAWING+256*8,x
	sta $_ADR_SCREEN_MEMORY+256*8,x
	lda $_ADR_DRAWING+256*9,x
	sta $_ADR_SCREEN_MEMORY+256*9,x
	
	lda $_ADR_DRAWING+256*10,x
	sta $_ADR_SCREEN_MEMORY+256*10,x
	lda $_ADR_DRAWING+256*11,x
	sta $_ADR_SCREEN_MEMORY+256*11,x
	lda $_ADR_DRAWING+256*12,x
	sta $_ADR_SCREEN_MEMORY+256*12,x
	lda $_ADR_DRAWING+256*13,x
	sta $_ADR_SCREEN_MEMORY+256*13,x
	lda $_ADR_DRAWING+256*14,x
	sta $_ADR_SCREEN_MEMORY+256*14,x
	lda $_ADR_DRAWING+256*15,x
	sta $_ADR_SCREEN_MEMORY+256*15,x
	lda $_ADR_DRAWING+256*16,x
	sta $_ADR_SCREEN_MEMORY+256*16,x
	lda $_ADR_DRAWING+256*17,x
	sta $_ADR_SCREEN_MEMORY+256*17,x
	lda $_ADR_DRAWING+256*18,x
	sta $_ADR_SCREEN_MEMORY+256*18,x
	lda $_ADR_DRAWING+256*19,x
	sta $_ADR_SCREEN_MEMORY+256*19,x
	lda $_ADR_DRAWING+256*20,x
	sta $_ADR_SCREEN_MEMORY+256*20,x

	dex
	beq end
	jmp loop_x
end

	rts
.)



#endif

; memset(ADR_DRAWING+(FIRSTLINE*SCREEN_WIDTH), 64, (8*12)*SCREEN_WIDTH); // FIXME .. should be 8*11*SCREEN_WIDTH
_HiresClear
.(
	lda #$40	; pixel eteint
	ldx #0		; compteur de boucle a 256
loop_x	
	sta $_ADR_DRAWING+256*0,x
	sta $_ADR_DRAWING+256*1,x
	sta $_ADR_DRAWING+256*2,x
	sta $_ADR_DRAWING+256*3,x
	sta $_ADR_DRAWING+256*4,x
	sta $_ADR_DRAWING+256*5,x
	sta $_ADR_DRAWING+256*6,x
	sta $_ADR_DRAWING+256*7,x
	sta $_ADR_DRAWING+256*8,x
	sta $_ADR_DRAWING+256*9,x
	sta $_ADR_DRAWING+256*10,x
	sta $_ADR_DRAWING+256*11,x
	sta $_ADR_DRAWING+256*12,x
	sta $_ADR_DRAWING+256*13,x
	sta $_ADR_DRAWING+256*14,x
	sta $_ADR_DRAWING+256*15,x
	sta $_ADR_DRAWING+256*16,x
	sta $_ADR_DRAWING+256*17,x
	sta $_ADR_DRAWING+256*18,x
	sta $_ADR_DRAWING+256*19,x
	sta $_ADR_DRAWING+256*20,x
	; TODO Ajouter les quelques octets manquant pour terminer la dernière ligne

	dex
	bne loop_x
	rts
.)
