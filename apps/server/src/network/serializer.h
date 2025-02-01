#pragma once

#include <span>

#include "message.h"

namespace selkie {

  template<typename TImpl, typename TMessage, typename TMessageType>
  concept Deserializer =
  Message<TMessage, TMessageType> && MessageType<TMessageType> &&
  requires(TImpl &impl, TMessage message, std::span<const std::byte> buffer) {
    { impl.template deserialize<TMessage>(buffer) } -> std::same_as<TMessage>;
  };

}