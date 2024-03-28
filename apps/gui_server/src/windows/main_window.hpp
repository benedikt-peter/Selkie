#pragma once

#include "selkie/world.hpp"

#include "world_inspector.hpp"
#include "world_view.hpp"

namespace selkie
{
  class MainWindow {
    public:
      explicit MainWindow(World& world);

      void Render();

    private:
      WorldInspector m_world_inspector;
      WorldView m_world_view;
      bool m_show_demo;
  };
}