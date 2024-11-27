#include <algorithm>
#include <cstdlib>
#include <socket.hpp>
#include <sockaddress.hpp>
#include <sys/socket.h>
#include <iostream>

int main()
{
    int port = 20000;
    npl::sockaddress<AF_INET> srv_addr(port);
    npl::socket<AF_INET, SOCK_STREAM> sock;

    sock.bind(srv_addr);
    sock.listen();

    for(;;)
    {
        auto [connected, client] = sock.accept();
        std::cout << "Connection request from client: " << client.host() << " port: " << client.port() << std::endl;

        auto pid = fork();

        if (pid == 0) {

            npl::buffer buff = connected.read(80);
            std::transform(buff.begin(),buff.end(),buff.begin(),::toupper);
            connected.write(buff);
            connected.close();
            return EXIT_SUCCESS;
        }

        connected.close();
    }
    sock.close();
    return EXIT_SUCCESS;
}