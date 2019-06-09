#include <stdlib.h>
#include <iostream>
#include "UdpSocket.hpp"

using std::cout;
using std::endl;
using std::cin;

#define CHECK(q)      \
    if ((q) == false) \
    {                 \
        return -1;    \
    }

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("input ./UdpServer ip port\n");
    }
    string ip = argv[1];
    uint16_t port = atoi(argv[2]);
    UdpSocket socket;
    // 创建socket
    CHECK(socket.Socket());
    // 绑定
    CHECK(socket.Bind(ip, port));
    // 接收
    string msg;
    // 获取客户端socket信息
    struct sockaddr_in addr;
    while (1)
    {
        CHECK(socket.Recv(msg, &addr));
        cout <<"client say:" << msg << endl;
        cout << "input you want to say:" << endl;
        cin >> msg;
        CHECK(socket.Send(msg, &addr));
    }
    socket.Close();

    return 0;
}