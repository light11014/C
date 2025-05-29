#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<pthread.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#define BUF_SIZE 1000
void *find_sequence(void* arg);
void insert(int data);

typedef struct node
{
	int data;
	struct node *next;
} Node;

typedef struct {
	char* input_file;
	char* str;
	int start;
	int num;
} my_arg;

Node *head = NULL; // shared linked-list
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char *argv[])
{
	char* str;
	int thread_num, line_num;
	char *input_file, *output_file;

	int status, pos;
	void *thread_result;
	
	int ifd, ofd; // output file descriptor
	char buf[BUF_SIZE];
	size_t ret;
	my_arg* arg;

	if(argc != 5){
		exit(1);
	}
	if(atoi(argv[2]) < 1) {
		exit(1);
	}

	// arguments of main function
	str = argv[1];
	thread_num = atoi(argv[2]);
	input_file = argv[3];
	output_file = argv[4];

	pthread_t thread_id[thread_num];

	// open the input file
	ifd = open(input_file, O_RDONLY, NULL);
	if(ifd < 0) {
		perror("input file open");
		exit(1);
	}
	
	// read the number of input substrings(first line)
	if((ret = read(ifd, buf, 5)) != 0) {
		if(ret == -1){
			exit(1);
		}
 		line_num = atoi(buf);
	}

	// calculate the threads' start line
	int line_arr[thread_num];
	int quota = line_num / thread_num;
	int remainder = line_num % thread_num;
	for(int i=0; i<thread_num; i++) {
		line_arr[i] = quota;
	}
	if(remainder) {
		for(int i=0; i<remainder; i++){
			line_arr[thread_num - 1 - i]++;
		}
	}
	
	// create threads
	for(int i=0; i<thread_num; i++) {
		
		arg = (my_arg*)malloc(sizeof(my_arg));
		arg->input_file = input_file;
		arg->str = str;
		arg->start = 0;
		for(int j=0; j<i; j++) {
			arg->start += line_arr[j];
		}
		arg->num = line_arr[i];

		status = pthread_create(&thread_id[i], NULL, find_sequence, arg);
		if(status != 0) {
			perror("pthread_create");
			exit(1);
		}
	}

	// join threads (terminate and reap)
	for(int i=0; i<thread_num; i++) {
		status = pthread_join(thread_id[i], &thread_result);
		if(status != 0) {
			perror("pthread_join");
			exit(1);
		}
	}
	
	// open the output file
	ofd = open(output_file, O_CREAT|O_WRONLY|O_TRUNC, S_IRUSR|S_IWUSR);
	if(ofd < 0) {
		perror("output file open");
		exit(1);
	}

	// write results on output file
	if(head != NULL) {
		Node* n = head->next;
		char nbuf[BUF_SIZE];
		sprintf(nbuf, "%d\n", head->data);
		write(ofd, nbuf, strlen(nbuf));
		

		while(n != NULL){
			int num = n->data;
			sprintf(nbuf, "%d\n", num);
			write(ofd, nbuf, strlen(nbuf));
			n = n->next;
		}
	}

	// close files
	close(ifd);
	close(ofd);

	return 0;
}

void *find_sequence(void* arg)
{
	my_arg *targ = (my_arg *)arg;
	char* str = targ->str;
	char* input_file = targ->input_file;

	int ifd, start_idx;
	char buf;
	off_t startpos = 0;
	off_t pos = 0;
	off_t prepos, curpos;

	// open the input file
	ifd = open(input_file, O_RDONLY, NULL);
	if(ifd < 0) {
		perror("input file open");
		exit(1);
	}

	// repostition of file offset
	start_idx = targ->start*5;
	startpos = (targ->start+1)*6;
	lseek(ifd, startpos, SEEK_SET);
	
	// find sequence
	for(int i=0; i<targ->num;) {
		int found = start_idx;
		if(read(ifd, &buf, 1) == 0) {
			found = -1;
			break; // EOF
		}	
		if(buf == '\n') {
			i++;
			continue;
		}

		prepos = lseek(ifd, 0, SEEK_CUR);
		for(int j=0; j<strlen(str); j++) {
			if(buf == str[j]) {
				if(read(ifd, &buf, 1) == 0) {
					found = -1;
					break; // EOF
				}
				continue;
			} else {
				if(buf == '\n') {
					j--;
					if(read(ifd, &buf, 1) == 0) {
						found = -1;
						break;
					} // EOF
					continue;
				}
				found = -1;
				break;
			}
		}
		if(found != -1) {
			pthread_mutex_lock(&mutex);
			insert(start_idx); // insert the start index to shared linked-list
			pthread_mutex_unlock(&mutex);
		}

		curpos = lseek(ifd, 0, SEEK_CUR);
		pos = prepos - curpos;
		lseek(ifd, pos, SEEK_CUR);

		start_idx++;
	}
	
	close(ifd);
	return arg;
}

void insert(int data)
{
	Node* ptr;
	Node* N = (Node*)malloc(sizeof(Node));
	N->data = data;
	N->next = NULL;

	if(head == NULL) {
		head = N;
	} else {
		if(head->data > N->data) {
			N->next = head;
			head = N;
			return;
		}
		for(ptr = head; ptr->next; ptr=ptr->next) {
			if(ptr->data < N->data && ptr->next->data > N->data) {
				N->next = ptr->next;
				ptr->next = N;
				return;
			}
		}
		ptr->next = N;
	}
}