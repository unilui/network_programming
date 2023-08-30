#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

int main() {
	const char *hostname = "www.google.com";
	const char *http_request = "GET / HTTP/1.1\r\nHost: www.google.com\r\nConnection: close\r\n\r\n";

	// Create a socket
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1) {
		perror("Socket creation failed");
		return 1;
	}

	// Get IP address of the hostname using getaddrinfo
	struct addrinfo hints, *result;
	std::memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	int addr_result = getaddrinfo(hostname, "http", &hints, &result);
	if (addr_result != 0) {
		std::cerr << "getaddrinfo: " << gai_strerror(addr_result) << std::endl;
		return 1;
	}

	// Connect to the remote server
	if (connect(sock, result->ai_addr, result->ai_addrlen) == -1) {
		perror("Connect failed");
		freeaddrinfo(result);
		return 1;
	}

	// Send the HTTP request
	if (send(sock, http_request, strlen(http_request), 0) == -1) {
		perror("Send failed");
		freeaddrinfo(result);
		close(sock);
		return 1;
	}

	// Receive and print the response
	char buffer[1024];
	ssize_t bytes_received;
	while ((bytes_received = recv(sock, buffer, sizeof(buffer) - 1, 0)) > 0) {
		buffer[bytes_received] = '\0';
		std::cout << buffer;
	}

	// Clean up
	freeaddrinfo(result);
	close(sock);

	return 0;
}
