#include <RTypeNet/Listen.hpp>
#include <RTypeNet/Subplatform/Listen.hpp>

RTYPE_NET_API rtype::network::Socket rtype::network::listen(const Endpoint &e, Protocol p)
{
    return subplatform::listen(e, p);
}
