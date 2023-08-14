#include "kernel/fcntl.h"
#include "kernel/types.h"
#include "user.h"

#define check_error(cond, msg) { \
	if (!(cond)) { \
		printf(msg); \
		exit(); \
	} \
}


int 
min(int a, int b) {
    return a > b ? b : a;
}

void
change_buf(char buf[], char ch, int len) {
	for (int i = 0; i < len; i++) {
		buf[i] = ch;
	}
}

int
main(int argc, char *argv[]) {

	check_error(argc == 3, "Not enough parameters\n");

	int fd = open(argv[1], O_CREATE | O_WRONLY);
	check_error(fd != -1, "Can't create fd\n");
	
	int cnt = atoi(argv[2]);

	char ch = argv[1][0];
	char buf[512];
	change_buf(buf, ch, 512);
	while (cnt > 0) {
		int to_write = min(cnt, 512);

		check_error(write(fd, buf, to_write) == to_write, "Failed to write\n");

		cnt -= to_write;
		if (cnt > 0) {
			ch++;
			change_buf(buf, ch, 512);
		}
	}
	
	close(fd);
	
	exit();
}
