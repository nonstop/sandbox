/*
 * Listing 2:
 * An example client for "Hello, World!" server
 * Ivan Griffin (ivan.griffin@ul.ie)
 */

#include <stdio.h>                /* perror() */
#include <stdlib.h>               /* atoi() */
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>               /* read() */
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

int main(int argc, char *argv[])
{
    int clientSocket,
        remotePort,
        status = 0;
    struct hostent *hostPtr = NULL;
    struct sockaddr_in serverName = { 0 };
    char buffer[256] = "";
    char *remoteHost = NULL;

    if (3 != argc)
    {
        fprintf(stderr, "Usage: %s <serverHost> <serverPort>\n",
            argv[0]);
        exit(1);
    }

    remoteHost = argv[1];
    remotePort = atoi(argv[2]);

    clientSocket = socket(PF_INET, SOCK_STREAM, 
		IPPROTO_TCP);
    if (-1 == clientSocket)
    {
        perror("socket()");
        exit(1);
    }

    /*
     * need to resolve the remote server name or 
     * IP address */
    hostPtr = gethostbyname(remoteHost);
    if (NULL == hostPtr)
    {
        hostPtr = gethostbyaddr(remoteHost, 
		strlen(remoteHost), AF_INET);
        if (NULL == hostPtr)
        {
        perror("Error resolving server address");
        exit(1);
        }
    }

    serverName.sin_family = AF_INET;
    serverName.sin_port = htons(remotePort);
    (void) memcpy(&serverName.sin_addr, 
		hostPtr->h_addr,
		hostPtr->h_length);

    status = connect(clientSocket, 
		(struct sockaddr*) &serverName,
        sizeof(serverName));
    if (-1 == status)
    {
        perror("connect()");
        exit(1);
    }

    /*
     * Client application specific code goes here
     *
     * e.g. receive messages from server, respond,
     * etc. */
    while (0 < (status = read(clientSocket,
        buffer, sizeof(buffer) - 1)))
    {
        printf("%d: %s", status, buffer);
    }

    if (-1 == status)
    {
        perror("read()");
    }

    close(clientSocket);

    return 0;
}

