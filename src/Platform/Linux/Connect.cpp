#include <RTypeNet/Connect.hpp>
#include <RTypeNet/Subplatform/Connect.hpp>

RTYPE_NET_API rtype::network::Handle rtype::network::connect(const Endpoint &mine, const Endpoint &endpoint, Protocol p) noexcept
{
    return subplatform::connect(mine, endpoint, p);
}
