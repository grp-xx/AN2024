#include <algorithm>
#include <cstdlib>
#include <socket.hpp>
#include <sockaddress.hpp>
#include <sys/socket.h>
#include <thread>
#include <iostream>

void reply_to_clt(npl::socket<AF_INET, SOCK_STREAM> connected, npl::sockaddress<AF_INET> client)
{           
    for(;;)
    {
        auto buff = connected.read(80);
        if (buff.empty())
            break;
        std::transform(buff.begin(),buff.end(),buff.begin(),::toupper);
        connected.write(buff);
    }    
    std::cout << "Disconnected from client " << client.host() << std::endl;
    connected.close();
}

int main()
{
    int port=12000;
    npl::sockaddress<AF_INET> srv_addr(port);
    npl::socket<AF_INET, SOCK_STREAM> sock;
    sock.set_reuseaddr();
    sock.bind(srv_addr);
    sock.listen();

    for(;;)
    {
        auto [connected_sock,client] = sock.accept();
        std::cout << "Connected to client " << client.host() << " Port " << client.port() << std::endl;

        std::thread t(reply_to_clt,std::move(connected_sock),std::move(client));
        t.detach();
    }

    sock.close();

    return EXIT_SUCCESS;
}