#pragma once

#include <array>
#include <string>

namespace selkie
{
  struct DebugInfo
  {
    std::string name;
  };

  struct Position
  {
    std::array<float, 2> position;
  };
}