#include <pocketsphinx.h>
#include <semaphore.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

struct control {
  //sem_t convertSem;
  pthread_mutex_t convert_mutex;
  pthread_cond_t convert_condition;
  int curRec;
  int curDec;
  int readyToDecode;
  char* files[2];
};

static int NUM_FILES = 2;

void *record_audio(void* data);
void *decode_audio(void* data);

void control_init(struct control* cont);

int main(int argc, char *argv[])
{
    flag = 0;

    pthread_t thread1, thread2;
    int ret1, ret2;

    struct control* cont = malloc(sizeof(struct control));
    control_init(cont);

    char* message1 = "Thread1";
    ret1 = pthread_create(&thread1, NULL, record_audio, (void*) cont);
    if (ret1){
      printf("Error opening thread1");
      return 1;
    }

  char* message2 = "Thread2";
    ret2 = pthread_create(&thread2, NULL, decode_audio, (void*) cont);
    if (ret2){
      printf("Error opening thread2");
      return 1;
    }

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    
    return 69;

}

void control_init(struct control* cont){
    int mut = pthread_mutex_init(&cont->convert_mutex, NULL);
    int cond = pthread_cond_init(&cont->convert_condition, NULL);
    cont->files[0] = "buffer1.raw";
    cont->files[1] = "buffer2.raw";
    cont->curDec = 0;
    cont->curRec = 0;
    cont->readyToDecode = 0;
}

void decode(struct control* cont){
  cont->curDec = cont->curDec % NUM_FILES;
  cont->readyToDecode--;
}

void record(struct control* cont){
  cont->curRec = cont->curRec % NUM_FILES;
  cont->readyToDecode++;
}

void *decode_audio(void* param){

  struct control* cont  = (struct control*) param;

  ps_decoder_t *ps;
    cmd_ln_t *config;
    FILE *fh;
    char const *hyp, *uttid;
    int16 buf[512];
    int rv;
    int32 score;

  config = cmd_ln_init(NULL, ps_args(), TRUE,
             "-hmm", MODELDIR "/en-us/en-us",
             "-lm", MODELDIR "/en-us/en-us.lm.bin",
           "-dict", MODELDIR "/en-us/cmudict-en-us.dict",
                 //"-dict", MODELDIR "/en-us/dan-test.dict",
                 "-samprate", "22100",
                 "-nfft", "1024",
                 "-ds", "2", // higher is less accurate
                 "-topn", "2", // lower less accurate
                 "-maxwpf", "5", // low means less accurate
                 "-maxhmmpf", "3000", // who knows man
                 "-pl_window", "10", // Greater mean less accurate

             NULL);
  if (config == NULL) {
    fprintf(stderr, "Failed to create config object, see log for details\n");
    return -1;
  }

  ps = ps_init(config);

  if (ps == NULL) {
    fprintf(stderr, "Failed to create recognizer, see log for details\n");
    return -1;
  }



  int i = 0;
  while (1) {

    pthread_mutex_lock( &(cont->convert_mutex) ); // lock condition

    while(cont->readyToDecode < 1)
    {
      pthread_cond_wait( &(cont->convert_condition) ,&(cont->convert_mutex) );
    }

    fh = fopen(cont->files[cont->curDec], "rb");

    decode(cont);

    if (fh == NULL) {
      fprintf(stderr, "Unable to open input file goforward.raw\n");
      return -1;
    }

    rv = ps_start_utt(ps);

    while (!feof(fh)) {
      size_t nsamp;
      nsamp = fread(buf, 2, 512, fh);
      rv = ps_process_raw(ps, buf, nsamp, FALSE, FALSE);
    }

    rv = ps_end_utt(ps);
    hyp = ps_get_hyp(ps, &score);
    printf("Recognized: %s\n", hyp);

    fclose(fh);
    i++;

    // send signal to wake
    pthread_cond_broadcast( &(cont->convert_condition) );
    // unlock mutex
    pthread_mutex_unlock( &(cont->convert_mutex) );
  }

  cmd_ln_free_r(config);


}

void *record_audio(void* param){

  struct control* cont  = (struct control*) param;

  while(1){

    pthread_mutex_lock( &(cont->convert_mutex) ); // lock condition

    while(cont->readyToDecode < NUM_FILES)
    {
      pthread_cond_wait( &(cont->convert_condition) ,&(cont->convert_mutex) );
    }

    char* command;

    sprintf(command, "arecord -f S16_LE -r22100 -D hw:1,0 -d 2 %s", cont->files[cont->curRec]);

    system("arecord -f S16_LE -r22100 -D hw:1,0 -d 2 continuous.raw");

    printf("Done recording");

    fflush(stdout);

    record(cont);

      // send signal to wake
    pthread_cond_broadcast( &(cont->convert_condition) );
    // unlock mutex
    pthread_mutex_unlock( &(cont->convert_mutex) );

  }

        

}