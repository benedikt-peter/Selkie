#pragma once

#include "../math/r_tree.hpp"

namespace selkie
{

  struct SearchTrees
  {
    RTree team_blue_search_tree{};
    RTree team_red_search_tree{};

    const RTree& GetOpponentsSearchTree(TeamId team_id) const
    {
      switch (team_id)
      {
        case TeamId::Blue:
          return team_red_search_tree;
        case TeamId::Red:
          return team_blue_search_tree;
      }

      throw std::runtime_error{"Invalid team_id"};
    }
  };

} // selkie
