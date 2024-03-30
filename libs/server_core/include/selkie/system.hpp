#pragma once

#include "time.hpp"
#include "world.hpp"

namespace selkie
{
  class BaseSystem
  {
    public:
      explicit BaseSystem(World& world) :
        m_world{&world}
      {}

      virtual ~BaseSystem() = default;

      virtual void Start()
      {
      }

      virtual void Update(Time time) = 0;

      virtual void Shutdown()
      {
      }

    protected:
      auto& GetWorld()
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
