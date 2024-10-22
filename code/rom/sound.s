;; #include "labels.h"


#define VIA_PCR $30C
#define VIA_IORA2 $30F
; parametre A = register number of 8912
; parametre X = donnée à transférer
WriteToAY:
.(
    PHP              
    SEI              
    STA VIA_IORA2    
    TAY              
    TXA              
    CPY #$07         
    BNE WriteToAY_F59D        
    ORA #$40         
WriteToAY_F59D:
    PHA              
    LDA VIA_PCR      
    ORA #$EE         
    STA VIA_PCR      
    AND #$11         
    ORA #$CC         
    STA VIA_PCR      
    TAX              
    PLA              
    STA VIA_IORA2    
    TXA              
    ORA #$EC         
    STA VIA_PCR      
    AND #$11         
    ORA #$CC         
    STA VIA_PCR      
    plp
.)              
    rts              


BlockToAY:
.(
	PHP 				;This routine takes X and Y
	SEI 				;as the low and high halves of
	STX $14 			;the start address of a table
	STY $15 			;to send data to the sound
	LDY #$00 			;chip from.
BlockToAY_FA8E:
	LDA ($14),Y 		; 14 bytes are sent to the 8912
	TAX 				; starting with register 0 and
	TYA 				; working up in order until
	PHA 				; register D. The data from
	JSR WriteToAY 		; the table is used starting
	PLA 				; from the low address.
	TAY

	INY 				; The I/O port is not written
	CPY #$0E 			; to.
	BNE BlockToAY_FA8E
	PLP
.)
RTS

_sndOups:
.(
	LDX #<(OUPS_DATA)	; LL de l'adresse des 14 paramètres
    LDY #>(OUPS_DATA)	; HH de l'adresse des 14 paramètres
    JSR BlockToAY		
; Début de la temporisation
	SEI		
YTOURS:
	LDY #$60		; Temporisation boucle externe (96 tours)
	LDX #$00		; Temporisation boucle interne (256 tours)
BCOUL1:
	DEX
	BNE BCOUL1		; Délai boucle interne de 1,28 ms
    DEY
    BNE BCOUL1		; Délai total de 0,12s (boucles X et Y)
    CLI
; Fin de la temporisation		
    LDA #$07		; Registre 7 du PSG : contrôle des canaux
    LDX #$3F		; 0011 1111 tous inactivés
    JSR WriteToAY
.)
    RTS

_sndZap:
ZAP:
.(
	LDX #<(ZAP_DATA_FB06) ; #$06 			ZAP
	LDY #>(ZAP_DATA_FB06); #$FB 			; Send sound data to 8912 as
	JSR BlockToAY		; in SHOOT etc.
	LDA #$00
	TAX 				; This section writes to the
ZAP_FAEB:
    TXA 			    ; 	tone channel A at regular
	PHA 				; intervals with increasing
	LDA #$00 			; tone periods. Thus
	JSR WriteToAY 		; 	successively lower frequencies
	LDX #$00 			; are produced. The delay loop
ZAP_FAF4: 
    DEX 			    ; 	takes about 1.25mS to
	BNE ZAP_FAF4 		; 	execute.
	PLA
	TAX
	INX
	CPX #$70 			; The main loop is executed 112
	BNE ZAP_FAEB 		; times in total.
	LDA #$08 			; Zero channel A amplitude.
	LDX #$00
	JSR WriteToAY
.)	
RTS
;                       R0   R1   R2   R3   R4   R5   R6   R7   R10  R11  R12  R13  R14  R15   
OUPS_DATA	.byt        $46, $00, $00, $00, $00, $00, $00, $3E, $0F, $00, $00, $BD, $28, $02

ZAP_DATA_FB06 .byt      $00, $00, $00, $00, $00, $00, $00, $3E, $0F, $00, $00, $00, $00, $00
EXPLODE_DATA_FAD3 .byt  $00, $00, $00, $00, $00, $00, $1F, $07, $10, $10, $10, $00, $18, $00

PING_DATA_FAA7 .byt     $18, $00, $00, $00, $00, $00, $00, $3E, $10, $00, $00, $00, $0F, $00
SHOOT_DATA_FABD .byt    $00, $00, $00, $00, $00, $00, $0F, $07, $10, $10, $10, $00, $08, $00

TOUNOR_DATA	.byt	    $1F, $00, $00, $00, $00, $00, $00, $3E, $10, $00, $00, $1F, $00, $00
TOUCON_DATA	.byt	    $2F, $00, $00, $00, $00, $00, $00, $3E, $10, $00, $00, $1F, $00, $00

HKEY_CLICK_DATA	.byt	$1F, $00, $00, $00, $00, $00, $00, $3E, $10, $00, $00, $1F, $00, $00
LKEY_CLICK_DATA	.byt	$2F, $00, $00, $00, $00, $00, $00, $3E, $10, $00, $00, $1F, $00, $00


