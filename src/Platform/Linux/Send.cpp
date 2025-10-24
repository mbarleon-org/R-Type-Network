#include <RTypeNet/Send.hpp>
#include <RTypeNet/Subplatform/Send.hpp>
#include <cstring>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

RTYPE_NET_API ssize_t rtype::network::send(Handle handle, const void *buffer, BufLen length, int flags) noexcept
{
    return subplatform::send(handle, buffer, length, flags);
}

RTYPE_NET_API ssize_t rtype::network::sendto(Handle handle, const void *buffer, BufLen length, int flags, const Endpoint &to) noexcept
{
    sockaddr_storage addr{};
    socklen_t addrlen = 0;
    if (rtype::network::isIPv6(to)) {
        sockaddr_in6 *a6 = reinterpret_cast<sockaddr_in6 *>(&addr);
        a6->sin6_family = AF_INET6;
        a6->sin6_port = htons(to.port);
        std::memcpy(&a6->sin6_addr, to.ip.data(), 16);
        addrlen = sizeof(sockaddr_in6);
    } else {
        sockaddr_in *a4 = reinterpret_cast<sockaddr_in *>(&addr);
        a4->sin_family = AF_INET;
        a4->sin_port = htons(to.port);
        if (::memcmp(to.ip.data() + rtype::network::IPv4Offset, "\0\0\0\0", 4) == 0
            || ::memcmp(to.ip.data() + rtype::network::IPv4Offset, "\x7F\0\0\x01", 4) == 0) {
            a4->sin_addr.s_addr = htonl(INADDR_LOOPBACK);
        } else {
            std::memcpy(&a4->sin_addr, to.ip.data() + rtype::network::IPv4Offset, rtype::network::IPv4Length);
        }
        addrlen = sizeof(sockaddr_in);
    }
    return ::sendto(handle, buffer, length, flags, reinterpret_cast<sockaddr *>(&addr), addrlen);
}
