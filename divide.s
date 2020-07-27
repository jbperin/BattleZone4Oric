; found at http://forums.nesdev.com/viewtopic.php?f=2&t=11336

; Unsigned Integer Division Routines
; by Omegamatrix

.zero

divideTemp .dsb 1

.text

_resDivide .dsb 1

DivideHandlerTableLow
  .byt 0
	.byt <(_DivideBy1)
	.byt <(_DivideBy2)
	.byt <(_DivideBy3)
	.byt <(_DivideBy4)
	.byt <(_DivideBy5)
	.byt <(_DivideBy6)
	.byt <(_DivideBy7)
	.byt <(_DivideBy8)
	.byt <(_DivideBy9)
	.byt <(_DivideBy10)
  .byt <(_DivideBy11)
	.byt <(_DivideBy12)
	.byt <(_DivideBy13)
	.byt <(_DivideBy14)
	.byt <(_DivideBy15)
	.byt <(_DivideBy16)
	.byt <(_DivideBy17)
	.byt <(_DivideBy18)
	.byt <(_DivideBy19)
	.byt <(_DivideBy20)
  .byt <(_DivideBy21)
	.byt <(_DivideBy22)
	.byt <(_DivideBy23)
	.byt <(_DivideBy24)
	.byt <(_DivideBy25)
	.byt <(_DivideBy26)
	.byt <(_DivideBy27)
	.byt <(_DivideBy28)
	.byt <(_DivideBy29)
	.byt <(_DivideBy30)
  .byt <(_DivideBy31)
	.byt <(_DivideBy32)

DivideHandlerTableHigh
  .byt 0
	.byt >(_DivideBy1)
	.byt >(_DivideBy2)
	.byt >(_DivideBy3)
	.byt >(_DivideBy4)
	.byt >(_DivideBy5)
	.byt >(_DivideBy6)
	.byt >(_DivideBy7)
	.byt >(_DivideBy8)
	.byt >(_DivideBy9)
	.byt >(_DivideBy10)
  .byt >(_DivideBy11)
	.byt >(_DivideBy12)
	.byt >(_DivideBy13)
	.byt >(_DivideBy14)
	.byt >(_DivideBy15)
	.byt >(_DivideBy16)
	.byt >(_DivideBy17)
	.byt >(_DivideBy18)
	.byt >(_DivideBy19)
	.byt >(_DivideBy20)
  .byt >(_DivideBy21)
	.byt >(_DivideBy22)
	.byt >(_DivideBy23)
	.byt >(_DivideBy24)
	.byt >(_DivideBy25)
	.byt >(_DivideBy26)
	.byt >(_DivideBy27)
	.byt >(_DivideBy28)
	.byt >(_DivideBy29)
	.byt >(_DivideBy30)
  .byt >(_DivideBy31)
	.byt >(_DivideBy32)


