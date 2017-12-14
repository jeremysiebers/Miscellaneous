/* 
 * File:   sequence.h
 * Author: Jeremy
 *
 * Created on December 29, 2012, 1:24 PM
 */

#ifndef SEQUENCE_H
#define	SEQUENCE_H

#define NO_OF_SEQUENCES 362                                                     // Max sequences 3230 with optimization (subract 20 from line number in sequence.c)

// Subtract 21 for index number of struct array //
#define MAIN_START 0
#define RANDOM_START 46
#define ALL_LED_ON 48
#define ALL_LED_OFF 50
#define SLOW_BLINK_ALL_LED 52
#define SPIRAL_CLK_WISE_ON 54
#define SPIRAL_CCLK_WISE_OFF 95
#define SLOW_BLINK_CNTR_LED 136
#define CNTR_LED_OFF 141

#define TW0_ON 146
#define TW1_ON 164
#define TW2_ON 174
#define TW3_ON 184
#define TW4_ON 194
#define TW5_ON 212
#define TW6_ON 222
#define TW7_ON 232
#define TW0_OFF 155
#define TW1_OFF 169
#define TW2_OFF 179
#define TW3_OFF 189
#define TW4_OFF 203
#define TW5_OFF 217
#define TW6_OFF 227
#define TW7_OFF 237

#define SLOW_BLINK_OUT_LED 242
#define SLOW_BLINK_BL_LED 251
#define LINE_AROUND_ON 260
#define LINE_AROUND_OFF 293
#define WINK_ON 326
#define WINK_OFF 339
#define FINISHED 0xFFFF
#define DELAY1 352
#define DELAY2 354
#define DELAY3 356
#define DELAY4 358
#define DELAY5 360

typedef struct
{
    unsigned long int Prog:4;                                                   // Holds the program type to run
    unsigned long int Led:6;                                                    // Holds the number of leds to turn on
    unsigned long int Speed:8;                                                  // Holds the speed setting for a program type
    unsigned long int Time1:8;                                                  // Holds the first part of the execution time for a program, bitfield max is 1 byte
    unsigned long int Time2:8;                                                  // Holds the second part of the execution time

}SEQUENCE;

extern const rom SEQUENCE Sequence[NO_OF_SEQUENCES];

#endif	/* SEQUENCE_H */

