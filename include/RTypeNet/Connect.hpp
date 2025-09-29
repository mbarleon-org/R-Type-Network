#pragma once

#include <RTypeNet/Api.hpp>
#include <RTypeNet/Interfaces.hpp>

namespace rtype::network {

[[nodiscard]] RTYPE_NET_API Handle connect(const Endpoint &mine, const Endpoint &endpoint, Protocol p) noexcept;

}// namespace rtype::network
