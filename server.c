#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
    char buffer[1024] = {};
    int serverSockfd = 0;
    int clientSockfd = 0;
    int errbind = 0;
    int errlisten = 0;
    struct sockaddr_in serverAddr,clientAddr;
    int addrlen = sizeof(serverAddr); //client訊息長度    
    serverSockfd = socket(AF_INET , SOCK_STREAM , 0);
    //AF_INET:Address family ,SOCK_STREAM:使用TCP
    if (serverSockfd == -1)
        printf("create a socket error");
    
    memset(&serverAddr,'\0',sizeof(serverAddr));//清空serverInfo  
    serverAddr.sin_family = PF_INET; //protocol family
    serverAddr.sin_addr.s_addr = INADDR_ANY;//讓kernel決定localhost ip
    serverAddr.sin_port = htons(1212);//server port
    errbind = bind(serverSockfd,(struct sockaddr *)&serverAddr,sizeof(serverAddr));//bind自己的資訊到socket
    if (errbind == -1)
        printf("create a bind error"); 
    
    errlisten = listen(serverSockfd,2);//最多2人連進server
    if (errlisten == -1)
        printf("listen a bind error");
    
    clientSockfd = accept(serverSockfd,(struct sockaddr*) &clientAddr, &addrlen);
                        //從哪個socket接受,接受到的client訊息,訊息長度
    while(1)
    {
        recv(clientSockfd,buffer,sizeof(buffer),0);//接收client訊息
        printf("[CLIENT send] :%s\n",buffer);
        send(clientSockfd,buffer,sizeof(buffer),0);//傳送訊息給client
       
    }
    close(serverSockfd);
    printf("close");
    return 0;
}
