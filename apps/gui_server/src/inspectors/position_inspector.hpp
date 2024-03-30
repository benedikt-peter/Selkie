#pragma once

#include <imgui.h>

#include "selkie/world.hpp"

#include "component_inspector.hpp"
#include "selkie/components.hpp"

namespace selkie
{

  class PositionInspector : public BaseComponentInspector
  {
    public:
      explicit PositionInspector(World& world) :
        BaseComponentInspector(world)
      {
      }

      void Render(entt::entity entity) override
      {
        auto& position = GetRegistry().get<Position>(entity);

        if (ImGui::TreeNode("Position"))
        {
          ImGui::InputFloat("X", &position.position.x);
          ImGui::InputFloat("Y", &position.position.y);

          ImGui::TreePop();
        }
      }
  };

} // selkie
