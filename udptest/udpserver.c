#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUFLEN 512
#define NPACK 10
#define PORT 9999

int main(void)
{
    struct sockaddr_in si_me, si_other;
    int s, slen = sizeof(si_other);
    char buf[BUFLEN] = {};

    if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1) {
        perror("socket");
        return 1;
    }

    memset((char *) &si_me, 0, sizeof(si_me));
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(PORT);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(s, (const struct sockaddr*)&si_me, sizeof(si_me))==-1) {
        perror("bind");
        return 1;
    }

    int cnt = 0;
    while (1) {
        if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr*)&si_other, &slen)==-1) {
            perror("recvfrom()");
            return 1;
        }
        if (!(cnt % 10))
            sleep(1);
        printf("%d Received packet from %s:%d\nData: %s\n\n", 
                cnt, inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port), buf);
        cnt++;
    }
    close(s);
    return 0;
}

