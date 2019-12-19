#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip_icmp.h>   	
#include <netinet/ip.h>    		
#include <netinet/if_ether.h>   
#include <net/ethernet.h>  		
#include <arpa/inet.h>
int total = 0;
int main()
{

    struct sockaddr socket_addr;
    int socket_addr_size , data;
    unsigned char *buffer = (unsigned char *) malloc(65536); 
    int raw = socket( AF_PACKET , SOCK_RAW , htons(ETH_P_ALL)) ;
    //AF_PACKET : 能夠監測所有輸入輸出的封包，並包含乙太頭
    //htons(ETH_P_ALL) : 可收發來源目的為本機MAC位址的所有封包
    if(raw < 0)
        printf("create a socket error");
	printf("\n--------------------- ICMP Sniffer ------------------------");
    while(1)
    {
        socket_addr_size = sizeof(socket_addr);
        data = recvfrom(raw , buffer , 65536 , 0 , &socket_addr , (socklen_t*)&socket_addr_size);

        if(data <0 )
            printf("recvfrom error\n");
        struct iphdr *ipheader = (struct iphdr*)(buffer + sizeof(struct ethhdr));//ip header
   	if ( ipheader->protocol == 1) 
    	{
    		//ip header
      	  	unsigned short ipheader_len;
		ipheader_len =ipheader->ihl*4; 						//iph(DWord):4bytes
    		printf("\nIPv4: " );
		printf("hdr_size:%d Bytes ",((unsigned int)(ipheader_len)));		//header size
		printf("pkt_size:%d Bytes ",ntohs(ipheader->tot_len));			//packet size
		printf("Protocol:%d ",(unsigned int)ipheader->protocol);		//protocol type
		printf("TTL:%d ",(unsigned int)ipheader->ttl);				//time to live

		//icmp header
	    	struct icmphdr *icmpheader = (struct icmphdr *)(buffer + ipheader_len  + sizeof(struct ethhdr)); 
	   	printf("\nICMP: "); 
	    	printf("Type:[%d/%d]",(unsigned int)(icmpheader->type),(unsigned int)(icmpheader->code));//icmp type       
		printf("Checksum:[%5d] ",ntohs(icmpheader->checksum));
	    	printf("ID:[%d] ",ntohs(icmpheader->un.echo.id));
	    	printf("Sequence:[%02d] ",ntohs(icmpheader->un.echo.sequence));
	    	printf("\n-------------------------------------------------------");
   	}
    }
    close(raw);
    printf("close socket");
    return 0;
}

