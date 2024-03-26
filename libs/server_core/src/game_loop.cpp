#include "selkie/game_loop.hpp"

namespace selkie
{
  std::chrono::duration<float> GameLoop::Tick(selkie::World& world, std::span<ISystem*> systems)
  {
    return std::chrono::duration<float>();
  }
}


