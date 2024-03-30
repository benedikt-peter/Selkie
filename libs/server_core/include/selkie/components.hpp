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
  };

  struct MinionSpawner
  {
    MinionSpawnerId minion_spawner_id;
    double next_spawn_time;
  };
}