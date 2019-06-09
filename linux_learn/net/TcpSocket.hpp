#include <string>
#include <sys/socket.h>
#include <errno.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <arpa/inet.h>

using std::string;

class TcpSocket
{
private:
    int _sock;
public:
    TcpSocket():_sock(-1){}
    bool Socket();
    void setSocket(int socket)
    {
        _sock = socket;
    }
    bool Bind(string ip, uint16_t port);
    bool Connect(struct sockaddr_in *addr);
    bool Listen(int backlog);
    bool Accept(TcpSocket &sock, struct sockaddr_in *addr);
    bool Send(string &data);
    bool Recv(string &data);
    void Close(){
        close(_sock);
        _sock = -1;
    }
};

bool TcpSocket::Socket()
{
    _sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (_sock < 0)
    {
        perror("socket create error");
        return false;
    }
    return true;
}

bool TcpSocket::Bind(string ip, uint16_t port)
{
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip.c_str());
    int ret = bind(_sock, (struct sockaddr*)&addr, sizeof(struct sockaddr));
    if (ret < 0)
    {
        perror("bind error");
        return false;
    }
    return true;
}

bool TcpSocket::Connect(struct sockaddr_in *addr)
{
    int ret = connect(_sock, (struct sockaddr*)addr, sizeof(struct sockaddr));
    if (ret < 0)
    {
        perror("connect error");
        return false;
    }
    return true;
}

// 输出型参数
bool TcpSocket::Accept(TcpSocket &sock, struct sockaddr_in *addr)
{
    socklen_t len = sizeof(struct sockaddr);
    // 返回新的socket
    int nSocket = accept(_sock, (struct sockaddr*)addr, &len);
    if (nSocket < 0)
    {
        return false;
    }
    sock.setSocket(nSocket);
    return true;
}

bool TcpSocket::Listen(int backlog)
{
    int ret = listen(_sock, backlog);
    if (ret != 0)
    {
        perror("listen error");
        return false;
    }
    return true;
}
bool TcpSocket::Recv(string &data)
{
    char buff[4096] = {0};
    int ret = recv(_sock, buff, 4096, 0);
    if (ret == 0)
    {
        return false;
    }
    
    if (ret < 0)
    {
        perror("recv error");
        return false;
    }
    data.assign(buff);
    return true;
}
bool TcpSocket::Send(string &data)
{
    int ret = send(_sock, data.c_str(), data.size(), 0);
    if (ret == 0)
    {
        return false;
    }
    if (ret < 0)
    {
        perror("send error");
        return false;
    }
    return true;
}