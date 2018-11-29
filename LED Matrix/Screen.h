#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include "ex_buff.h"


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
void changeColor(struct screen *s,uint8_t ncolor);
void updateScreen(struct screen * s);
void addLetter(struct screen *s, char newLetter);
void addPhrase(struct screen * s, char* phrase);
void placeLetter(struct letter* l, int col, int row,struct screen * s);
void placeWord(char* word,int col,int row,struct screen *s);
void advance(struct screen * s);
void fillBufferTest(struct buffer * mybuf);
struct screen * screenInit();
void freeScreen(struct screen * myscreen);
void resetScreen(struct screen *s);
void clearRegionOfScreen(struct screen *s, int coll,int colh, int rowl,int rowh);

// Helper function to make string lowercase
// Must declare string Y as 
// char Y[] = "XXXXX";
void makeUpperCase(char* myString);
