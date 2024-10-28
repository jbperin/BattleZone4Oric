; FOCAL = 32 * log2(48)
#define FOCAL 100
#define SW 240
#define SH 136

.zero

octant .dsb 1          ;

_tx .dsb 1
_ty .dsb 1
_res .dsb 1

.text

;https://codebase64.org/doku.php?id=base:8bit_atan2_8-bit_angle
_atan2_8:
.(

    lda _tx
    clc
    bpl Xpositiv
    eor #$ff
	adc #1
    sec
Xpositiv:
    tax
    rol octant

    lda _ty
    clc
    bpl Ypositiv
    eor #$ff
	adc #1
    sec
Ypositiv:
    tay
    rol octant

    sec
    lda _log2_tab,x
    sbc _log2_tab,y
    bcc *+4
    eor #$ff
    tax

    lda octant
    rol
    and #$07
    tay

    lda atan_tab, x
    eor octant_adjust,y
    sta _res
.)
    rts


octant_adjust	.byt %00111111		;; x+,y+,|x|>|y|
		.byt %00000000		;; x+,y+,|x|<|y|
		.byt %11000000		;; x+,y-,|x|>|y|
		.byt %11111111		;; x+,y-,|x|<|y|
		.byt %01000000		;; x-,y+,|x|>|y|
		.byt %01111111		;; x-,y+,|x|<|y|
		.byt %10111111		;; x-,y-,|x|>|y|
		.byt %10000000		;; x-,y-,|x|<|y|


		;;;;;;;; atan(2^(x/32))*128/pi ;;;;;;;;

atan_tab	.byt $00,$00,$00,$00,$00,$00,$00,$00
		.byt $00,$00,$00,$00,$00,$00,$00,$00
		.byt $00,$00,$00,$00,$00,$00,$00,$00
		.byt $00,$00,$00,$00,$00,$00,$00,$00
		.byt $00,$00,$00,$00,$00,$00,$00,$00
		.byt $00,$00,$00,$00,$00,$00,$00,$00
		.byt $00,$00,$00,$00,$00,$00,$00,$00
		.byt $00,$00,$00,$00,$00,$00,$00,$00
		.byt $00,$00,$00,$00,$00,$00,$00,$00
		.byt $00,$00,$00,$00,$00,$00,$00,$00
		.byt $00,$00,$00,$00,$00,$01,$01,$01
		.byt $01,$01,$01,$01,$01,$01,$01,$01
		.byt $01,$01,$01,$01,$01,$01,$01,$01
		.byt $01,$01,$01,$01,$01,$01,$01,$01
		.byt $01,$01,$01,$01,$01,$02,$02,$02
		.byt $02,$02,$02,$02,$02,$02,$02,$02
		.byt $02,$02,$02,$02,$02,$02,$02,$02
		.byt $03,$03,$03,$03,$03,$03,$03,$03
		.byt $03,$03,$03,$03,$03,$04,$04,$04
		.byt $04,$04,$04,$04,$04,$04,$04,$04
		.byt $05,$05,$05,$05,$05,$05,$05,$05
		.byt $06,$06,$06,$06,$06,$06,$06,$06
		.byt $07,$07,$07,$07,$07,$07,$08,$08
		.byt $08,$08,$08,$08,$09,$09,$09,$09
		.byt $09,$0a,$0a,$0a,$0a,$0b,$0b,$0b
		.byt $0b,$0c,$0c,$0c,$0c,$0d,$0d,$0d
		.byt $0d,$0e,$0e,$0e,$0e,$0f,$0f,$0f
		.byt $10,$10,$10,$11,$11,$11,$12,$12
		.byt $12,$13,$13,$13,$14,$14,$15,$15
		.byt $15,$16,$16,$17,$17,$17,$18,$18
		.byt $19,$19,$19,$1a,$1a,$1b,$1b,$1c
		.byt $1c,$1c,$1d,$1d,$1e,$1e,$1f,$1f

