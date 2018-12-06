#include "Screen.h"

// This function will display to stdout the screenBuffer
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

// Helper function to make string lowercase
// Must declare string Y as 
// char Y[] = "XXXXX";
void makeUpperCase(char* myString)
{
  for (int i = 0; myString[i];++i)
  {
    myString[i] = toupper(myString[i]);
  }
}

// This function will set all of the screen pixels to nothing (0) 
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

// The addPhrase function takes in a string and queues up
// the letters to be added to the screen. The addPhrase
// function also looks for key words in the phrase to control the
// color of the text. See the function implementation to see what 
// words are supported
void addPhrase(struct screen * s, char* phrase)
{
    makeUpperCase(phrase); // make the phrase uppercase
    int end = strlen(phrase);
    for (int i = 0; i < end; ++i) // Add eacah leter to the screen's letter buffer
    {
        addLetter(s,phrase[i]);
    }
    addLetter(s,' '); // At the end of the phrase, add a few spaces/
    addLetter(s,' ');
    if (strstr(phrase,"RED") != NULL) // See if there were any special words passed
    {                                   // that might change the color of the text
        changeColor(s,1);
    }
    if (strstr(phrase,"YELLOW") != NULL)
    {
        changeColor(s,3);
    }
    if (strstr(phrase,"GREEN") != NULL)
    {
        changeColor(s,2);
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

}

// This function will display to stdout the screen
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

// Sets the screen member of the screen struct to the values in 
// the screenBuffer so tht the relevant 32x16 bits are are the same
// for both buffers.
void updateScreen(struct screen *s)
{
    for (int i = 0; i < 15; ++i)
    {
        for (int j = 0; j < 32; ++j)
        {
            s->screen[j][i] = s->screenBuffer[j][i];
            if (s->screen[j][i] != 0 && i > 8){
                s->screen[j][i] = s->color;
            }
        }
    }
}

// Enqueues a new letter to the screen buffer's buffer of letters

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
// Similar to placeLetter but rather places a row across the screen struct.
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

// advances the screen buffer by 2 pixels from the right to the left
// if the queue is empty, send in a ' ' as a filler
// if the screenBuffer buffer space is empty, then dequeue
// a new letter from the buffer of letters.
// At the end, update the screen to contain the relevant values
// of screen buffer.
void advance(struct screen * s)
{
    if (s->advanceCounter % 4 == 0) // have we advanced enough so that a new letter can be placed?
    {
        // get next letter
        struct letter myletter;
        pthread_mutex_lock( &(s->enqueueMutex) );
        if (size(s->bufferOfLetters) == 0)
        {
            enqueue(s->bufferOfLetters,' '); // If the buffer of letters is empty, enqueue a ' '
        }
        pthread_mutex_unlock( &(s->enqueueMutex) );
        myletter = dequeue(s->bufferOfLetters); // Get the next letter from the buffer of letteres
        s->advanceCounter = 1;
        // place letter in bufferScreen
        int row = 9; // Place the letter at the bottom right portion of the screen.
        int col = 32;
        placeLetter(&myletter,row,col,s); 
        cleanLetter(&myletter); // Clean the dynamic memory allocated to the letter.
    }
    // advance the screen by 1 to the left and appropriately adjust 
    
    for (int i = 6; i < 15; ++i)
    {
        for (int j = 0; j < 36; ++j)
        {
            s->screenBuffer[j][i] = s->screenBuffer[j+2][i]; // Advance the screen buffer by two pixels from right to left.
        }
        s->screenBuffer[37][i] = 0;
        s->screenBuffer[36][i] = 0;
    }
    
    updateScreen(s); // Set the relevant screen pixels in the screen to the screen buffer
    s->advanceCounter++;
}

// Initially used to test the letters by filling the buffer
// with all letters A through Z.
void fillBufferTest(struct buffer * mybuf)
{
    for (char i = 'A'; i <= 'Z';++i)
    {
        enqueue(mybuf,i);
    }
}

// Initializes the screen struct, including allocating the
// buffer of letters.
// The phrase "SPEECH2TEXT" is added and scrolled across the display.
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
    char word[] = "SPEECH2TEXT";
    addPhrase(newScreen,word);
    //fillBufferTest(newScreen->bufferOfLetters);
    return newScreen;
}

// Cleans the allocated memory associated to the screen.
void freeScreen(struct screen * myscreen)
{
    free(myscreen->bufferOfLetters);    
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
        //if (count > 30)
       // {
       //     //clearRegionOfScreen(newScreen,0,38,0,5);
       // }
    }
    printScreenBuffer(newScreen);
}
*/



