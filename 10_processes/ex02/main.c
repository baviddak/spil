#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#include "getparentid.h"

struct pidlineage {
	int lineage[100];
	int size;
};

void construct_pid_lineage(struct pidlineage *pidl, pid_t pd) {

	pidl->lineage[0] = pd;
	pidl->size = 1;

	pid_t nextpd = pd;

	int counter = 1;
	while ( 1 ) {
		nextpd = getparentid(nextpd);
		pidl->lineage[counter] = nextpd;
		pidl->size++;
		counter++;

		if (pidl->size > 99) {
			break;
		}

		if (nextpd == 1) {
			break;
		}
	}
}


void print_pid_lineage(const struct pidlineage *pidl) {

	for (int i = 0; i < pidl->size; i++) {
		printf("%d\n", pidl->lineage[i]);
	}
}


int main(int argc, char *argv[]) {

	if ( argc != 3 ) {
		fprintf(stderr, "Usage: nca p1 p2\n");
		exit(EXIT_FAILURE);
	}


	pid_t p1 = atoi(argv[1]);
	pid_t p2 = atoi(argv[2]);

	struct pidlineage p1_lin;
	struct pidlineage p2_lin;

	p1_lin.size = 0;
	p2_lin.size = 0;

	construct_pid_lineage(&p1_lin, p1);
	construct_pid_lineage(&p2_lin, p2);

	bool breakout = false;
	for ( int i = 0; i < p1_lin.size; i++) {
		for ( int j = 0; j < p2_lin.size; j++) {
			if ( p1_lin.lineage[i] == p2_lin.lineage[j] ) {
				printf("The nearest common ancestor is %d\n", p1_lin.lineage[i]);
				breakout = true;
				break;
			}
		}
		if (breakout == true) {
			break;
		}
	}

	return 0;
}
