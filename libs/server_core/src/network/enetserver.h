#pragma once

#include <memory>
#include <vector>

#include "../../../protocol/include/messagequeue.h"

struct _ENetHost; // NOLINT(*-reserved-identifier)

namespace selkie {
  constexpr std::size_t MaxClients = 10;

  class EventsBuffer {
  public:
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
    std::vector<ConnectEvent> connectQueue_;
    std::vector<DisconnectEvent> disconnectQueue_;
    std::vector<TimeoutEvent> timeoutQueue_;
  };

  class ENetServer {
  public:
    explicit ENetServer(std::uint16_t port);

    ~ENetServer();

    ENetServer(const ENetServer &) = delete;

    ENetServer &operator=(const ENetServer &) = delete;

    ENetServer(ENetServer &&) noexcept;

    ENetServer &operator=(ENetServer &&) noexcept;

    void processEvents(EventsBuffer& eventsCollector, MessageQueue &messageCollector);

  private:
    std::unique_ptr<_ENetHost, void (*)(_ENetHost *)> m_server;
  };
}
