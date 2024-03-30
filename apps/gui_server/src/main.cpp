#include <memory>
#include <vector>

#include "selkie/minions/lane_movement_system.hpp"
#include "selkie/minions/minion_spawner_system.hpp"
#include "selkie/game_loop.hpp"
#include "selkie/system.hpp"
#include "selkie/world.hpp"

#include "gui/gui.hpp"
#include "windows/main_window.hpp"
#include "test_map.hpp"

using namespace selkie;

int main(int, char**)
{
  World world{CreateMap()};

  MainWindow main_window{world};

  std::vector<std::unique_ptr<BaseSystem>> systems{};
  systems.push_back(std::make_unique<MinionSpawnerSystem>(world));
  systems.push_back(std::make_unique<LaneMovementSystem>(world));

  std::vector<BaseSystem*> all_systems{};
  all_systems.reserve(systems.size());
  for (auto& system: systems)
  {
    all_systems.push_back(system.get());
  }

  GameLoop game_loop{world, all_systems};

  game_loop.Start();

  RunGUI(
    [&main_window, &game_loop]()
    {
      game_loop.WakeUp();

      main_window.Render();
    });

  game_loop.Shutdown();
}