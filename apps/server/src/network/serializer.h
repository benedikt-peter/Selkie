#pragma once

#include <span>

#include "message.h"

namespace selkie {

  template<typename TImpl>
  concept ByteWriter = requires(TImpl &impl, std::span<const std::byte> buffer) {
    impl.write(buffer);
  };

  template<typename TImpl, typename TMessage, typename TWriter>
  concept Serializer = ByteWriter<TWriter> && requires(TImpl &impl, TMessage message, TWriter &buffer) {
    impl.template derialize<TMessage>(message, buffer);
  };

  template<typename TImpl>
  concept Deserializer = requires(TImpl &impl, const std::span<const std::byte> &buffer) {
    impl.deserialize(buffer);
  };

}