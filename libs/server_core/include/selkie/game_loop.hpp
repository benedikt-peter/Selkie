#pragma once

#include <chrono>
#include <span>

#include "system.hpp"
#include "world.hpp"

namespace selkie
{
  class GameLoop
  {
    public:
      std::chrono::duration<float> Tick(World& world, std::span<ISystem*> systems);
  };
}
