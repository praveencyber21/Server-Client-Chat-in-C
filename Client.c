// Socket programming - Client

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

void chatFunction(int sockfd)
{
    printf("Start a chat with server\n");
    char buffer[250];

    while (1)
    {
        bzero(buffer, sizeof(buffer));

        printf("\nYou: ");
        scanf(" %[^\n]s", buffer);

        send(sockfd, buffer, sizeof(buffer), 0);
        if ((strncmp(buffer, "exit", 4)) == 0)
        {
            printf("\nExiting....\n");
            break;
        }
        recv(sockfd, buffer, sizeof(buffer), 0);
        printf("Server: %s", buffer);
    }
}

int main(int argc, char const *argv[])
{
    int sockfd;

    struct sockaddr_in client_addr;

    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(9999);
    client_addr.sin_addr.s_addr = INADDR_ANY;

    // Socket creation
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Socket error");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("Socket Created\n");
    }

    // Connect to the server
    if (connect(sockfd, (struct sockaddr *)&client_addr, sizeof(client_addr)) < 0)
    {
        perror("Connection error");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("Successfully connected with server\n");
    }

    chatFunction(sockfd);

    close(sockfd);

    return 0;
}