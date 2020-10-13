#include <unistd.h>
#include <arpa/inet.h> // inet_ntop
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>


int main(int argc, char** argv) {

	if(argc !=2){
		printf("cantidad de argumentos invalida\n");
	}

	struct addrinfo hints, *server_info;
	int fd;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;
    getaddrinfo(NULL, argv[1], &hints, &server_info);

	fd = socket(server_info->ai_family, server_info->ai_socktype, server_info->ai_protocol);

	int val = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));

    bind(fd, server_info->ai_addr, server_info->ai_addrlen);


    freeaddrinfo(server_info);
    listen(fd,10);

    struct sockaddr_in address;
    socklen_t addressLength = (socklen_t) sizeof(address);
    int peer = accept(fd, (struct sockaddr *)&address, &addressLength);

    char mensaje [50];
    recv(peer, mensaje, 50, 0);
    printf("%s\n",mensaje);


    shutdown(fd, 2);
    close(fd);

    shutdown(peer, 2);
    close(peer);

    return 0;

	}
