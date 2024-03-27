#pragma once

#include "selkie/world.hpp"

#include "world_inspector.hpp"

namespace selkie
{
  class MainWindow {
    public:
      explicit MainWindow(World& world);

      void Render();

    private:
      WorldInspector m_world_inspector;
      bool m_show_demo;
  };
}