#include <RTypeNet/Connect.hpp>
#include <RTypeNet/Subplatform/Connect.hpp>

RTYPE_NET_API rtype::network::Handle rtype::network::connect(Handle socket, const Endpoint &endpoint) noexcept
{
    return subplatform::connect(socket, endpoint);
}
