#pragma once

#include "selkie/system.hpp"

namespace selkie
{

  class WaypointMovementSystem : public BaseSystem
  {
    public:
      explicit WaypointMovementSystem(World& world);

      void Update(Time time) override;
  };

} // selkie