#define USE_ASM_LOGTRIGO
#ifdef USE_ASM_LOGTRIGO
#define OPTIMIZE_SIZE
_tabLog2Sin
        .byt 192, 192, 194, 213, 226, 236, 245, 252, 2, 7, 12, 16, 20, 24, 27, 30
        .byt 33, 36, 38, 40, 43, 45, 47, 48, 50, 52, 53, 55, 56, 58, 59, 60
        .byt 61, 62, 63, 64, 65, 66, 67, 68, 69, 69, 70, 71, 71, 72, 73, 73
        .byt 74, 74, 75, 75, 75, 76, 76, 76, 76, 77, 77, 77, 77, 77, 77, 77
#ifndef OPTIMIZE_SIZE
        .byt 77, 77, 77, 77, 77, 77, 77, 77, 76, 76, 76, 76, 75, 75, 75, 74
        .byt 74, 73, 73, 72, 71, 71, 70, 69, 69, 68, 67, 66, 65, 64, 63, 62
        .byt 61, 60, 59, 58, 56, 55, 53, 52, 50, 48, 47, 45, 43, 40, 38, 36
        .byt 33, 30, 27, 24, 20, 16, 12, 7, 2, 252, 245, 236, 226, 213, 194, 192
        .byt 192, 192, 194, 213, 226, 236, 245, 252, 2, 7, 12, 16, 20, 24, 27, 30
        .byt 33, 36, 38, 40, 43, 45, 47, 48, 50, 52, 53, 55, 56, 58, 59, 60
        .byt 61, 62, 63, 64, 65, 66, 67, 68, 69, 69, 70, 71, 71, 72, 73, 73
        .byt 74, 74, 75, 75, 75, 76, 76, 76, 76, 77, 77, 77, 77, 77, 77, 77
        .byt 77, 77, 77, 77, 77, 77, 77, 77, 76, 76, 76, 76, 75, 75, 75, 74
        .byt 74, 73, 73, 72, 71, 71, 70, 69, 69, 68, 67, 66, 65, 64, 63, 62
        .byt 61, 60, 59, 58, 56, 55, 53, 52, 50, 48, 47, 45, 43, 40, 38, 36
        .byt 33, 30, 27, 24, 20, 16, 12, 7, 2, 252, 245, 236, 226, 213, 194, 192
#endif
_tabLog2Cos
        .byt 77, 77, 77, 77, 77, 77, 77, 77, 76, 76, 76, 76, 75, 75, 75, 74
        .byt 74, 73, 73, 72, 71, 71, 70, 69, 69, 68, 67, 66, 65, 64, 63, 62
        .byt 61, 60, 59, 58, 56, 55, 53, 52, 50, 48, 47, 45, 43, 40, 38, 36
        .byt 33, 30, 27, 24, 20, 16, 12, 7, 2, 252, 245, 236, 226, 213, 194, 192
        .byt 192, 192, 194, 213, 226, 236, 245, 252, 2, 7, 12, 16, 20, 24, 27, 30
        .byt 33, 36, 38, 40, 43, 45, 47, 48, 50, 52, 53, 55, 56, 58, 59, 60
        .byt 61, 62, 63, 64, 65, 66, 67, 68, 69, 69, 70, 71, 71, 72, 73, 73
        .byt 74, 74, 75, 75, 75, 76, 76, 76, 76, 77, 77, 77, 77, 77, 77, 77
        .byt 77, 77, 77, 77, 77, 77, 77, 77, 76, 76, 76, 76, 75, 75, 75, 74
        .byt 74, 73, 73, 72, 71, 71, 70, 69, 69, 68, 67, 66, 65, 64, 63, 62
        .byt 61, 60, 59, 58, 56, 55, 53, 52, 50, 48, 47, 45, 43, 40, 38, 36
        .byt 33, 30, 27, 24, 20, 16, 12, 7, 2, 252, 245, 236, 226, 213, 194, 192
        .byt 192, 192, 194, 213, 226, 236, 245, 252, 2, 7, 12, 16, 20, 24, 27, 30
        .byt 33, 36, 38, 40, 43, 45, 47, 48, 50, 52, 53, 55, 56, 58, 59, 60
        .byt 61, 62, 63, 64, 65, 66, 67, 68, 69, 69, 70, 71, 71, 72, 73, 73
        .byt 74, 74, 75, 75, 75, 76, 76, 76, 76, 77, 77, 77, 77, 77, 77, 77
