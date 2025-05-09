#pragma once

#include <memory>
#include <span>
#include <vector>

#include "boost/core/noncopyable.hpp"

#include "message.h"
#include "serializer.h"

namespace selkie {
  class MessageQueue {
  public:
    template<MessageType TMessageType, Message<TMessageType> TMessage, Serializer<TMessage, TMessageType> TSerializer>
    void registerMessageType(TSerializer &&serializer) {
      const auto messageTypeIndex = static_cast<IntegralMessageType>(TMessage::getMessageType());
      const auto requiredSize = messageTypeIndex + 1;
      if (messageStores_.size() < requiredSize) {
        messageStores_.resize(requiredSize);
      }

      auto &queuePtr = messageStores_[messageTypeIndex];
      if (!queuePtr) {
        queuePtr = std::make_unique<MessageStore < TMessageType, TMessage, TSerializer>>(std::forward<TSerializer>(serializer));
      }
    }

    void pushMessage(IntegralMessageType messageType, std::span<const std::byte> buffer) {
      if (messageStores_.size() <= messageType) {
        return;
      }

      auto &queuePtr = messageStores_[messageType];
      if (!queuePtr) {
        return;
      }

      queuePtr->push(buffer);
    }

  private:
    class IMessageStore : boost::noncopyable {
    public:
      virtual ~IMessageStore() = default;

      virtual void clear() = 0;

      virtual void push(std::span<const std::byte> buffer) = 0;
    };

    template<MessageType TMessageType, Message<TMessageType> TMessage, Serializer<TMessage, TMessageType> TSerializer>
    class MessageStore : public IMessageStore {
    public:
      explicit MessageStore(TSerializer &&serializer)
          : serializer_{std::move(serializer)}, messages_{} {}

      void clear() override {
        messages_.clear();
      }

      void push(TMessage message) {
        messages_.push_back(message);
      }

      void push(std::span<const std::byte> buffer) override {
        messages_.push_back(serializer_.template deserialize<TMessage>(buffer));
      }

      std::span<const TMessage> get() const {
        return messages_;
      }

    private:
      TSerializer serializer_;
      std::vector<TMessage> messages_;
    };

    std::vector<std::unique_ptr<IMessageStore>> messageStores_;
  };
}