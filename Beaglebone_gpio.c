#include<stdio.h>
#include<stdlib.h>
#include<iolib.c>
#include <unistd.h>
#include "time.h"

static int onCount  = 0;
static int offCount = 0;

static int onTime  = 5; // in secs
static int offTime = 2; // in secs


void printTime()
{
    time_t t ;
    struct tm *tmp ;
    char MY_TIME[32];
    time( &t );

    //localtime() uses the time pointed by t ,
    // to fill a tm structure with the
    // values that represent the
    // corresponding local time.

    tmp = localtime( &t );

    // using strftime to display time
    strftime(MY_TIME, sizeof(MY_TIME), "%x - %I:%M%p", tmp);

    printf("%s\n", MY_TIME );
}



int main(void)

{
        int relay = 13;
        int discrete = 7;

        iolib_init();
        iolib_setdir(8, relay, DIR_OUT);
        iolib_setdir(8, discrete, DIR_IN);

        printf("Test In Progress\n");

        // current state
        int state = -1;

        // 1 hr x 24 hours x days
        int numLoops = 3600 * 24 * 3;

        int onCountdown = 0;

        while(numLoops--)
        {
                if ((is_high(8, discrete)) && (state != 0))
                {
                        state = 0;
                        //printf("Relay is ON.  count = %i\n", ++onCount);
                        //pin_high(8, relay);
                        //usleep(1000 * onTime);
                        printf("--> Relay is OFF. count = %i. ", ++offCount);
                        printTime();
						exit(0);
                        pin_low(8, relay);
                        onCountdown = 0;
                }
                else if ((is_low(8, discrete)) && (state != 1))
                {
                        state = 1;
                        printf("Relay is ON. count = %i\n", ++onCount);
                        pin_high(8, relay);
                        //usleep(1000 * offTime);
                        //state = 0;
                        //printf("Relay is OFF. count = %i\n", ++offCount);
                        //usleep(1000 * onTime);
                        //pin_low(8, relay);
                }
                else if ((state == 1) && (onCountdown++ == onTime))
                {
                        state = -1;
                        printf("Relay is OFF. count = %i\n", ++offCount);
                        pin_low(8, relay);
                        usleep(1000 * 1000 * offTime);
                        onCountdown = 0;
                }
        //printf("1s..\n");
        sleep(1);
        }
        iolib_free();
}
