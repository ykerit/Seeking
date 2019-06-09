#include <string>
#include <errno.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

using std::string;

class UdpSocket
{
private:
    int _sock;

public:
    UdpSocket() : _sock(-1) {}
    bool Socket();
    bool Bind(string &ip, uint16_t port);
    bool Recv(string &data, struct sockaddr_in *addr);
    bool Send(string &buff, struct sockaddr_in *addr);
    void Close();
};

bool UdpSocket::Socket()
{
    _sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (_sock < 0)
    {
        perror("sock create error");
        return false;
    }
    return true;
}
bool UdpSocket::Bind(string &ip, uint16_t port)
{
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    // inet_addr() 将点分十进制ip（192.168.1.1）转化为uint32_t的无符号整型
    addr.sin_addr.s_addr = inet_addr(ip.c_str());

    int ret = bind(_sock, (struct sockaddr*)&addr, sizeof(struct sockaddr));
    if (ret != 0)
    {
        perror("bind error");
        return false;
    }
    return true;
}
bool UdpSocket::Recv(string &data, struct sockaddr_in *addr)
{
    char buff[4096] = {0};
    socklen_t len = sizeof(struct sockaddr_in);
    ssize_t ret = recvfrom(_sock, buff, 4096, 0, (struct sockaddr*)addr, &len);
    if (ret < 0)
    {
        perror("recv error");
        return false;
    }
    data.assign(buff);
    return true;
}
bool UdpSocket::Send(string &buff, struct sockaddr_in *addr)
{
    socklen_t len = sizeof(struct sockaddr_in);
    ssize_t ret = sendto(_sock, buff.c_str(), buff.size(), 0, (struct sockaddr*)addr, len);
    if (ret < 0)
    {
        perror("send error");
        return false;
    }
    return true;
}

void UdpSocket::Close()
{
    close(_sock);
    _sock =  -1;
}