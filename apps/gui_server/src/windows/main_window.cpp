#include "main_window.hpp"

#include "imgui.h"

namespace selkie
{
  MainWindow::MainWindow(World& world) :
    m_world_inspector{world},
    m_world_view{world},
    m_show_demo{false}
  {
  }

  void MainWindow::Render()
  {
    if (ImGui::BeginMainMenuBar())
    {
      if (ImGui::BeginMenu("File"))
      {
        if (ImGui::MenuItem("Toggle ImGUI Demo Window"))
        {
          m_show_demo = !m_show_demo;
        }

        if (ImGui::MenuItem("Exit"))
        {
          exit(0);
        }

        ImGui::EndMenu();
      }

      ImGui::EndMainMenuBar();
    }

    if (m_show_demo)
    {
      ImGui::ShowDemoWindow(&m_show_demo);
    }

    const auto* main_viewport = ImGui::GetMainViewport();

    constexpr auto world_inspector_width = 300.0f;
    m_world_inspector.Render(
      main_viewport->WorkPos.x,
      main_viewport->WorkPos.y,
      world_inspector_width,
      main_viewport->WorkSize.y
    );


    m_world_view.Render(
      Vector2
        {
          main_viewport->WorkPos.x + world_inspector_width,
          main_viewport->WorkPos.y
        },
      Vector2
        {
          main_viewport->WorkSize.x - world_inspector_width,
          main_viewport->WorkSize.y
        }
    );
  }
}


