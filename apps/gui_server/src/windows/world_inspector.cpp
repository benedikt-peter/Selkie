#include "world_inspector.hpp"

#include <imgui.h>

#include <spdlog/fmt/bundled/format.h>

#include <selkie/components.hpp>

#include "../inspectors/position_inspector.hpp"
#include "../inspectors/debug_info_inspector.hpp"

namespace selkie
{
  template<typename TComponent, typename TInspector>
  void
  CreateInspector(std::unordered_map<entt::id_type, std::unique_ptr<BaseComponentInspector>>& inspectors, World& world)
  {
    inspectors[entt::type_id<TComponent>().hash()] = std::make_unique<TInspector>(world);
  }

  WorldInspector::WorldInspector(selkie::World& world) :
    m_world{&world},
    m_inspectors{}
  {
    CreateInspector<DebugInfo, DebugInfoInspector>(m_inspectors, world);
    CreateInspector<Position, PositionInspector>(m_inspectors, world);
  }

  void WorldInspector::Render(float x, float y, float width, float height)
  {
    ImGui::SetNextWindowPos(ImVec2{x, y});
    ImGui::SetNextWindowSize(ImVec2{width, height});

    ImGui::Begin("World Inspector", nullptr,
                 ImGuiWindowFlags_NoBringToFrontOnFocus |
                 ImGuiWindowFlags_NoMove |
                 ImGuiWindowFlags_NoResize |
                 ImGuiWindowFlags_NoCollapse |
                 ImGuiWindowFlags_NoNav
    );

    const auto& registry = m_world->GetRegistry();

    for (const auto& entity: registry.view<DebugInfo>())
    {
      const auto& debug_info = registry.get<DebugInfo>(entity);
      if (ImGui::TreeNode(debug_info.name.c_str()))
      {
        for (auto&& curr: registry.storage())
        {
          auto& storage = curr.second;
          if (storage.contains(entity))
          {
            entt::id_type type = curr.first;

            const auto inspector_iter = m_inspectors.find(type);
            if (inspector_iter == m_inspectors.end())
            {
              ImGui::TextUnformatted(fmt::format("Missing: {}", storage.type().name()).c_str());
              continue;
            }

            inspector_iter->second->Render(entity);
          }
        }

        ImGui::TreePop();
      }
    }
    ImGui::End();
  }
}


