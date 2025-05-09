#include "enetserver.h"

#include "boost/core/noncopyable.hpp"
#include "enet.h"
#include "spdlog/spdlog.h"

namespace selkie {

  static void FreeENetServer(ENetHost *eNetHost) noexcept {
    enet_host_destroy(eNetHost);
    enet_deinitialize();
  }

  ENetServer::ENetServer(std::uint16_t port)
      : m_server{nullptr, FreeENetServer} {
    if (enet_initialize() != 0) {
      throw std::runtime_error{"An error occurred while initializing ENet."};
    }

    const ENetAddress address{
        .host = ENET_HOST_ANY,
        .port = port
    };

    m_server = {enet_host_create(&address, MaxClients, 2, 0, 0), FreeENetServer};

    if (!m_server) {
      throw std::runtime_error{"An error occurred while trying to create an ENet server host."};
    }
  }

  ENetServer::~ENetServer() = default;

  ENetServer::ENetServer(ENetServer &&) noexcept = default;

  ENetServer &ENetServer::operator=(ENetServer &&) noexcept = default;

  void ENetServer::processEvents(EventsBuffer &eventsCollector, MessageQueue &messageCollector) {
    if (!m_server) {
      return;
    }

    ENetEvent event{};

    while (enet_host_service(m_server.get(), &event, 0) > 0) {
      switch (event.type) {
        case ENET_EVENT_TYPE_CONNECT: {
          char buffer[INET6_ADDRSTRLEN];
          inet_ntop(AF_INET6, &event.peer->address.host, buffer, INET6_ADDRSTRLEN);
          spdlog::info("A new client connected from {}:{}.", buffer, event.peer->address.port);
          event.peer->data = (void *) "Client information";

          eventsCollector.pushConnectEvent({});

          break;
        }

        case ENET_EVENT_TYPE_RECEIVE: {
          spdlog::info("A packet of length {} containing {} was received from {} on channel {}.",
                       event.packet->dataLength,
                       (const char *) event.packet->data,
                       (const char *) event.peer->data,
                       event.channelID);

          const auto data = std::span<const std::byte>{reinterpret_cast<std::byte*>(event.packet->data), event.packet->dataLength};
          const auto messageType = static_cast<IntegralMessageType>(data[0]);
          static_assert(sizeof(messageType) == 1);
          const auto payload = data.subspan(MessageTypeSize);

          messageCollector.pushMessage(messageType, data);

          /* Clean up the packet now that we're done using it. */
          enet_packet_destroy(event.packet);
          break;
        }

        case ENET_EVENT_TYPE_DISCONNECT: {
          spdlog::info("{} disconnected.", event.peer->data);
          /* Reset the peer's client information. */
          event.peer->data = nullptr;

          eventsCollector.pushDisconnectEvent({});

          break;
        }

        case ENET_EVENT_TYPE_DISCONNECT_TIMEOUT: {
          spdlog::info("{} disconnected due to timeout.", event.peer->data);
          /* Reset the peer's client information. */
          event.peer->data = nullptr;

          eventsCollector.pushTimeoutEvent({});

          break;
        }

        case ENET_EVENT_TYPE_NONE:
          break;
      }
    }
  }
}


