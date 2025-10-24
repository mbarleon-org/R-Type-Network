#pragma once

#include <RTypeNet/Api.hpp>
#include <array>
#include <cstddef>
#include <cstdint>
#include <span>

#if defined(_WIN32)
    #include <winsock2.h>
#else
    #include <poll.h>
#endif

namespace rtype::network {

#if defined(_WIN32)

typedef SOCKET Handle;
typedef unsigned long NFDS;
typedef int BufLen;
constexpr auto INVALID_SOCK = INVALID_SOCKET;

#else

typedef int Handle;
typedef nfds_t NFDS;
typedef size_t BufLen;
constexpr auto INVALID_SOCK = -1;

#endif

enum class Protocol : uint8_t { UDP, TCP };

struct RTYPE_NET_API PollFD {
        Handle handle;
        short events;
        short revents;
};

struct RTYPE_NET_API Endpoint {
        std::array<std::uint8_t, 16> ip{};
        std::uint16_t port{};
        bool operator==(const Endpoint &other) const noexcept = default;
};

inline constexpr std::size_t IPv4Offset = 12;
inline constexpr std::size_t IPv4Length = 4;

inline bool isIPv6(const Endpoint &endpoint) noexcept
{
    bool first12_zero = true;

    for (std::size_t i = 0; i < IPv4Offset; ++i) {
        if (endpoint.ip[i] != 0) {
            first12_zero = false;
            break;
        }
    }
    if (first12_zero) {
        return false;
    }
    bool first10_zero = true;
    for (std::size_t i = 0; i < IPv4Offset - 2; ++i) {
        if (endpoint.ip[i] != 0) {
            first10_zero = false;
            break;
        }
    }
    if (first10_zero && endpoint.ip[10] == 0xff && endpoint.ip[11] == 0xff) {
        return false;
    }
    return true;
}

inline bool isIPv4(const Endpoint &endpoint) noexcept
{
    return !isIPv6(endpoint);
}

struct RTYPE_NET_API Socket {
        Endpoint endpoint{};
        Handle handle{};
        Protocol protocol{};
        bool operator==(const Socket &other) const noexcept = default;
};

}// namespace rtype::network
