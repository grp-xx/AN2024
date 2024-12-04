#include <cstdlib>
#include <socket.hpp>
#include <sockaddress.hpp>
#include <string>
#include <iostream>
#include <sys/socket.h>

int main(int argc, char* argv[])
{
    if (argc < 3) {
        std::cout << "Usage: " << argv[0] << " <server> <port>" << std::endl;
        return (1);
    }

    npl::socket<AF_INET, SOCK_DGRAM> sock;
    npl::sockaddress<AF_INET> srv_addr(argv[1],std::atoi(argv[2]));

    std::string line;
    std::getline(std::cin, line);

    npl::buffer buff(line.begin(),line.end());

    sock.sendto(buff, srv_addr);

    auto [ricevuto, remoto] = sock.recvfrom(80);

    std::cout << "Received text from: " << remoto.host() << " Port: " << remoto.port() << std::endl;

    std::cout << "Testo: " << std::string(ricevuto.begin(),ricevuto.end()) << std::endl;

    sock.close();





    return EXIT_SUCCESS;
}