#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * Demonstrates the problems with relying on the
 * lseek+read/write pattern for file descriptors.
 *
 * Use the atomic pread/pwrite calls to avoid these
 * race conditions
 */

void *write_first_byte(void *param)
{
	int *fd = param;
	char byte = 1;
	lseek(*fd, 0, SEEK_SET);
	(void)write(*fd, &byte, 1);
	return 0;
}

void *write_second_byte(void *param)
{
	int *fd = param;
	char byte = 2;
	lseek(*fd, 1, SEEK_SET);
	(void)write(*fd, &byte, 1);
	return 0;
}

int main()
{
	char tmpfile_template[] = "file-raceXXXXXX";
	int fd = mkstemp(tmpfile_template);
	if (fd < 0)
		return 1;

	for (;;) {
		pthread_t
			thread1 = { 0 },
			thread2 = { 0 };

		if (pthread_create(&thread1, 0, write_first_byte, &fd))
			return 1;
		if (pthread_create(&thread2, 0, write_second_byte, &fd))
			return 1;
		pthread_join(thread2, 0);
		pthread_join(thread1, 0);

		off_t current = lseek(fd, 0, SEEK_CUR);
		if (current >= 3)
			printf("both threads wrote after thread2 lseek, current: %ld\n", current);

		char byte = 0;
		lseek(fd, 0, SEEK_SET);
		read(fd, &byte, 1);
		if (byte != 1)
			printf("first byte wasn't thread1 value: %d\n", byte);
		read(fd, &byte, 1);
		if (byte != 2)
			printf("second byte wasn't thread2 value: %d\n", byte);
	}
}

