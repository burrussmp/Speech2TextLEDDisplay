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

void addPhrase(struct screen * s, char* phrase)
{
    int end = strlen(phrase);
    for (int i = 0; i < end; ++i)
    {
        addLetter(s,phrase[i]);
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
void changeColor(struct screen *s,int ncolor)
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
void placeLetter(struct letter* l, int col, int row,struct screen * s)
{
    for (int i = 0; i < LETTERHEIGHT; ++i)
    {
        for (int j = 0; j < LETTERHEIGHT; ++j){
            s->screenBuffer[row+j][col+i] = l->pixelMatrix[i][j];
        }
    }
}
// advance
// if the queue is empty, send in a space.. using trylock
// if the error code reads empty, then we advance with a space and do not unlock
// the queue is filled with letter objects
// Every six advances, we should dequeue
void advance(struct screen * s)
{
    //usleep(330000);
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
        int row = 5;
        int col = 32;
        placeLetter(&myletter,row,col,s);
        cleanLetter(&myletter);
    }
    // advance the screen by 1 to the left and appropriately adjust 
    for (int i = 0; i < 16; ++i)
    {
        for (int j = 0; j < 38; ++j)
        {
            s->screenBuffer[j][i] = s->screenBuffer[j+1][i];
            if (s->screenBuffer[j][i] != 0){
                s->screenBuffer[j][i] = s->color;
            }
        }
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
    updateScreen(newScreen);
    newScreen->bufferOfLetters = malloc(sizeof(struct buffer));
    buffer_init(newScreen->bufferOfLetters);
    char *word = "JORDY IS A GREAT GUY";
    addPhrase(newScreen,word);
    //fillBufferTest(newScreen->bufferOfLetters);
    return newScreen;
}


int main(void)
{
    struct screen * newScreen;
    newScreen = screenInit();
    printf("here");
    fflush(stdout);
    while(1){
        usleep(100000);
        advance(newScreen);
        //printScreenBuffer(newScreen);
        //printScreenBuffer(newScreen);
        printScreen(newScreen);
    }
}

void freeScreen(struct screen * myscreen)
{
    free(myscreen->bufferOfLetters);    
}


