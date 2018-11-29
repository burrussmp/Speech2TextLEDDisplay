#include "Screen.h"

void printScreenBuffer(struct screen * s){
    for (int i = 0; i < 16; ++i)
    {
        for (int j = 0; j < 38; ++j)
        {
            if (s->screenBuffer[j][i] == 0)
            {
                printf(" ");
            } else {
                printf("%d",s->screenBuffer[j][i]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

void makeUpperCase(char* myString)
{
  for (int i = 0; myString[i];++i)
  {
    myString[i] = toupper(myString[i]);
  }
}
void resetScreen(struct screen *s){
    clearRegionOfScreen(s,0,38,0,16);
}

// Clears a region of the screen, noninclusive for
// hight value
void clearRegionOfScreen(struct screen *s, int coll,int colh, int rowl,int rowh)
{
    for (int j = coll; j < colh; ++j){
        for (int i = rowl; i < rowh; ++i)
        {
            s->screenBuffer[j][i] = 0;
        }
    }
    updateScreen(s);
}
void addPhrase(struct screen * s, char* phrase)
{
    // add each letter to the letter buffer
    makeUpperCase(phrase);
    int end = strlen(phrase);
    for (int i = 0; i < end; ++i)
    {
        addLetter(s,phrase[i]);
    }    
    if (strstr(phrase,"RED") != NULL)
    {
        changeColor(s,1);
    }
    if (strstr(phrase,"YELLOW") != NULL)
    {
        changeColor(s,2);
    }
    if (strstr(phrase,"GREEN") != NULL)
    {
        changeColor(s,3);
    }
    if (strstr(phrase,"BLUE") != NULL)
    {
        changeColor(s,4);
    }
    if (strstr(phrase,"VIOLET") != NULL)
    {
        changeColor(s,5);
    }
    if (strstr(phrase,"LIGHT BLUE") != NULL)
    {
        changeColor(s,6);
    }
    if (strstr(phrase,"WHITE") != NULL)
    {
        changeColor(s,7);
    }
    if (strstr(phrase,"FLASH"))
    {
        changeColor(s,7);
    }

}
void printScreen(struct screen * s){
    for (int i = 0; i < 16; ++i)
    {
        for (int j = 0; j < 32; ++j)
        {
            if (s->screen[j][i] == 0)
            {
                printf(" ");
            } else {
                printf("%d",s->screen[j][i]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

// changeColor
void changeColor(struct screen *s,uint8_t ncolor)
{
    s->color = ncolor;
    if (s->color > 7){
        s->color = 1;
    }
}

// updateScreen
void updateScreen(struct screen *s)
{
    for (int i = 0; i < 16; ++i)
    {
        for (int j = 0; j < 32; ++j)
        {
            s->screen[j][i] = s->screenBuffer[j][i];
            if (s->screen[j][i] != 0){
                s->screen[j][i] = s->color;
            }
        }
    }
}

void addLetter(struct screen * s, char newLetter)
{
    pthread_mutex_lock( &(s->enqueueMutex) );
    enqueue(s->bufferOfLetters,newLetter);
    pthread_mutex_unlock( &(s->enqueueMutex) );
}
// placeLetter
// col and row specify location of upperleft corner of the letter
// Note(0,0) is in the top left corner of the matrix
// Placeletter will overwrite the buffer
void placeLetter(struct letter* l, int row, int col,struct screen * s)
{
    for (int i = 0; i < l->LETTERHEIGHT; ++i)
    {
        for (int j = 0; j < l->LETTERWIDTH; ++j){
            s->screenBuffer[col+j][row+i] = l->pixelMatrix[i][j];
        }
    }
}

// pre condition: The word will fit given # of characters and position
void placeWord(char* word,int row,int col,struct screen *s)
{
    struct letter* newLetter;
    int letterwidth;
    for (int i = 0; word[i];++i)
    {
        newLetter = createLetter(word[i]);
        letterwidth = newLetter->LETTERWIDTH;
        placeLetter(newLetter,row,col+i*letterwidth,s);
        cleanLetter(newLetter);
    }
}

// advance
// if the queue is empty, send in a space.. using trylock
// if the error code reads empty, then we advance with a space and do not unlock
// the queue is filled with letter objects
// Every six advances, we should dequeue
void advance(struct screen * s)
{
    if (s->advanceCounter % 7 == 0)
    {
        // get next letter
        struct letter myletter;
        pthread_mutex_lock( &(s->enqueueMutex) );
        if (size(s->bufferOfLetters) == 0)
        {
            enqueue(s->bufferOfLetters,' ');
        }
        pthread_mutex_unlock( &(s->enqueueMutex) );
        myletter = dequeue(s->bufferOfLetters);
        s->advanceCounter = 1;
        // place letter in bufferScreen
        int row = 10;
        int col = 32;
        placeLetter(&myletter,row,col,s);
        cleanLetter(&myletter);
    }
    // advance the screen by 1 to the left and appropriately adjust 
    
    for (int i = 10; i < 16; ++i)
    {
        for (int j = 0; j < 37; ++j)
        {
            s->screenBuffer[j][i] = s->screenBuffer[j+1][i];
        }
        s->screenBuffer[37][i] = 0;
    }
    
    updateScreen(s);
    s->advanceCounter++;
}

void fillBufferTest(struct buffer * mybuf)
{
    for (char i = 'A'; i <= 'Z';++i)
    {
        enqueue(mybuf,i);
    }
}


struct screen* screenInit()
{
    struct screen * newScreen = malloc(sizeof(struct screen));
    newScreen->advanceCounter = 1;
    newScreen->color = 1;
    pthread_mutex_init(&(newScreen->enqueueMutex),NULL);
    for (int i = 0; i < 16; ++i)
    {
        for (int j = 0; j < 38; ++j)
        {
           newScreen->screenBuffer[j][i] = 0;
        }
    }
    resetScreen(newScreen);
    newScreen->bufferOfLetters = malloc(sizeof(struct buffer));
    buffer_init(newScreen->bufferOfLetters);
    char word[] = "STARTING";
    addPhrase(newScreen,word);
   // char rec[] = "rec";
   // placeWord(rec,0,0,newScreen);
    //fillBufferTest(newScreen->bufferOfLetters);
    return newScreen;
}

/*
int main(void)
{
    struct screen * newScreen;
    newScreen = screenInit();
    int count = 0;
    while(1){
        usleep(100000);
        advance(newScreen);
        //printScreenBuffer(newScreen);
        printScreen(newScreen);
        if (count > 30)
        {
            clearRegionOfScreen(newScreen,0,38,0,7);
        }
    }
    printScreenBuffer(newScreen);
}
*/

void freeScreen(struct screen * myscreen)
{
    free(myscreen->bufferOfLetters);    
}


