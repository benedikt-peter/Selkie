#pragma once

#include <string>

#include <entt/entity/entity.hpp>

#include "map_data.hpp"

namespace selkie
{
  struct DebugInfo
  {
    std::string name;
  };

  struct Position
  {
    Vector2 position;
  };

  struct Hitbox
  {
    float radius;
  };

  struct Team
  {
    TeamId team_id;
  };

  struct Minion
  {
    MinionType minion_type{};
  };

  struct Targeting
  {
    float max_range;
    entt::entity target_entity;
  };

  struct FollowLane
  {
    LaneId lane_id;
    TeamId team_id;
    WaypointId next_waypoint_id;
  };

  struct MinionSpawner
  {
    MinionSpawnerId minion_spawner_id;
    double next_spawn_time;
  };
}