#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <memory.h>

int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        printf("sockfd error\n");
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(9000);
    int ret = connect(sockfd, (struct sockaddr *)&addr, sizeof(addr));
    if (ret < 0)
    {
        printf("connect error\n");
    }

    char buf[1024];
    while (1)
    {
        scanf("%s", buf);
        ret = send(sockfd, buf, 1024, 0);
        if (ret < 0)
        {
            printf("send error\n");
        }
        memset(buf, 0, 1024);
        ret = recv(sockfd, buf, 9, 0);
        if (ret < 0)
        {
            printf("recv error\n");
        }
        printf("%s\n", buf);
    }
    close(sockfd);
}