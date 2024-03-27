#include <memory>
#include <vector>

#include <spdlog/fmt/bundled/format.h>

#include <selkie/components.hpp>
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

  for (int i = 0; i < 10; ++i)
  {
    const auto entity = world.registry.create();
    world.registry.emplace<DebugInfo>(entity, fmt::format("Entity {}", i));
    world.registry.emplace<Position>(entity, static_cast<float>(i), static_cast<float>(i));
  }

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