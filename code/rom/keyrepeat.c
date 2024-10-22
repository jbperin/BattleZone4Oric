

#define NB_MAX_KEYPRESSED 4
static unsigned char keydelay   = 5;  // 32; // 
static unsigned char keyrepeat  = 1;  // 4; // 

unsigned char keyvallist[NB_MAX_KEYPRESSED+1];
unsigned char keycptlist[NB_MAX_KEYPRESSED+1];
unsigned char keylistidx    = 0;
unsigned char iW_keylist    = 0;
unsigned char nbE_keylist   = 0;

#ifdef __GNUC__
void onKey(unsigned char c){
    printf (" ==> onKey %d\n",c);

}
#endif // __GNUC__
// onPeriod
    // Pour chaque touche appuyée
        // décrémenter la valeur de son compteur
        // si compteur à 0
            // compteur = keyrepeat
            // appel onKey


// onKeyReleased
    // delKeyInList

// onKeyPressed
    // Si la touche n'était pas déjà appuyée
        // idxKeyinList = addKeyInList()
        // compteur[idxKeyInList] = keydelay

// addKeyInList

void pressKey(unsigned char c){
    keyvallist[iW_keylist]  = c;
    keycptlist[iW_keylist]  = keydelay;
    iW_keylist              = (iW_keylist + 1)%NB_MAX_KEYPRESSED;
    if (nbE_keylist < NB_MAX_KEYPRESSED) {
        nbE_keylist             += 1;
    }
}


void releaseKey(unsigned char c){
#ifdef __GNUC__    
    printf (" releaseKey %d\n", c);
#endif // __GNUC__    
    keylistidx = 0;
    while ((keylistidx < nbE_keylist) && (keyvallist[keylistidx] != c)){
        keylistidx++;
    }
    if (keylistidx != nbE_keylist) {
        do {
            keyvallist[keylistidx]  = keyvallist[keylistidx+1];
            keycptlist[keylistidx]  = keycptlist[keylistidx+1];
            keylistidx ++;
        } while ((keylistidx != nbE_keylist));
        nbE_keylist -= 1;
        if (iW_keylist == 0) {
            iW_keylist=NB_MAX_KEYPRESSED-1;
        }else{
            iW_keylist-=1;
        }
    }
}
void scanKey(){
    for (keylistidx=0; keylistidx< nbE_keylist; keylistidx++){
        keycptlist[keylistidx]  -=  1;
        if (keycptlist[keylistidx] == 0){
            keycptlist[keylistidx] = keyrepeat;
            onKey(keyvallist[keylistidx]);
        }
    }
}
#ifdef __GNUC__
void show(){
    printf (" ---\n %d %d %d %d\n",keyvallist[0],keyvallist[1],keyvallist[2],keyvallist[3]);
    printf (" %d %d %d %d\n ---\n",keycptlist[0],keycptlist[1],keycptlist[2],keycptlist[3]);
}
void main (){
    int nb;
    show();
    pressKey('a');show();
    for (nb=16; nb>0; nb--) scanKey();
    show();
    for (nb=16; nb>0; nb--) scanKey();
    show();
    for (nb=16; nb>0; nb--) scanKey();
    pressKey('b');show();
    for (nb=16; nb>0; nb--) scanKey();
    show();
    for (nb=16; nb>0; nb--) scanKey();
    show();
    releaseKey('a');show();
    for (nb=16; nb>0; nb--) scanKey();
    show();
    for (nb=16; nb>0; nb--) scanKey();
    show();
    pressKey('c');show();

}

#endif // __GNUC__
