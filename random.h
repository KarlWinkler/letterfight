#ifndef RANDOM_H
#define RANDOM_H

#include <sys/time.h>
#include <stdio.h>

// My random because I was too lazy to figure out the default one
// and I thought it should be a good experiment to try to make something
// that is at least somewhat random

// not perfect but it gets the job done
int random_int(int max){
    struct timeval time;

    //get time as microseconds since unix epoch
    gettimeofday(&time, NULL);

    // to add a small element of randomness so not everything is in order
    usleep(23); 

    return (int)time.tv_usec % max;
}

// not used yet(maybe later but probably not)
int random_range(int min, int max){
    struct timeval time;

    //get time as microseconds since unix epoch
    gettimeofday(&time, NULL);

    // datetime modulo delta range added to min
    // leaves negative modulo unhandled
    usleep(23);
    return (min + (int)time.tv_usec % (max - min + 1));
    
}

#endif