// Socket programming - Server

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

void chatFunction(int sockfd)
{
    char buffer[250];

    while (1)
    {
        bzero(buffer, sizeof(buffer));

        recv(sockfd, buffer, sizeof(buffer), 0);
        printf("Client: %s", buffer);

        printf("\nYou: ");
        scanf(" %[^\n]s", buffer);

        send(sockfd, buffer, sizeof(buffer), 0);

        if ((strncmp(buffer, "exit", 4)) == 0)
        {
            printf("\nExiting....\n");
            break;
        }
    }
}

int main(int argc, char const *argv[])
{
    int sockfd;
    char buffer[] = "Message from server";

    struct sockaddr_in server_addr;
    socklen_t addrlen = sizeof(server_addr);

    // Socket creation
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Socket error\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("Socket created\n");
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9999);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr *)&server_addr, addrlen) < 0)
    {
        perror("Bind error");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("Server is listening.....\n");
    }

    if (listen(sockfd, 3) < 0)
    {
        perror("Listen error");
        exit(EXIT_FAILURE);
    }

    int new_sockfd;
    new_sockfd = accept(sockfd, (struct sockaddr *)&server_addr, &addrlen);

    chatFunction(new_sockfd);

    close(new_sockfd);
    close(sockfd);

    return 0;
}
