#pragma once

#include <span>

#include <msgpack.hpp>

namespace selkie {
  class MsgPackSerializer {
  public:
    template<typename TMessage>
    std::size_t Serialize(std::span<std::byte> buffer, const TMessage& message) {
      msgpack::pack(m_buffer, message);

      if (m_buffer.size() > buffer.size()) {
        throw std::runtime_error{"MsgPackSerializer::Serialize(): destination buffer too small"};
      }

      std::memcpy(buffer.data(), m_buffer.data(), m_buffer.size());

      return m_buffer.size();
    }

    template<typename TMessage>
    TMessage Deserialize(std::span<const std::byte> buffer) {
      const auto message_object = msgpack::unpack(reinterpret_cast<const char *>(buffer.data()), buffer.size());
      return message_object.get().convert();
    }

  private:
    msgpack::sbuffer m_buffer;
  };
} // selkie
