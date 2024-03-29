#pragma once

#include <selkie/world.hpp>

#include "component_inspector.hpp"

namespace selkie
{

  class DebugInfoInspector : public IComponentInspector
  {
    public:
      explicit DebugInfoInspector(World&) {}

      void Render(entt::entity entity) const override
      {
      }
  };

} // selkie
