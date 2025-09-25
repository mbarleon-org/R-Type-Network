#include <RTypeNet/Clock.hpp>
#include <RTypeNet/Subplatform/Clock.hpp>

RTYPE_NET_API uint64_t rtype::network::now_ns() noexcept
{
    return subplatform::now_ns();
}
