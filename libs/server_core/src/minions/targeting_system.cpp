#include <glm/geometric.hpp>

#include "targeting_system.hpp"
#include "selkie/components.hpp"
#include "../combat/search_trees.hpp"

namespace selkie
{
  static bool IsValidTarget(const entt::registry& registry, entt::entity entity, Vector2 center, float max_distance)
  {
    const auto* position = registry.try_get<Position>(entity);

    return position && glm::distance(center, position->position) <= max_distance;
  }

  void TargetingSystem::Update(Time time)
  {
    const auto& search_trees = GetRegistry().ctx().get<SearchTrees>();

    for (auto& entity : GetRegistry().view<Position, Targeting, Team>())
    {
      const auto& position = GetRegistry().get<Position>(entity);
      auto& targeting = GetRegistry().get<Targeting>(entity);
      const auto& team = GetRegistry().get<Team>(entity);

      if (IsValidTarget(GetRegistry(), targeting.target_entity, position.position, targeting.max_range))
      {
        continue;
      }

      const auto& search_tree = search_trees.GetOpponentsSearchTree(team.team_id);

      TreeEntry nearest_result{};
      search_tree.query(boost::geometry::index::nearest(position.position, 1), &nearest_result);

      if (IsValidTarget(GetRegistry(), nearest_result.second, position.position, targeting.max_range))
      {
        targeting.target_entity = nearest_result.second;
      }
    }
  }

} // selkie