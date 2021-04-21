

#include <sys/types.h>  // for all types with _t
#include <sys/socket.h> // for function in TCP/UDP flow diagram
#include <netinet/in.h> //for sockaddr_in numbers
#include <arpa/inet.h>  // for sockaddr_in and inet_ntoa
#include <stdio.h>      // print f
#include <stdlib.h>     // atoi, itoa, exit
#include <string.h>     // memset
#include <unistd.h>

int main(void)
{
    int socket_desc;
    struct sockaddr_in server_addr;
    char server_message[2000], client_message[2000];
    socklen_t server_struct_length = sizeof(server_addr);

    // Clean buffers:
    memset(server_message, '\0', sizeof(server_message));
    memset(client_message, '\0', sizeof(client_message));

    // Create socket:
    socket_desc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (socket_desc < 0)
    {
        printf("Error while creating socket\n");
        return -1;
    }
    printf("Socket created successfully\n");

    // Set port and IP:
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5678);
    //server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    
     int res = inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);
    if (res <= 0)
    {
        perror("IP address conversion failed.");
        exit(EXIT_FAILURE);
    }
    

    // Get input from the user:
    // printf("Enter message: ");

    // gets(client_message);

    //hard coded msg
    sprintf(client_message, "This is the message sent by client.\n");

    // Send the message to server:
    if (sendto(socket_desc, client_message, strlen(client_message), 0,
               (struct sockaddr *)&server_addr, server_struct_length) < 0)
    {
        printf("Unable to send message\n");
        return -1;
    }

    // Receive the server's response:
    if (recvfrom(socket_desc, server_message, sizeof(server_message), 0,
                 (struct sockaddr *)&server_addr, &server_struct_length) < 0)
    {
        printf("Error while receiving server's msg\n");
        return -1;
    }

    printf("Server's response: %s\n", server_message);

    // Close the socket:
    close(socket_desc);

    return 0;
}
