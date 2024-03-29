#pragma once

#include "entt/entity/entity.hpp"

namespace selkie
{

  class BaseComponentInspector
  {
    public:
      explicit BaseComponentInspector(World& world) :
        m_world{&world}
      {}

      virtual ~BaseComponentInspector() = default;

      virtual void Render(entt::entity entity) = 0;

    protected:
      World& GetWorld()
      {
        return *m_world;
      }

      auto& GetRegistry()
      {
        return m_world->GetRegistry();
      }

    private:
      World* m_world;
  };

} // selkie
