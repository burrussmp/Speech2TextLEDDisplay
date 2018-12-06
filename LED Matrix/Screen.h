// Author: Matthew P. Burruss
// Date: 9/24/2018
// Brief: The screen class defines operations and
// structs to control Adafruit's 32x16 RGB screen.
// Note: This class does not directly control the GPIO
// of the BBB, but rather provides functionality to a Screen struct
// that can be used to control the behavior of the LED screen.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include "Letter_Buffer.h"

// The screen struct.
// The screenBuffer is a virtually extended version of the screen, 
// allowing letters to be queued to the buffer before displaying on
// the screen.
// The screen is the virtual version of the 32x16 RGB LED screen.
// The color represents the color of the text
// The bufferOfLetters is the buffer of letters about to be displayed on
// the screen in a scrolling motion from right to left
// The advanceCounter is the number of times the screen has been advanced one
// pixel from right to left.
// The enqueuMutex protects the screen which protects multiple threads from
// adding letters to the buffer in screenBuffer
struct screen {
    uint8_t screenBuffer[38][16];
    uint8_t screen[32][16];
    uint8_t color;
    struct buffer* bufferOfLetters;
    uint8_t advanceCounter;
    pthread_mutex_t enqueueMutex;
};

// This function will display to stdout the screenBuffer
void printScreenBuffer(struct screen * s);

// Helper function to make string lowercase
// Must declare string Y as 
// char Y[] = "XXXXX";
void makeUpperCase(char* myString);

// This function will display to stdout the screen
void printScreen(struct screen * s);

// This function will set all of the screen pixels to nothing (0) 
void resetScreen(struct screen *s);

// The addPhrase function takes in a string and queues up
// the letters to be added to the screen. The addPhrase
// function also looks for key words in the phrase to control the
// color of the text. See the function implementation to see what 
// words are supported
void addPhrase(struct screen * s, char* phrase);

// Sets the color component of the struct and ensures that it
// is a valid color. If it is not a supported color, the text is set
// to RED by default.
void changeColor(struct screen *s,uint8_t ncolor);

// Sets the screen member of the screen struct to the values in 
// the screenBuffer so tht the relevant 32x16 bits are are the same
// for both buffers.
void updateScreen(struct screen * s);

// Enqueues a new letter to the screen buffer's buffer of letters
void addLetter(struct screen *s, char newLetter);

// placeLetter
// col and row specify location of upperleft corner of the letter
// Note(0,0) is in the top left corner of the matrix
// Placeletter will overwrite the buffer
void placeLetter(struct letter* l, int col, int row, struct screen * s);

// pre condition: The word will fit given # of characters and position
// Similar to placeLetter but rather places a row across the screen struct.
void placeWord(char* word,int col,int row,struct screen *s);

// Initially used to test the letters by filling the buffer
// with all letters A through Z.
void fillBufferTest(struct buffer * mybuf);

void freeScreen(struct screen * myscreen);
struct screen * screenInit();

// pre condition: The word will fit given # of characters and position
// Similar to placeLetter but rather places a row across the screen struct.
void placeWord(char* word,int col,int row,struct screen *s);

// advances the screen buffer by 2 pixels from the right to the left
// if the queue is empty, send in a ' ' as a filler
// if the screenBuffer buffer space is empty, then dequeue
// a new letter from the buffer of letters.
// At the end, update the screen to contain the relevant values
// of screen buffer.
void advance(struct screen * s);
void clearRegionOfScreen(struct screen *s, int coll,int colh, int rowl,int rowh);



// Helper function to make string lowercase
// Must declare string Y as 
// char Y[] = "XXXXX";
void makeUpperCase(char* myString);
