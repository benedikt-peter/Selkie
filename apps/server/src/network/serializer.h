#pragma once

#include <span>

#include "message.h"

namespace selkie {

  template<typename TImpl, typename TMessage>
  concept Deserializer =
  Message<TMessage> && requires(TImpl &impl, TMessage message, std::span<const std::byte> buffer) {
    { impl.template derialize<TMessage>(buffer) } -> std::same_as<TMessage>;
  };

}