#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 3979

int main(void)
{

    int sockfd;
    struct sockaddr_in address;

    sockfd = socket(AF_INET,SOCK_STREAM,0);

    if(sockfd == 0)
    {
        printf("socket failed");
        return -1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(sockfd, (struct sockaddr *)&address, sizeof(address));

    listen(sockfd,5);

    int addrlen = sizeof(address);

    int new_door = accept(sockfd, (struct sockaddr *)&address, (socklen_t*)&addrlen);

    char tmp[256] = {0};

    int valread = read( new_door , tmp, 256);
    printf("%s\n",tmp );

    char *msg = "I'm alive!";

    send(new_door , msg , 12 , 0 );
                       


}