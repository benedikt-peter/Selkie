#pragma once

#include <imgui.h>

#include "selkie/world.hpp"

#include "component_inspector.hpp"
#include "selkie/components.hpp"

namespace selkie
{

  class TargetingInspector : public BaseComponentInspector
  {
    public:
      explicit TargetingInspector(World& world) :
        BaseComponentInspector(world)
      {
      }

      void Render(entt::entity entity) override
      {
        auto& targeting = GetRegistry().get<Targeting>(entity);

        if (ImGui::TreeNode("Targeting"))
        {
          ImGui::InputFloat("Max Range", &targeting.max_range);

          const auto* debug_info = GetRegistry().try_get<DebugInfo>(targeting.target_entity);
          if (debug_info)
          {
            ImGui::TextUnformatted(fmt::format("Target: {}", debug_info->name).c_str());
          }
          else
          {
            ImGui::TextUnformatted("Target: None");
          }

          ImGui::TreePop();
        }
      }
  };

} // selkie
