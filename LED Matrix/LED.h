#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include <errno.h>
#include <sys/time.h>
#include <errno.h>

#include "Screen.h"
/*** GLOBAL VARIABLE ***/
/* GPIO PATH */
#define GPIO_PATH "/sys/class/gpio/"

/* GPIO Pins Definition */
#define RED1_PIN 67     // UPPER
#define GREEN1_PIN 66
#define BLUE1_PIN 68
#define RED2_PIN 44 // LOWER
#define GREEN2_PIN 69
#define BLUE2_PIN 26
#define CLK_PIN 27      // Arrival of each data
#define LATCH_PIN 47    // End of a row of data
#define OE_PIN 61       // Transition from one row to another
#define A_PIN 46        // Row select
#define B_PIN 45
#define C_PIN 65

#define S_IWRITE "S_IWUSR"

/* TIMING */
#define DELAY_IN_US 2
#define DELAY_IN_SEC 0

/* FILES HANDLER */
static int fileDesc_red1;
static int fileDesc_blue1;
static int fileDesc_green1;
static int fileDesc_red2;
static int fileDesc_blue2;
static int fileDesc_green2;
static int fileDesc_clk;
static int fileDesc_latch;
static int fileDesc_oe;
static int fileDesc_a;
static int fileDesc_b;
static int fileDesc_c;

// timer static variables
static struct timespec wait; // declares timespec structs
static uint64_t period_ns = 2000; // 0.0002 s

/**
 * exportAndOut
 * Export a pin and set the direction to output
 * @params
 *  int pinNum: the pin number to be exported and set for output
 */
void exportAndOut(int pinNum);

/**
 * ledMatrix_setupPins
 * Setup the pins used by the led matrix, by exporting and set the direction to out
 */
void ledMatrix_setupPins(void);

/** 
 *  ledMatrix_clock
 *  Generate the clock pins
 */
void ledMatrix_clock(void);

/**
 *  ledMatrix_latch
 *  Generate the latch pins
 */
void ledMatrix_latch(void);

/**
 *  ledMatrix_bitsFromInt
 *  Convert integer passed on into bits and put in array
 *  @params:
 *      int * arr: pointer to array to be filled with bits
 *      int input: integer to be converted to bits
 */
void ledMatrix_bitsFromInt(int * arr, int input);

/**
 *  ledMatrix_setRow
 *  Set LED Matrix row
 *  @params:
 *      int rowNum: the rowNumber to be inputted to row pins
 */
void ledMatrix_setRow(int rowNum);

/**
 *  ledMatrix_setColourTop
 *  Set the colour of the top part of the LED
 *  @params:
 *      int colour: colour to be set
 */
void ledMatrix_setColourTop(int colour);

/**
 *  ledMatrix_setColourBottom
 *  Set the colour of the bottom part of the LED
 *  @params:
 *      int colour: colour to be set
 */
void ledMatrix_setColourBottom(int colour);

/**
 *  ledMatrix_refresh
 *  Fill the LED Matrix with the respective pixel colour
 */
void ledMatrix_refresh(struct screen * s);

// timer functions
void start_periodic_timer();
void wait_next_activation();
void timespec_add_ns(struct timespec *t, uint64_t delta);