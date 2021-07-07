#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#include <netdb.h> //addrinfo

#define PORT 3979

int main(void)
{

    int sockfd;
    struct sockaddr_in address;

    struct addrinfo hints; //hints basically determines which sockets get to be in res.
    struct addrinfo *res; //sockets we get from getaddrinfo, restricted by the attributes we specified in hints.


    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET; //We only want IPV4 sockets in res. So we specify this in hints. Use AF_INET6 for IPV6 and AF_UNSPEC for both.
    hints.ai_socktype = SOCK_STREAM;

    sockfd = socket(AF_INET,SOCK_STREAM,0);

    getaddrinfo(NULL, "3979" , &hints, &res);

    if(sockfd == 0)
    {
        printf("socket failed");
        return -1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    //bind(sockfd, (struct sockaddr *)&address, sizeof(address));
    bind(sockfd,res->ai_addr,res->ai_addrlen);

    listen(sockfd,5);

    int addrlen = sizeof(address);
    struct sockaddr_storage their_addr;
    unsigned int addr_size;


    //int new_door = accept(sockfd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
    int new_door = accept(sockfd, (struct sockaddr*) &their_addr, &addr_size);

    char tmp[256] = {0};

    int valread = read( new_door , tmp, 256);
    printf("%s\n",tmp );

    char *msg = "I'm alive!";

    send(new_door , msg , 12 , 0 );
                       


}