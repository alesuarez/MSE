#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void hand(int sig) {
	write(1,"se presiono ctrl+c!!\n",21);
}

int main(void) {
	struct sigaction sa;

	sa.sa_handler = hand;
	sa.sa_flags = 0; //SA_RESTART; //0;
	sigemptyset(&sa.sa_mask);

	sigaction(SIGINT,&sa,NULL);

	char s[200];

	if(fgets(s,sizeof(s),stdin) == NULL) 	{
		perror("error en fgets\n");
	} else {
		printf("ingresaste:%s\n",s);
	}


	return 0;
}
