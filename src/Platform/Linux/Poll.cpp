#include <RTypeNet/Poll.hpp>
#include <RTypeNet/Subplatform/Poll.hpp>

RTYPE_NET_API int rtype::network::poll(PollFD *fds, NFDS nfds, int timeout) noexcept
{
    return subplatform::poll(fds, nfds, timeout);
}
