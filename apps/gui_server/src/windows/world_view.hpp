#pragma once

#include <imgui.h>

#include <selkie/vector2.hpp>
#include <selkie/world.hpp>

namespace selkie
{

  class WorldView
  {
    public:
      explicit WorldView(World& world);

      void Render(Vector2 position, Vector2 size);

    private:
      World* m_world;
      float m_scale;
      Vector2 m_offset;

      Vector2 m_view_origin;

      Vector2 ToView(Vector2 position) const;
      ImVec2 ToImGuiView(Vector2 position) const;

      Vector2 GetWorldMin() const;
      Vector2 GetWorldMax() const;
  };

} // selkie
