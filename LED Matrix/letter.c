/*
    @author: Matthew Burruss
    @date: 11/28/2018
    @description: The letter class which defines the pixelated values and encapsulates
    the creation of the letters. Supports a-z and space.
*/

#include "letter.h"
void letter_init(struct letter* l)
{
    l->pixelMatrix=(uint8_t **) malloc(LETTERHEIGHT*sizeof(uint8_t *));

    for(int i=0;i<LETTERHEIGHT;i++)
        l->pixelMatrix[i]=(uint8_t *) malloc(20*sizeof(uint8_t));
    for (int i = 0; i<LETTERHEIGHT;++i)
    {
        for (int j = 0; j < LETTERWIDTH; ++j)
        {
            l->pixelMatrix[i][j] = 0;
        }
    }
}

void printLetter(struct letter *l)
{
    for (uint8_t i = 0; i < LETTERHEIGHT;++i)
    {
        for (uint8_t j = 0; j < LETTERWIDTH;++j)
        {
            printf("%d",l->pixelMatrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}


struct letter* createLetter(char l)
{
  struct letter* newLetter = malloc(sizeof(struct letter)); 
  letter_init(newLetter);
  switch(l)
  {
      /*
        0   0   0   0   0   0
        0   0   1   1   0   0
        0   1   0   0   1   0
        0   1   0   0   1   0
        0   1   1   1   1   0
        0   1   0   0   1   0
      */
    case 'A':
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
    case 'B':
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
    case 'C':
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
    case 'D':
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
    case 'E':
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
    case 'F':
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
    case 'G':
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
    case 'H':
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
    case 'I':
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
    case 'J':
        newLetter->pixelMatrix[1][3] = 1;
        newLetter->pixelMatrix[1][4] = 1;
        newLetter->pixelMatrix[2][4] = 1;
        newLetter->pixelMatrix[3][4] = 1;
        newLetter->pixelMatrix[4][1] = 1;
        newLetter->pixelMatrix[4][4] = 1;
        newLetter->pixelMatrix[5][2] = 1;
        newLetter->pixelMatrix[5][3] = 1;
        break;
    case 'K':
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
    case 'L':
        newLetter->pixelMatrix[1][1] = 1;
        newLetter->pixelMatrix[2][1] = 1;
        newLetter->pixelMatrix[3][1] = 1;
        newLetter->pixelMatrix[4][1] = 1;
        newLetter->pixelMatrix[5][1] = 1;
        newLetter->pixelMatrix[5][2] = 1;
        newLetter->pixelMatrix[5][3] = 1;
        newLetter->pixelMatrix[5][4] = 1;
        break;
    case 'M':
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
    case 'N':
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
    case 'O':
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
    case 'P':
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
    case 'Q':
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
    case 'R':
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
    case 'S':
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
    case 'T':
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
    case 'U':
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
    case 'V':
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
    case 'W':
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
    case 'X':
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
    case 'Y':
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
    case 'Z':
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
        break;
  }
   return newLetter;
}


void cleanLetter(struct letter *l)
{
  for (int i = 0; i < LETTERHEIGHT; i++)
  {
    uint8_t* currentIntPtr = l->pixelMatrix[i];
    free(currentIntPtr);
  }
}

//int main(void) {
//    struct letter* newLetter = createLetter(' ');
//    printLetter(newLetter);
//}