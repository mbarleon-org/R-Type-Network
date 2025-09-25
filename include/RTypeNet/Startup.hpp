#pragma once

#if defined(_WIN32)
    #include <system_error>
    #include <winsock2.h>
#endif

namespace rtype::network {

inline void startup()
{
#if defined(_WIN32)
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        throw std::system_error(std::error_code(WSAGetLastError(), std::system_category()), "Socket could not be initialized");
    }
#endif
}

}// namespace rtype::network
