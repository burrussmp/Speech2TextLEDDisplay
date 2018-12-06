/*
    @author: Matthew Burruss
    @date: 11/28/2018
    @description: The letter class which defines the pixelated values and encapsulates
    the creation of the letters. Supports a-z and space.
*/

#include "Letter.h"

// helper function for createLetter that
// initializes the pixelMatrix to contain all 0s
void letter_init(struct letter* l,int height,int width)
{
    l->LETTERHEIGHT = height;
    l->LETTERWIDTH = width;
    l->pixelMatrix=(uint8_t **) malloc(l->LETTERHEIGHT*sizeof(uint8_t *));
    for(uint8_t i=0; i<l->LETTERHEIGHT;i++)
        l->pixelMatrix[i]=(uint8_t *) malloc(l->LETTERWIDTH*sizeof(uint8_t));
    for (uint8_t i = 0; i<l->LETTERHEIGHT;++i)
    {
        for (uint8_t j = 0; j < l->LETTERWIDTH; ++j)
        {
            l->pixelMatrix[i][j] = 0;
        }
    }
}


// prints the pixelMatrix member of the letter
// struct
void printLetter(struct letter *l)
{
    for (uint8_t i = 0; i < l->LETTERHEIGHT;++i)
    {
        for (uint8_t j = 0; j < l->LETTERWIDTH;++j)
        {
            printf("%d",l->pixelMatrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Creates a letter based on the character input l
// return the letter struct
// Supports A-Z and a few selected characters
struct letter* createLetter(char l)
{
  struct letter* newLetter = malloc(sizeof(struct letter)); 
  switch(l)
  {
    case 'a':
    case 'A':
        letter_init(newLetter,6,6);
        newLetter->pixelMatrix[1][2] = 1;
        newLetter->pixelMatrix[1][3] = 1;
        newLetter->pixelMatrix[2][1] = 1;
        newLetter->pixelMatrix[2][4] = 1;
        newLetter->pixelMatrix[3][1] = 1;
        newLetter->pixelMatrix[3][4] = 1;
        newLetter->pixelMatrix[4][1] = 1;
        newLetter->pixelMatrix[4][2] = 1;
        newLetter->pixelMatrix[4][3] = 1;
        newLetter->pixelMatrix[4][4] = 1;
        newLetter->pixelMatrix[5][1] = 1;
        newLetter->pixelMatrix[5][4] = 1;
        break;
    case 'b':
    case 'B':
        letter_init(newLetter,6,6);
        newLetter->pixelMatrix[1][1] = 1;
        newLetter->pixelMatrix[1][2] = 1;
        newLetter->pixelMatrix[1][3] = 1;
        newLetter->pixelMatrix[2][1] = 1;
        newLetter->pixelMatrix[2][4] = 1;
        newLetter->pixelMatrix[3][1] = 1;
        newLetter->pixelMatrix[3][2] = 1;
        newLetter->pixelMatrix[3][3] = 1;
        newLetter->pixelMatrix[4][1] = 1;
        newLetter->pixelMatrix[4][4] = 1;
        newLetter->pixelMatrix[5][1] = 1;
        newLetter->pixelMatrix[5][2] = 1;
        newLetter->pixelMatrix[5][3] = 1;
        break;
    case 'c':
        letter_init(newLetter,5,4);
        newLetter->pixelMatrix[1][1] = 7;
        newLetter->pixelMatrix[1][2] = 7;
        newLetter->pixelMatrix[2][0] = 7;
        newLetter->pixelMatrix[3][0] = 7;
        newLetter->pixelMatrix[4][1] = 7;
        newLetter->pixelMatrix[4][2] = 7;
        break;
    case 'C':
        letter_init(newLetter,6,6);
        newLetter->pixelMatrix[1][2] = 1;
        newLetter->pixelMatrix[1][3] = 1;
        newLetter->pixelMatrix[2][1] = 1;
        newLetter->pixelMatrix[2][4] = 1;
        newLetter->pixelMatrix[3][1] = 1;
        newLetter->pixelMatrix[4][1] = 1;
        newLetter->pixelMatrix[4][4] = 1;
        newLetter->pixelMatrix[5][2] = 1;
        newLetter->pixelMatrix[5][3] = 1;
        break;
    case 'd':
    case 'D':
        letter_init(newLetter,6,6);
        newLetter->pixelMatrix[1][1] = 1;
        newLetter->pixelMatrix[1][2] = 1;
        newLetter->pixelMatrix[1][3] = 1;
        newLetter->pixelMatrix[2][1] = 1;
        newLetter->pixelMatrix[2][4] = 1;
        newLetter->pixelMatrix[3][1] = 1;
        newLetter->pixelMatrix[3][4] = 1;
        newLetter->pixelMatrix[4][1] = 1;
        newLetter->pixelMatrix[4][4] = 1;
        newLetter->pixelMatrix[5][1] = 1;
        newLetter->pixelMatrix[5][2] = 1;
        newLetter->pixelMatrix[5][3] = 1;
        break;
    case 'e':
        letter_init(newLetter,5,4);
        newLetter->pixelMatrix[1][0] = 7;
        newLetter->pixelMatrix[1][1] = 7;
        newLetter->pixelMatrix[1][2] = 7;
        newLetter->pixelMatrix[2][0] = 7;
        newLetter->pixelMatrix[2][1] = 7;
        newLetter->pixelMatrix[2][2] = 7;
        newLetter->pixelMatrix[3][0] = 7;
        newLetter->pixelMatrix[4][1] = 7;
        newLetter->pixelMatrix[4][2] = 7;
        break;
    case 'E':
        letter_init(newLetter,6,6);
        newLetter->pixelMatrix[1][1] = 1;
        newLetter->pixelMatrix[1][2] = 1;
        newLetter->pixelMatrix[1][3] = 1;
        newLetter->pixelMatrix[1][4] = 1;
        newLetter->pixelMatrix[2][1] = 1;
        newLetter->pixelMatrix[3][1] = 1;
        newLetter->pixelMatrix[3][2] = 1;
        newLetter->pixelMatrix[3][3] = 1;
        newLetter->pixelMatrix[4][1] = 1;
        newLetter->pixelMatrix[5][1] = 1;
        newLetter->pixelMatrix[5][2] = 1;
        newLetter->pixelMatrix[5][3] = 1;
        newLetter->pixelMatrix[5][4] = 1;
        break;
    case 'f':
    case 'F':
        letter_init(newLetter,6,6);
        newLetter->pixelMatrix[1][1] = 1;
        newLetter->pixelMatrix[1][2] = 1;
        newLetter->pixelMatrix[1][3] = 1;
        newLetter->pixelMatrix[1][4] = 1;
        newLetter->pixelMatrix[2][1] = 1;
        newLetter->pixelMatrix[3][1] = 1;
        newLetter->pixelMatrix[3][2] = 1;
        newLetter->pixelMatrix[3][3] = 1;
        newLetter->pixelMatrix[4][1] = 1;
        newLetter->pixelMatrix[5][1] = 1;
        break;
    case 'g':
    case 'G':
        letter_init(newLetter,6,6);
        newLetter->pixelMatrix[1][2] = 1;
        newLetter->pixelMatrix[1][3] = 1;
        newLetter->pixelMatrix[2][1] = 1;
        newLetter->pixelMatrix[3][1] = 1;
        newLetter->pixelMatrix[3][3] = 1;
        newLetter->pixelMatrix[3][4] = 1;
        newLetter->pixelMatrix[4][1] = 1;
        newLetter->pixelMatrix[4][4] = 1;
        newLetter->pixelMatrix[5][2] = 1;
        newLetter->pixelMatrix[5][3] = 1;
        break;
    case 'h':
    case 'H':
        letter_init(newLetter,6,6);
        newLetter->pixelMatrix[1][1] = 1;
        newLetter->pixelMatrix[1][4] = 1;
        newLetter->pixelMatrix[2][1] = 1;
        newLetter->pixelMatrix[2][4] = 1;
        newLetter->pixelMatrix[3][1] = 1;
        newLetter->pixelMatrix[3][2] = 1;
        newLetter->pixelMatrix[3][3] = 1;
        newLetter->pixelMatrix[3][4] = 1;
        newLetter->pixelMatrix[4][1] = 1;
        newLetter->pixelMatrix[4][4] = 1;
        newLetter->pixelMatrix[5][1] = 1;
        newLetter->pixelMatrix[5][4] = 1;
        break;
    case 'i':
    case 'I':
        letter_init(newLetter,6,6);
        newLetter->pixelMatrix[1][1] = 1;
        newLetter->pixelMatrix[1][2] = 1;
        newLetter->pixelMatrix[1][3] = 1;
        newLetter->pixelMatrix[2][2] = 1;
        newLetter->pixelMatrix[3][2] = 1;
        newLetter->pixelMatrix[4][2] = 1;
        newLetter->pixelMatrix[5][1] = 1;
        newLetter->pixelMatrix[5][2] = 1;
        newLetter->pixelMatrix[5][3] = 1;
        break;
    case 'j':
    case 'J':
        letter_init(newLetter,6,6);
        newLetter->pixelMatrix[1][3] = 1;
        newLetter->pixelMatrix[1][4] = 1;
        newLetter->pixelMatrix[2][4] = 1;
        newLetter->pixelMatrix[3][4] = 1;
        newLetter->pixelMatrix[4][1] = 1;
        newLetter->pixelMatrix[4][4] = 1;
        newLetter->pixelMatrix[5][2] = 1;
        newLetter->pixelMatrix[5][3] = 1;
        break;
    case 'k':
    case 'K':
        letter_init(newLetter,6,6);
        newLetter->pixelMatrix[1][1] = 1;
        newLetter->pixelMatrix[1][4] = 1;
        newLetter->pixelMatrix[2][1] = 1;
        newLetter->pixelMatrix[2][3] = 1;
        newLetter->pixelMatrix[3][1] = 1;
        newLetter->pixelMatrix[3][2] = 1;
        newLetter->pixelMatrix[4][1] = 1;
        newLetter->pixelMatrix[4][3] = 1;
        newLetter->pixelMatrix[5][1] = 1;
        newLetter->pixelMatrix[5][4] = 1;
        break;
    case 'l':
    case 'L':
        letter_init(newLetter,6,6);
        newLetter->pixelMatrix[1][1] = 1;
        newLetter->pixelMatrix[2][1] = 1;
        newLetter->pixelMatrix[3][1] = 1;
        newLetter->pixelMatrix[4][1] = 1;
        newLetter->pixelMatrix[5][1] = 1;
        newLetter->pixelMatrix[5][2] = 1;
        newLetter->pixelMatrix[5][3] = 1;
        newLetter->pixelMatrix[5][4] = 1;
        break;
    case 'm':
    case 'M':
        letter_init(newLetter,6,6);
        newLetter->pixelMatrix[1][1] = 1;
        newLetter->pixelMatrix[1][5] = 1;
        newLetter->pixelMatrix[2][1] = 1;
        newLetter->pixelMatrix[2][2] = 1;
        newLetter->pixelMatrix[2][4] = 1;
        newLetter->pixelMatrix[2][5] = 1;
        newLetter->pixelMatrix[3][1] = 1;
        newLetter->pixelMatrix[3][3] = 1;
        newLetter->pixelMatrix[3][5] = 1;
        newLetter->pixelMatrix[4][1] = 1;
        newLetter->pixelMatrix[4][5] = 1;
        newLetter->pixelMatrix[5][1] = 1;
        newLetter->pixelMatrix[5][5] = 1;
        break;
    case 'n':
    case 'N':
        letter_init(newLetter,6,6);
        newLetter->pixelMatrix[1][1] = 1;
        newLetter->pixelMatrix[1][4] = 1;
        newLetter->pixelMatrix[2][1] = 1;
        newLetter->pixelMatrix[2][2] = 1;
        newLetter->pixelMatrix[2][4] = 1;
        newLetter->pixelMatrix[3][1] = 1;
        newLetter->pixelMatrix[3][3] = 1;
        newLetter->pixelMatrix[3][4] = 1;
        newLetter->pixelMatrix[4][1] = 1;
        newLetter->pixelMatrix[4][4] = 1;
        newLetter->pixelMatrix[5][1] = 1;
        newLetter->pixelMatrix[5][4] = 1;
        break;
    case 'o':
    case 'O':
        letter_init(newLetter,6,6);
        newLetter->pixelMatrix[1][2] = 1;
        newLetter->pixelMatrix[1][3] = 1;
        newLetter->pixelMatrix[2][1] = 1;
        newLetter->pixelMatrix[2][4] = 1;
        newLetter->pixelMatrix[3][1] = 1;
        newLetter->pixelMatrix[3][4] = 1;
        newLetter->pixelMatrix[4][1] = 1;
        newLetter->pixelMatrix[4][4] = 1;
        newLetter->pixelMatrix[5][2] = 1;
        newLetter->pixelMatrix[5][3] = 1;
        break;
    case 'p':
    case 'P':
        letter_init(newLetter,6,6);
        newLetter->pixelMatrix[1][1] = 1;
        newLetter->pixelMatrix[1][2] = 1;
        newLetter->pixelMatrix[1][3] = 1;
        newLetter->pixelMatrix[2][1] = 1;
        newLetter->pixelMatrix[2][4] = 1;
        newLetter->pixelMatrix[3][1] = 1;
        newLetter->pixelMatrix[3][2] = 1;
        newLetter->pixelMatrix[3][3] = 1;
        newLetter->pixelMatrix[4][1] = 1;
        newLetter->pixelMatrix[5][1] = 1;
        break;
    case 'q':
    case 'Q':
        letter_init(newLetter,6,6);
        newLetter->pixelMatrix[1][2] = 1;
        newLetter->pixelMatrix[1][3] = 1;
        newLetter->pixelMatrix[2][1] = 1;
        newLetter->pixelMatrix[2][4] = 1;
        newLetter->pixelMatrix[3][1] = 1;
        newLetter->pixelMatrix[3][4] = 1;
        newLetter->pixelMatrix[4][1] = 1;
        newLetter->pixelMatrix[4][4] = 1;
        newLetter->pixelMatrix[5][2] = 1;
        newLetter->pixelMatrix[5][3] = 1;
        newLetter->pixelMatrix[5][4] = 1;
        newLetter->pixelMatrix[5][5] = 1;
        break;
    case 'r':
        letter_init(newLetter,5,4);
        newLetter->pixelMatrix[1][1] = 7;
        newLetter->pixelMatrix[1][2] = 7;
        newLetter->pixelMatrix[2][0] = 7;
        newLetter->pixelMatrix[3][0] = 7;
        newLetter->pixelMatrix[4][0] = 7;
        break;
    case 'R':
        letter_init(newLetter,6,6);
        newLetter->pixelMatrix[1][1] = 1;
        newLetter->pixelMatrix[1][2] = 1;
        newLetter->pixelMatrix[1][3] = 1;
        newLetter->pixelMatrix[2][1] = 1;
        newLetter->pixelMatrix[2][4] = 1;
        newLetter->pixelMatrix[3][1] = 1;
        newLetter->pixelMatrix[3][2] = 1;
        newLetter->pixelMatrix[3][3] = 1;
        newLetter->pixelMatrix[4][1] = 1;
        newLetter->pixelMatrix[4][4] = 1;
        newLetter->pixelMatrix[5][1] = 1;
        newLetter->pixelMatrix[5][4] = 1;
        break;
    case 's':
    case 'S':
        letter_init(newLetter,6,6);
        newLetter->pixelMatrix[1][2] = 1;
        newLetter->pixelMatrix[1][3] = 1;
        newLetter->pixelMatrix[1][4] = 1;
        newLetter->pixelMatrix[2][1] = 1;
        newLetter->pixelMatrix[3][2] = 1;
        newLetter->pixelMatrix[3][3] = 1;
        newLetter->pixelMatrix[4][4] = 1;
        newLetter->pixelMatrix[5][1] = 1;
        newLetter->pixelMatrix[5][2] = 1;
        newLetter->pixelMatrix[5][3] = 1;
        break;
    case 't':
    case 'T':
        letter_init(newLetter,6,6);
        newLetter->pixelMatrix[1][1] = 1;
        newLetter->pixelMatrix[1][2] = 1;
        newLetter->pixelMatrix[1][3] = 1;
        newLetter->pixelMatrix[1][4] = 1;
        newLetter->pixelMatrix[1][5] = 1;
        newLetter->pixelMatrix[2][3] = 1;
        newLetter->pixelMatrix[3][3] = 1;
        newLetter->pixelMatrix[4][3] = 1;
        newLetter->pixelMatrix[5][3] = 1;
        break;
    case 'u':
    case 'U':
        letter_init(newLetter,6,6);
        newLetter->pixelMatrix[1][1] = 1;
        newLetter->pixelMatrix[1][4] = 1;
        newLetter->pixelMatrix[2][1] = 1;
        newLetter->pixelMatrix[2][4] = 1;
        newLetter->pixelMatrix[3][1] = 1;
        newLetter->pixelMatrix[3][4] = 1;
        newLetter->pixelMatrix[4][1] = 1;
        newLetter->pixelMatrix[4][4] = 1;
        newLetter->pixelMatrix[5][2] = 1;
        newLetter->pixelMatrix[5][3] = 1;
        break;
    case 'v':
    case 'V':
        letter_init(newLetter,6,6);
        newLetter->pixelMatrix[1][1] = 1;
        newLetter->pixelMatrix[1][4] = 1;
        newLetter->pixelMatrix[2][1] = 1;
        newLetter->pixelMatrix[2][4] = 1;
        newLetter->pixelMatrix[3][1] = 1;
        newLetter->pixelMatrix[3][4] = 1;
        newLetter->pixelMatrix[4][1] = 1;
        newLetter->pixelMatrix[4][3] = 1;
        newLetter->pixelMatrix[5][2] = 1;
        break;
    case 'w':
    case 'W':
        letter_init(newLetter,6,6);
        newLetter->pixelMatrix[1][1] = 1;
        newLetter->pixelMatrix[1][5] = 1;
        newLetter->pixelMatrix[2][1] = 1;
        newLetter->pixelMatrix[2][5] = 1;
        newLetter->pixelMatrix[3][1] = 1;
        newLetter->pixelMatrix[3][3] = 1;
        newLetter->pixelMatrix[3][5] = 1;
        newLetter->pixelMatrix[4][1] = 1;
        newLetter->pixelMatrix[4][3] = 1;
        newLetter->pixelMatrix[4][5] = 1;
        newLetter->pixelMatrix[5][2] = 1;
        newLetter->pixelMatrix[5][4] = 1;
        break;
    case 'x':
    case 'X':
        letter_init(newLetter,6,6);
        newLetter->pixelMatrix[1][1] = 1;
        newLetter->pixelMatrix[1][5] = 1;
        newLetter->pixelMatrix[2][2] = 1;
        newLetter->pixelMatrix[2][4] = 1;
        newLetter->pixelMatrix[3][3] = 1;
        newLetter->pixelMatrix[4][2] = 1;
        newLetter->pixelMatrix[4][4] = 1;
        newLetter->pixelMatrix[5][1] = 1;
        newLetter->pixelMatrix[5][5] = 1;
        break;
    case 'y':
    case 'Y':
        letter_init(newLetter,6,6);
        newLetter->pixelMatrix[1][1] = 1;
        newLetter->pixelMatrix[1][4] = 1;
        newLetter->pixelMatrix[2][1] = 1;
        newLetter->pixelMatrix[2][4] = 1;
        newLetter->pixelMatrix[3][1] = 1;
        newLetter->pixelMatrix[3][2] = 1;
        newLetter->pixelMatrix[3][3] = 1;
        newLetter->pixelMatrix[4][3] = 1;
        newLetter->pixelMatrix[5][2] = 1;
        break;
    case 'z':
    case 'Z':
        letter_init(newLetter,6,6);
        newLetter->pixelMatrix[1][1] = 1;
        newLetter->pixelMatrix[1][2] = 1;
        newLetter->pixelMatrix[1][3] = 1;
        newLetter->pixelMatrix[1][4] = 1;
        newLetter->pixelMatrix[2][4] = 1;
        newLetter->pixelMatrix[3][2] = 1;
        newLetter->pixelMatrix[3][3] = 1;
        newLetter->pixelMatrix[4][1] = 1;
        newLetter->pixelMatrix[5][1] = 1;
        newLetter->pixelMatrix[5][2] = 1;
        newLetter->pixelMatrix[5][3] = 1;
        newLetter->pixelMatrix[5][4] = 1;
        break;
    case ' ':
        letter_init(newLetter,6,6);
        break;
    case '*':
        letter_init(newLetter,5,4);
        newLetter->pixelMatrix[2][1] = 1;
        newLetter->pixelMatrix[2][2] = 1;
        newLetter->pixelMatrix[3][1] = 1;
        newLetter->pixelMatrix[3][2] = 1;
        break;
    case '+':
        letter_init(newLetter,5,4);
        newLetter->pixelMatrix[0][2] = 1;
        newLetter->pixelMatrix[0][3] = 1;
        newLetter->pixelMatrix[0][4] = 1;
        newLetter->pixelMatrix[1][2] = 1;
        newLetter->pixelMatrix[1][3] = 1;
        newLetter->pixelMatrix[1][4] = 1;
        newLetter->pixelMatrix[2][2] = 1;
        newLetter->pixelMatrix[2][3] = 1;
        newLetter->pixelMatrix[2][4] = 1;
        break;
    case '2':
        letter_init(newLetter,6,6);
        newLetter->pixelMatrix[1][1] = 1;
        newLetter->pixelMatrix[1][2] = 1;
        newLetter->pixelMatrix[1][3] = 1;
        newLetter->pixelMatrix[2][4] = 1;
        newLetter->pixelMatrix[3][2] = 1;
        newLetter->pixelMatrix[3][3] = 1;
        newLetter->pixelMatrix[4][1] = 1;
        newLetter->pixelMatrix[5][1] = 1;
        newLetter->pixelMatrix[5][2] = 1;
        newLetter->pixelMatrix[5][3] = 1;
        newLetter->pixelMatrix[5][4] = 1;
        break;
  }
   return newLetter;
}

// cleans the dynamic memory used to allocate the letter
void cleanLetter(struct letter *l)
{
  for (int i = 0; i < l->LETTERHEIGHT; i++)
  {
    uint8_t* currentIntPtr = l->pixelMatrix[i];
    free(currentIntPtr);
  }
}

/*
int main(void) {
    struct letter* newLetter = createLetter(' ');
    printLetter(newLetter);
}
*/