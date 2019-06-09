#include "TcpSocket.hpp"
#include <iostream>
#include <stdlib.h>
#include <sys/wait.h>
#include <pthread.h>

using std::cin;
using std::cout;
using std::endl;

#define CHECK(q)      \
    if ((q) == false) \
    {                 \
        return -1;    \
    }

void *str_th(void *arg)
{
    TcpSocket *socket = (TcpSocket *)arg;
    string msg;
    while (socket->Recv(msg))
    {
        cout << "client say:" << msg << endl;
        cout << "input you want to say:" << endl;
        cin >> msg;
        socket->Send(msg);
    }
    cout << "conect dispost" << endl;
    socket->Close();
    // delete socket;
    return NULL;
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
    CHECK(socket.Socket());
    CHECK(socket.Bind(ip, port));
    CHECK(socket.Listen(10));
    struct sockaddr_in addr;
    string msg;
    TcpSocket newSocket;
    while (1)
    {
        // 接收客户端消息
        if (socket.Accept(newSocket, &addr) == false)
        {
            continue;
        }
        pthread_t tid;
        pthread_create(&tid, NULL, str_th, (void *)&newSocket);
        pthread_detach(tid);
    }
    socket.Close();
    return 0;
}
