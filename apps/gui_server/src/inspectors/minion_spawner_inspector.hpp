#pragma once

#include <imgui.h>

#include "selkie/world.hpp"

#include "component_inspector.hpp"
#include "selkie/components.hpp"

namespace selkie
{

  class MinionSpawnerInspector : public BaseComponentInspector
  {
    public:
      explicit MinionSpawnerInspector(World& world) :
        BaseComponentInspector(world)
      {
      }

      void Render(entt::entity entity) override
      {
        auto& minion_spawner = GetRegistry().get<MinionSpawner>(entity);

        if (ImGui::TreeNode("Minion Spawner"))
        {
          ImGui::BeginDisabled();
          ImGui::InputInt("Id", &minion_spawner.minion_spawner_id);
          ImGui::EndDisabled();

          ImGui::InputDouble("Next spawn time", &minion_spawner.next_spawn_time);

          ImGui::TreePop();
        }
      }
  };

} // selkie
