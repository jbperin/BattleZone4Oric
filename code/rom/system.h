#ifndef SYSTEM_H
#define SYSTEM_H
#define USE_OSME
extern unsigned char 	kernel_cs;
extern unsigned char 	kernel_s;
#ifdef USE_OSME
extern unsigned char 	kernel_fraction;
extern unsigned char 	kernel_beat;
extern unsigned char getTempo();
extern void setTempo(unsigned char tempo);
#endif // USE_OSME

extern void onKeyPressed(unsigned char c);
extern void onKeyReleased(unsigned char c);
extern void lsys(void);
#endif // SYSTEM_H
