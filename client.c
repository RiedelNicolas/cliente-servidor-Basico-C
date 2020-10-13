#define _POSIX_C_SOURCE 201112L // Habilita getaddrinfo
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#define POS_HOST 1
#define POS_PUERTO 2

int main(int argc, char** argv){
	if(argc !=3){
		printf("cantidad de argumentos erronea\n");
		printf("se espera, host puerto");
		return -1;
	}

	int fd;

	struct addrinfo hints, *serv_info;
	memset(&hints, 0, sizeof(hints) );
	int error = getaddrinfo(argv[POS_HOST],argv[POS_PUERTO],&hints,&serv_info);
	if(error){
		printf("hubo un error info: %s\n",gai_strerror(error) );
	}

	fd = socket(serv_info->ai_family, serv_info->ai_socktype, serv_info->ai_protocol);
	connect(fd, serv_info->ai_addr, serv_info->ai_addrlen); //Esto deberia loopear.
	freeaddrinfo(serv_info);

	//hasta aca ya se realizo la connect.

	char mensaje [50];
	printf("ingrese el mensaje que quiere enviar\n");
	scanf("%s",mensaje);
	send(fd,mensaje,strlen(mensaje),MSG_NOSIGNAL);

	shutdown(fd, 2);
    close(fd);

    return 0;
}
