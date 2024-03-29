#pragma once

#include <unordered_map>

#include <imgui.h>

#include <selkie/vector2.hpp>
#include <selkie/world.hpp>

#include "../views/view.hpp"

namespace selkie
{

  class WorldView : private BaseView
  {
    public:
      explicit WorldView(World& world);

      void Render(Vector2 position, Vector2 size);

    private:
      std::unordered_map<entt::id_type, std::unique_ptr<BaseComponentView>> m_views;
  };

} // selkie
