#include "minion_view.hpp"

#include <imgui.h>

namespace selkie
{
  MinionView::MinionView(World& world) :
    BaseComponentView{world}
  {

  }

  void MinionView::Render(entt::entity entity)
  {
    const auto& registry = GetWorld().registry;

    const auto& minion = registry.get<Minion>(entity);
    const auto& position = registry.get<Position>(entity);
    const auto& debug_info = registry.get<DebugInfo>(entity);

    const auto center = ToImGuiView(position.position);
    const auto scaled_radius = GetScale() * minion.radius;

    auto* draw_list = ImGui::GetWindowDrawList();

    draw_list->AddCircleFilled(center, scaled_radius, IM_COL32(255, 255, 0, 255));

    if (ShouldRenderText())
    {
      const auto text_size = ImGui::CalcTextSize(debug_info.name.c_str());
      const ImVec2 text_center{center.x - text_size.x / 2.0f, center.y - text_size.y / 2.0f};
      draw_list->AddText(text_center, IM_COL32(0, 0, 0, 255), debug_info.name.c_str());
    }
  }

  bool MinionView::IsValid(entt::entity entity) const
  {
    return GetWorld().registry.all_of<Minion, DebugInfo, Position>(entity);
  }

} // selkie