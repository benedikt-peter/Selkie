#pragma once

#include <glm/vec2.hpp>

namespace selkie
{
//  struct Vector2
//  {
//    std::array<float, 2> coords;
//
//    auto& X()
//    {
//      return coords[0];
//    }
//
//    const auto& X() const
//    {
//      return coords[0];
//    }
//
//    auto& Y()
//    {
//      return coords[1];
//    }
//
//    const auto& Y() const
//    {
//      return coords[1];
//    }
//
//    constexpr auto* data()
//    {
//      return coords.data();
//    }
//
//    constexpr auto* data() const
//    {
//      return coords.data();
//    }
//
//    constexpr auto size() const
//    {
//      return coords.size();
//    }
//
//
//  };
//
//  static_assert(std::is_standard_layout_v<Vector2> && std::is_trivially_copyable_v<Vector2>);

  using Vector2 = glm::vec2;

}