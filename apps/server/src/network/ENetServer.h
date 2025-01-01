#pragma once

#include <cstdint>

#include <enet.h>
#include <spdlog/spdlog.h>

namespace selkie {
  constexpr std::size_t MaxClients = 10;

  template<typename TSerializer>
  class ENetServer {
  public:
    ENetServer(std::uint16_t port, const TSerializer& serializer)
      : m_port{port},
        m_serializer{&serializer} {
      if (enet_initialize() != 0) {
        throw std::runtime_error{"An error occurred while initializing ENet."};
      }

      const ENetAddress address{
        .host = ENET_HOST_ANY,
        .port = m_port
      };

      m_server = enet_host_create(&address, MaxClients, 2, 0, 0);

      if (!m_server) {
        throw std::runtime_error{"An error occurred while trying to create an ENet server host."};
      }
    }

    ~ENetServer() {
      enet_host_destroy(m_server);
      enet_deinitialize();
    }

    void Run() {
      ENetEvent event{};

      while (enet_host_service(m_server, &event, 10000) > 0) {
        switch (event.type) {
          case ENET_EVENT_TYPE_CONNECT: {
            char buffer[INET6_ADDRSTRLEN];
            inet_ntop(AF_INET6, &event.peer->address.host, buffer, INET6_ADDRSTRLEN);
            spdlog::info("A new client connected from {}:{}.", buffer, event.peer->address.port);
            event.peer->data = (void *) "Client information";
            break;
          }

          case ENET_EVENT_TYPE_RECEIVE: {
            spdlog::info("A packet of length {} containing {} was received from {} on channel {}.",
                         event.packet->dataLength,
                         (const char *) event.packet->data,
                         (const char *) event.peer->data,
                         event.channelID);
            /* Clean up the packet now that we're done using it. */
            enet_packet_destroy(event.packet);
            break;
          }

          case ENET_EVENT_TYPE_DISCONNECT: {
            spdlog::info("{} disconnected.", event.peer->data);
            /* Reset the peer's client information. */
            event.peer->data = nullptr;
            break;
          }

          case ENET_EVENT_TYPE_DISCONNECT_TIMEOUT: {
            spdlog::info("{} disconnected due to timeout.", event.peer->data);
            /* Reset the peer's client information. */
            event.peer->data = nullptr;
            break;
          }

          case ENET_EVENT_TYPE_NONE:
            break;
        }
      }
    }

  private:
    std::uint16_t m_port;
    const TSerializer* m_serializer;
    ENetHost* m_server;
  };
}
