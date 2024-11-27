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

    return EXIT_SUCCESS;
}