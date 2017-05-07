#include <unistd.h>
#include <stdio.h>
#include "pa1.h"
#include "ipc.h"

#define  DEFAULT_NPROCESSES 10
local_id nprocesses = DEFAULT_NPROCESSES;

typedef struct {
    local_id n;
    int ***pipes;
} __attribute__((packed)) table_of_papes;


int create_table(local_id n, table_of_papes* table){
    int ***pipes = new int[nprocesses][nprocesses][2];
    if (pipes==NULL)
        return -1;

    for (size_t i = 0; i < nprocesses+1; i++)
        for (size_t j = 0; j < nprocesses+1; j++) {
            if (pipe(pipes[i][j]) == -1) {
                perror("pipe");
                exit(EXIT_FAILURE);
            }
        }

    table->n = n;
    table->pipes = pipes;
    return  0;
}


int create_childs(table_of_papes* table) {
    for (size_t i = 0; i < nprocesses; i++){
        pid_t cpid = fork();
        if (cpid == -1){
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if (cpid == 0)//child
            return i+1;
    }
    return 0;
}


int calc_nprocesses(int argc, char * args[]){
    for(size_t optid = 1 ; optid < argc; optid++)
        if( args[optid][0] == "-" && args[optid][1] == "p")
        if ( argc > optid+1)
            return int(argc[optid + 1]);
        else
            return -1;

    return  DEFAULT_NPROCESSES;
}

int exec_child(local_id lpid, table_of_papes* table) {
    start(pipes, lpid);
    doWork(pipes, lpid);
    before_exit(pipes, lpid);
    exit(EXIT_SUCCESS);
}



int start(int*** pipes, local_id lpid){
    fprintf(f, log_started_fmt, lpid, getpid(), getppid());
    fprintf(stdout, log_started_fmt, lpid, getpid(), getppid());

    send_multicast(pipes,)


}



int main(int argc, char * args[]) {

    local_id nprocesses = calc_nprocesses(argc, args);
    if (nprocesses == -1) {
        fprintf(stderr, "Usage: %s [-p number_of_processes]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    table_of_papes main_table;
    if (create_table(nprocesses, &main_table) == -1) {
        perror("new pipes");
        exit(EXIT_FAILURE);
    }


    local_id lpid = create_childs(&main_table);

    if (lpid != 0)
        exec_child(lpid,main_table);
    else {//parent
        
    }
    return 0;
}