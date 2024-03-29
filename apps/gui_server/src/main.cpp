#include <memory>
#include <vector>

#include <spdlog/fmt/bundled/format.h>

#include <selkie/minions/waypoint_movement_system.hpp>

#include <selkie/components.hpp>
#include <selkie/game_loop.hpp>
#include <selkie/system.hpp>

#include <selkie/world.hpp>
#include "gui.hpp"
#include "windows/main_window.hpp"

using namespace selkie;

int main(int, char**)
{
  World world{std::make_unique<MapData>(MapData{.size = Vector2{50.0f, 50.0f}})};

  MainWindow main_window{world};

  auto& registry = world.GetRegistry();

  for (int i = 0; i < 10; ++i)
  {
    const auto entity = registry.create();
    registry.emplace<DebugInfo>(entity, fmt::format("Minion {}", i + 1));
    registry.emplace<Minion>(entity, 0.5f);
    registry.emplace<Position>(entity, Vector2{static_cast<float>(i), static_cast<float>(i)});
  }

  std::vector<std::unique_ptr<BaseSystem>> systems{};
  systems.push_back(std::make_unique<WaypointMovementSystem>(world));

  std::vector<BaseSystem*> all_systems{};
  all_systems.reserve(systems.size());
  for (auto& system: systems)
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