_sndHKeyClick:
.(
    LDX #<(HKEY_CLICK_DATA)           ; HKEY_CLICK
    LDY #>(HKEY_CLICK_DATA)           ; Sets X and Y to point to the
    JSR BlockToAY                   ; data below to generate the
.)
    RTS         ; sound.

_sndLKeyClick:
.(
    LDX #<(LKEY_CLICK_DATA)           ; LKEY_CLICK
    LDY #>(LKEY_CLICK_DATA)           ; Sets X and Y to point to the
    JSR BlockToAY                   ; data below to generate the
.)
    RTS         ; sound.

_sndTounor:
.(
    LDX #<(TOUNOR_DATA)           ; TOUNOR
    LDY #>(TOUNOR_DATA)           ; Sets X and Y to point to the
    JSR BlockToAY                   ; data below to generate the
.)
    RTS         ; sound.

_sndToucon:
.(
    LDX #<(TOUCON_DATA)           ; TOUCON
    LDY #>(TOUCON_DATA)           ; Sets X and Y to point to the
    JSR BlockToAY                   ; data below to generate the
.)
    RTS         ; sound.

_sndPing:
.(
    LDX #<(PING_DATA_FAA7)           ; PING
    LDY #>(PING_DATA_FAA7)           ; Sets X and Y to point to the
    JSR BlockToAY                   ; data below to generate the
.)
    RTS         ; sound.

_sndShoot:
.(
    LDX #<(SHOOT_DATA_FABD) ;SHOOT
    LDY #>(SHOOT_DATA_FABD) ;Sets X and Y to point to the
    JSR BlockToAY ; data below to generate the
.)
    RTS ;sound.

_sndExplode:
.(
    LDX #<(EXPLODE_DATA_FAD3) ;EXPLODE
    LDY #>(EXPLODE_DATA_FAD3) ;Sets X and Y to point to the
    JSR BlockToAY     ; data below to generate the
.)
    RTS ; sound.




; MUSIC:  $FC18 -> $FC5D
; PARAMS+1 canal (1 à 3)
; PARAMS+3 octave (0 à 7)
; PARAMS+5 note (0 à 12)
; PARAMS+7 volume (0 à 15)

_canal .dsb 1  // PARAMS + 1
_music_octave .dsb 1 // PARAMS + 3
_music_note .dsb 1   // PARAMS + 5
_music_volume .dsb 1 // PARAMS + 7

// sndMusic(int chanel,int octave,int key,int volume)
_sndMusic:
.(
    ldy #0:	lda (sp),y: sta _canal
	ldy #2:	lda (sp),y: sta _music_octave
    ldy #4:	lda (sp),y: sta _music_note
    ldy #6:	lda (sp),y: sta _music_volume
	jsr MUSIC

.)
    rts
MUSIC:
.(
    LDX #$E1         
    LDA #$04         
    ; JSR unknown_F2E4        

    STA $0204        
    LDA _canal // $0200,X         // $02E1
    BEQ unknown_F2F6       
    CMP $0204        
    BCC unknown_F2F7        
unknown_F2F6:
    SEC
unknown_F2F7:



    BCS MUSIC_FC5A        
    LDX #$E3         
    LDA #$08         
    ; JSR unknown_F2F8        


    STA $0204        
    LDA _music_octave // $0200,X    // $02E3  
    CMP $0204        
    BCC unknown2_F309        
unknown2_F308: 
    SEC              
unknown2_F309: 




    BCS MUSIC_FC5A        
    LDX #$E5         
    LDA #$0D         
    ;JSR unknown_F2E4     

    STA $0204        
    LDA _music_note // $0200,X    // $02E5
    BEQ unknown_F2F6_bis       
    CMP $0204        
    BCC unknown_F2F7_bis        
unknown_F2F6_bis:
    SEC
unknown_F2F7_bis:

    BCS MUSIC_FC5A        
    LDY _music_octave // $02E3        
    LDX _music_note // $02E5        
    LDA MusicData,X  
    STA snd_period+1        
    LDA MUSIC_FC6B,X      
    STA snd_period        
    LDA _music_volume        
    STA snd_volume        
MUSIC_FC4B:      
    DEY              
    BMI MUSIC_FC57        
    LSR snd_period+1        
    ROR snd_period        
    JMP MUSIC_FC4B        
MUSIC_FC57:  
    JMP SOUND        
MUSIC_FC5A:  ;INC $02E0  
.)      
    RTS 

MusicData:  .byt $00, $07, $07, $06, $06, $05, $05, $05, $04, $04, $04, $04, $03
MUSIC_FC6B: .byt $00, $77, $0B, $A6, $47, $EC, $97, $47, $FB, $B3, $70, $30, $F4 




; SOUND: $FB40
; PARAMS+1 canal (de 1 à 6)
; PARAMS+3 période (1 à 65535) (bruit)
; PARAMS+5 volume (1 à 15)