_tab_1oversin
        .byt 255, 171, 139, 120, 107, 97, 89, 82, 75, 70, 65, 61, 57, 54, 50, 47
        .byt 44, 42, 39, 37, 35, 33, 31, 29, 27, 25, 24, 22, 21, 20, 18, 17
        .byt 16, 15, 14, 13, 12, 11, 10, 9, 9, 8, 7, 6, 6, 5, 5, 4
        .byt 4, 3, 3, 2, 2, 2, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0
#ifndef OPTIMIZE_SIZE
        .byt 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 2, 2, 2, 3, 3
        .byt 4, 4, 5, 5, 6, 6, 7, 8, 9, 9, 10, 11, 12, 13, 14, 15
        .byt 16, 17, 18, 20, 21, 22, 24, 25, 27, 29, 31, 33, 35, 37, 39, 42
        .byt 44, 47, 50, 54, 57, 61, 65, 70, 75, 82, 89, 97, 107, 120, 139, 171
        .byt 255, 171, 139, 120, 107, 97, 89, 82, 75, 70, 65, 61, 57, 54, 50, 47
        .byt 44, 42, 39, 37, 35, 33, 31, 29, 27, 25, 24, 22, 21, 20, 18, 17
        .byt 16, 15, 14, 13, 12, 11, 10, 9, 9, 8, 7, 6, 6, 5, 5, 4
        .byt 4, 3, 3, 2, 2, 2, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0
        .byt 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 2, 2, 2, 3, 3
        .byt 4, 4, 5, 5, 6, 6, 7, 8, 9, 9, 10, 11, 12, 13, 14, 15
        .byt 16, 17, 18, 20, 21, 22, 24, 25, 27, 29, 31, 33, 35, 37, 39, 42
        .byt 44, 47, 50, 54, 57, 61, 65, 70, 75, 82, 89, 97, 107, 120, 139, 171
#endif
_tab_1overcos
        .byt 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 2, 2, 2, 3, 3
        .byt 4, 4, 5, 5, 6, 6, 7, 8, 9, 9, 10, 11, 12, 13, 14, 15
        .byt 16, 17, 18, 20, 21, 22, 24, 25, 27, 29, 31, 33, 35, 37, 39, 42
        .byt 44, 47, 50, 54, 57, 61, 65, 70, 75, 82, 89, 97, 107, 120, 139, 171
        .byt 255, 171, 139, 120, 107, 97, 89, 82, 75, 70, 65, 61, 57, 54, 50, 47
        .byt 44, 42, 39, 37, 35, 33, 31, 29, 27, 25, 24, 22, 21, 20, 18, 17
        .byt 16, 15, 14, 13, 12, 11, 10, 9, 9, 8, 7, 6, 6, 5, 5, 4
        .byt 4, 3, 3, 2, 2, 2, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0
        .byt 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 2, 2, 2, 3, 3
        .byt 4, 4, 5, 5, 6, 6, 7, 8, 9, 9, 10, 11, 12, 13, 14, 15
        .byt 16, 17, 18, 20, 21, 22, 24, 25, 27, 29, 31, 33, 35, 37, 39, 42
        .byt 44, 47, 50, 54, 57, 61, 65, 70, 75, 82, 89, 97, 107, 120, 139, 171
        .byt 255, 171, 139, 120, 107, 97, 89, 82, 75, 70, 65, 61, 57, 54, 50, 47
        .byt 44, 42, 39, 37, 35, 33, 31, 29, 27, 25, 24, 22, 21, 20, 18, 17
        .byt 16, 15, 14, 13, 12, 11, 10, 9, 9, 8, 7, 6, 6, 5, 5, 4
        .byt 4, 3, 3, 2, 2, 2, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0
        
#endif //USE_ASM_LOGTRIGO        

