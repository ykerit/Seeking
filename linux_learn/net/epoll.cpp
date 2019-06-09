#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <iostream>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        std::cout << "sockfd create error!\n";
        return -1;
    }

    //设置重用ip地址和端口号
    int on = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on));
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT, (char *)&on, sizeof(on));

    //将监听socker设置为非阻塞的
    int oldSocketFlag = fcntl(sockfd, F_GETFL, 0);
    int newSocketFlag = oldSocketFlag | O_NONBLOCK;
    if (fcntl(sockfd, F_SETFL, newSocketFlag) == -1)
    {
        close(sockfd);
        std::cout << "set sockfd to nonblock error" << std::endl;
        return -1;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(9000);

    if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
    {
        std::cout << "bind listen socker error." << std::endl;
        close(sockfd);
        return -1;
    }

    if (listen(sockfd, SOMAXCONN) == -1)
    {
        std::cout << "listen error." << std::endl;
        close(sockfd);
        return -1;
    }

    // 创建epoll
    int epollfd = epoll_create(1);
    if (epollfd == -1)
    {
        std::cout << "epollfd create error" << std::endl;
        close(sockfd);
        return -1;
    }

    epoll_event listen_fd_event;
    listen_fd_event.data.fd = sockfd;
    listen_fd_event.events = EPOLLIN;
    listen_fd_event.events |= EPOLLET;

    // 将sockfd绑定到epollfd上
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, sockfd, &listen_fd_event) == -1)
    {
        std::cout << "epoll_ctl error" << std::endl;
        close(sockfd);
        return -1;
    }
    int n;
    while (1)
    {
        epoll_event epoll_events[1024];
        n = epoll_wait(epollfd, epoll_events, 1024, 1000);
        if (n < 0)
        {
            // 被信号中断
            if (errno == EINTR)
            {
                continue;
            }
            break;
        }
        else if (n == 0)
        {
            // 超时
            continue;
        }
        for (int i = 0; i < n; i++)
        {
            // 有可读事件
            if (epoll_events[i].events & EPOLLIN)
            {
                if (epoll_events[i].data.fd == sockfd)
                {
                    // 如果监听socket有可读事件说明有新的客户端连接
                    sockaddr_in connaddr;
                    socklen_t len = sizeof(connaddr);
                    int connfd = accept(sockfd, (struct sockaddr *)&connaddr, &len);
                    if (connfd != -1)
                    {
                        // 设置connsocket为非阻塞
                        int oldSocketFlag = fcntl(connfd, F_GETFL, 0);
                        int newSocketFlag = oldSocketFlag | O_NONBLOCK;
                        if (fcntl(connfd, F_SETFD, newSocketFlag) == -1)
                        {
                            close(connfd);
                            std::cout << "set clientfd to nonblocking error." << std::endl;
                        }
                        else
                        {
                            epoll_event conn_fd_event;
                            conn_fd_event.data.fd = connfd;
                            conn_fd_event.events = EPOLLIN;
                            //取消注释这一行，则使用ET模式
                            conn_fd_event.events |= EPOLLET;
                            if (epoll_ctl(epollfd, EPOLL_CTL_ADD, connfd, &conn_fd_event) != -1)
                            {
                                std::cout << "new client accepted,clientfd: " << connfd << std::endl;
                            }
                            else
                            {
                                std::cout << "add client fd to epollfd error" << std::endl;
                                close(connfd);
                            }
                        }
                    }
                }
                else
                {
                    std::cout << "client fd: " << epoll_events[i].data.fd << " recv data." << std::endl;
                    //普通clientfd
                    char ch;
                    //每次只收一个字节
                    int m = recv(epoll_events[i].data.fd, &ch, 1, 0);
                    if (m == 0)
                    {
                        //对端关闭了连接，从epollfd上移除clientfd
                        if (epoll_ctl(epollfd, EPOLL_CTL_DEL, epoll_events[i].data.fd, NULL) != -1)
                        {
                            std::cout << "client disconnected,clientfd:" << epoll_events[i].data.fd << std::endl;
                        }
                        close(epoll_events[i].data.fd);
                    }
                    else if (m < 0)
                    {
                        //出错
                        if (errno != EWOULDBLOCK && errno != EINTR)
                        {
                            if (epoll_ctl(epollfd, EPOLL_CTL_DEL, epoll_events[i].data.fd, NULL) != -1)
                            {
                                std::cout << "client disconnected,clientfd:" << epoll_events[i].data.fd << std::endl;
                            }
                            close(epoll_events[i].data.fd);
                        }
                    }
                    else
                    {
                        //正常收到数据
                        std::cout << "recv from client:" << epoll_events[i].data.fd << ", " << ch << std::endl;
                    }
                }
            }
        }
    }

    return 0;
}