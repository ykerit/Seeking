#include "TcpSocket.hpp"
#include <iostream>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

using std::cin;
using std::cout;
using std::endl;

#define CHECK(q)      \
    if ((q) == false) \
    {                 \
        return -1;    \
    }


void sigcb(int no)
{
    while (waitpid(-1, NULL, WNOHANG) > 0)
    {
        printf("wait child exit!\n");
    }
    
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("./TcpServer ip port\n");
    }

    signal(SIGCHLD, sigcb);

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
        cout << "new client is ready" << endl;
        pid_t pid = fork();
        if (pid < 0)
        {
            printf("child process error\n");
        }
        else if (pid == 0)
        {
            // child process
            while (1)
            {
                CHECK(newSocket.Recv(msg));
                cout << "client say:" << msg << endl;
                // cout << "input you want to say:" << endl;
                // cin >> msg;
                // CHECK(socket.Send(msg));
            }
        }
        newSocket.Close();
    }
    socket.Close();
    return 0;
}
