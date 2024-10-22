

own_get_2ptr
	ldy #0
	lda (sp),y
	sta op1
	iny
	lda (sp),y
	sta op1+1

	ldy #2
	lda (sp),y
	sta op2
	iny
	lda (sp),y
	sta op2+1
	rts


_memoryset
	ldy #0          
	lda (sp),y
	sta op1
	sta patch_ownmemsetret_x+1 
	iny
	lda (sp),y
	sta op1+1
	sta patch_ownmemsetret_a+1 

	iny             
	lda (sp),y
	pha             

	ldy #4          
	sec
	lda #0
	sbc (sp),y
	sta tmp
	tax
	iny
	cmp #1
	lda (sp),y
	adc #0
	tay
	beq ownmemsetret   

	sec             
	lda op1
	sbc tmp
	sta ownmemsetloop+1
	lda op1+1
	sbc #0
	sta ownmemsetloop+2

	pla             

ownmemsetloop              
    sta $2211,x     
    inx
    bne ownmemsetloop
    inc ownmemsetloop+2
	dey
    bne ownmemsetloop

ownmemsetret
patch_ownmemsetret_x
    ldx #1          
patch_ownmemsetret_a
	lda #3
	rts




_memorycpy
.(
	jsr own_get_2ptr
	ldy #4
	sec
	lda #0
	sbc (sp),y
	sta tmp
	tax
	iny
	cmp #1
	lda (sp),y
	adc #0
	tay
	beq return

	sec
	lda op1
	sbc tmp
	sta memcpyloop+4
	lda op1+1
	sbc #0
	sta memcpyloop+5

	sec
	lda op2
	sbc tmp
	sta memcpyloop+1
	lda op2+1
	sbc #0
	sta memcpyloop+2

memcpyloop
	lda $2211,x
	sta $5544,x
	inx
	bne memcpyloop
	inc memcpyloop+2
	inc memcpyloop+5
	dey
	bne memcpyloop
return
	rts
.)


