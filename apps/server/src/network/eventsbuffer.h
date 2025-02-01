#pragma once

#include <memory>
#include <span>
#include <vector>

#include <boost/core/noncopyable.hpp>

#include "events.h"
#include "message.h"
#include "serializer.h"

namespace selkie {
  class IMessageReceiver : boost::noncopyable {
  public:
    virtual ~IMessageReceiver() = default;

    virtual void clear() = 0;

    virtual void push(std::span<const std::byte> buffer) = 0;
  };

  template<MessageType TMessageType, Message<TMessageType> TMessage, Deserializer<TMessage, TMessageType> TDeserializer>
  class MessageReceiver : public IMessageReceiver {
  public:
    explicit MessageReceiver(TDeserializer &&deserializer)
        : deserializer_{std::move(deserializer)}, messages_{} {}

    void clear() override {
      messages_.clear();
    }

    void push(std::span<const std::byte> buffer) override {
      messages_.push_back(deserializer_.template deserialize<TMessage>(buffer));
    }

    std::span<const TMessage> get() const {
      return messages_;
    }

  private:
    TDeserializer deserializer_;
    std::vector<TMessage> messages_;
  };

  class EventsBuffer {
  public:
    template<MessageType TMessageType, Message<TMessageType> TMessage, Deserializer<TMessage, TMessageType> TDeserializer>
    void registerMessageType(TDeserializer &&deserializer) {
      const auto messageTypeIndex = static_cast<IntegralMessageType>(TMessage::getMessageType());
      const auto requiredSize = messageTypeIndex + 1;
      if (messageQueues_.size() < requiredSize) {
        messageQueues_.resize(requiredSize);
      }

      auto &queuePtr = messageQueues_[messageTypeIndex];
      if (!queuePtr) {
        queuePtr = std::make_unique<MessageReceiver<TMessageType, TMessage, TDeserializer>>(std::forward<TDeserializer>(deserializer));
      }
    }

    void pushMessage(IntegralMessageType messageType, std::span<const std::byte> buffer) {
      if (messageQueues_.size() <= messageType) {
        return;
      }

      auto &queuePtr = messageQueues_[messageType];
      if (!queuePtr) {
        return;
      }

      queuePtr->push(buffer);
    }

    void pushConnectEvent(ConnectEvent event) {
      connectQueue_.push_back(event);
    }

    void pushDisconnectEvent(DisconnectEvent event) {
      disconnectQueue_.push_back(event);
    }

    void pushTimeoutEvent(TimeoutEvent event) {
      timeoutQueue_.push_back(event);
    }

  private:
    std::vector<std::unique_ptr<IMessageReceiver>> messageQueues_;
    std::vector<ConnectEvent> connectQueue_;
    std::vector<DisconnectEvent> disconnectQueue_;
    std::vector<TimeoutEvent> timeoutQueue_;
  };
}