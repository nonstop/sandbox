#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUFLEN 512
#define NPACK 100
#define PORT 9999

int main(void)
{
    struct sockaddr_in si_other;
    int s, i, slen=sizeof(si_other);
    char buf[BUFLEN];

    if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1) {
        perror("socket");
        return 1;
    }

    memset((char *) &si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(PORT);
    if (inet_aton("127.0.0.1", &si_other.sin_addr)==0) {
        fprintf(stderr, "inet_aton() failed\n");
        return 1;
    }

    fprintf(stderr, "%s:%d\n", __FILE__, __LINE__);
    for (i=0; i<NPACK; i++) {
        sprintf(buf, "This is packet %d\n", i);
        int res = sendto(s, buf, BUFLEN, 0, (const struct sockaddr*)&si_other, slen);
        fprintf(stderr, "%s:%d res=%d\n", __FILE__, __LINE__, res);
        if (res ==-1) {
            perror("sendto");
            return 1;
        }
    }

    close(s);
    return 0;
}