_tab_exp
    .byt $01, $01, $01, $01, $01, $01, $01, $01, $01, $01, $01, $01, $01, $01, $01, $01
    .byt $01, $01, $01, $02, $02, $02, $02, $02, $02, $02, $02, $02, $02, $02, $02, $02
    .byt $02, $02, $02, $02, $02, $02, $02, $02, $02, $02, $02, $03, $03, $03, $03, $03
    .byt $03, $03, $03, $03, $03, $03, $03, $03, $03, $03, $04, $04, $04, $04, $04, $04
    .byt $04, $04, $04, $04, $04, $04, $05, $05, $05, $05, $05, $05, $05, $05, $05, $06
    .byt $06, $06, $06, $06, $06, $06, $06, $07, $07, $07, $07, $07, $07, $07, $08, $08
    .byt $08, $08, $08, $09, $09, $09, $09, $09, $0a, $0a, $0a, $0a, $0a, $0b, $0b, $0b
    .byt $0b, $0c, $0c, $0c, $0c, $0d, $0d, $0d, $0d, $0e, $0e, $0e, $0f, $0f, $0f, $10
    .byt $10, $10, $11, $11, $11, $12, $12, $13, $13, $13, $14, $14, $15, $15, $16, $16
    .byt $17, $17, $18, $18, $19, $19, $1a, $1a, $1b, $1b, $1c, $1d, $1d, $1e, $1f, $1f
    .byt $20, $21, $21, $22, $23, $24, $24, $25, $26, $27, $28, $29, $29, $2a, $2b, $2c
    .byt $2d, $2e, $2f, $30, $31, $32, $34, $35, $36, $37, $38, $39, $3b, $3c, $3d, $3f
    .byt $40, $41, $43, $44, $46, $47, $49, $4a, $4c, $4e, $4f, $51, $53, $55, $57, $59
    .byt $5b, $5c, $5f, $61, $63, $65, $67, $69, $6c, $6e, $70, $73, $75, $78, $7b, $7d
    .byt $80, $83, $86, $89, $8c, $8f, $92, $95, $98, $9c, $9f, $a2, $a6, $aa, $ad, $b1
    .byt $b5, $b9, $bd, $c1, $c5, $ca, $ce, $d3, $d7, $dc, $e1, $e6, $eb, $f0, $f5, $fb


_tab_exp_extended
    .byt 0, 6, 11, 17, 23, 29, 36, 42
    .byt 48, 55, 62, 69, 76, 83, 91, 98
    .byt 106, 114, 122, 130, 139, 147, 156, 165
    .byt 175, 184, 194, 203, 214, 224, 234, 245, 255

_tab_exp_extended2
    .byt 11, 23, 34, 46, 59, 71, 84, 97
    .byt 110, 124, 138, 152, 167, 181, 197, 212
    .byt 228, 244

_tab_exp_extended3
    .byt 17, 34, 51, 69, 87, 105, 124, 143, 163, 183, 204, 225, 246

_log2_tab
        .byt $00,$00,$20,$32,$40,$4a,$52,$59
        .byt $60,$65,$6a,$6e,$72,$76,$79,$7d
        .byt $80,$82,$85,$87,$8a,$8c,$8e,$90
        .byt $92,$94,$96,$98,$99,$9b,$9d,$9e
        .byt $a0,$a1,$a2,$a4,$a5,$a6,$a7,$a9
        .byt $aa,$ab,$ac,$ad,$ae,$af,$b0,$b1
        .byt $b2,$b3,$b4,$b5,$b6,$b7,$b8,$b9
        .byt $b9,$ba,$bb,$bc,$bd,$bd,$be,$bf
        .byt $c0,$c0,$c1,$c2,$c2,$c3,$c4,$c4
        .byt $c5,$c6,$c6,$c7,$c7,$c8,$c9,$c9
        .byt $ca,$ca,$cb,$cc,$cc,$cd,$cd,$ce
        .byt $ce,$cf,$cf,$d0,$d0,$d1,$d1,$d2
        .byt $d2,$d3,$d3,$d4,$d4,$d5,$d5,$d5
        .byt $d6,$d6,$d7,$d7,$d8,$d8,$d9,$d9
        .byt $d9,$da,$da,$db,$db,$db,$dc,$dc
        .byt $dd,$dd,$dd,$de,$de,$de,$df,$df
        .byt $df,$e0,$e0,$e1,$e1,$e1,$e2,$e2
        .byt $e2,$e3,$e3,$e3,$e4,$e4,$e4,$e5
        .byt $e5,$e5,$e6,$e6,$e6,$e7,$e7,$e7
        .byt $e7,$e8,$e8,$e8,$e9,$e9,$e9,$ea
        .byt $ea,$ea,$ea,$eb,$eb,$eb,$ec,$ec
        .byt $ec,$ec,$ed,$ed,$ed,$ed,$ee,$ee
        .byt $ee,$ee,$ef,$ef,$ef,$ef,$f0,$f0
        .byt $f0,$f1,$f1,$f1,$f1,$f1,$f2,$f2
        .byt $f2,$f2,$f3,$f3,$f3,$f3,$f4,$f4
        .byt $f4,$f4,$f5,$f5,$f5,$f5,$f5,$f6
        .byt $f6,$f6,$f6,$f7,$f7,$f7,$f7,$f7
        .byt $f8,$f8,$f8,$f8,$f9,$f9,$f9,$f9
        .byt $f9,$fa,$fa,$fa,$fa,$fa,$fb,$fb
        .byt $fb,$fb,$fb,$fc,$fc,$fc,$fc,$fc
        .byt $fd,$fd,$fd,$fd,$fd,$fd,$fe,$fe
        .byt $fe,$fe,$fe,$ff,$ff,$ff,$ff,$ff

