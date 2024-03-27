#pragma once

#include "system.hpp"

namespace selkie
{
  class TestSystem : public ISystem
  {
    public:
      void Update(World& world, Time time) override;
  };
}
