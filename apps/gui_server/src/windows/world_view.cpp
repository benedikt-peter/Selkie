#include "world_view.hpp"

#include <spdlog/fmt/bundled/format.h>
#include <imgui.h>

#include <selkie/components.hpp>

#include "../views/minion_view.hpp"

namespace selkie
{
  template<typename TComponent, typename TView>
  void
  CreateView(std::unordered_map<entt::id_type, std::unique_ptr<BaseComponentView>>& views, World& world)
  {
    views[entt::type_id<TComponent>().hash()] = std::make_unique<TView>(world);
  }

  WorldView::WorldView(World& world) :
    BaseView{world}
  {
    CreateView<Minion, MinionView>(m_views, world);
  }

  void WorldView::Render(Vector2 position, Vector2 size)
  {
    ImGui::SetNextWindowPos(ImVec2{position.x, position.y});
    ImGui::SetNextWindowSize(ImVec2{size.x, size.y});

    ImGui::Begin("World", nullptr,
                 ImGuiWindowFlags_NoDecoration |
                 ImGuiWindowFlags_NoBringToFrontOnFocus |
                 ImGuiWindowFlags_NoMove |
                 ImGuiWindowFlags_NoResize |
                 ImGuiWindowFlags_NoCollapse |
                 ImGuiWindowFlags_NoNav
    );

    const auto& io = ImGui::GetIO();

    auto scale = GetScale();
    auto offset = GetOffset();
    if (ImGui::IsWindowHovered())
    {
      const auto mouse_wheel = io.MouseWheel;
      scale = std::clamp(scale * std::pow(2.0f, mouse_wheel), 1.0f, 100.0f);

      if (ImGui::IsMouseDragging(0))
      {
        const auto mouse_drag = io.MouseDelta;
        offset += Vector2{mouse_drag.x, mouse_drag.y} / scale;

        offset = Vector2{
          std::clamp(offset.x, GetWorldMin().x, GetWorldMax().x),
          std::clamp(offset.y, GetWorldMin().y, GetWorldMax().y)
        };
      }
    }

    const auto origin = position + size / 2.0f;

    UpdateView(origin, scale, offset);

    auto* draw_list = ImGui::GetWindowDrawList();

    draw_list->AddRectFilled(ToImGuiView(GetWorldMin()), ToImGuiView(GetWorldMax()), IM_COL32(196, 196, 196, 255));

    const auto& registry = GetRegistry();
    for (const auto& view_entry: m_views)
    {
      const auto type = view_entry.first;
      auto& view = *view_entry.second;

      view.UpdateView(origin, scale, offset);

      const auto storage = registry.storage(type);
      for (const auto entity: *storage)
      {
        if (!view.IsValid(entity))
        {
          continue;
        }

        view.Render(entity);
      }
    }

    ImGui::PushItemWidth(100.0f);
    ImGui::TextUnformatted(fmt::format("Offset ({},{})", offset.x, offset.y).c_str());
    if (ImGui::SliderFloat("Scale", &scale, 1.0f, 100.0f))
    {
      UpdateView(origin, scale, offset);
    }
    ImGui::PopItemWidth();

    ImGui::End();
  }
} // selkie