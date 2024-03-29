#include "selkie/minions/waypoint_movement_system.hpp"

#include "selkie/components.hpp"

namespace selkie
{
  WaypointMovementSystem::WaypointMovementSystem(World& world) :
    BaseSystem{world}
  {

  }

  void WaypointMovementSystem::Update(Time time)
  {
    for (const auto entity : GetRegistry().view<Minion, Position>())
    {
      GetRegistry().get<Position>(entity).position += time.delta_time * Vector2{1.0f, 0.0f};
    }
  }
} // selkie