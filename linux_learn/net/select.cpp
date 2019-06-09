#include <sys/select.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <vector>

// int main()
// {
//     fd_set rd;
//     struct timeval tv;
//     int err;

//     FD_ZERO(&rd);
//     FD_SET(STDIN_FILENO, &rd);

//     tv.tv_sec = 5;
//     tv.tv_usec = 0;

//     err = select(1, &rd, NULL, NULL, &tv);

//     if (err == 0)
//     {
//         printf("select time out\n");
//     }
//     else if (err == -1)
//     {
//         printf("fail to select\n");
//     }
//     else
//     {
//         printf("data is ok\n");
//     }

//     return 0;

// }

// int main()
// {

//     int sockfd = socket(AF_INET, SOCK_STREAM, 0);

//     if (sockfd < 0)
//     {
//         printf("scokfd error");
//     }

//     struct sockaddr_in addr;
//     addr.sin_family = AF_INET;
//     addr.sin_port = htons(9000);
//     addr.sin_addr.s_addr = INADDR_ANY;

//     int ret = bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));
//     if (ret < 0)
//     {
//         printf("bind error");
//     }

//     ret = listen(sockfd, 5);
//     if (ret < 0)
//     {
//         printf("listen error");
//     }

//     struct sockaddr_in connaddr;
//     socklen_t connaddrLen = sizeof(connaddr);
//     int connfd = accept(sockfd, (struct sockaddr *)&connaddr, &connaddrLen);
//     if (connfd < 0)
//     {
//         printf("connfd error");
//     }

//     char buf[1024] = {0};

//     fd_set read_fds;
//     fd_set execption_fds;
//     FD_ZERO(&read_fds);
//     FD_ZERO(&execption_fds);

//     while (1)
//     {
//         FD_SET(connfd, &read_fds);
//         FD_SET(connfd, &execption_fds);

//         ret = select(connfd + 1, &read_fds, NULL, &execption_fds, NULL);
//         if (ret < 0)
//         {
//             printf("select error!\n");
//         }
//         else if (ret == 0)
//         {
//             printf("select time out\n");
//         }

//         if (FD_ISSET(connfd, &read_fds))
//         {
//             ret = recv(connfd, buf, 1023, 0);
//             if (ret < 0)
//             {
//                 break;
//             }
//             printf("s-data: %s\n", buf);
//         }
//         else if (FD_ISSET(connfd, &execption_fds))
//         {
//             ret = recv(connfd, buf, sizeof(buf) - 1, MSG_OOB);
//             if (ret <= 0)
//             {
//                 break;
//             }

//             printf("exec data: %s \n", buf);
//         }
//     }
//     close(connfd);
//     close(sockfd);
// }

int main()
{

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0)
    {
        printf("scokfd error");
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9000);
    addr.sin_addr.s_addr = INADDR_ANY;

    int ret = bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));
    if (ret < 0)
    {
        printf("bind error");
    }

    ret = listen(sockfd, 5);
    if (ret < 0)
    {
        printf("listen error");
    }

    struct sockaddr_in connaddr;
    socklen_t connaddrLen = sizeof(connaddr);

    char buf[1024] = {0};
    fd_set read_fds;
    fd_set write_fds;

    // connfd数组
    std::vector<int> connfds;
    printf("server is watting!\n");
    int maxfd = sockfd;
    while (1)
    {
        // 每次需要清空集合，否则不能检测描述符变化
        FD_ZERO(&read_fds);
        FD_ZERO(&write_fds);
        FD_SET(sockfd, &read_fds);
        int len = connfds.size();
        for (int i = 0; i < len; ++i)
        {
            FD_SET(connfds[i], &read_fds);
            FD_SET(connfds[i], &write_fds);
        }

        ret = select(maxfd + 1, &read_fds, &write_fds, NULL, NULL);
        if (ret < 0)
        {
            printf("select error!\n");
        }
        else if (ret == 0)
        {
            printf("select time out\n");
        }
        else
        {
            // 判断是否有读事件
            if (FD_ISSET(sockfd, &read_fds))
            {
                struct sockaddr_in connaddr;
                socklen_t connaddrLen = sizeof(connaddr);
                int connfd = accept(sockfd, (struct sockaddr *)&connaddr, &connaddrLen);
                if (connfd < 0)
                {
                    printf("accept error");
                }
                printf("sockt = %d ip=%s:port=%d\n", connfd,
                       inet_ntoa(connaddr.sin_addr), ntohs(connaddr.sin_port));
                maxfd = connfd;
                // 将其加入监听队列
                connfds.push_back(connfd);
            }
            else
            {
                // 有写事件的connfd 处理
                int len = connfds.size();
                for (int i = 0; i < len; i++)
                {
                    if (connfds[i] != -1 && FD_ISSET(connfds[i], &read_fds))
                    {
                        ret = recv(connfds[i], buf, 1024, 0);
                        if (ret < 0)
                        {
                            perror("read error:");
                            break;
                        }
                        if (ret == 0)
                        {
                            // 客户端断开连接
                            FD_CLR(connfds[i], &read_fds);
                            std::vector<int>::iterator iter = connfds.begin();
                            while (iter != connfds.end())
                            {
                                if (connfds[0] == *iter)
                                {
                                    iter = connfds.erase(iter);
                                    break;
                                }
                                else
                                {
                                    ++iter;
                                }
                            }
                            close(connfds[i]);
                        }

                        printf("len: %d data: %s\n", ret, buf);

                        // 写事件
                        if (connfds[i] != -1 && FD_ISSET(connfds[i], &write_fds))
                        {
                            int ret = send(connfds[i], "Received", 9, 0);
                            if (ret < 0)
                            {
                                perror("send error:");
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    int len = connfds.size();
    for (int i = 0; i < len; i++)
    {
        close(connfds[i]);
    }

    return 0;
}
