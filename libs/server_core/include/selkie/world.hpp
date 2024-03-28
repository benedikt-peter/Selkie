#pragma once

#include <entt/entt.hpp>

#include "vector2.hpp"

namespace selkie
{
  struct World
  {
    entt::registry registry{};
    Vector2 size;
  };
}