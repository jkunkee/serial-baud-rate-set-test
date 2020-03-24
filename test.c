
#include <stdio.h>
#include <termios.h>
#include <fcntl.h>

#define CHECK_POSIX_CALL(expr) \
{ \
	int errVal; \
	printf("Attempting to execute '%s'\n", #expr); \
	errVal = expr; \
	if (errVal < 0) { \
	perror(#expr " failed"); \
	return errVal; } \
}

int main(int argc, char** argv)
{
	char* ttyFileName;
	int fd;
	struct termios options;
	int errVal;

	ttyFileName = (argc >= 2 ? argv[1] : "/dev/ttyS2");

	printf("Attempting to open %s\n", ttyFileName);

	// based on https://www.cmrr.umn.edu/~strupp/serial.html
	fd = open(ttyFileName, O_RDWR | O_NOCTTY | O_NDELAY);
	if (fd < 0) { perror("opening TTY failed"); return fd; }

	printf("Setting baud rate to B115200\n");
	CHECK_POSIX_CALL(tcgetattr(fd, &options));
	options.c_cflag     |= (CLOCAL | CREAD);
	cfsetispeed(&options, B115200);
	cfsetospeed(&options, B115200);
	CHECK_POSIX_CALL(tcsetattr(fd, TCSANOW, &options));

	printf("Setting baud rate to B460800\n");
	CHECK_POSIX_CALL(tcgetattr(fd, &options));
	options.c_cflag     |= (CLOCAL | CREAD);
	cfsetispeed(&options, B460800);
	cfsetospeed(&options, B460800);
	CHECK_POSIX_CALL(tcsetattr(fd, TCSANOW, &options));

	printf("Done.\n");
	return 0;
}

