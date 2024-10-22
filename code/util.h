
#ifndef UTIL_H
#define UTIL_H

#define abs(x)          (((x)<0)?-(x):(x))
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#define pe(addr) ((unsigned char *)addr)[0]
#define pk(addr, val)                     \
    {                                     \
        ((unsigned char *)addr)[0] = val; \
    }
    
#endif 