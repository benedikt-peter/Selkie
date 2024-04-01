#pragma once

#include "selkie/system.hpp"

namespace selkie
{

  class MinionSpawnerSystem : public BaseSystem
  {
    public:
      explicit MinionSpawnerSystem(World& world) :
        BaseSystem{world}
      {}

      void Start() override;

      void Update(Time time) override;
  };

} // selkie
