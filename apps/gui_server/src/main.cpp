#include "gui.hpp"
#include "main_window.hpp"
#include <selkie/world.hpp>

using namespace selkie;

int main(int, char**)
{
  MainWindow main_window{};

  World world{};

  RunGUI(
    [&main_window]()
    {
      main_window.Render();
    });
}