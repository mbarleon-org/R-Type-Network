#include <RTypeNet/Send.hpp>
#include <RTypeNet/Subplatform/Send.hpp>

RTYPE_NET_API ssize_t rtype::network::send(Handle handle, const void *buffer, BufLen length, int flags) noexcept
{
    return subplatform::send(handle, buffer, length, flags);
}

RTYPE_NET_API ssize_t rtype::network::sendto(Handle handle, const void *buffer, BufLen length, int flags, const Endpoint &to) noexcept
{
    return subplatform::sendto(handle, buffer, length, flags, to);
}
