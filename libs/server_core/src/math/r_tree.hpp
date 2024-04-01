#pragma once

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/register/point.hpp>

#include <entt/entity/entity.hpp>

#include "selkie/math/vector2.hpp"

BOOST_GEOMETRY_REGISTER_POINT_2D(selkie::Vector2, float, boost::geometry::cs::cartesian, x, y)

namespace selkie
{
  using Bounds = boost::geometry::model::box<Vector2>;

  using Id = entt::entity;

  using TreeEntry = std::pair<Bounds, Id>;

  using RTree = boost::geometry::index::rtree <TreeEntry, boost::geometry::index::quadratic<16>>;

  constexpr inline Bounds CreateCircleBounds(Vector2 center, float radius)
  {
    Vector2 radii{radius, radius};
    return Bounds{center - radii, center + radii};
  }
}