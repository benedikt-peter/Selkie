#include "network/enetserver.h"
#include "network/msgpackserializer.h"
#include "network/eventsbuffer.h"

int main() {
  selkie::ENetServer server{7777};

  selkie::MsgPackSerializer serializer{};

  selkie::EventsBuffer eventsBuffer{};

  while (true) {
    server.processMessages<>()
  }
  server.Run();

  return 0;
}
