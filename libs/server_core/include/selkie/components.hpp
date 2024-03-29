#pragma once

#include <array>
#include <string>

#include "vector2.hpp"

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
}