#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>
#include <netinet/if_ether.h>
struct mine
{
    u_int16_t proto_id;
    u_int32_t my_addr;
};
// 做 checksum 運算, 驗證資料有無毀損
unsigned short checksum(unsigned short *buf, int bufsz){
    unsigned long sum = 0xffff;

    while(bufsz > 1){
        sum += *buf;
        buf++;
        bufsz -= 2;
    }

    if(bufsz == 1)
        sum += *(unsigned char*)buf;

    sum = (sum & 0xffff) + (sum >> 16);
    sum = (sum & 0xffff) + (sum >> 16);

    return ~sum;
}

int main(int argc, char *argv[]){
	struct mine header_mine,mineptr;
    int sd;
    struct icmphdr hdr;
    struct sockaddr_in addr;
    int num;
    char buf[1024];
    struct icmphdr *icmphdrptr;
    struct iphdr *iphdrptr;

    if(argc != 2){
        printf("usage: %s IPADDR\n", argv[0]);
        exit(-1);
    }

    addr.sin_family = PF_INET; // IPv4

    // 將使用者輸入的 IP 轉成 network order
    num = inet_pton(PF_INET, argv[1], &addr.sin_addr);
    if(num < 0){
        perror("inet_pton");
        exit(-1);
    }

    // 開一個 IPv4 的 RAW Socket , 並且準備收取 ICMP 封包
    //sd = socket(PF_INET, SOCK_RAW, IPPROTO_ICMP);
    sd = socket( AF_PACKET , SOCK_RAW , htons(ETH_P_ALL));
    if(sd < 0){
        perror("socket");
        exit(-1);
    }

    // 清空結構內容
    memset(&hdr, 0, sizeof(hdr));
    memset(&header_mine, 0, sizeof(header_mine));

    // 初始化 ICMP Header
   /* hdr.type = ICMP_ECHO;
    hdr.code = 0;
    hdr.checksum = 0;
    hdr.un.echo.id = 0;
    hdr.un.echo.sequence = 0;*/

    // 計算出 checksum
    //hdr.checksum = checksum((unsigned short*)&hdr, sizeof(hdr));

    // 將定義好的 ICMP Header 送到目標主機
    //num = sendto(sd, (char*)&hdr, sizeof(hdr), 0, (struct sockaddr*)&addr, sizeof(addr));
    num = sendto(sd, (char*)&header_mine, sizeof(header_mine), 0, (struct sockaddr*)&addr, sizeof(addr));
    if(num < 1){
        perror("sendto");
        exit(-1);
    }
    

    // 清空 buf
    memset(buf, 0, sizeof(buf));

    

    // 接收來自目標主機的 Echo Reply
    num = recv(sd, buf, sizeof(buf), 0);
    if(num < 1){
        perror("recv");
        exit(-1);
    }
	struct sockaddr_in source_epc,dest_epc;
	
    // 取出 IP Header
    iphdrptr = (struct iphdr*)buf;
    //mineptr = buf;
    
   /* memset(&source_epc, 0, sizeof(source_epc));
    source_epc.sin_addr.s_addr = iphdrptr->saddr;
    memset(&dest_epc, 0, sizeof(dest_epc));
    dest_epc.sin_addr.s_addr = iphdrptr->daddr;
    
    printf("saddr = %s\n",inet_ntoa(source_epc.sin_addr));
    printf("daddr = %s\n",inet_ntoa(dest_epc.sin_addr));

    // 取出 ICMP Header
    icmphdrptr = (struct icmphdr*)(buf+(iphdrptr->ihl)*4);*/
    


	close(sd); // 關閉 socket
    return EXIT_SUCCESS;
}
