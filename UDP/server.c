
#include <sys/types.h>  // for all types with _t
#include <sys/socket.h> // for function in TCP/UDP flow diagram
#include <netinet/in.h> //for sockaddr_in numbers
#include <arpa/inet.h>  // for sockaddr_in and inet_ntoa
#include <stdio.h>      // print f
#include <stdlib.h>     // atoi, itoa, exit
#include <string.h>     // memset
#include <unistd.h>     // close

int main(){
    int udp_server_fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (udp_server_fd == -1){
        perror("Cannot create a socket.\n");
        exit(EXIT_FAILURE);
    }
    printf("UDP socket created.\n");

    struct sockaddr_in udp_sa;

    memset(&udp_sa, 0, sizeof udp_sa);

    // Filling server information
    udp_sa.sin_family = AF_INET;
    udp_sa.sin_port = htons(5678);
    udp_sa.sin_addr.s_addr = htonl(INADDR_ANY);

    //bind the socket with the server address

    if(bind(udp_server_fd, (const struct sockaddr *) &udp_sa, sizeof udp_sa ) == -1){
        perror("Bind failed.\n");
        exit(EXIT_FAILURE);

    }
    printf("Bind success.\n");

   printf("Listening to clients...\n");

    //message
    int size = 1000;
    char buffer[size];
    memset(buffer, 0, size);
    
    struct sockaddr_in udp_client_sa;

    socklen_t len, n;
    len = sizeof(udp_client_sa);

    if (recvfrom(udp_server_fd, (char *)buffer, size,
                 MSG_WAITALL, (struct sockaddr *)&udp_client_sa,
                 &len) == -1)
    {
        perror("Couldn't receive message.\n");
        exit(EXIT_FAILURE);
    }
    printf("Received message from IP: %s and port: %i\n",
           inet_ntoa(udp_client_sa.sin_addr), ntohs(udp_client_sa.sin_port));

    printf("Msg from client: %s\n", buffer);



    //Respond to client
    memset(buffer, 0, size);
    sprintf(buffer, "This is the message sent by server.\n");

    if (sendto(udp_server_fd, buffer, strlen(buffer), 0,
               (struct sockaddr *)&udp_client_sa, len) < 0)
    {
        perror("Couldn't send message.\n");
        exit(EXIT_FAILURE);
    }
    printf("Message sent: %s\n", buffer);
    printf("Closing socket..........");
    close(udp_server_fd);
}