; unsigned char glCamRotZ;
_glCamRotZ       .dsb 1

; unsigned char glCamPosX, glCamPosY, glCamPosZ ;
_glCamPosX       .dsb 1
_glCamPosY       .dsb 1
_glCamPosZ       .dsb 1


; signed char deltaX, deltaY, deltaZ;
_DeltaX .dsb 1
_DeltaY .dsb 1
_DeltaZ .dsb 1

; signed char theta, alpha ;
_theta .dsb 1
_alpha .dsb 1

; unsigned char log_distance;
_log_distance .dsb 1

; unsigned char logDistancePlanCam;
_logDistancePlanCam .dsb 1

; int tmpXScreen, tmpYScreen;
_tmpXScreen .dsb 2
_tmpYScreen .dsb 2


; signed char PtX;
; signed char PtY;
; signed char PtZ;
_PointX .dsb 1
_PointY .dsb 1
_PointZ .dsb 1


; signed char OriginX;
; signed char OriginY;
_OriginX .dsb 1
_OriginY .dsb 1
; _OriginZ .dsb 1

; signed char *AngleH;
_AngleH .dsb 1

; signed int *xScreen;
_xScreen .dsb 2
; signed int *yScreen;
_yScreen .dsb 2




; _tabAngle2Col_High
;         .byt 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
;         .byt 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255, 255, 255, 255
;         .byt 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 254
;         .byt 254, 254, 254, 254, 254, 254, 253, 253, 253, 252, 251, 251, 249, 247, 242, 229
;         .byt 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128
;         .byt 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128
;         .byt 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128
;         .byt 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128
;         .byt 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127
;         .byt 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127
;         .byt 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127
;         .byt 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127
;         .byt 127, 27, 14, 9, 7, 5, 4, 4, 3, 3, 3, 2, 2, 2, 2, 2
;         .byt 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
;         .byt 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
;         .byt 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
; _tabAngle2Col_Low
;         .byt 120, 116, 112, 107, 103, 99, 95, 90, 86, 82, 77, 73, 68, 63, 59, 54
;         .byt 49, 44, 39, 34, 28, 23, 17, 11, 5, 255, 249, 242, 235, 228, 221, 213
;         .byt 205, 196, 187, 177, 167, 156, 145, 133, 120, 105, 90, 73, 55, 36, 14, 245
;         .byt 218, 188, 153, 113, 67, 13, 204, 125, 26, 156, 245, 11, 172, 101, 216, 51
;         .byt 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
;         .byt 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
;         .byt 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
;         .byt 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
;         .byt 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255
;         .byt 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255
;         .byt 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255
;         .byt 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255
;         .byt 255, 189, 24, 139, 68, 229, 251, 84, 214, 115, 36, 227, 173, 127, 87, 52
;         .byt 22, 251, 226, 204, 185, 167, 150, 135, 120, 107, 95, 84, 73, 63, 53, 44
;         .byt 35, 27, 19, 12, 5, 254, 247, 241, 235, 229, 223, 217, 212, 206, 201, 196
;         .byt 191, 186, 181, 177, 172, 167, 163, 158, 154, 150, 145, 141, 137, 133, 128, 124

