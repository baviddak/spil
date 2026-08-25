#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>

int main( int argc, char *argv[] ) {
	
	int cfd, sfd, connectval;
	struct addrinfo hints;
	struct addrinfo *rp;
	int gai_ret;
	char *node = argv[1];
	char *service = argv[2];
	char hostbuffer[INET_ADDRSTRLEN];
	memset(hostbuffer, '\0', INET_ADDRSTRLEN);
	struct sockaddr_in *sap;
	
	memset(&hints, 0, sizeof(struct addrinfo));	
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = 0;
	hints.ai_flags = AI_NUMERICHOST;
	hints.ai_addrlen = 0;
	hints.ai_addr = NULL;
	hints.ai_canonname = NULL;
	hints.ai_next = NULL;	
	
	if ( (gai_ret = getaddrinfo(node, service, &hints, &rp)) != 0 ) {
		fprintf(stderr, "Error in getaddrinfo(): %s\n", gai_strerror(gai_ret));
		return -1;
	}

	struct sockaddr_in claddr;
	socklen_t slen = sizeof(struct sockaddr_in);

	while ( rp != NULL ) {
		fprintf(stdout, "found an address!\n");
		if ( rp->ai_family == AF_INET ) {
			fprintf(stdout, "the family is AF_INET\n");
		}
		if ( rp->ai_family == AF_INET6 ) {
			fprintf(stdout, "the family is AF_INET6\n");
		}
		if ( rp->ai_socktype == SOCK_STREAM ) {
			fprintf(stdout, "the socktype is SOCK_STREAM\n");
		}
		
		sap = (struct sockaddr_in *)rp->ai_addr;
			
		fprintf(stdout, "the address is %s\n", inet_ntop(AF_INET, (void *)&sap->sin_addr, hostbuffer, INET_ADDRSTRLEN));
		fprintf(stdout, "the port is %d\n", ntohs(sap->sin_port));

		/* try to create the socket, continue if it fails */
		sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
		if ( sfd == -1 ) {
			fprintf(stderr, "error in socket(): %s\n", strerror(errno));
			continue;
		}
		connectval = connect(sfd, rp->ai_addr, rp->ai_addrlen);
		if ( connectval == -1 ) {
			fprintf(stdout, "connect failed\n");
			continue;
		} else {
			fprintf(stdout, "successfully connected!\n");
			break;
		}
		
		
		rp = rp->ai_next;
	}
	if ( connectval == -1 ) {
		fprintf(stderr, "error in bind(), exiting program\n");
		return -1;
	}
	
	/* no longer needed */
	freeaddrinfo(rp);

	/* 
	 * socket
	 * connect
	 * write / read 
	 * close
	 */

	ssize_t num_bytes;
	char buffer[256];

	while ( 1 ) {
		num_bytes = read(STDIN_FILENO, buffer, 256);
		if ( num_bytes <= 0) {
			break;
		}
		num_bytes = write(sfd, buffer, num_bytes);
		if ( num_bytes <= 0 ) {
			break;
		}
	}
	
	close(sfd);
	
	return 0;
}
