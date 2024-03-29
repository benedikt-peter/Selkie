#pragma once

#include <span>
#include <vector>

#include "system.hpp"
#include "time.hpp"
#include "world.hpp"

namespace selkie
{
  constexpr double TargetFrameRate = 1.0 / 15.0;

  class GameLoop
  {
    public:
      GameLoop(World& world, std::span<BaseSystem*> systems);

      void WakeUp();

      void Pause();

      void Unpause();

    private:
      World* m_world;
      std::vector<BaseSystem*> m_systems;

      bool m_paused;
      Tick m_next_tick;
      double m_start_time;

      double GetTotalTime() const;
  };
}
