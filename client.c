#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
    int sockfd = 0;
    struct sockaddr_in myAddr;
    int errConnect = 0;	
    sockfd = socket(AF_INET , SOCK_STREAM , 0);
    if (sockfd == -1)
        printf("create a socket error");
    memset(&myAddr,'\0',sizeof(myAddr));
    myAddr.sin_family = PF_INET;
    myAddr.sin_addr.s_addr = inet_addr("127.0.0.1");//localhost
    myAddr.sin_port = htons(1212);//port
    errConnect = connect(sockfd,(struct sockaddr *)&myAddr,sizeof(myAddr));
    if(errConnect == -1){
        printf("Connect error\n");
        return 1;
    }
    else
	printf("Connect to server.\n");
    while(1){ 
		char message[1024] = {};
		char receiveMessage[1024] = {};
		printf("Enter your message : ");
		scanf("%s",message);
		if(message[0] == 'e' && message[1] == 'x' && message[2] == 'i' && message[3] =='t'){
			close(sockfd);
			printf("close Socket\n");
			exit(1);
		}
		else{
			send(sockfd,message,sizeof(message),0);
			recv(sockfd,receiveMessage,sizeof(receiveMessage),0);
			printf("[SERVER read] %s \n",receiveMessage);  
		}	
	}
    return 0;
}
