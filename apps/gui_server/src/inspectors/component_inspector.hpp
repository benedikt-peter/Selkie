#pragma once

#include "entt/entity/entity.hpp"

namespace selkie
{

  class IComponentInspector
  {
    public:
      virtual ~IComponentInspector() = default;

      virtual void Render(entt::entity entity) const = 0;
  };

} // selkie
