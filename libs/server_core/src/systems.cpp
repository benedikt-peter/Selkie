#include "selkie/systems.hpp"
#include "minions/minion_spawner_system.hpp"
#include "minions/lane_movement_system.hpp"
#include "combat/search_tree_update_system.hpp"
#include "minions/targeting_system.hpp"

namespace selkie
{
  Systems CreateDefaultSystems(World& world)
  {
    Systems default_systems{};

    default_systems.Emplace<SearchTreeUpdateSystem>(world);
    default_systems.Emplace<MinionSpawnerSystem>(world);
    default_systems.Emplace<LaneMovementSystem>(world);
    default_systems.Emplace<TargetingSystem>(world);

    return default_systems;
  }
}