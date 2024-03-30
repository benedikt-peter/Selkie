#pragma once

#include <memory>
#include <unordered_map>

#include <entt/entt.hpp>

#include "selkie/world.hpp"

#include "../inspectors/component_inspector.hpp"

namespace selkie
{
  class WorldInspector
  {
    public:
      explicit WorldInspector(World& world);

      void Render(float x, float y, float width, float height);

    private:
      World* m_world;
      std::unordered_map<entt::id_type, std::unique_ptr<BaseComponentInspector>> m_inspectors;
  };
}


