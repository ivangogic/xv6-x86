#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "kernel/fs.h"


void
solve (char* path)
{
    char buf[64][DIRSIZ + 1];
	int num_del;
	int fd;
	struct stat st;

	if((fd = open(path, 0)) < 0){
		fprintf(2, "lsdel: cannot open %s\n", path);
		return;
	}

	if(fstat(fd, &st) < 0){
		fprintf(2, "lsdel: cannot stat %s\n", path);
		close(fd);
		return;
	}

    switch(st.type){
        case T_FILE:
            fprintf(2, "Path to dir required\n");
            break;

        case T_DIR:
            num_del = lsdel(path, (char*)buf);

            if (num_del <= 0)
                printf("Nothing to recover in this dir\n");
            else {
                for (int i = 0; i < num_del; i++)
                    printf("%s ", buf[i]);
                printf("\n");
            }

            break;
	}
	close(fd);
}

int
main(int argc, char *argv[])
{
	if (argc < 2) {
		solve(".");
	}
	else if (argc == 2) {
        solve(argv[1]);
	}
    else {
        fprintf(2, "Usage: lsdel [path/to/dir]\n");
	}
	exit();
}
