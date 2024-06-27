#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 12345
#define BUFFER_SIZE 1024

int main()
{
	int client_socket;
	struct sockaddr_in server_addr;
	int read_bytes;

	if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);

	if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
		perror("invalid address");
		exit(EXIT_FAILURE);
	}

	if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
		perror("connection failed");
		exit(EXIT_FAILURE);
	}

	printf("Connected to server on port %d\n", PORT);

	char const *buffer = "Hello, world!";
	if (send(client_socket, buffer, strlen(buffer), 0) != strlen(buffer)) {
		perror("send failed");
		exit(EXIT_FAILURE);
	}

	close(client_socket);

	return 0;
}
