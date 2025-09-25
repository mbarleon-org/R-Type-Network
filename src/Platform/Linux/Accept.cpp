#include <RTypeNet/Accept.hpp>
#include <RTypeNet/Subplatform/Accept.hpp>

RTYPE_NET_API rtype::network::Socket rtype::network::accept(Handle serverHandle)
{
    return subplatform::accept(serverHandle);
}
