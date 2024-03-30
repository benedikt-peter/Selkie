#pragma once

#include <string>

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

  struct Minion
  {
    float radius;
    TeamId team_id;
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