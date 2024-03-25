#include <enet.h>
#include <spdlog/spdlog.h>

int main() {
  if (enet_initialize() != 0) {
    spdlog::error("An error occurred while initializing ENet.");
    return 1;
  }

  ENetAddress address = {0};

  address.host = ENET_HOST_ANY; /* Bind the server to the default localhost.     */
  address.port = 7777; /* Bind the server to port 7777. */

#define MAX_CLIENTS 32

  /* create a server */
  ENetHost* server = enet_host_create(&address, MAX_CLIENTS, 2, 0, 0);

  if (server == nullptr) {
    spdlog::error("An error occurred while trying to create an ENet server host.");
    return 1;
  }

  spdlog::info("Started a server...");

  ENetEvent event;

  while (enet_host_service(server, &event, 10000) > 0) {
    switch (event.type) {
      case ENET_EVENT_TYPE_CONNECT:
        char buffer[INET6_ADDRSTRLEN];
        inet_ntop(AF_INET6, &event.peer->address.host, buffer, INET6_ADDRSTRLEN);
        spdlog::info("A new client connected from {}:{}.", buffer, event.peer->address.port);
        /* Store any relevant client information here. */
        event.peer->data = (void*) "Client information";
        break;

      case ENET_EVENT_TYPE_RECEIVE:
        spdlog::info("A packet of length {} containing {} was received from {} on channel {}.",
                     event.packet->dataLength,
                     (const char*) event.packet->data,
                     (const char*) event.peer->data,
                     event.channelID);
        /* Clean up the packet now that we're done using it. */
        enet_packet_destroy(event.packet);
        break;

      case ENET_EVENT_TYPE_DISCONNECT:
        spdlog::info("{} disconnected.", event.peer->data);
        /* Reset the peer's client information. */
        event.peer->data = nullptr;
        break;

      case ENET_EVENT_TYPE_DISCONNECT_TIMEOUT:
        spdlog::info("{} disconnected due to timeout.", event.peer->data);
        /* Reset the peer's client information. */
        event.peer->data = nullptr;
        break;

      case ENET_EVENT_TYPE_NONE:
        break;
    }
  }

  enet_host_destroy(server);
  enet_deinitialize();
  return 0;
}
