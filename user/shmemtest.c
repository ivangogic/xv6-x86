#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"


void
forktest()
{
    int *arr = malloc(100000 * sizeof(int));

    if (share_mem("arr", arr, 100000 * sizeof(int)) < 0) {
        fprintf(2, "shmemtest: forktest - share_mem\n");
        fprintf(2, "shmemtest: forktest FAIL\n");
        goto end;
    }

    if (fork() == 0) {
        void *ptr_arr;
        if (get_shared("arr", &ptr_arr) < 0)
            printf("shmemtest: forktest OK\n");
        else {
            fprintf(2, "shmemtest: forktest - get_shared\n");
            fprintf(2, "shmemtest: forktest FAIL\n");
        }
        
        exit();
    }
    else {
        wait();
    }

end:
    free(arr);
    return;
}

void
exectest()
{
    if (fork() == 0) {
        char *argv1[] = {"/bin/proc1", 0};
        exec("/bin/proc1", argv1);

        fprintf(2, "shmemtest: exectest - exec\n");
        fprintf(2, "shmemtest: exectest FAIL\n");
    }
    else {
        wait();
    }

    return;
}

int 
main(int argc, char *argv[]) 
{
    forktest();
    exectest();

    exit();
}
