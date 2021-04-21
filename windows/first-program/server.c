#include<stdio.h>
#include <winsock2.h> //1>
//diiference
/*
1> library load --> 
 wsa startup and wsa cleanup

2>functions different
3>error handelnig -> NO_ERROR, SOCKET_ERROR
4> socket type -> unix ma int socket hunthyo yesma chai socket nai huncha
5> use closesocket() instead of close()
*/

/*
ws2_32.lib ko kaam ka bata windows ko   load garne ho
*/
void main(){
    WSADATA wsaData; 
    int res = WSAStartup(MAKEWORD(2,2), &wsaDATA);//2>

    if (res != NO_ERROR){//3>
        printf("Error during WSASTARTUP");
    }

    SOCKET m_socket = socket(AP_INET, SOCK_STREAM, IPPROTO_TCP);

    if (m_socket == INVALID_SOCKET)
    {
        printf("Error at socket(): %ld\n", WSAGetLastError());
        WSACleanup();
        return;
    }
    sockaddr_in service;
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = inet_addr("127.0.0.1");
    service.sin_port = htons(27015);

    if (bind(m_socket, (SOCKADDR *)&service, sizeof(service)) == SOCKET_ERROR)
    {
        printf("bind() failed.\n");
        closesocket(m_socket);
        return;
    }
    if (listen(m_socket, 1) == SOCKET_ERROR)
        printf("Error listening on socket.\n");
    
    //accepting a socket
    SOCKET AcceptSocket;

    printf("Waiting for a client to connect...\n");
    while (1)
    {
        AcceptSocket = SOCKET_ERROR;
        while (AcceptSocket == SOCKET_ERROR)
        {
            AcceptSocket = accept(m_socket, NULL, NULL);
        }
        printf("Client Connected.\n");
        m_socket = AcceptSocket;
        break;
    }
}