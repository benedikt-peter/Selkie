#include "position_inspector.hpp"

#include <imgui.h>

#include "selkie/components.hpp"

namespace selkie
{
  PositionInspector::PositionInspector(World& world) :
    BaseComponentInspector(world)
  {
  }

  void PositionInspector::Render(entt::entity entity)
  {
    auto& position = GetRegistry().get<Position>(entity);

    if (ImGui::TreeNode("Position"))
    {
      ImGui::InputFloat("X", &position.position.x);
      ImGui::InputFloat("Y", &position.position.y);

      ImGui::TreePop();
    }
  }
} // selkie