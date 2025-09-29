#include <RTypeNet/Connect.hpp>
#include <winsock2.h>
#include <ws2tcpip.h>

RTYPE_NET_API rtype::network::Handle rtype::network::connect(Handle handle, const Endpoint &e) noexcept
{
    sockaddr_storage addr{};
    int addrlen = 0;

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
    if (::connect(handle, reinterpret_cast<sockaddr *>(&addr), addrlen) == SOCKET_ERROR) {
        return INVALID_SOCKET;
    }
    return handle;
}
