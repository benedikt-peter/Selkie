#include "minion_spawner_system.hpp"

#include "spdlog/fmt/bundled/format.h"

#include "selkie/components.hpp"

namespace selkie
{
  void MinionSpawnerSystem::Start()
  {
    for (const auto& spawner : GetWorld().GetMapData().minion_spawners)
    {
      const auto entity = GetRegistry().create();
      GetRegistry().emplace<MinionSpawner>(entity, spawner.minion_spawner_id, 0.0);
      GetRegistry().emplace<DebugInfo>(entity, fmt::format("Spawner {} Lane {} {}",
                                                           spawner.minion_spawner_id, spawner.lane_id,
                                                           GetTeamName(spawner.team_id)));
      GetRegistry().emplace<Position>(entity, spawner.position);
    }
  }

  void MinionSpawnerSystem::Update(Time time)
  {
    for (auto& minion_spawner : GetRegistry().storage<MinionSpawner>())
    {
      if (minion_spawner.next_spawn_time > time.total_time)
      {
        continue;
      }

      const auto& data = GetWorld().GetMapData().minion_spawners[minion_spawner.minion_spawner_id];

      minion_spawner.next_spawn_time = time.total_time + data.spawn_delay;

      for (const auto& minion_type : data.minion_types)
      {
        const auto entity = GetRegistry().create();
        GetRegistry().emplace<Minion>(entity, minion_type.name);
        GetRegistry().emplace<Hitbox>(entity, 0.5f);
        GetRegistry().emplace<Team>(entity, data.team_id);
        GetRegistry().emplace<DebugInfo>(entity, fmt::format("{} Lane {} {}",
                                                             minion_type.name, data.lane_id,
                                                             GetTeamName(data.team_id)));
        GetRegistry().emplace<Position>(entity, data.position);
        GetRegistry().emplace<Targeting>(entity, 5.0f);
      }
    }
  }
} // selkie