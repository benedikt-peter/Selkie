#pragma once

#include "world.hpp"

namespace selkie
{
  class ISystem
  {
    public:
      virtual ~ISystem() = default;

      virtual void Update(World& world) = 0;
  };

} // selkie
