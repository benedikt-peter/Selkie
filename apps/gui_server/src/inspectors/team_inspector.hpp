#pragma once

#include <imgui.h>

#include "selkie/world.hpp"

#include "component_inspector.hpp"
#include "selkie/components.hpp"

namespace selkie
{

  class TeamInspector : public BaseComponentInspector
  {
    public:
      explicit TeamInspector(World& world) :
        BaseComponentInspector(world)
      {
      }

      void Render(entt::entity entity) override
      {
        auto& team = GetRegistry().get<Team>(entity);

        if (ImGui::TreeNode("Team"))
        {
          static const char* items[] = {"Blue", "Red"};
          ImGui::Combo("Team", reinterpret_cast<int*>(&team.team_id), items, IM_ARRAYSIZE(items));

          ImGui::TreePop();
        }
      }
  };

} // selkie
