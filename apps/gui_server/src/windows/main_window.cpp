#include "main_window.hpp"

#include "imgui.h"

namespace selkie
{
  MainWindow::MainWindow(World& world) :
    m_world_inspector{world},
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

    m_world_inspector.Render();
  }
}


