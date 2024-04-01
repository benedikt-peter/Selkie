#pragma once

#include <imgui.h>

#include "selkie/world.hpp"

#include "component_inspector.hpp"
#include "selkie/components.hpp"

namespace selkie
{

  class HitboxInspector : public BaseComponentInspector
  {
    public:
      explicit HitboxInspector(World& world) :
        BaseComponentInspector(world)
      {
      }

      void Render(entt::entity entity) override
      {
        auto& hitbox = GetRegistry().get<Hitbox>(entity);

        if (ImGui::TreeNode("Hitbox"))
        {
          ImGui::InputFloat("Radius", &hitbox.radius);

          ImGui::TreePop();
        }
      }
  };

} // selkie
