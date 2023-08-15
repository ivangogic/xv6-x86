#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "kernel/fs.h"


void
solve (char* path)
{
	int res = rec(path);
	switch (res)
	{
	case -11:
		printf("sys_rec: argstr\n");
		break;
	case -1:
		printf("sys_rec: parent\n");
		break;
	case -2:
		printf("sys_rec: path\n");
		break;
	case -3:
		printf("Cannot recover %s. Inode has been reused.\n", path);
		break;
	case -4:
		printf("Cannot recover %s. Some blocks have been reused.\n", path);
		break;
	default:
		break;
	}
}

int
main(int argc, char *argv[])
{
	if (argc == 2) {
		solve(argv[1]);
	}
    else {
        fprintf(2, "Usage: rec path/to/file\n");
	}

	exit();
}
