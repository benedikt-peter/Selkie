#include "network/enetserver.h"
#include "network/msgpackserializer.h"
#include "network/eventsbuffer.h"
#include "network/message.h"

using namespace selkie;

enum class ClientToServerMessageType : IntegralMessageType {
  Ping
};

template<ClientToServerMessageType MessageType>
struct ClientToServerMessage
{
  consteval static ClientToServerMessageType getMessageType() {
    return MessageType;
  }

  static_assert(Message<ClientToServerMessage, ClientToServerMessageType>);
};

struct PingMessage : ClientToServerMessage<ClientToServerMessageType::Ping> {
  double serverTime;

  MSGPACK_DEFINE(serverTime);
};

int main() {
  selkie::ENetServer server{7777};

  selkie::EventsBuffer eventsBuffer{};
  eventsBuffer.registerMessageType<ClientToServerMessageType, PingMessage>(selkie::MsgPackSerializer{});

  while (true) {
    server.processEvents(eventsBuffer);
  }
  return 0;
}
