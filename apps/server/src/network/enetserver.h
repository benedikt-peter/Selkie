#pragma once

#include <cstdint>
#include <memory>

#include "eventsbuffer.h"

class ENetHost;

namespace selkie {
  constexpr std::size_t MaxClients = 10;

  class ENetServer {
  public:
    explicit ENetServer(std::uint16_t port);

    ~ENetServer();

    ENetServer(const ENetServer &) = delete;

    ENetServer &operator=(const ENetServer &) = delete;

    ENetServer(ENetServer &&) noexcept;

    ENetServer &operator=(ENetServer &&) noexcept;

    void processEvents(EventsBuffer& collector);

  private:
    std::unique_ptr<ENetHost, void (*)(ENetHost *)> m_server;
  };
}
