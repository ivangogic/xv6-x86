#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"


int 
main(int argc, char *argv[]) 
{
    void *ptr_arr1, *ptr_arr2;
    int *arr1, *arr2;

    if (get_shared("arr1", &ptr_arr1) < 0 ||
        get_shared("arr2", &ptr_arr2) < 0
    ) {
        fprintf(2, "proc3: get_shared\n");
        fprintf(2, "shmemtest: exectest FAIL\n");
        exit();
    }

    arr1 = (int *) ptr_arr1;
    arr2 = (int *) ptr_arr2;

    for (int i = 0; i < 20; i++) {
        if (i > 0)
            printf(" ");
        printf("%d", arr1[i]);
    }
    printf("\n");

    for (int i = 0; i < 10; i++) {
        if (i > 0)
            printf(" ");
        printf("%d", arr2[i]);
    }
    printf("\n");

    printf("shmemtest: exectest OK\n");
    exit();
}
