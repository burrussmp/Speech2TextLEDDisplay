#include <pocketsphinx.h>
#include <semaphore.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "LED.h"


/*
* Control structur encapsulating the synch variables
* Holds the readyToDecode, files, and screen buffer
*/
struct control {
  pthread_mutex_t convert_mutex;
  pthread_cond_t convert_condition;

  // Number of files ready to decode
  int readyToDecode;
  char* files;
  struct screen* newScreen;
};

// Current number of files to write
static int NUM_FILES = 1;

// Refresh mutex to guard the LED matrix
static pthread_mutex_t refreshMut;

void *screen_advance(void* param);
void *record_audio(void* data);
void *decode_audio(void* data);
void* screen_refresh(void* data);

void control_init(struct control* cont);

int main(int argc, char *argv[])
{
    pthread_t thread1, thread2, thread3, thread4;
    int ret1, ret2, ret3, ret4;

    
    // Setup the control struct
    struct control* cont = malloc(sizeof(struct control));
    control_init(cont);

    // Setup lED pins to display
    ledMatrix_setupPins();

    int mut = pthread_mutex_init(&refreshMut, NULL);

    // Recording thread
    
    ret1 = pthread_create(&thread1, NULL, record_audio, (void*) cont);
    if (ret1){
      printf("Error opening thread1");
      return 1;
    }

    // Psphinx decoding thread
    ret2 = pthread_create(&thread2, NULL, decode_audio, (void*) cont);
    if (ret2){
      printf("Error opening thread2");
      return 1;
    }
    
    // Screen advance thread
    ret3 = pthread_create(&thread3, NULL, screen_advance, (void*) cont);
    if (ret3){
      printf("Error opening thread2");
      return 1;
    }

    // Refresh thread
    ret4 = pthread_create(&thread4, NULL, screen_refresh, (void*) cont);
    if (ret4){
     printf("Error opening thread2");
     return 1;
    }

    // Join threads
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    pthread_join(thread4, NULL);
    
    return 1;

}

/*
* Refreshes the screen so the most updated version displays
*/
void *screen_refresh(void* data){
  struct control* cont = (struct control*)data;

  while(1){
    // Lock screen mutex
    pthread_mutex_lock(&refreshMut);

    // Refresh the screen to achieve display the updated screen
    ledMatrix_refresh(cont->newScreen);

    // Unlock screen mutex
    pthread_mutex_unlock(&refreshMut);
  }
}

/*
* Advances and updates the screen every .1 seconds
*/ 
void *screen_advance(void* param){
  struct control* cont  = (struct control*) param;

  while(1){

      // Sleep to give other threads a chance to run
      usleep(100000);

      // Advance the LED text across the screen
      advance(cont->newScreen);

      // Lock screen mutex
      pthread_mutex_lock(&refreshMut);

      // Display the advanced pattern on the screen
      updateScreen(cont->newScreen);

      // Unlock screen mutex
      pthread_mutex_unlock(&refreshMut);
  }

  return (void*)1;
}


