#include "RTypeNet/Subplatform/Connect.hpp"
#include <RTypeNet/Interfaces.hpp>
#include <arpa/inet.h>
#include <cstring>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <system_error>
#include <unistd.h>

static int createSocket(rtype::network::Protocol p, int family)
{
    int type = (p == rtype::network::Protocol::TCP) ? SOCK_STREAM : SOCK_DGRAM;
    int proto = (p == rtype::network::Protocol::TCP) ? IPPROTO_TCP : IPPROTO_UDP;
    int s = ::socket(family, type, proto);
    if (s == -1) {
        throw std::system_error(errno, std::system_category(), "socket creation failed");
    }
    return s;
}

RTYPE_NET_API rtype::network::Handle rtype::network::subplatform::connect(const Endpoint &mine, const Endpoint &endpoint,
    Protocol p) noexcept
{
    sockaddr_storage addr;
    std::memset(&addr, 0, sizeof(addr));
    socklen_t addrlen = 0;
    Handle h = createSocket(p, rtype::network::isIPv6(mine) ? AF_INET6 : AF_INET);

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
        addrlen = sizeof(sockaddr_in);
    }
    if (::connect(h, reinterpret_cast<sockaddr *>(&addr), addrlen) < 0) {
        perror("connect failed");
        ::close(h);
        return -1;
    }
    return h;
}
