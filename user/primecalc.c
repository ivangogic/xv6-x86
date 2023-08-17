#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"


#define VOIDPTR2INT(a) (*((int *) (a)))

int
isPrime(int n)
{
    // Check if n=1 or n=0
    if (n <= 1)
        return 0;
    // Check if n=2 or n=3
    if (n == 2 || n == 3)
        return 1;
    // Check whether n is divisible by 2 or 3
    if (n % 2 == 0 || n % 3 == 0)
        return 0;
    // Check from 5 to square root of n
    // Iterate i by (i+6)
    for (int i = 5; i * i <= n; i = i + 6)
        if (n % i == 0 || n % (i + 2) == 0)
            return 0;
 
    return 1;
}

int 
main(void)
{
    int n = 2, n_stop = 1;
    void *ptr_arr, *ptr_cnt, *ptr_cmd;
    if (get_shared("arr", &ptr_arr) < 0 ||
        get_shared("cnt", &ptr_cnt) < 0 ||
        get_shared("cmd", &ptr_cmd) < 0
    ) {
        fprintf(2, "primecalc: get_shared\n");
        exit();
    }

    int ind = 0, ind1 = 1;  
    while (1) {
        if (ind && ind1) {
            if (isPrime(n)) {
                int *arr = (int *) ptr_arr;
                int cnt = VOIDPTR2INT(ptr_cnt);
                arr[cnt] = n;
                (*((int *) ptr_cnt))++;
                
                if (cnt == 99999)
                    ind1 = 0;
            }
            n++;
        }

        int cmd = VOIDPTR2INT(ptr_cmd);
        if (cmd == 5 || ind1 == 0)
            break;    
        if (cmd == 3)
            ind = 0;
        if (cmd == 4)
            ind = 1;
        
        // In case primecom doesn't signal
        if (ind == 0) {
            n_stop++;
            if (n_stop == 3000)
                break;
        }
        sleep(1);
    }

    exit();
}
