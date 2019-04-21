#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>

#define FIFO_NAME "myfifo"
#define INPUT_LENGTH 	300
#define OUTPUT_LENGTH 	306

int file_descriptor;

void send(char[]);
void handler_USR1();
void handler_USR2();

int main(void) {
	struct sigaction sig_usr_1, sig_usr_2;

	sig_usr_1.sa_handler = handler_USR1;
	sig_usr_1.sa_flags = SA_RESTART;
	sigemptyset(&sig_usr_1.sa_mask);

	if (sigaction(SIGUSR1,&sig_usr_1,NULL) == -1) {
		perror("Error: while signal Handling 1 was creating.");
	}


	sig_usr_2.sa_handler = handler_USR2;
	sig_usr_2.sa_flags = SA_RESTART;
	sigemptyset(&sig_usr_2.sa_mask);

	if (sigaction(SIGUSR2,&sig_usr_2,NULL) == -1) {
		perror("Error: while signal Handling 2 was creating.");
	}

	char input_data[INPUT_LENGTH];

	if (mknod(FIFO_NAME, S_IFIFO | 0666, 0) == 0) {
		perror("Error: while fifo was creating.");
	}

	printf("Waiting for readers...\n");

	file_descriptor = open(FIFO_NAME, O_WRONLY);

	if (file_descriptor < 0) {
		perror("Error: while file_descriptor was opend.");
	}
	
	printf("Got a reader--type some stuff\n");

	while (1) {
		char output_data[OUTPUT_LENGTH] = "DATA:\0";
		
		fgets(input_data, INPUT_LENGTH, stdin);

		strcat(output_data, input_data);

		send(output_data);
	}

	close(file_descriptor);
	
	return 0;
}

void send(char message[]) {
	int num;
	if ((num = write(file_descriptor, message, strlen(message))) == -1) {
		perror("Error: while fifo was writing.");
	} else {
		printf("Writer: wrote %d bytes.\n", num);
	}
	return;
}

void handler_USR1() {
	send("SIGN:1\n");
	return;
}

void handler_USR2() {
	send("SIGN:2\n");
	return;
}
