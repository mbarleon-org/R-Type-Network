#include <RTypeNet/Connect.hpp>
#include <system_error>
#include <winsock2.h>
#include <ws2tcpip.h>

static SOCKET createSocket(rtype::network::Protocol p, int family)
{
    int type = (p == rtype::network::Protocol::TCP) ? SOCK_STREAM : SOCK_DGRAM;
    int proto = (p == rtype::network::Protocol::TCP) ? IPPROTO_TCP : IPPROTO_UDP;
    SOCKET s = ::socket(family, type, proto);
    if (s == INVALID_SOCKET) {
        throw std::system_error(WSAGetLastError(), std::system_category(), "socket creation failed");
    }
    return s;
}

RTYPE_NET_API rtype::network::Handle rtype::network::connect(const Endpoint &mine, const Endpoint &e, Protocol p) noexcept
{
    sockaddr_storage addr{};
    int addrlen = 0;
    Handle h = createSocket(p, rtype::network::isIPv6(mine) ? AF_INET6 : AF_INET);

    if (isIPv6(e)) {
        sockaddr_in6 *a6 = reinterpret_cast<sockaddr_in6 *>(&addr);
        a6->sin6_family = AF_INET6;
        a6->sin6_port = htons(e.port);
        std::memcpy(&a6->sin6_addr, e.ip.data(), 16);
        addrlen = sizeof(sockaddr_in6);
    } else {
        sockaddr_in *a4 = reinterpret_cast<sockaddr_in *>(&addr);
        a4->sin_family = AF_INET;
        a4->sin_port = htons(e.port);
        std::memcpy(&a4->sin_addr, e.ip.data() + rtype::network::IPv4Offset, rtype::network::IPv4Length);
        addrlen = sizeof(sockaddr_in);
    }
    if (::connect(h, reinterpret_cast<sockaddr *>(&addr), addrlen) == SOCKET_ERROR) {
        ::closesocket(h);
        return INVALID_SOCKET;
    }
    return h;
}
