#include <RTypeNet/Recv.hpp>
#include <RTypeNet/Subplatform/Recv.hpp>

RTYPE_NET_API ssize_t rtype::network::recv(Handle handle, void *buffer, BufLen length, int flags) noexcept
{
    return subplatform::recv(handle, buffer, length, flags);
}

RTYPE_NET_API ssize_t rtype::network::recvfrom(Handle handle, void *buffer, BufLen length, int flags, Endpoint &from) noexcept
{
    return subplatform::recvfrom(handle, buffer, length, flags, from);
}
