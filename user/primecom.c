#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"


#define VOIDPTR2INT(a) (*((int *) (a)))

int 
main(void)
{
    void *ptr_arr, *ptr_cnt, *ptr_cmd;
    if (get_shared("arr", &ptr_arr) < 0 ||
        get_shared("cnt", &ptr_cnt) < 0 ||
        get_shared("cmd", &ptr_cmd) < 0
    ) {
        fprintf(2, "primecom: get_shared\n");
        exit();
    }

    *((int *) ptr_cmd) = 4;

    char usage[] = "Usage:\n\tprime <n>\n\tlatest\n\tpause\n\tresume\n\tend\n";
    printf("%s\n", usage);

	while (1) {
		char buf[100];
		char command[40], arg[20];

		gets(buf, 100);

        int i = 0, cb, ce = -1, pos1 = -1, pos2 = -1;
        while (buf[i] == ' ')
            i++;
        cb = i;
        for (; i < 100; i++)
            if (buf[i] == '\0')
                break;
            else if (buf[i] == ' ') {
                if (pos1 == -1) {
                    ce = i;
                    pos1 = i;
                }
                else {
                    if (pos1 == i - 1)
                        pos1 = i;
                    else {
                        if (pos2 == -1)
                            pos2 = i;      
                    }
                }
            }

        if (pos1 != -1 && pos1 != i - 2) {
            safestrcpy(command, buf + cb, ce - cb + 1);
            pos2 = pos2 == -1 ? i - 1 : pos2;
            safestrcpy(arg, buf + pos1 + 1, pos2 - pos1);

            if (strcmp(command, "prime") != 0) {
                printf("Command not valid\n%s\n", usage);
                continue;
            }

            int n = atoi(arg), cnt = VOIDPTR2INT(ptr_cnt);
            int *arr = (int *) ptr_arr;

            if (n == 0 || n > 100000) {
                printf("<n> is in range [1, 100000]\n");
                continue;
            }
            if (n > cnt) {
                printf("Prime number no. %d still isn't calculated\n", n);
                continue;
            }
            printf("%d\n", arr[n - 1]);
        }
        else {
            ce = ce == -1 ? i - 1 : ce;
            safestrcpy(command, buf + cb, ce - cb + 1);

            if (strcmp(command, "latest") == 0){
                int cnt = VOIDPTR2INT(ptr_cnt);
                int *arr = (int *) ptr_arr;

                if (cnt == 0)
                    printf("No primes currently found\n");
                else
                    printf("%d, prime no. %d\n", arr[cnt - 1], cnt);		
            }
            else if (strcmp(command, "pause") == 0){
                *((int *) ptr_cmd) = 3;
            }
            else if (strcmp(command, "resume") == 0){
                *((int *) ptr_cmd) = 4;
            }
            else if (strcmp(command, "end") == 0){
                *((int *) ptr_cmd) = 5;
                break;
            }
            else {
                printf("Command not valid\n%s\n", usage);
            }
        }
	}
    
    exit();
}