absDeltaX .dsb 1
absDeltaY .dsb 1

; unsigned int LogNumerator;
; unsigned int ExpResult;
_LogNumerator .dsb 2
_ExpResult .dsb 2

lexp:
.(
    lda #0
    ;;sta _ExpResult
    sta _ExpResult+1
    lda _LogNumerator+1
    beq LogNumeratorUnder256
    lda _LogNumerator
    cmp #$21
    bmi LogNumeratorUnder289
    cmp #$33
    bmi LogNumeratorUnder307
    cmp #$40
    bmi LogNumeratorUnder320
    lda #$FF
    sta _ExpResult
    lda #$7F
    sta _ExpResult+1
    jmp exponentiateRatio_done
LogNumeratorUnder320
    sec
    sbc #$33;
    tay
    lda _tab_exp_extended3, y
    clc
    adc #$f4
    sta _ExpResult
    lda #$02
    adc #0
    sta _ExpResult+1
    jmp exponentiateRatio_done
LogNumeratorUnder307
    sec
    sbc #$21
    tay
    lda _tab_exp_extended2, y
    sta _ExpResult
    lda #2
    sta _ExpResult+1
    jmp exponentiateRatio_done
LogNumeratorUnder289
    sec
    sbc #$00
    tay
    lda _tab_exp_extended, y
    sta _ExpResult
    lda #1
    sta _ExpResult+1
    jmp exponentiateRatio_done
LogNumeratorUnder256
    ldy _LogNumerator
    lda _tab_exp, y
    sta _ExpResult
exponentiateRatio_done
.)
    rts

