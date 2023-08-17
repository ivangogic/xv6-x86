#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"


int 
main(int argc, char *argv[]) 
{
    int *arr = malloc(100000 * sizeof(int));
    int cnt = 0, cmd = 0;
    
    if (share_mem("arr", arr, 100000 * sizeof(int)) < 0 ||
        share_mem("cnt", &cnt, sizeof(cnt)) < 0 ||
        share_mem("cmd", &cmd, sizeof(cmd)) < 0
    ) {
        fprintf(2, "primestart: share_mem\n");
        goto end;
    }
    
    if (fork() == 0) {
        char *argv1[] = {"/bin/primecalc", 0};
        exec("/bin/primecalc", argv1);

        fprintf(2, "primestart: exec\n");
    }
    else {
        if (fork() == 0) {
            char *argv2[] = {"/bin/primecom", 0};
            exec("/bin/primecom", argv2);

            fprintf(2, "primestart: exec\n");
        }
        else {
            wait();
            wait();
        }
    }

end:
    free(arr);
    exit();
}
