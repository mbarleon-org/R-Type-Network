#pragma once

#if defined(_WIN32)
    #include <winsock2.h>
#endif

namespace rtype::network {

inline void cleanup() noexcept
{
#ifdef _WIN32
    WSACleanup();
#endif
}

}// namespace rtype::network
