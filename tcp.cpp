#include <iostream>
#include <string>
#include <sys/socket.h>

#define SERVER_PORT 80
#define MAX_LINE 4096

int main(int argc, char **argv)
{
    struct sockaddr skad;
    
    int sockfd, n;
    int sendbytes;
    struct sockaddr_in servaddr; 

    if (argc != 2)
    {
        std::cout << "Usage: ./tcp <URL>" << std::endl;
        return (1);
    }



    std::cout << "Site: " << std::string(argv[1]) << std::endl;
    return (0);
}