; unsigned int LONGEXP(unsigned int x){
;     LogNumerator = x;
;     asm (
;     return (ExpResult);
; }


tmp_log .dsb 2

_lgdistance:
.(
    pha:txa:pha:tya:pha 


    ; DeltaX = PtX - glCamPosX ;
	sec
	lda _PointX
	sbc _OriginX
	sta _DeltaX
    sta _tx

    ; DeltaY = PtY - glCamPosY ;
	sec
	lda _PointY
	sbc _OriginY
	sta _DeltaY
    sta _ty

    ; theta = ATAN2 (DeltaY, DeltaX);
	jsr _atan2_8
	lda _res
	sta _theta

    lda _DeltaX
    bmi deltaX_negativ
    jmp absDeltaX_done
deltaX_negativ
    eor #$ff: sec: adc #$00
absDeltaX_done
    sta absDeltaX

    lda _DeltaY
    bmi deltaY_negativ
    jmp absDeltaY_done
deltaY_negativ
    eor #$ff: sec: adc #$00
absDeltaY_done
    sta absDeltaY

    lda absDeltaX
    cmp absDeltaY
    bcc absDeltaX_less_than_absDeltaY
    ; IF abs(DeltaX) > abs(DeltaY)
        ; log_distance = log2_tab[abs(DeltaX)] + tab_1overcos[(unsigned char)theta];
        ldy absDeltaX
        lda _log2_tab, y
        ldy _theta
        clc
        adc _tab_1overcos, y
        sta _log_distance

    jmp end_if_absDeltaX_less_than_absDeltaY
absDeltaX_less_than_absDeltaY    
    ; ELIF abs(DeltaX) < abs(DeltaY)
        ; log_distance = log2_tab[abs(DeltaY)] + tab_1oversin[(unsigned char)theta];
        ldy absDeltaY
        lda _log2_tab, y
        ldy _theta
        clc
        adc _tab_1oversin, y
        sta _log_distance
end_if_absDeltaX_less_than_absDeltaY


lgdistance_done
    pla:tay:pla:tax:pla
.)
    rts

_sproject:
.(
    pha:txa:pha:tya:pha 

    ; DeltaX = PtX - glCamPosX ;
	sec
	lda _PointX
	sbc _glCamPosX
	sta _DeltaX
    sta _tx

    ; DeltaY = PtY - glCamPosY ;
	sec
	lda _PointY
	sbc _glCamPosY
	sta _DeltaY
    sta _ty

    ; DeltaZ = PtZ - glCamPosZ ;
	sec
	lda _PointZ
	sbc _glCamPosZ
	sta _DeltaZ

    ; theta = ATAN2 (DeltaY, DeltaX);
	jsr _atan2_8
	lda _res
	sta _theta

    ; alpha = theta - glCamRotZ;
    sec
    sbc _glCamRotZ
    sta _alpha

    ;*AngleH = alpha;
    sta _AngleH

    ; xScreen = tabAngle2Col [alpha]
    lda _alpha
    tay 
    lda _tabAngle2Col_Low, Y
    sta _xScreen
    lda _tabAngle2Col_High, Y
    sta _xScreen + 1
   

    lda _DeltaX
    bmi deltaX_negativ
    jmp absDeltaX_done
deltaX_negativ
    eor #$ff: sec: adc #$00
absDeltaX_done
    sta absDeltaX

    lda _DeltaY
    bmi deltaY_negativ
    jmp absDeltaY_done
deltaY_negativ
    eor #$ff: sec: adc #$00
absDeltaY_done
    sta absDeltaY

    lda absDeltaX
    cmp absDeltaY
    bcc absDeltaX_less_than_absDeltaY
    ; IF abs(DeltaX) > abs(DeltaY)
        ; log_distance = log2_tab[abs(DeltaX)] + tab_1overcos[(unsigned char)theta];
        ldy absDeltaX
        lda _log2_tab, y
        ldy _theta
        clc
        adc _tab_1overcos, y
        sta _log_distance

    jmp end_if_absDeltaX_less_than_absDeltaY
absDeltaX_less_than_absDeltaY    
    ; ELIF abs(DeltaX) < abs(DeltaY)
        ; log_distance = log2_tab[abs(DeltaY)] + tab_1oversin[(unsigned char)theta];
        ldy absDeltaY
        lda _log2_tab, y
        ldy _theta
        clc
        adc _tab_1oversin, y
        sta _log_distance
end_if_absDeltaX_less_than_absDeltaY

    ; if (log_distance < tab_1overcos[(unsigned char)alpha]) {
    ldy _alpha
    lda _log_distance
    cmp _tab_1overcos, y
    bcs LogDistanceGreaterOrEquals1overCos
    ;     logDistancePlanCam = tab_1overcos[(unsigned char)alpha]  - log_distance ;
        ldy _alpha 
        lda _tab_1overcos, y
        sec 
        sbc _log_distance
        sta _logDistancePlanCam
    jmp endifLogDistance
LogDistanceGreaterOrEquals1overCos    
    ; } else {
    ;     logDistancePlanCam = log_distance - tab_1overcos[(unsigned char)alpha];
        lda _log_distance
        sec
        ldy _alpha
        sbc _tab_1overcos, y
        sta _logDistancePlanCam
    ; }
endifLogDistance

    ; log2_tab[abs(DeltaZ)] + log2_tab[FOCAL] - logDistancePlanCam
    lda #0
    sta tmp_log+1
    ldy #FOCAL
    lda _log2_tab, y
    sta tmp_log

    lda _DeltaZ
    .(:bpl skip: eor #$FF: clc: adc #1: skip:.)
    tay
    lda _log2_tab, y
    clc
    adc tmp_log
    sta tmp_log
    lda tmp_log + 1 ; TODO to optimize . can at least be replace by lda #0
    adc #0
    sta tmp_log + 1

    sec
    lda tmp_log
    sbc _logDistancePlanCam
    sta _LogNumerator
    lda tmp_log+1
    sbc #0 ; _LogNumerator+1
    sta _LogNumerator+1

    jsr lexp

    lda _DeltaZ
    bpl deltaZIsPositiv
    clc
    lda #<(SH/2)
    adc _ExpResult
    sta _yScreen
    lda #>(SH/2)
    adc _ExpResult + 1
    sta _yScreen+1

    jmp sproject_done
deltaZIsPositiv    
    sec 
    lda #<(SH/2)
    sbc _ExpResult
    sta _yScreen
    lda #>(SH/2)
    sbc _ExpResult + 1
    sta _yScreen+1
    
sproject_done
    pla:tay:pla:tax:pla
.)
    rts

