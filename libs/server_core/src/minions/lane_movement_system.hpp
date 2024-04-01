#pragma once

#include "selkie/system.hpp"

namespace selkie
{

  class LaneMovementSystem : public BaseSystem
  {
    public:
      explicit LaneMovementSystem(World& world);

      void Update(Time time) override;
  };

} // selkie
