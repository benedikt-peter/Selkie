#include "selkie/game_loop.hpp"
#include "selkie/systems.hpp"
#include "selkie/world.hpp"

#include "gui/gui.hpp"
#include "windows/main_window.hpp"
#include "test_map.hpp"

using namespace selkie;

int main(int, char**)
{
  World world{CreateMap()};
  auto systems = CreateDefaultSystems(world);
  GameLoop game_loop{world, systems};

  MainWindow main_window{world};

  game_loop.Start();

  RunGUI(
    [&main_window, &game_loop]()
    {
      game_loop.WakeUp();

      main_window.Render();
    });

  game_loop.Shutdown();
}