/* 
* This thread decodes the audio data within the file
* Uses the pocketsphinx library to perform the decoding
* Intializes the speech recognizer with the proper settings
* Synchronizes with the recording thread
*/
void *decode_audio(void* param){

  struct control* cont  = (struct control*) param;

  ps_decoder_t *ps;
    cmd_ln_t *config;
    FILE *fh;
    char const *hyp, *uttid;
    int16 buf[512];
    int rv;
    int32 score;

  // Initialize the PocketSphinx library configurations
  // With the correct arguments: sample rate, dict., lang. model, etc.  
  config = cmd_ln_init(NULL, ps_args(), TRUE,
             "-hmm", MODELDIR "/en-us/en-us",
             "-lm", MODELDIR "/en-us/en-us2.lm.bin",
             //"-lm", MODELDIR "/en-us/newlm.lm",
             "-dict", MODELDIR "/en-us/cmudict-en-us2.dict",
             //"-dict", MODELDIR "/en-us/newdict.dict",
                // "-dict", MODELDIR "/en-us/dan-test.dict",
                 "-samprate", "22100",
                 "-nfft", "1024",
                 "-ds", "1", // higher is less accurate
                 "-topn", "2", // lower less accurate
                 "-maxwpf", "5", // low means less accurate
                 "-maxhmmpf", "3000", // who knows man
                 "-pl_window", "10", // Greater mean less accurate

             NULL);

  // If configuration is null (fail) return
  if (config == NULL) {
    fprintf(stderr, "Failed to create config object, see log for details\n");
    return (void*)-1;
  }

  // Initialize the pocketsphinx recognizer using configurations
  ps = ps_init(config);

  // If recognizer init failed, return
  if (ps == NULL) {
    fprintf(stderr, "Failed to create recognizer, see log for details\n");
    return (void*)-1;
  }

  while (1) {
    pthread_mutex_lock( &(cont->convert_mutex) ); // lock condition

    // Waits while no file is ready to decode (ready for double buffer if another processor was introduced)
    while(cont->readyToDecode <= 0)
    {
      pthread_cond_wait( &(cont->convert_condition) ,&(cont->convert_mutex) );
    }

    // Open specified file
    fh = fopen(cont->files, "rb");

    if (fh == NULL) {
      fprintf(stderr, "Unable to open input file buffer1.raw\n");
      return (void*)-1;
    }

    // Initialize buffer with decoding symbol
    char rec[] = "+";

    // Place decoding symbol on the screen 
    placeWord(rec,0,24,cont->newScreen);

    rv = ps_start_utt(ps);

    // Until end of file, read from file and process 512 2-byte elements each iteration
    while (!feof(fh)) {
      size_t nsamp;
      nsamp = fread(buf, 2, 512, fh);
      rv = ps_process_raw(ps, buf, nsamp, FALSE, FALSE);
    }

    rv = ps_end_utt(ps);

    // Receive hypothesis string 
    hyp = ps_get_hyp(ps, &score);

    // Clear screen region for new character to be added
    clearRegionOfScreen(cont->newScreen,17,38,0,5);

    // Interpret the hypothesis, adding the phrase if not null
    if (hyp == NULL){
      printf("NOTHING SPOKEN, RECEIVED NULL\n");
    } else {
      printf("Recognized: %s\n", hyp);
      char phrase[strlen(hyp)];
      strcpy(phrase, hyp);
      //addPhrase(cont->newScreen,"Test");
      addPhrase(cont->newScreen, phrase);
    }

    fflush(stdout);

    fclose(fh);

    // Decode the file stream
    cont->readyToDecode--;

    // send signal to wake
    pthread_cond_broadcast( &(cont->convert_condition) );
    // unlock mutex
    pthread_mutex_unlock( &(cont->convert_mutex) );
  }

  cmd_ln_free_r(config);

  return (void*)1;
}

/*
* This thread records to an audio file when readyToDecode is less than NUM_FILES
* ReadyToDecode signifies recorded audio to decode and NUM_FILES, for the time being, is 1
*
* This function alternates with decode_audio in order to capture and process the audio signals
* Calls ALSA library function from the command line
* Specs:
* - Sample Rate: 22100 kHz; USB device: hw:1,0; Duration: 3 seconds; Destination: buffer1.raw
  - Format: S16_LE
*/
void *record_audio(void* param){

  struct control* cont  = (struct control*) param;

  while(1){
    pthread_mutex_lock( &(cont->convert_mutex) ); // lock condition

    while(cont->readyToDecode >= NUM_FILES)
    {
      pthread_cond_wait( &(cont->convert_condition),&(cont->convert_mutex) );
    }

    //char* command;

    // Sleep 5 seconds to give the user time to read text and then speak 
    usleep(5000000);

    // Place the recording symbol
    char rec[] = "rec*";
    placeWord(rec,0,0,cont->newScreen);

    // Call command function to record
    system("arecord -f S16_LE -r22100 -D hw:1,0 -d 3 buffer1.raw");

    // Clear recording symbol
    clearRegionOfScreen(cont->newScreen,0,16,0,5);
    //system(command); // This might not work

    printf("Done recording");

    fflush(stdout);

    // Increment ReadyToDecode
    cont->readyToDecode++;

      // send signal to wake
    pthread_cond_broadcast( &(cont->convert_condition) );
    // unlock mutex
    pthread_mutex_unlock( &(cont->convert_mutex) );

  }

  return (void*)1;
}


/*
* Initialize the control struct
* Contains synchronization variables, bufferfile name, screen to initialize
*/
void control_init(struct control* cont){

    // Control mutex and condition variable for synch
    int mut = pthread_mutex_init(&cont->convert_mutex, NULL);
    int cond = pthread_cond_init(&cont->convert_condition, NULL);

    // Files
    cont->files = "buffer1.raw";

    // Number of files ready to decode
    cont->readyToDecode = 0;

    // Initialize the screen for the LED
    cont->newScreen = screenInit();
}