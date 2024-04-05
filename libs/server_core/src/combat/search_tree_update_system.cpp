#include "search_tree_update_system.hpp"
#include "search_trees.hpp"
#include "selkie/components.hpp"

namespace selkie
{
  void SearchTreeUpdateSystem::Start()
  {
    GetRegistry().ctx().emplace<SearchTrees>();
  }

  void SearchTreeUpdateSystem::Update(Time time)
  {
    m_team_blue_buffer.clear();
    m_team_red_buffer.clear();

    const auto view = GetRegistry().view<Position, Hitbox, Team>();

    for (const auto entity : view)
    {
      const auto [position, hitbox, team] = view.get<Position, Hitbox, Team>(entity);

      GetBuffer(team.team_id).emplace_back(CreateCircleBounds(position.position, hitbox.radius), entity);
    }

    auto& search_trees = GetRegistry().ctx().get<SearchTrees>();
    search_trees.team_blue_search_tree = RTree{std::begin(m_team_blue_buffer), std::end(m_team_blue_buffer)};
    search_trees.team_red_search_tree = RTree{std::begin(m_team_red_buffer), std::end(m_team_red_buffer)};
  }

  std::vector<TreeEntry>& SearchTreeUpdateSystem::GetBuffer(TeamId team_id)
  {
    switch (team_id)
    {
      case TeamId::Blue:
        return m_team_blue_buffer;
      case TeamId::Red:
        return m_team_red_buffer;
    }

    throw std::runtime_error{"Invalid team_id"};
  }
} // selkie