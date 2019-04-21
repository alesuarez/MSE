#include <stdio.h>
#include <stdlib.h>
#include "SerialManager.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <pthread.h>
#include <signal.h>

#define SERIAL_ADDRESS        1
#define SERIAL_BAUD_RATE    115200

struct sockaddr_in serveraddr;
struct sockaddr_in clientaddr;
char buffer_serial[10];
char buffer_tcp[128];
int file_descriptor;
int s;
pthread_mutex_t mutexData = PTHREAD_MUTEX_INITIALIZER;
int has_data = 0;
int has_client = 0;
struct sigaction sig_usr_1, sig_usr_2;

pthread_t serial;
pthread_t server_tcp;

void init_serial();
void init_socket_tcp();
void init_signals();
void handler_USR();

void *start_serial_thread(void *);
void *start_tcp_thread(void *);

void update_has_client(int);
void block_sign();
void unblock_sign();

int main(void) {

    init_serial();
    init_socket_tcp();
    init_signals();

    block_sign(); // bloqueo señales para que solo las maneje el hilo principal
    
    if (pthread_create(&serial, NULL, start_serial_thread, NULL)) {
        perror("Error: while serial thread was creating.");
        exit(EXIT_FAILURE);
    }

    if (pthread_create(&server_tcp, NULL, start_tcp_thread, NULL)) {
        perror("Error: while server tcp thread was creating.");
        exit(EXIT_FAILURE);
    }
    
    unblock_sign();
    
    pthread_join(serial, NULL);
    pthread_join(server_tcp, NULL);
}

void init_serial() {
    printf("Inicio Serial Service\r\n");

    if (serial_open(SERIAL_ADDRESS, SERIAL_BAUD_RATE) < 0) {
        perror("Error: while serial port was opennig.");
    }
}

void init_signals() {
    // inicio de señales

    sig_usr_1.sa_handler = handler_USR;
    sig_usr_1.sa_flags = SA_RESTART;
    sigemptyset(&sig_usr_1.sa_mask);

    if (sigaction(SIGINT,&sig_usr_1,NULL) == -1) {
        perror("Error: while signal Handling 1 was creating.");
    }

    sig_usr_2.sa_handler = handler_USR;
    sig_usr_2.sa_flags = SA_RESTART;
    sigemptyset(&sig_usr_2.sa_mask);

    if (sigaction(SIGTERM, &sig_usr_2, NULL) == -1) {
        perror("Error: while signal Handling 2 was creating.");
    }

}

void handler_USR() {
    printf("saluedi\n");
    // handler de señales
    pthread_cancel(serial);     // cierro lo hilos
    pthread_cancel(server_tcp);

    if (file_descriptor > 0) {  // si es un file descriptor valido
        printf(":)\n");
        close(file_descriptor);
        
    }
    
    close(s);
    exit(EXIT_FAILURE);
}

void init_socket_tcp() {

    s = socket(PF_INET, SOCK_STREAM, 0);

    struct addrinfo hints;
    struct addrinfo *result;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET; // ipv4
    hints.ai_socktype = SOCK_STREAM; // tcp
    hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */

    int r = getaddrinfo(NULL, "10000", &hints, &result); // NULL para localhost

    if (r != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(r));
        exit(EXIT_FAILURE);
    }

    if (bind(s, (struct sockaddr *) result->ai_addr, result->ai_addrlen) == -1) {
        close(s);
        perror("listener: bind");
    }

    freeaddrinfo(result);

    if (listen(s, 10) == -1) { // backlog=10
        perror("error en listen");
        exit(EXIT_FAILURE);
    }

}

void *start_serial_thread(void *message) {
    while (1) {
        int i = serial_receive(buffer_serial, sizeof(buffer_serial));

        pthread_mutex_lock(&mutexData);
        if (i > 0 && has_client > 0) { // si tengo datos en el buffer serial y tengo clientes conectados
           if (write(file_descriptor, buffer_serial, i) == -1) {
                perror("Error escribiendo mensaje en socket");
                exit(EXIT_FAILURE);
            }
        }
        pthread_mutex_unlock (&mutexData);

        sleep(1);
    }
}


void *start_tcp_thread(void *message) {
    while (1) {
        socklen_t addr_len = sizeof(struct sockaddr_in);

        if ((file_descriptor = accept(s, (struct sockaddr *) &clientaddr, &addr_len)) == -1) {
            perror("error en accept");
            exit(1);
        }

        printf("Conexion desde:  %s\n", inet_ntoa(clientaddr.sin_addr));

        update_has_client(1);

        int n;

        if( (n = recv(file_descriptor,buffer_tcp, 128, 0)) == -1 ) {
            perror("Error leyendo mensaje en socket");
        }

        update_has_client(0);

        close(file_descriptor);

        buffer_tcp[n] = 0x00;

        serial_send(buffer_tcp, sizeof(buffer_tcp));
            
        // Cerramos conexion con cliente
    }
}

void update_has_client(int i) {
    pthread_mutex_lock(&mutexData);
    has_client = i;
    pthread_mutex_unlock (&mutexData);
}

void block_sign() {
    sigset_t set;
    int s;
    sigemptyset(&set);

    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGTERM);

    pthread_sigmask(SIG_BLOCK, &set, NULL);
}

void unblock_sign() {
    sigset_t set;
    int s;
    sigemptyset(&set);
    
    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGTERM);

    pthread_sigmask(SIG_UNBLOCK, &set, NULL);
}