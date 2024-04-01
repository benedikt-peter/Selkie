#pragma once

#include <vector>

#include "selkie/system.hpp"
#include "../math/r_tree.hpp"

namespace selkie
{

  class SearchTreeUpdateSystem : public BaseSystem
  {
    public:
      explicit SearchTreeUpdateSystem(World& world) :
        BaseSystem{world},
        m_team_blue_buffer{},
        m_team_red_buffer{}
      {}

      void Start() override;

      void Update(Time time) override;

    private:
      std::vector<TreeEntry> m_team_blue_buffer;
      std::vector<TreeEntry> m_team_red_buffer;

      std::vector<TreeEntry>& GetBuffer(TeamId team_id);
  };

} // selkie
