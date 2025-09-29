#pragma once

#include <RTypeNet/Api.hpp>
#include <RTypeNet/Interfaces.hpp>

namespace rtype::network {

[[nodiscard]] RTYPE_NET_API Handle connect(Handle handle, const Endpoint &e) noexcept;

}// namespace rtype::network
