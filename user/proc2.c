#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"


int 
main(int argc, char *argv[]) 
{
    void *ptr_arr1;
    int *arr1, *arr2;

    if (get_shared("arr1", &ptr_arr1) < 0) {
        fprintf(2, "proc2: get_shared\n");
        fprintf(2, "shmemtest: exectest FAIL\n");
        exit();
    }

    arr2 = malloc(100 * sizeof(int));

    if (share_mem("arr2", arr2, 100 * sizeof(int)) < 0) {
        fprintf(2, "proc2: share_mem\n");
        fprintf(2, "shmemtest: exectest FAIL\n");
        goto end;
    }

    arr1 = (int *) ptr_arr1;
    for (int i = 10; i < 20; i++) {
        arr1[i] = i;
        arr2[i - 10] = i + 90;
    }
    
    if (fork() == 0) {
        char *argv1[] = {"/bin/proc3", 0};
        exec("/bin/proc3", argv1);

        fprintf(2, "proc2: exec\n");
        fprintf(2, "shmemtest: exectest FAIL\n");
    }
    else {
        wait();
    }

end:
    free(arr2);
    exit();
}
