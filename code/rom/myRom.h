#ifndef MYROM_H
#define MYROM_H

typedef void voidfct(void);
typedef void printsfct(unsigned char , unsigned char, char* );
typedef void printnfct(unsigned char , unsigned char, unsigned char );
typedef void inputtxtfct(unsigned char, unsigned char, unsigned char, char *);
typedef void strcallbackfct(char*);
typedef void asyncInputTextfct(unsigned char l, unsigned char c, unsigned char maxlen, strcallbackfct *callback);
typedef unsigned char inputkeyfct();
typedef unsigned char randfct();

typedef void musicfct(int ,int ,int ,int );
typedef void soundfct(int ,int ,int );
typedef void playfct(int ,int ,int ,int );

typedef int memorycpyfct(void *, void *, int );
typedef void *memorysetfct(void *, int , int );

void AdvancedPrint(unsigned char column, unsigned char line, char* message);
void DecimalPrint(unsigned char column, unsigned char line,unsigned char value);
void SwitchToText(void);
void SwitchToHires(void);
void inputText(unsigned char l, unsigned char c, unsigned char maxlen, char *target);
void asyncInputText(unsigned char l, unsigned char c, unsigned char maxlen, strcallbackfct *callback);
unsigned char getKey(void);
unsigned char getRand(void);

void sndMusic(int chanel,int octave,int key,int volume);
void sndSound(int chanel,int period,int volume);
void sndPlay(int soundchanels,int noisechanels,int envelop,int volume);
void sndZap(void);
void sndOups(void);
void sndHKeyClick(void);
void sndLKeyClick(void);
void sndTounor(void);
void sndToucon(void);
void sndPing(void);
void sndShoot(void);
void sndExplode(void);

int memorycpy(void *dst, void *src, int n);
void *memoryset(void *buffer, int c, int count);

// void (*ptrRomFct[]) (void) = {
//     (voidfct*)AdvancedPrint,    // 0
//     (voidfct*)DecimalPrint,     // 1
//     (voidfct*)SwitchToText,     // 2
//     (voidfct*)SwitchToHires,    // 3
//     (voidfct*)inputText,        // 4
//     (voidfct*)getKey,           // 5
//     (voidfct*)getRand,          // 6
//     (voidfct*)sndMusic,         // 7
//     (voidfct*)sndSound,         // 8
//     (voidfct*)sndPlay,          // 9
//     (voidfct*)sndZap,           // 10
//     (voidfct*)sndPing,          // 11
//     (voidfct*)sndShoot,         // 12
//     (voidfct*)sndExplode,       // 13
//     (voidfct*)sndHKeyClick,     // 14

//     };
extern void (*ptrRomFct[]) (void);
void initRomFct(void);

#define PRINTS(c,l,txt) ((printsfct*)ptrRomFct[0])((c),(l),(txt))
#define PRINTN(c,l,n) ((printnfct*)ptrRomFct[1])((c),(l),(n))
#define TEXTMODE() (ptrRomFct[2])()
#define HIRESMODE() (ptrRomFct[3])()
#define INPUTS(l,c,ml,dest) ((inputtxtfct*)ptrRomFct[4])((l),(c),(ml),(dest))
#define GETKEY() ((inputkeyfct*)ptrRomFct[5])()
#define GETRAND() ((randfct*)ptrRomFct[6])()
#define MUSIC(chanel,octave,key,volume) ((musicfct*)ptrRomFct[7])((chanel), (octave), (key), (volume))
#define SOUND(chanel,period,volume) ((soundfct*)ptrRomFct[8])((chanel), (period),(volume))
#define PLAY(soundchanels,noisechanels,envelop,volume) ((playfct*)ptrRomFct[9])((soundchanels),(noisechanels),(envelop),(volume))
#define ZAP()           (ptrRomFct[10])()
#define PING()          (ptrRomFct[11])()
#define SHOOT()         (ptrRomFct[12])()
#define EXPLODE()       (ptrRomFct[13])()
#define HKEYCLICK()     (ptrRomFct[14])()
#define MEMCPY(dst,src,n)        ((memorycpyfct*)ptrRomFct[15])((dst),(src),(n))
#define MEMSET(buf,c,n)        ((memorysetfct*)ptrRomFct[16])((buf),(c),(n))
#define ASYNCINPUTS(l,c,ml,clbck) ((asyncInputTextfct*)ptrRomFct[17])((l),(c),(ml),(clbck))
#endif MYROM_H
