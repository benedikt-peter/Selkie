#include "selkie/minions/lane_movement_system.hpp"

#include "selkie/components.hpp"

namespace selkie
{
  LaneMovementSystem::LaneMovementSystem(World& world) :
    BaseSystem{world}
  {

  }

  void LaneMovementSystem::Update(Time time)
  {
    for (const auto entity : GetRegistry().view<Minion, Position>())
    {
      const auto direction = GetRegistry().get<Minion>(entity).team_id == TeamId::Blue ? Vector2{1.0f, 0.0f} : Vector2{-1.0f, 0.0f};
      GetRegistry().get<Position>(entity).position += time.delta_time * direction;
    }
  }
} // selkie