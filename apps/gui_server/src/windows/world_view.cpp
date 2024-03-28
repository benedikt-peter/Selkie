#include "world_view.hpp"

#include <spdlog/fmt/bundled/format.h>
#include <imgui.h>

#include "selkie/components.hpp"

namespace selkie
{
  constexpr auto ToIm(Vector2 position)
  {
    return ImVec2{position.x, position.y};
  }

  WorldView::WorldView(World& world) :
    m_world{&world},
    m_scale{15.0f},
    m_offset{},
    m_view_origin{}
  {

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

    if (ImGui::IsWindowHovered())
    {
      const auto mouse_wheel = io.MouseWheel;
      m_scale = std::clamp(m_scale * std::pow(2.0f, mouse_wheel), 1.0f, 100.0f);

      if (ImGui::IsMouseDragging(0))
      {
        const auto mouse_drag = io.MouseDelta;
        m_offset += Vector2{mouse_drag.x, mouse_drag.y} / m_scale;

        m_offset = Vector2{
          std::clamp(m_offset.x, GetWorldMin().x, GetWorldMax().x),
          std::clamp(m_offset.y, GetWorldMin().y, GetWorldMax().y)
        };
      }
    }

    m_view_origin = position + size / 2.0f;

    auto* draw_list = ImGui::GetWindowDrawList();

    draw_list->AddRectFilled(ToImGuiView(GetWorldMin()), ToImGuiView(GetWorldMax()), IM_COL32(64, 64, 64, 255));

    for (const auto& entity: m_world->registry.view<DebugInfo, Position>())
    {
      const auto& debug_info = m_world->registry.get<DebugInfo>(entity);
      const auto& current_position = m_world->registry.get<Position>(entity);

      const auto center = ToImGuiView(current_position.position);
      const auto scaled_radius = m_scale * 0.5f;

      draw_list->AddCircleFilled(center, scaled_radius, IM_COL32(255, 255, 0, 255));
      draw_list->AddText(center, IM_COL32(255, 255, 255, 255), debug_info.name.c_str());
    }

    ImGui::PushItemWidth(100.0f);
    ImGui::TextUnformatted(fmt::format("Offset ({},{})", m_offset.x, m_offset.y).c_str());
    ImGui::SliderFloat("Scale", &m_scale, 1.0f, 100.0f);
    ImGui::PopItemWidth();

    ImGui::End();
  }

  Vector2 WorldView::ToView(Vector2 position) const
  {
    const auto scaled_offset = m_scale * m_offset;
    const auto scaled_position = m_scale * position;
    return m_view_origin + scaled_offset + scaled_position;
  }

  ImVec2 WorldView::ToImGuiView(Vector2 position) const
  {
    return ToIm(ToView(position));
  }

  Vector2 WorldView::GetWorldMin() const
  {
    return -m_world->size / 2.0f;
  }

  Vector2 WorldView::GetWorldMax() const
  {
    return m_world->size / 2.0f;
  }
} // selkie