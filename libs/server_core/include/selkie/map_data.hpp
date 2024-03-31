#pragma once

#include <vector>

#include "selkie/math/vector2.hpp"

namespace selkie
{
  using LaneId = std::int32_t;

  enum class TeamId
  {
    Blue,
    Red
  };

  inline std::string GetTeamName(TeamId team_id)
  {
    switch (team_id)
    {
      case TeamId::Blue:
        return "Blue";
      case TeamId::Red:
        return "Red";
    }

    return "";
  }

  using WaypointId = std::int32_t;

  struct LaneData
  {
    LaneId lane_id;
    std::vector<Vector2> waypoints{};

    std::vector<Vector2> GetWaypoints(TeamId team_id) const
    {
      auto team_waypoints = waypoints;
      if (team_id == TeamId::Red)
      {
        std::reverse(team_waypoints.begin(), team_waypoints.end());
      }

      return team_waypoints;
    }
  };

  struct MinionType
  {
    std::string name;
  };

  using MinionSpawnerId = std::int32_t;

  struct MinionSpawnerData
  {
    MinionSpawnerId minion_spawner_id;
    TeamId team_id;
    LaneId lane_id;
    Vector2 position;
    float spawn_delay;
    std::vector<MinionType> minion_types{};
  };

  struct MapData
  {
    Vector2 size;
    std::vector<LaneData> lanes{};
    std::vector<MinionSpawnerData> minion_spawners{};
  };

} // selkie
