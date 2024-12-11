#include <socket.hpp>
#include <sockaddress.hpp>
#include <string>
#include <sys/socket.h>
#include <iostream>

int main(int argc, char* argv[])
{
    if (argc < 3) {
        std::cout << "Usage: " << argv[0] << " <server> <port>" << std::endl;
        return (1);
    }

    npl::socket<AF_INET,SOCK_STREAM> sock;

    std::string srv_ip_addr(argv[1]);
    int srv_port = std::atoi(argv[2]);

    npl::sockaddress<AF_INET> srv_addr(srv_ip_addr,srv_port);

    sock.connect(srv_addr);

    std::string line;

    for(;;)
    {
        std::getline(std::cin,line);
        if (line.empty())
            break;

        npl::buffer buff(line.begin(),line.end());
        sock.write(buff);
        npl::buffer response = sock.read(80);
        std::cout << std::string(response.begin(),response.end()) << std::endl;
    }

    sock.close();


    return EXIT_SUCCESS;
}