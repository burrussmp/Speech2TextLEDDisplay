/*
    @author: Matthew Burruss
    @date: 11/28/2018
    @description: The letter class which defines the pixelated values and encapsulates
    the creation of the letters. Supports a-z and space.
*/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>


// the letter struct
// A LETTERHEIGHTxLETTERWIDTH 2D matrix
// of unsigned integers to represent a pixelated
// character.
struct letter
{
    uint8_t **pixelMatrix;
    uint8_t LETTERHEIGHT;
    uint8_t LETTERWIDTH;
};

// prints the pixelMatrix member of the letter
// struct
void printLetter(struct letter *l);

// Creates a letter based on the character input l
// return the letter struct
// Supports A-Z and a few selected characters
struct letter* createLetter(char l);

// cleans the dynamic memory used to allocate the letter
void cleanLetter(struct letter *l);

// helper function for createLetter that
// initializes the pixelMatrix to contain all 0s
void letter_init(struct letter* l,int height, int width);
