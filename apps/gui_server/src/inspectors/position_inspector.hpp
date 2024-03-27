#pragma once

#include <selkie/world.hpp>

#include "component_inspector.hpp"

namespace selkie
{

  class PositionInspector : public IComponentInspector
  {
    public:
      explicit PositionInspector(World& world);

      void Render(entt::entity entity) override;

    private:
      World* m_world;
  };

} // selkie
