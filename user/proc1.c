#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"


int 
main(int argc, char *argv[]) 
{
    int *arr1 = malloc(100 * sizeof(int));

    if (share_mem("arr1", arr1, 100 * sizeof(int)) < 0) {
        fprintf(2, "proc1: share_mem\n");
        fprintf(2, "shmemtest: exectest FAIL\n");
        goto end;
    }

    for (int i = 0; i < 10; i++)
        arr1[i] = i;
    
    if (fork() == 0) {
        char *argv1[] = {"/bin/proc2", 0};
        exec("/bin/proc2", argv1);

        fprintf(2, "proc1: exec\n");
        fprintf(2, "shmemtest: exectest FAIL\n");
    }
    else {
        wait();
    }

end:
    free(arr1);
    exit();
}
