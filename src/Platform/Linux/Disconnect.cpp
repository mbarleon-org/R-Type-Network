#include <RTypeNet/Disconnect.hpp>
#include <RTypeNet/Subplatform/Disconnect.hpp>

RTYPE_NET_API void rtype::network::disconnect(Socket &sock) noexcept
{
    subplatform::disconnect(sock);
}
