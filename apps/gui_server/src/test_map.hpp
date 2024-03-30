#pragma once

#include <memory>

#include "selkie/map_data.hpp"

namespace selkie
{
  inline std::unique_ptr<MapData> CreateMap()
  {
    const Vector2 size{50.0f, 25.0f};

    const std::vector<MinionType> minion_wave
      {
        MinionType{"Knight"},
        MinionType{"Sorcerer"},
        MinionType{"Archer"},
      };

    const std::vector<LaneData> lanes
      {
        LaneData
          {
            .lane_id = 0,
            .waypoints =
              {
                Vector2{-22.5f, 0.0f},
                Vector2{0.0f, 0.0f},
                Vector2{22.5f, 0.0f}
              }
          }
      };
    const std::vector<MinionSpawnerData> minion_spawners
      {
        MinionSpawnerData
          {
            .minion_spawner_id = 0,
            .team_id = TeamId::Blue,
            .lane_id = lanes[0].lane_id,
            .position = Vector2{-25.0f, 0.0f},
            .spawn_delay = 10.0f,
            .minion_types = minion_wave
          },
        MinionSpawnerData
          {
            .minion_spawner_id = 1,
            .team_id = TeamId::Red,
            .lane_id = lanes[0].lane_id,
            .position = Vector2{25.0f, 0.0f},
            .spawn_delay = 10.0f,
            .minion_types = minion_wave
          }
      };

    return std::make_unique<MapData>
      (
        MapData
          {
            .size = size,
            .lanes = lanes,
            .minion_spawners = minion_spawners
          }
      );
  }
}