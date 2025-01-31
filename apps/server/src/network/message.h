#pragma once

#include <concepts>
#include <cstdint>
#include <type_traits>

namespace selkie {

  using MessageType = std::uint8_t;

  template<typename TMessage>
  concept Message = requires(const TMessage& message) {
    { TMessage::getMessageType() } -> std::same_as<MessageType>;
  };

}