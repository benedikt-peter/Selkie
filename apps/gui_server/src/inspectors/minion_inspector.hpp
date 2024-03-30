#pragma once

#include <imgui.h>

#include "selkie/world.hpp"

#include "component_inspector.hpp"
#include "selkie/components.hpp"

namespace selkie
{

  class MinionInspector : public BaseComponentInspector
  {
    public:
      explicit MinionInspector(World& world) :
        BaseComponentInspector(world)
      {
      }

      void Render(entt::entity entity) override
      {
        auto& minion = GetRegistry().get<Minion>(entity);

        if (ImGui::TreeNode("Minion"))
        {
          ImGui::InputFloat("Radius", &minion.radius);

          static const char* items[] = {"Blue", "Red"};
          ImGui::Combo("Team", reinterpret_cast<int*>(&minion.team_id), items, IM_ARRAYSIZE(items));
//          ImGui::Comb

          ImGui::TreePop();
        }
      }
  };

} // selkie
