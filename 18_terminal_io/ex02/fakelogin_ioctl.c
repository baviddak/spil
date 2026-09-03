/* Implement the fakelogin.c program using ioctl rather than the termios
 * interface.
 */

#include <termios.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>

const char loginstr[] = "login: "; /* Prompt for login */
const char passwdstr[] = "password: "; /* Prompt for password */

int main(int argc, char *argv[])
{

	struct termios tt; 
	char username[33]; 
	char passwd[33];
	int ttyfd, n; 

	if ( -1 == (ttyfd = open("/dev/tty", O_RDWR)) ) {
		fprintf(stderr, "Error in open(): %s\n", strerror(errno) );
		exit(EXIT_FAILURE);
	}

	memset(username, 0, 33); 
	memset(passwd, 0, 33); 

	write(ttyfd, loginstr, strlen(loginstr)); 

	n = read(ttyfd, username, 32); 

	if ( username[n-1] == '\n' ) {
		username[n-1] = '\0'; /* Get rid of \n at end. */
	}

	/* tcflush(ttyfd, TCIFLUSH); */

	if ( ioctl(ttyfd, TCFLSH, TCIFLUSH) == -1 ) {
		fprintf(stderr, "Error in ioctl(): %s\n", strerror(errno));
		exit(EXIT_FAILURE);	
	}

	/* tcgetattr(ttyfd, &tt); */
	if ( ioctl(ttyfd, TCGETS, &tt) == -1 ) {
		fprintf(stderr, "Error in ioctl(): %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	
	tt.c_lflag &= ~ECHO; /* Turn off echo bit. */

	/* tcsetattr(ttyfd, TCSANOW, &tt); */
	if ( ioctl(ttyfd, TCSETS, &tt) == -1 ) {
		fprintf(stderr, "Error in ioctl(): %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	write(ttyfd, passwdstr, strlen(passwdstr)); /* Display prompt. */
	n = read(ttyfd, passwd, 32); /* Get user's hidden typing. */

	if ( passwd[n-1] == '\n' ) {
		passwd[n-1] = '\0'; /* Get rid of \n at end. */
	}

	/* tcflush(ttyfd, TCIFLUSH); */
	if ( ioctl(ttyfd, TCFLSH, TCIFLUSH) == -1 ) {
		fprintf(stderr, "Error in ioctl(): %s\n", strerror(errno));
		exit(EXIT_FAILURE);	
	}
	tt.c_lflag |= ECHO; /* Turn echo on. */
	/* tcsetattr(ttyfd, TCSAFLUSH, &tt); */
	if ( ioctl(ttyfd, TCSETSF, &tt) == -1 ) {
		fprintf(stderr, "Error in ioctl(): %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	printf("\nUser %s entered %s as a password.\n", username, passwd);

	return 0;
}
