#pragma once

#include <memory>
#include <span>
#include <vector>

#include <boost/core/noncopyable.hpp>

#include "events.h"
#include "message.h"
#include "serializer.h"

namespace selkie {
  class MessageReceiverBase : boost::noncopyable {
  public:
    explicit MessageReceiverBase(MessageType messageType) : messageType_{messageType} {}

    virtual ~MessageReceiverBase() = default;

    [[nodiscard]]
    MessageType getMessageType() const {
      return messageType_;
    }

    virtual void clear() = 0;

    virtual void push(std::span<const std::byte> buffer) = 0;

  private:
    MessageType messageType_;
  };

  template<Message TMessage, Deserializer<TMessage> TDeserializer>
  class MessageReceiver : public MessageReceiverBase {
  public:
    explicit MessageReceiver(TDeserializer &&deserializer)
        : MessageReceiverBase{TMessage::getMessageType()}, deserializer_{std::forward(deserializer)}, messages_{} {}

    void push(std::span<const std::byte> buffer) override {
      messages_.push_back(deserializer_.derialize(buffer));
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
    template<Message TMessage, Deserializer<TMessage> TDeserializer>
    void registerMessageType(TDeserializer &&deserializer) {
      const auto messageType = TMessage::getMessageType();
      const auto requiredSize = messageType + 1;
      if (messageQueues_.size() < requiredSize) {
        messageQueues_.resize(requiredSize);
      }

      auto &queuePtr = messageQueues_[messageType];
      if (!queuePtr) {
        queuePtr = std::make_unique<MessageReceiver<TMessage, TDeserializer>>(std::forward(deserializer));
      }
    }

    void pushMessage(MessageType messageType, std::span<const std::byte> buffer) {
      if (messageQueues_.size() <= messageType) {
        return;
      }

      auto &queuePtr = messageQueues_[messageType];
      if (!queuePtr || queuePtr->getMessageType() != messageType) {
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
    std::vector<std::unique_ptr<MessageReceiverBase>> messageQueues_;
    std::vector<ConnectEvent> connectQueue_;
    std::vector<DisconnectEvent> disconnectQueue_;
    std::vector<TimeoutEvent> timeoutQueue_;
  };
}