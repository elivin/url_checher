#define ARGS 19

#include "checker.hh"
#include <stdio.h>
#include <string.h>


int main(int argc, char *argv[]) {
	int i;
	thread_arg args[ARGS];

	printf("----- Test URL Checker -----\n");
	printf("--- Test data ---\n");
	for (i = 0; i < ARGS; i++) {
		args[i].status = 0;
		args[i].url = strdup("http://nihilis1.myihor.ru/");
		printf("- Status: %d; URL: %s\n", args[i].status, args[i].url);
	}

	printf("\n--- Total ---\n");
	check_all_urls(args, ARGS);
	for (i = 0; i < ARGS; i++) {
		printf("-[%d] Status: %d; URL: %s\n", i, args[i].status, args[i].url);
	}

	for (i = 0; i < ARGS; i++) {
		free(args[i].url);
	}

	return 0;
}

