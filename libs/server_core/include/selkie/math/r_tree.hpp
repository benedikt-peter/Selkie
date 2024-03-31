#pragma once

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/register/point.hpp>

#include "vector2.hpp"

BOOST_GEOMETRY_REGISTER_POINT_2D(selkie::Vector2, float, boost::geometry::cs::cartesian, x, y)

namespace selkie
{
  using Bounds = boost::geometry::model::box<Vector2>;

  template<typename TId>
  using Value = std::pair<Bounds, TId>;

  template<typename TId>
  using RTree = boost::geometry::index::rtree<Value<TId>, boost::geometry::index::quadratic<16> >;
}