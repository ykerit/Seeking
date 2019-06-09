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
    // 接收
    string msg;
    // 服务端socket信息
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip.c_str());

    while (1)
    {
        cout << "input you want to say:" << endl;
        cin >> msg;
        CHECK(socket.Send(msg, &addr));
        CHECK(socket.Recv(msg, &addr));
        cout <<"server say:" << msg << endl;
    }
    socket.Close();

    return 0;
}