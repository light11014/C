#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <wait.h>
#include "ku_fs_input.h"
void findStr(const char* str, int s, int n, int fd);

int main(int argc, char* argv[]) {
	const char* str = argv[1];
	const int pcount = atoi(argv[2]);
	pid_t pid[pcount];
	int N[pcount];
	int count = 0;
	int pipefd[2];
	int buf, fcount=0;
	int foundIndex[MAXS];
	int min;

	/* error */
	if(argc != 3 || str == NULL || pcount  <= 0) {
		printf("argument error\n");
		exit(EXIT_FAILURE);
	}

	if(pipe(pipefd) == -1) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	/* calculate N */
	for(int i=0; i<pcount; i++) {
		N[i] = MAXS / pcount;
	}

	if((MAXS%pcount) != 0) {
		for(int i=0; i<(MAXS%pcount); i++) {
			N[i] += 1;
		}
	}

	/* fork & find sequence */
	for(int i=0; i<pcount; i++) {
		count += N[i]; /* update count */
		pid[i] = fork();
		if(pid[i] == -1) {
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if(pid[i]  == 0) { /* child process */
			close(pipefd[0]);
			findStr(str, count-N[i], N[i], pipefd[1]);
			close(pipefd[1]);
			exit(EXIT_SUCCESS);
		} 
	}
	
	/* read from pipe */
	close(pipefd[1]);
	wait(NULL);
	while(read(pipefd[0], &buf, sizeof(int))>0)
		foundIndex[fcount++] = buf;
	close(pipefd[0]);

	/* sort index */
	for(int i=0; i<fcount-1; i++) {
		min = i;
		for(int j=i+1; j<fcount; j++) {
			if(foundIndex[min] > foundIndex[j])
				min = j;
		}
		if(min != i) {
			int temp = foundIndex[min];
			foundIndex[min] = foundIndex[i];
			foundIndex[i] = temp;
		}
	}

	/* print index */
	for(int i=0; i<fcount; i++)
		printf("%d\n", foundIndex[i]);
	
	return 0;
}

void findStr(const char* str, int s, int n, int fd) {
	int found = -1;
	int end = s+n;

	for(int k=s; k<end; k++) {
		found = k;
		for(int j=0, i=k; j<strlen(str); j++, i++) {
			if(i >= MAXS) break;
			if(input[i] == str[j]) {
				continue;
			} else {
				found = -1;
				break;
			}
		}
		if(found != -1) {
			write(fd, &found, sizeof(found)); /* write to pipe */	
		}
	}
}


