#pragma once

#include <memory>
#include <span>
#include <vector>

#include "events.h"
#include "message.h"

namespace selkie {
  class IMessageQueue {
  public:
    explicit IMessageQueue(MessageType messageType) : messageType_{messageType} {}

    virtual ~IMessageQueue() = default;

    IMessageQueue(const IMessageQueue &) = delete;

    IMessageQueue &operator=(const IMessageQueue &) = delete;

    IMessageQueue(IMessageQueue &&) = default;

    IMessageQueue &operator=(IMessageQueue &&) = default;

  private:
    MessageType messageType_;
  };

  template<Message TMessage>
  class MessageQueue : public IMessageQueue {
  public:
    MessageQueue() : IMessageQueue{TMessage::getMessageType()} {}

    void push(TMessage &&message) {
      messages_.push_back(message);
    }

    std::span<const TMessage> get() const {
      return messages_;
    }

  private:
    std::vector<TMessage> messages_{};
  };

  class EventsBuffer {
  public:
    void pushMessage(MessageType messageType, std::span<const std::byte> data) {
      const auto requiredSize = messageType + 1;
      if (messageQueues_.size() < requiredSize) {
        messageQueues_.resize(requiredSize);
      }

      auto &queuePtr = messageQueues_[messageType];
      if (!queuePtr) {
        queuePtr = std::make_unique<MessageQueue<TMessage>>();
      }

      queuePtr->push(message);
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
    std::vector<std::unique_ptr<IMessageQueue>> messageQueues_;
    std::vector<ConnectEvent> connectQueue_;
    std::vector<DisconnectEvent> disconnectQueue_;
    std::vector<TimeoutEvent> timeoutQueue_;
  };
}