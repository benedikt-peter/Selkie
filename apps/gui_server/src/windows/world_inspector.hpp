#pragma once

#include <selkie/world.hpp>

namespace selkie
{
  class WorldInspector
  {
    public:
      explicit WorldInspector(World& world);

      void Render();

    private:
      World* m_world;
  };
}


