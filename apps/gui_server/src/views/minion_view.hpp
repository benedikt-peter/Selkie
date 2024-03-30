#pragma once

#include <span>

#include "selkie/components.hpp"
#include "selkie/world.hpp"

#include "view.hpp"

namespace selkie
{

  class MinionView : public BaseComponentView
  {
    public:
      explicit MinionView(World& world);

      void Render(entt::entity entity) override;

      bool IsValid(entt::entity entity) const override;
  };

} // selkie
