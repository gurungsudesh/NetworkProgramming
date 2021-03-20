#include<stdio.h>
#include "winsock2.h" //1>
//diiference
/*
1> library load --> 
 wsa startup and wsa cleanup

2>functions different
3>error handelnig 
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

    SOCKET s_fd = socket(AP_INET, SOCK_STREAM, IPPROTO_TCP);

    if(s_fd == INVALID_SOCKET){

        WSACleanup();

    }
    
    




}