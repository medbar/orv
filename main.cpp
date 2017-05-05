#include <unistd.h>
#include <stdio.h>
#include "pa1_starter_code/pa1.h"

#define  DEFAULT_NPROCESSES 10

int calc_nprocesses(int argc, char * args[]){
    for(size_t optid = 1 ; optid < argc; optid++)
        if( args[optid][0] == "-" && args[optid][1] == "p")
            if ( argc > optid+1)
                return int(argc[optid+1]);
            else
                return -1;

    return  DEFAULT_NPROCESSES;
}

int main(int argc, char * args[]) {

    int nprocesses = calc_nprocesses( argc, args);
    if (nprocesses==-1){
        fprintf(stderr, "Usage: %s [-p number_of_processes]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    

    return 0;
}