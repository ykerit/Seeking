all:TcpThread TcpClient
TcpThread:TcpServer_thread.cpp
	clang++ $^ -o $@ -lpthread
TcpServer:TcpServer.cpp
	clang++ $^ -o $@
TcpClient:TcpClient.cpp
	clang++ $^ -o $@
UdpServer:UdpServer.cpp
	clang++ $^ -o $@
UdpClient:UdpClient.cpp
	clang++ $^ -o $@

.PHONY: clean
clean: 
	rm TcpServer TcpClient TcpThread