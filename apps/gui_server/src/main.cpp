#include <memory>
#include <vector>

#include <selkie/game_loop.hpp>
#include <selkie/system.hpp>
#include <selkie/test_system.hpp>
#include <selkie/world.hpp>

#include "gui.hpp"
#include "windows/main_window.hpp"

using namespace selkie;

int main(int, char**)
{
  World world{};

  MainWindow main_window{world};

  const auto entity = world.registry.create();
  world.registry.emplace<std::string>(entity, "Entity 1");

  std::vector<std::unique_ptr<ISystem>> systems{};
  systems.push_back(std::make_unique<TestSystem>());

  std::vector<ISystem*> all_systems{};
  all_systems.reserve(systems.size());
  for (auto& system : systems)
  {
    all_systems.push_back(system.get());
  }

  GameLoop game_loop{world, all_systems};

  RunGUI(
    [&main_window, &game_loop]()
    {
      game_loop.WakeUp();

      main_window.Render();
    });
}