snd_period .dsb 2   // $02E3
snd_volume .dsb 1   // $02E5

 // void sndSound(int chanel,int period,int volume)
_sndSound:
.(
    ldy #0:	lda (sp),y: sta _canal
	ldy #2:	lda (sp),y: sta snd_period : iny : lda (sp),y: sta snd_period+1
    ldy #6:	lda (sp),y: sta snd_volume
	jsr MUSIC

.)
    rts
SOUND: // FB40
.(
    LDA _canal // $02E1        
    CMP #$01         
    BNE SOUND_FB69        
    LDA #$00         
    LDX snd_period // $02E3        
    JSR WriteToAY    
    LDA #$01         
    LDX snd_period+1    // $02E4     
    JSR WriteToAY    
SOUND_FB57:  
    LDA snd_volume // $02E5        
    AND #$0F         
    BNE SOUND_FB62        
    LDX #$10         
    BNE SOUND_FB63        
SOUND_FB62:
    TAX              
SOUND_FB63:
    LDA #$08         
    JSR WriteToAY    
    RTS              
SOUND_FB69:
    CMP #$02         
    BNE SOUND_FB8F        
    LDA #$02         
    LDX snd_period // $02E3        
    JSR WriteToAY    
    LDA #$03         
    LDX snd_period+1    // $02E4        
    JSR WriteToAY    
SOUND_FB7D: 
    LDA snd_volume // $02E5        
    AND #$0F         
    BNE SOUND_FB88        
    LDX #$10         
    BNE SOUND_FB89        
SOUND_FB88: 
    TAX              
SOUND_FB89: 
    LDA #$09         
    JSR WriteToAY    
    RTS              
SOUND_FB8F: 
    CMP #$03         
    BNE SOUND_FBB5        
    LDA #$04         
    LDX snd_period // $02E3        
    JSR WriteToAY    
    LDA #$05         
    LDX snd_period+1    // $02E4        
    JSR WriteToAY    
SOUND_FBA3: 
    LDA snd_volume // $02E5        
    AND #$0F         
    BNE SOUND_FBAE        
    LDX #$10         
    BNE SOUND_FBAF        
SOUND_FBAE: 
    TAX              
SOUND_FBAF:
    LDA #$0A         
    JSR WriteToAY    
    RTS              
SOUND_FBB5: LDA #$06         
    LDX snd_period // $02E3        
    JSR WriteToAY    
    LDA _canal // $02E1        
    CMP #$04         
    BEQ SOUND_FB57        
    CMP #$05         
    BEQ SOUND_FB7D        
    CMP #$06         
    BEQ SOUND_FBA3        
    ;INC $02E0        
.)
    RTS              

; PLAY: $FBD0
; PARAMS+1 canaux actifs (0 à 7) (son)
; PARAMS+3 canaux actifs (0 à 7) (bruit)
; PARAMS+5 enveloppe (1 à 7) (bruit)
; PARAMS+7 durée enveloppe (0 à 65535) (bruit)

sound_channels      .dsb 1 // $02E1 
noise_channels      .dsb 1 // $02E3 
enveloppe           .dsb 1 // $02E5
enveloppe_duration  .dsb 2 // $02E7

// void sndPlay(int soundchanels,int noisechanels,int envelop,int volume)
_sndPlay:
.(
    ldy #0:	lda (sp),y: sta sound_channels
	ldy #2:	lda (sp),y: sta noise_channels
    ldy #4:	lda (sp),y: sta enveloppe
    ldy #6:	lda (sp),y: sta enveloppe_duration: iny : lda (sp),y: sta enveloppe_duration+1
	jsr PLAY

.)
    rts

PLAY:
.(
    LDA noise_channels // $02E3        
    ASL              
    ASL              
    ASL              
    ORA sound_channels // $02E1        
    EOR #$3F         
    TAX              
    LDA #$07         
    JSR WriteToAY    
    CLC              
    LDA enveloppe_duration        
    ASL              
    STA enveloppe_duration        
    LDA enveloppe_duration+1        
    ROL              
    STA enveloppe_duration+1        
    LDA #$0B         
    LDX enveloppe_duration        
    JSR WriteToAY    
    LDA #$0C         
    LDX enveloppe_duration+1        
    JSR WriteToAY    
    LDA enveloppe //$02E5        
    AND #$07         
    TAY              
    LDA PLAY_FC10,Y      
    TAX              
    LDA #$0D         
    JSR WriteToAY    
.)
    RTS

;   FC10  00 00     BRK #$00         
;   FC12  04 08     DOP $08          
;   FC14  0A        ASL              
;   FC15  0B 0C     ANC #$0C         
;   FC17  0D A2 E1  ORA $E1A2        

PLAY_FC10 .byt $00, $00, $04, $08, $0A, $0B, $0C, $0D, $A2, $E1
