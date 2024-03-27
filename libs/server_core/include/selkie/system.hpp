#pragma once

#include "time.hpp"
#include "world.hpp"

namespace selkie
{
  class ISystem
  {
    public:
      virtual ~ISystem() = default;

      virtual void Update(World& world, Time time) = 0;
  };

} // selkie
