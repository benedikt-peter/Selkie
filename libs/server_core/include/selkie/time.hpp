#pragma once

#include <cstdint>

namespace selkie
{
  struct Tick
  {
    std::uint32_t number;
  };

  struct Time
  {
    Tick tick;
    double delta_time;
    double total_time;
  };
}