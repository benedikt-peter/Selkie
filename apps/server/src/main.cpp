#include "network/ENetServer.h"
#include "network/MsgPackSerializer.h"

int main() {
  selkie::MsgPackSerializer serializer{};
  selkie::ENetServer server{7777, serializer};
  server.Run();
  return 0;
}
