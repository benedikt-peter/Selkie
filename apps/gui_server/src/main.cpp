#include <vector>

#include <selkie/game_loop.hpp>
#include <selkie/system.hpp>
#include <selkie/world.hpp>

#include "gui.hpp"
#include "main_window.hpp"

using namespace selkie;

int main(int, char**)
{
  MainWindow main_window{};

  World world{};

  std::vector<ISystem*> systems{};

  GameLoop game_loop{};

  RunGUI(
    [&main_window, &world, &systems, &game_loop]()
    {
      game_loop.Tick(world, systems);

      main_window.Render();
    });
}