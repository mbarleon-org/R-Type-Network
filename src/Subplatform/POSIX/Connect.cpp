#include "RTypeNet/Subplatform/Connect.hpp"
#include <RTypeNet/Interfaces.hpp>
#include <arpa/inet.h>
#include <cstring>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

RTYPE_NET_API rtype::network::Handle rtype::network::subplatform::connect(Handle socket, const Endpoint &endpoint) noexcept
{
    sockaddr_storage addr;
    std::memset(&addr, 0, sizeof(addr));
    socklen_t addrlen = 0;

    if (isIPv6(endpoint)) {
        sockaddr_in6 *addr6 = reinterpret_cast<sockaddr_in6 *>(&addr);
        addr6->sin6_family = AF_INET6;
        addr6->sin6_port = htons(endpoint.port);
        std::memcpy(&addr6->sin6_addr, endpoint.ip.data(), 16);
        addrlen = sizeof(sockaddr_in6);
    } else {
        sockaddr_in *addr4 = reinterpret_cast<sockaddr_in *>(&addr);
        addr4->sin_family = AF_INET;
        addr4->sin_port = htons(endpoint.port);
        std::memcpy(&addr4->sin_addr, endpoint.ip.data() + rtype::network::IPv4Offset, rtype::network::IPv4Length);
        addrlen = sizeof(sockaddr_in6);
    }
    if (::connect(socket, reinterpret_cast<sockaddr *>(&addr), addrlen) < 0) {
        return -1;
    }
    return socket;
}
