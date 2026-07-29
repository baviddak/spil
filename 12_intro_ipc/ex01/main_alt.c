#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main() {
	fprintf(stdout, "The maximum value a semaphore can have is %d\n", SEM_VALUE_MAX);
	exit(EXIT_SUCCESS);
}
