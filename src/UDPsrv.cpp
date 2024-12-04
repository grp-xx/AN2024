#include <algorithm>
#include <cctype>
#include <socket.hpp>
#include <sockaddress.hpp>
#include <string>
#include <iostream>
#include <sys/socket.h>

int main() {
    auto srv_port=10000;
    npl::socket<AF_INET, SOCK_DGRAM> sock;
    npl::sockaddress<AF_INET> srv_addr(srv_port);
    // npl::sockaddress<AF_INET> srv_addr("127.0.0.1",srv_port);
    sock.bind(srv_addr);

    for(;;) {
        auto [buff,client] = sock.recvfrom(80);
        std::cout << "Received request from host: " << client.host() << " Port: " << client.port() << std::endl;

        std::string text(buff.begin(),buff.end());
        std::transform(text.begin(),text.end(),text.begin(),::toupper);

        sock.sendto(npl::buffer(text.begin(),text.end()), client);

    }

    sock.close();


    return EXIT_SUCCESS;






}
