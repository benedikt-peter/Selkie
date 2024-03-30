#pragma once

#include "selkie/world.hpp"

#include "component_inspector.hpp"

namespace selkie
{

  class DebugInfoInspector : public BaseComponentInspector
  {
    public:
      explicit DebugInfoInspector(World& world) :
        BaseComponentInspector(world)
      {}

      void Render(entt::entity entity) override
      {
      }
  };

} // selkie
