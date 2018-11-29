#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "ex_buff.h"
/* LED Screen Values */

struct screen {
    uint8_t screenBuffer[38][16];
    uint8_t screen[32][16];
    uint8_t color;
    struct buffer* bufferOfLetters;
    uint8_t advanceCounter;
    pthread_mutex_t enqueueMutex;
};
void printScreenBuffer(struct screen * s);
void printScreen(struct screen * s);
void changeColor(struct screen *s,int ncolor);
void updateScreen(struct screen * s);
void addLetter(struct screen *s, char newLetter);
void addPhrase(struct screen * s, char* phrase);
void placeLetter(struct letter* l, int col, int row,struct screen * s);
void advance(struct screen * s);
void fillBufferTest(struct buffer * mybuf);
struct screen * screenInit();
void freeScreen(struct screen * myscreen);