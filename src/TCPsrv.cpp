#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <socket.hpp>
#include <sockaddress.hpp>
#include <sys/socket.h>
#include <iostream>

int main()
{
    int port=12000;

    npl::sockaddress<AF_INET> srv_addr(port);
    npl::socket<AF_INET, SOCK_STREAM> sock;
    sock.bind(srv_addr);

    sock.listen();

    for(;;) {
        auto [connected_sock,client] = sock.accept();
        std::cout << "Connected to client " << client.host() << " Port " << client.port() << std::endl;

        npl::buffer buff = connected_sock.read(80);
        std::transform(buff.begin(),buff.end(),buff.begin(),::toupper);
        connected_sock.write(buff);

        connected_sock.close();

    }

    sock.close();

    return EXIT_SUCCESS;
}