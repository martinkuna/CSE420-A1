/*
 * Assignment #1 for CSE 420: Computer Architecture I
 * 
 * MARTIN KUNA (<REMOVED>)
 * ID: <REMOVED>
 */

#include <stdio.h>  // std in/out for prints
#include <stdlib.h> // needed for function exit
#include <time.h>   // Needed for clock_gettime
#include <unistd.h> // Needed for getopt

//Do not uncomment line below unless DEBUGGING
//#define DEBUG
#ifdef DEBUG
static unsigned int const ARRAY_MAX_POWER = 16;       //Array size max 2^(MAX_POWER)
#endif
static unsigned int const ARRAY_ITERATIONS = 10000;  //times to iterate accross all tests

struct element{
    int x;
    int padding[15];
};

struct timespec start, stop;

struct timespec difference(struct timespec start, struct timespec end){
    struct timespec temp;
    if ((end.tv_nsec-start.tv_nsec)<0){
        temp.tv_sec = end.tv_sec-start.tv_sec-1;
        temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
    } else {
        temp.tv_sec = end.tv_sec-start.tv_sec;
        temp.tv_nsec = end.tv_nsec-start.tv_nsec;
    }

    return temp;
}

/* Linear write
 *
 */
void linearWrite(unsigned long power){
    size_t size = 1 << power;
    printf("\n::ARRAY SIZE = %lu", size);
    struct element array[size];
    unsigned i, j;

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
    for(i = 0; i < ARRAY_ITERATIONS; i++){
        for(j = 0; j < size; j++){
            array[j].x = 139021;
        }
    }
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &stop);
    
    printf("\nStart timespec (ns)\t%ld", start.tv_nsec);
    printf("\nStop timespec (ns)\t%ld", stop.tv_nsec);
    printf("\nDifference timespec(ns)\t%ld", difference(start, stop).tv_nsec);
    printf("\nAvg access time (ns)\t%ld", difference(start,stop).tv_nsec/(size*ARRAY_ITERATIONS));
    // garbage to use the array and avoid error for now
    printf("\n\tArrayFill Value %d\n", array[0].x);
}

/* linear read
 *
 */
void linearRead(){

}

/* randWrite
 *
 */
void randWrite(){

}

/* randRead
 *
 */
void randRead(){

}

void testSleep(){

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
    sleep(2);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &stop);

    printf("\nStart nsec\t%ld", start.tv_nsec);
    printf("\nStop  nsec\t%ld", stop.tv_nsec);
    printf("\nDiff  nsec\t%ld", stop.tv_nsec - start.tv_nsec);
    printf("\nDiff   sec\t%ld", stop.tv_sec - start.tv_sec);
    printf("\nDiff  nsec\t%ld", difference(start, stop).tv_nsec);
    printf("\n%.10ld", difference(start,stop).tv_sec);

    printf("\nTest new calc\t%.10f", (double)(stop.tv_nsec - start.tv_nsec)/1000000000);
}

int main(int argc, char*argv[]){

    int opt;
    int mode = -1, power = -1;

    while ((opt = getopt(argc, argv, "m:p:")) != -1) {
        switch(opt) {
            case 'm':
                mode = atoi(optarg);
                break;
            case 'p':
                power = atoi(optarg);
                break;
            case '?':
                if (optopt == 'm') {
                    printf("\nMissing mandatory mode setting between 1 and 4");
                } else if (optopt == 'p') {
                    printf("\nMissing mandatory power settings for array");
                } else {
                    printf("\nInvalid option received");
                }
                break;
            default: /* '? */
                fprintf(stderr, "Usage: %s [-m 1-4] [-p 1-16]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if(mode < 1 || mode > 4 || power < 0 || power > 16){
        fprintf(stderr, "Usage: %s [-m 1-4] [-p 1-16]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    switch(mode){
        case 1:
            printf("\n[ Linear Write -- Mode %d -- Power %d]\n",mode,power);
            linearWrite(power);
            break;
        case 2:
            printf("\n[ Linear Read -- Mode %d -- Power %d]\n",mode,power);
            linearRead(power);
            break;
        case 3:
            printf("\n[ Random Write -- Mode %d -- Power %d]\n",mode,power);
            randWrite();
            break;
        case 4:
            printf("\n[ Random Read -- Mode %d -- Power %d]\n",mode,power);
            randRead();
            break;
    }

    exit(EXIT_SUCCESS);

#ifdef DEBUG
    printf("\n[ LINEAR WRITE TEST ]\n");
    unsigned int i;
    for(i=0; i <= ARRAY_MAX_POWER; i++){
        printf("\n::POWER %d",i);
        linearWrite(i);
    }

    printf("\n[ LINEAR READ TEST ]\n");
    for(i=0; i<= ARRAY_MAX_POWER; i++){
        printf("\n::POWER %d",i);
        linearRead(i);
    }

    printf("\n[ RANDOM WRITE TEST ]\n");
    for(i=0; i<= ARRAY_MAX_POWER; i++){
        printf("\n::POWER %d",i);
        randWrite(i);
    }

    printf("\n[ RANDOM READ TEST ]\n");
    for(i=0; i<= ARRAY_MAX_POWER; i++){
        printf("\n::POWER %d",i);
        randRead(i);
    }
    unsigned cycles_high, cycles_high1, cycles_low, cycles_low1;

    asm volatile ("CPUID\n\t"
            "RDTSC\n\t"
            "mov %%edx, %0\n\t"
            "mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low)::
            "%eax", "%ebx", "%ecx", "%edx");
    /***********************************/
    /*call the function to measure here*/
    /***********************************/
    asm volatile("RDTSCP\n\t"
            "mov %%edx, %0\n\t"
            "mov %%eax, %1\n\t"
            "CPUID\n\t": "=r" (cycles_high1), "=r" (cycles_low1)::
            "%eax", "%ebx", "%ecx", "%edx");


    printf("ch  >>> %u\n", cycles_high);
    printf("cl  >>> %u\n", cycles_low);
    printf("ch1 >>> %u\n", cycles_high1);
    printf("cl1 >>> %u\n", cycles_low1);


    testSleep();
#endif

    return 0;
}
