#pragma once

#include "selkie/system.hpp"

namespace selkie
{

  class TargetingSystem : public BaseSystem
  {
    public:
      explicit TargetingSystem(World& world) :
        BaseSystem{world}
      {}

      void Update(Time time) override;
  };

} // selkie
