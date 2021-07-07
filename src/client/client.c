#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>

#define DOMAIN "www.google.com" //owner of the ports we're checking.
#define PORT "3979" //port

void baglan(void);

int main(void)
{
  baglan();
 return 0;
}

void baglan(void)
{

    struct addrinfo hints; //hints basically determines which sockets get to be in res.
    struct addrinfo *res; //sockets we get from getaddrinfo, restricted by the attributes we specified in hints.
    int sockfd;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET; //We only want IPV4 sockets in res. So we specify this in hints. Use AF_INET6 for IPV6 and AF_UNSPEC for both.
    hints.ai_socktype = SOCK_STREAM;

    
    getaddrinfo(NULL, PORT , &hints, &res);

    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    int c = connect(sockfd, res->ai_addr, res->ai_addrlen);
    if(c != -1)
    {
            printf("%d Port açık. Baglanti kuruldu\n", PORT);
        }
    else printf("%s Port Kapalı", PORT);
    
    char *msg = "Mee too!";
    char tmp[256];

    send(sockfd , msg , 16 , 0 );
    printf("Mesaj gönderildi\n");

    read( sockfd , tmp, 256);

    printf("Gelen: %s\n",tmp );

}