;; void divide(unsigned char N,
;;           unsigned char D) {
_divide:

; sp+0 => N
; sp+2 => D

	;; save context
  ;;pha:tya:pha

	ldy		#0
	lda		(sp),y				; Access Numerator
	sta		divideTemp

	ldy		#2
	lda		(sp),y				; stare  Diviser in X 
	tax

  lda   divideTemp    ; store Numerator in A

	jsr 	fastDivide

  sta   _resDivide    ; Store Quotient

divide_done:
	;; restore context
	;;pla:tay:pla
  
    rts


fastDivide:
;; INPUT : 
;; A contains numerator
;; X contains divisor (<= 32)
;; OUTPUT : 
;; A contains
  tay
  lda	DivideHandlerTableLow,x
  sta gotoDivide+1
  lda	DivideHandlerTableHigh,x
  sta gotoDivide+2
  tya
gotoDivide:
  jmp $1234

_DivideBy1:

  rts


_DivideBy2:
;1 byte, 2 cycles
  lsr
  rts

_DivideBy3:
;18 bytes, 30 cycles
  sta  divideTemp
  lsr
  adc  #21
  lsr
  adc  divideTemp
  ror
  lsr
  adc  divideTemp
  ror
  lsr
  adc  divideTemp
  ror
  lsr
  rts

_DivideBy4:
;2 bytes, 4 cycles
  lsr
  lsr
  rts

_DivideBy5:
;18 bytes, 30 cycles
  sta  divideTemp
  lsr
  adc  #13
  adc  divideTemp
  ror
  lsr
  lsr
  adc  divideTemp
  ror
  adc  divideTemp
  ror
  lsr
  lsr
  rts

_DivideBy6:
;17 bytes, 30 cycles
  lsr
  sta  divideTemp
  lsr
  lsr
  adc  divideTemp
  ror
  lsr
  adc  divideTemp
  ror
  lsr
  adc  divideTemp
  ror
  lsr
  rts

_DivideBy7:
;Divide by 7 (From December '84 Apple Assembly Line)
;15 bytes, 27 cycles
  sta  divideTemp
  lsr
  lsr
  lsr
  adc  divideTemp
  ror
  lsr
  lsr
  adc  divideTemp
  ror
  lsr
  lsr
  rts

_DivideBy8:
;3 bytes, 6 cycles
  lsr
  lsr
  lsr
  rts

_DivideBy9:
;17 bytes, 30 cycles
  sta  divideTemp
  lsr
  lsr
  lsr
  adc  divideTemp
  ror
  adc  divideTemp
  ror
  adc  divideTemp
  ror
  lsr
  lsr
  lsr
  rts

_DivideBy10:
;17 bytes, 30 cycles
  lsr
  sta  divideTemp
  lsr
  adc  divideTemp
  ror
  lsr
  lsr
  adc  divideTemp
  ror
  adc  divideTemp
  ror
  lsr
  lsr
  rts

_DivideBy11:
;20 bytes, 35 cycles
  sta  divideTemp
  lsr
  lsr
  adc  divideTemp
  ror
  adc  divideTemp
  ror
  adc  divideTemp
  ror
  lsr
  adc  divideTemp
  ror
  lsr
  lsr
  lsr
  rts

_DivideBy12:
;17 bytes, 30 cycles
  lsr
  lsr
  sta  divideTemp
  lsr
  adc  divideTemp
  ror
  lsr
  adc  divideTemp
  ror
  lsr
  adc  divideTemp
  ror
  lsr
  rts

_DivideBy13:
; 21 bytes, 37 cycles
  sta  divideTemp
  lsr
  adc  divideTemp
  ror
  adc  divideTemp
  ror
  adc  divideTemp
  ror
  lsr
  lsr
  clc
  adc  divideTemp
  ror
  lsr
  lsr
  lsr
  rts

_DivideBy14:
;1/14 = 1/7 * 1/2
;16 bytes, 29 cycles
  sta  divideTemp
  lsr
  lsr
  lsr
  adc  divideTemp
  ror
  lsr
  lsr
  adc  divideTemp
  ror
  lsr
  lsr
  lsr
  rts

_DivideBy15:
;14 bytes, 24 cycles
  sta  divideTemp
  lsr
  adc  #4
  lsr
  lsr
  lsr
  adc  divideTemp
  ror
  lsr
  lsr
  lsr
  rts

_DivideBy16:
;4 bytes, 8 cycles
  lsr
  lsr
  lsr
  lsr
  rts

_DivideBy17:
;18 bytes, 30 cycles
  sta  divideTemp
  lsr
  adc  divideTemp
  ror
  adc  divideTemp
  ror
  adc  divideTemp
  ror
  adc  #0
  lsr
  lsr
  lsr
  lsr
  rts

_DivideBy18:
;18 bytes, 32 cycles
  sta  divideTemp
  lsr
  lsr
  lsr
  adc  divideTemp
  ror
  adc  divideTemp
  ror
  adc  divideTemp
  ror
  lsr
  lsr
  lsr
  lsr
  rts

_DivideBy19:
;17 bytes, 30 cycles
  sta  divideTemp
  lsr
  adc  divideTemp
  ror
  lsr
  adc  divideTemp
  ror
  adc  divideTemp
  ror
  lsr
  lsr
  lsr
  lsr
  rts

_DivideBy20:
;18 bytes, 32 cycles
  lsr
  lsr
  sta  divideTemp
  lsr
  adc  divideTemp
  ror
  lsr
  lsr
  adc  divideTemp
  ror
  adc  divideTemp
  ror
  lsr
  lsr
  rts

_DivideBy21:
;20 bytes, 36 cycles
  sta  divideTemp
  lsr
  adc  divideTemp
  ror
  lsr
  lsr
  lsr
  lsr
  adc  divideTemp
  ror
  adc  divideTemp
  ror
  lsr
  lsr
  lsr
  lsr
  rts

_DivideBy22:
;21 bytes, 34 cycles
   lsr
   cmp  #33
   adc  #0
   sta  divideTemp
   lsr
   adc  divideTemp
   ror
   adc  divideTemp
   ror
   lsr
   adc  divideTemp
   ror
   lsr
   lsr
   lsr
  rts

_DivideBy23:
;19 bytes, 34 cycles
  sta  divideTemp
  lsr
  lsr
  lsr
  adc  divideTemp
  ror
  adc  divideTemp
  ror
  lsr
  adc  divideTemp
  ror
  lsr
  lsr
  lsr
  lsr
  rts

_DivideBy24:
;15 bytes, 27 cycles
   lsr
   lsr
   lsr
   sta   divideTemp
   lsr
   lsr
   adc   divideTemp
   ror
   lsr
   adc   divideTemp
   ror
   lsr
  rts

_DivideBy25:
;16 bytes, 29 cycles
  sta  divideTemp
  lsr
  lsr
  lsr
  adc  divideTemp
  ror
  lsr
  adc  divideTemp
  ror
  lsr
  lsr
  lsr
  lsr
  rts

_DivideBy26:
;21 bytes, 37 cycles
  lsr
  sta  divideTemp
  lsr
  adc  divideTemp
  ror
  adc  divideTemp
  ror
  adc  divideTemp
  ror
  lsr
  lsr
  adc  divideTemp
  ror
  lsr
  lsr
  lsr
  rts

_DivideBy27:
;15 bytes, 27 cycles
  sta  divideTemp
  lsr
  adc  divideTemp
  ror
  lsr
  lsr
  adc  divideTemp
  ror
  lsr
  lsr
  lsr
  lsr
  rts

_DivideBy28:
;14 bytes, 24 cycles
  lsr
  lsr
  sta  divideTemp
  lsr
  adc  #2
  lsr
  lsr
  adc  divideTemp
  ror
  lsr
  lsr
  rts

_DivideBy29:
;20 bytes, 36 cycles
  sta  divideTemp
  lsr
  lsr
  adc  divideTemp
  ror
  adc  divideTemp
  ror
  lsr
  lsr
  lsr
  adc  divideTemp
  ror
  lsr
  lsr
  lsr
  lsr
  rts

_DivideBy30:
;14 bytes, 26 cycles
  sta  divideTemp
  lsr
  lsr
  lsr
  lsr
  sec
  adc  divideTemp
  ror
  lsr
  lsr
  lsr
  lsr
  rts

_DivideBy31:
;14 bytes, 26 cycles
  sta  divideTemp
  lsr
  lsr
  lsr
  lsr
  lsr
  adc  divideTemp
  ror
  lsr
  lsr
  lsr
  lsr
  rts

_DivideBy32:
  lsr
  lsr
  lsr
  lsr
  lsr
  rts

