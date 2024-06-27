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
	int server_socket;
	struct sockaddr_in server_addr, client_addr;
	socklen_t client_addr_len;
	int recv_bytes;
	char buffer[BUFFER_SIZE];

	if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(PORT);

	if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

	while (1) {
		if (listen(server_socket, 5) < 0) {
			perror("listen failed");
			exit(EXIT_FAILURE);
		}

		//printf("Server listening on port %d...\n", PORT);

		client_addr_len = sizeof(client_addr);
		int client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);
		if (client_socket < 0) {
			perror("accept failed");
			exit(EXIT_FAILURE);
		}

		//printf("Client connected from %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

		while (1) {
			recv_bytes = recv(client_socket, buffer, BUFFER_SIZE, 0);
			if (recv_bytes < 1) break;
			buffer[recv_bytes] = '\0';
			puts(buffer);
		}
		close(client_socket);
	}

	close(server_socket);

	return 0;
}
