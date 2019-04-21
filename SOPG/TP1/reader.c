#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define FIFO_NAME "myfifo"

#define HEAD_DATA "DATA"
#define HEAD_SIGN "SIGN"

#define FILE_NAME_DATA "log.txt"
#define FILE_NAME_SIGN "signals.txt"

#define HEAD_LENGTH 	4
#define INPUT_LENGTH 	300

void write_file(char [], int, FILE *);
FILE * open_file(FILE *, char []);
void handler_data(char[], FILE *, FILE *, int); 
int input_lenth_text(int);

int main(void) {
	char input_text[INPUT_LENGTH];

	int num, file_descriptor;

	FILE *file_log = open_file(file_log, FILE_NAME_DATA);
	FILE *file_sign = open_file(file_sign, FILE_NAME_SIGN);

	if (mknod(FIFO_NAME, S_IFIFO | 0666, 0) == 0) {
		perror("Error: while fifo was creating.");
	}

	printf("Waiting for writers...\n");

	file_descriptor = open(FIFO_NAME, O_RDONLY);

	if (file_descriptor < 0) {
		perror("Error: while file_descriptor was opend.");
	}

	printf("Got a writer\n");

	do {
		if ((num = read(file_descriptor, input_text, INPUT_LENGTH)) == -1) {
			perror("Error: while file descriptor was opened.");
		} else {
			int input_length = input_lenth_text(num);
			handler_data(input_text, file_log, file_sign, input_length);
		}
	} while (num > 0);
	
	fclose(file_log);
	fclose(file_sign);
	close(file_descriptor);
	
	return 0;
}

void write_file(char text[], int length, FILE *file) {
	fwrite(text, sizeof(char), length, file);

	printf("Some data was writer.\n");
}

FILE * open_file(FILE *file, char file_name[]) {
	if((file = fopen (file_name, "a")) == NULL) {
		printf("Error: while %s file was opened.", file_name);
		exit(EXIT_FAILURE);
	}
	return file;
}

void handler_data(char input_text[], FILE *file_log, FILE *file_sign, int data_length) {
	input_text[data_length] = '\0';
	if(!strncmp(input_text, HEAD_DATA, HEAD_LENGTH)) {
		write_file(input_text, data_length, file_log);
	} 
	else if (!strncmp(input_text, HEAD_SIGN, HEAD_LENGTH)) {
		write_file(input_text, data_length, file_sign);
	} else {
		printf("Wrong data was received.");
	}
}

int input_lenth_text(int num) {
	int input_length;
	if (num > INPUT_LENGTH) {
		input_length = INPUT_LENGTH - 1;
	} else {
		input_length = num;
	}
	return input_length;
}
