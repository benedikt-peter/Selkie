#pragma once

#include <concepts>
#include <cstdint>
#include <type_traits>

namespace selkie {

  using IntegralMessageType = std::uint8_t;
  constexpr auto MessageTypeSize = sizeof(IntegralMessageType);

  template<typename TMessageType>
  concept MessageType = std::is_enum_v<TMessageType> &&
                        !std::is_convertible_v<TMessageType, std::underlying_type_t<TMessageType>> &&
                        std::same_as<std::underlying_type_t<TMessageType>, IntegralMessageType> &&
                        sizeof(TMessageType) ==
                        MessageTypeSize;

  template<typename TMessage, typename TMessageType>
  concept Message = MessageType<TMessageType> && requires(const TMessage &message) {
    { TMessage::getMessageType() } -> std::same_as<TMessageType>;
  };

}