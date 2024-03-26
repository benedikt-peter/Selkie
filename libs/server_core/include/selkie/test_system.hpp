#pragma once

#include "system.hpp"

namespace selkie
{
  class TestSystem : ISystem
  {
    public:
      void Update(World& world) override;
  };
}
