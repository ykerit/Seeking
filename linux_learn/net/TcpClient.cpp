#include "TcpSocket.hpp"
#include <iostream>
#include <stdlib.h>

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
        printf("./TcpServer ip port\n");
    }
    string ip = argv[1];
    uint16_t port = atoi(argv[2]);

    TcpSocket socket;
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip.c_str());
    CHECK(socket.Socket());
    CHECK(socket.Connect(&addr));
    
    string msg;
    while (1)
    {
        cout << "input you want to say:" << endl;
        cin >> msg;
        CHECK(socket.Send(msg));
        CHECK(socket.Recv(msg));
        cout <<"server say:" << msg << endl;
    }
    socket.Close();
    return 0;
}
