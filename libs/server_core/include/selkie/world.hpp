#pragma once

#include <memory>

#include <entt/entt.hpp>

#include "map_data.hpp"
#include "selkie/math/vector2.hpp"

namespace selkie
{
  class World
  {
    public:
      explicit World(std::unique_ptr<MapData> map_data) :
        m_registry{},
        m_map_data{std::move(map_data)}
      {}

      const MapData& GetMapData() const
      {
        return *m_map_data;
      }

      const entt::registry& GetRegistry() const
      {
        return m_registry;
      }

      entt::registry& GetRegistry()
      {
        return m_registry;
      }

    private:
      entt::registry m_registry;
      std::unique_ptr<MapData> m_map_data;
  };
}