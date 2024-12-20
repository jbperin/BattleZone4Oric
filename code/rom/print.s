
;
; This is a simple display module
; called by the C part of the program
;

/*
 * We define the adress of the TEXT screen.
 */
#define DISPLAY_ADRESS $BB80


;
; We use a table of bytes to avoid the multiplication 
; by 40. We could have used a multiplication routine
; but introducing table accessing is not a bad thing.
; In order to speed up things, we precompute the real
; adress of each start of line. Each table takes only
; 28 bytes, even if it looks impressive at first glance.
;

; This table contains lower 8 bits of the adress
_ScreenAdressLow
	.byt <(DISPLAY_ADRESS+40*0)
	.byt <(DISPLAY_ADRESS+40*1)
	.byt <(DISPLAY_ADRESS+40*2)
	.byt <(DISPLAY_ADRESS+40*3)
	.byt <(DISPLAY_ADRESS+40*4)
	.byt <(DISPLAY_ADRESS+40*5)
	.byt <(DISPLAY_ADRESS+40*6)
	.byt <(DISPLAY_ADRESS+40*7)
	.byt <(DISPLAY_ADRESS+40*8)
	.byt <(DISPLAY_ADRESS+40*9)
	.byt <(DISPLAY_ADRESS+40*10)
	.byt <(DISPLAY_ADRESS+40*11)
	.byt <(DISPLAY_ADRESS+40*12)
	.byt <(DISPLAY_ADRESS+40*13)
	.byt <(DISPLAY_ADRESS+40*14)
	.byt <(DISPLAY_ADRESS+40*15)
	.byt <(DISPLAY_ADRESS+40*16)
	.byt <(DISPLAY_ADRESS+40*17)
	.byt <(DISPLAY_ADRESS+40*18)
	.byt <(DISPLAY_ADRESS+40*19)
	.byt <(DISPLAY_ADRESS+40*20)
	.byt <(DISPLAY_ADRESS+40*21)
	.byt <(DISPLAY_ADRESS+40*22)
	.byt <(DISPLAY_ADRESS+40*23)
	.byt <(DISPLAY_ADRESS+40*24)
	.byt <(DISPLAY_ADRESS+40*25)
	.byt <(DISPLAY_ADRESS+40*26)
	.byt <(DISPLAY_ADRESS+40*27)

; This table contains hight 8 bits of the adress
_ScreenAdressHigh
	.byt >(DISPLAY_ADRESS+40*0)
	.byt >(DISPLAY_ADRESS+40*1)
	.byt >(DISPLAY_ADRESS+40*2)
	.byt >(DISPLAY_ADRESS+40*3)
	.byt >(DISPLAY_ADRESS+40*4)
	.byt >(DISPLAY_ADRESS+40*5)
	.byt >(DISPLAY_ADRESS+40*6)
	.byt >(DISPLAY_ADRESS+40*7)
	.byt >(DISPLAY_ADRESS+40*8)
	.byt >(DISPLAY_ADRESS+40*9)
	.byt >(DISPLAY_ADRESS+40*10)
	.byt >(DISPLAY_ADRESS+40*11)
	.byt >(DISPLAY_ADRESS+40*12)
	.byt >(DISPLAY_ADRESS+40*13)
	.byt >(DISPLAY_ADRESS+40*14)
	.byt >(DISPLAY_ADRESS+40*15)
	.byt >(DISPLAY_ADRESS+40*16)
	.byt >(DISPLAY_ADRESS+40*17)
	.byt >(DISPLAY_ADRESS+40*18)
	.byt >(DISPLAY_ADRESS+40*19)
	.byt >(DISPLAY_ADRESS+40*20)
	.byt >(DISPLAY_ADRESS+40*21)
	.byt >(DISPLAY_ADRESS+40*22)
	.byt >(DISPLAY_ADRESS+40*23)
	.byt >(DISPLAY_ADRESS+40*24)
	.byt >(DISPLAY_ADRESS+40*25)
	.byt >(DISPLAY_ADRESS+40*26)
	.byt >(DISPLAY_ADRESS+40*27)


.zero
tmpY .dsb 1


.text

varA .byt  128,160,200
varB .dsb  1
varC .dsb  1

idwWrt .dsb 1


;; Inspired from http://6502org.wikidot.com/software-output-decimal

;
; The value and display position will be read from the stack.
; sp+0 => X coordinate
; sp+2 => Y coordinate
; sp+4 => Value to display
;
_DecimalPrint

					ldy #2
					lda (sp),y				; Access Y coordinate
					tax
					
					lda _ScreenAdressLow,x	; Get the LOW part of the screen adress
					clc						; Clear the carry (because we will do an addition after)
					ldy #0
					sty idwWrt
					adc (sp),y				; Add X coordinate
					sta decprint_write+1
					lda _ScreenAdressHigh,x	; Get the HIGH part of the screen adress
					adc #0					; Eventually add the carry to complete the 16 bits addition
					sta decprint_write+2				

					;; LDA _remaining_seconds
					ldy #4
					lda (sp),y

					LDX #1
					STX varC
					INX
					LDY #$40
decprint_label1     STY varB
		            LSR
decprint_label2     ROL
					BCS decprint_label3
					CMP varA,X
					BCC decprint_label4
decprint_label3     SBC varA,X
		            SEC
decprint_label4     ROL varB
					BCC decprint_label2
					TAY
					CPX varC
					LDA varB
					BCC decprint_label5
					BEQ decprint_label6
					STX varC
decprint_label5     EOR #$10
decprint_label6     EOR #$20

            ;;JSR OUTPUT
					sty tmpY
					ldy idwWrt
decprint_write		sta $0123, Y
					inc idwWrt
					ldy tmpY


					TYA
					LDY #$10
					DEX
					BPL decprint_label1
	RTS

;
; The message and display position will be read from the stack.
; sp+0 => X coordinate
; sp+2 => Y coordinate
; sp+4 => Adress of the message to display
;
_AdvancedPrint

	; Initialise display adress
	; this uses self-modifying code
	; (the $0123 is replaced by display adress)
	
	; The idea is to get the Y position from the stack,
	; and use it as an index in the two adress tables.
	; We also need to add the value of the X position,
	; also taken from the stack to the resulting value.
	
	ldy #2
	lda (sp),y				; Access Y coordinate
	tax
	
	lda _ScreenAdressLow,x	; Get the LOW part of the screen adress
	clc						; Clear the carry (because we will do an addition after)
	ldy #0
	adc (sp),y				; Add X coordinate
	sta write+1
	lda _ScreenAdressHigh,x	; Get the HIGH part of the screen adress
	adc #0					; Eventually add the carry to complete the 16 bits addition
	sta write+2				



	; Initialise message adress using the stack parameter
	; this uses self-modifying code
	; (the $0123 is replaced by message adress)
	ldy #4
	lda (sp),y
	sta read+1
	iny
	lda (sp),y
	sta read+2


	; Start at the first character
	ldx #0
loop_char

	; Read the character, exit if it is a 0
read
	lda $0123,x
	beq end_loop_char

	; Write the character on screen
write
	sta $0123,x

	; Next character, and loop
	inx
	jmp loop_char  

	; Finished !
end_loop_char
	rts

end_AdvancedPrint