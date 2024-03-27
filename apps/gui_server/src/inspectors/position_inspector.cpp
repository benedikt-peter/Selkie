#include "position_inspector.hpp"

#include <imgui.h>

#include <selkie/components.hpp>

namespace selkie
{
  PositionInspector::PositionInspector(World& world) :
    m_world{&world}
  {
  }

  void PositionInspector::Render(entt::entity entity)
  {
    auto& position = m_world->registry.get<Position>(entity);

    if (ImGui::TreeNode("Position"))
    {
      ImGui::InputFloat2("", position.position.data());

      ImGui::TreePop();
    }
  }
} // selkie