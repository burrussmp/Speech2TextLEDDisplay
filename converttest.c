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

int flag;
char* message;

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

    printf("%d\n", cont->curDec);
    printf("%d\n", cont->curRec);
    printf("%s\n", cont->files[0]);

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
    cont->curDec = 1;
    cont->curRec = 0;
    cont->readyToDecode = 0;
}

void *decode_audio(void* param){

  struct control* cont  = (struct control*) param;

  while (flag == 0){
    usleep(10);
  }

  while (1){
    sem_wait(&convertSem);
    printf("****************");//%s \n", message);

    sem_post(&convertSem);
    usleep(10000);
  }
  return (void*)1;
}

void *record_audio(void* param){

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


    int i = 0;
    while (1) {

        if (ps == NULL) {
            fprintf(stderr, "Failed to create recognizer, see log for details\n");
            return -1;
        }
        system("arecord -f S16_LE -r22100 -D hw:1,0 -d 2 continuous.raw");

        printf("Done recording");

        fflush(stdout);

        fh = fopen("continuous.raw", "rb");
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
    }

  cmd_ln_free_r(config);

}