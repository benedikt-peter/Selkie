#pragma once

#include <span>

#include "message.h"

namespace selkie {

  template<typename TImpl, typename TMessage, typename TMessageType>
  concept Serializer =
  Message<TMessage, TMessageType> && MessageType<TMessageType> &&
  requires(TImpl &impl, TMessage message) {
    { impl.template serialize<TMessage>(message, std::span<std::byte>{}) } -> std::same_as<std::size_t>;
    { impl.template deserialize<TMessage>(std::span<const std::byte>{}) } -> std::same_as<TMessage>;
  };

}