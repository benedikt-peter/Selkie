#pragma once

#include <vector>

#include "vector2.hpp"

namespace selkie
{
  struct Lane
  {
    std::vector<Vector2> waypoints;
  };

  struct MapData
  {
    Vector2 size;
    std::vector<Lane> lanes;
  };

} // selkie
