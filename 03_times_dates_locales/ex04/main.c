/* 
 * The locale command without any arguments or options prints out the values
 * of the categories in the current locale. Write a program that does this.
 */

#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <langinfo.h>

int main() {

	if ( setlocale(LC_ALL, "") == NULL ) {
		fprintf(stderr, "Error in calling setlocale()\n");
		exit(EXIT_FAILURE);
	}

	/* fprintf(stdout, "LANG=%s\n", nl_langinfo(LANG)); */
	/* fprintf(stdout, "LANGUAGE=%s\n", nl_langinfo(_NL_LOCALE_NAME(LC_CTYPE))); */
	fprintf(stdout, "LC_CTYPE=%s\n", nl_langinfo(_NL_LOCALE_NAME(LC_CTYPE)));
	fprintf(stdout, "LC_NUMERIC=%s\n", nl_langinfo(_NL_LOCALE_NAME(LC_NUMERIC)));
	fprintf(stdout, "LC_TIME=%s\n", nl_langinfo(_NL_LOCALE_NAME(LC_TIME)));
	fprintf(stdout, "LC_COLLATE=%s\n", nl_langinfo(_NL_LOCALE_NAME(LC_COLLATE)));
	fprintf(stdout, "LC_MONETARY=%s\n", nl_langinfo(_NL_LOCALE_NAME(LC_MONETARY)));
	fprintf(stdout, "LC_MESSAGES=%s\n", nl_langinfo(_NL_LOCALE_NAME(LC_MESSAGES)));
	fprintf(stdout, "LC_PAPER=%s\n", nl_langinfo(_NL_LOCALE_NAME(LC_PAPER)));
	fprintf(stdout, "LC_NAME=%s\n", nl_langinfo(_NL_LOCALE_NAME(LC_NAME)));
	fprintf(stdout, "LC_ADDRESS=%s\n", nl_langinfo(_NL_LOCALE_NAME(LC_ADDRESS)));
	fprintf(stdout, "LC_TELEPHONE=%s\n", nl_langinfo(_NL_LOCALE_NAME(LC_TELEPHONE)));
	fprintf(stdout, "LC_MEASUREMENT=%s\n", nl_langinfo(_NL_LOCALE_NAME(LC_MEASUREMENT)));
	fprintf(stdout, "LC_IDENTIFICATION=%s\n", nl_langinfo(_NL_LOCALE_NAME(LC_IDENTIFICATION)));
	fprintf(stdout, "LC_ALL=%s\n", nl_langinfo(_NL_LOCALE_NAME(LC_ALL)));

	exit(EXIT_SUCCESS);
}
