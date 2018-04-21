#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(void) {
	puts("Soy el servidor"); /* prints !!!Hello World!!! */

	//creo el socket del server
	struct sockaddr_in direccionDelServidor;//estructura con el puerto en el que hay que escuchar
	direccionDelServidor.sin_family = AF_INET;
	direccionDelServidor.sin_addr.s_addr = INADDR_ANY;
	direccionDelServidor.sin_port = htons(5000);
	int servidor = socket(AF_INET, SOCK_STREAM, 0);//guardo el id del socket del servidor

	//para no tener que esperar 2min si el server se cierra mal
	int activado = 1;
	setsockopt(servidor,SOL_SOCKET,SO_REUSEADDR,&activado,sizeof(activado));

	//Asocia el soket con la direccion(8080) y evalúa que el perto no este ocupado
	if(bind(servidor,(void*) &direccionDelServidor,sizeof(direccionDelServidor)) != 0 ){
		perror("Falló el bind");
		return 1;
	}

	//pongo a escuchar al socket
	puts("estoy escuchando");
	listen(servidor,100);//el segundo valor es la cantidad de conexiones que puede recibir hasta ser aceptadas

	//acepto la conexion
	//esto tiene que quedar adentro de un if para filtrar conexiones no deseadas
	struct sockaddr_in dirCliente;
	unsigned int tamanioDireccionCliente;
	int cliente;
	if((cliente = accept(servidor,(void*) &dirCliente,&tamanioDireccionCliente))<0){
		perror("accept");
		return -1;
	}
	puts("conexion aceptada");
	//aceptada la conexion ya le puedo mandar un mensaje al cliente
	send(cliente, "hola cliente",13,0);

	char* buffer = malloc(13);//buffer donde voy a almacenar lo que reciba
	int bytesRecibidos = recv(cliente, buffer, 13,0);//MSG_WAITALL
	if (bytesRecibidos <= 0 ){//devuelve negativo si hay un error del otro lado de la conexion
		perror("el cliente se desconecto");
		return 1;
	}

	buffer[bytesRecibidos] = '\0';
	printf("me llegaron %d bytes con %s", bytesRecibidos, buffer);
	free(buffer);

	return 0;
}
