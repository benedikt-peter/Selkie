#include "selkie/game_loop.hpp"

#include <chrono>

namespace selkie
{
  double GetCurrentTime()
  {
    const auto current_time = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double>{current_time.time_since_epoch()}.count();;
  }

  GameLoop::GameLoop(World& world, std::span<ISystem*> systems) :
    m_world{&world},
    m_systems{std::begin(systems), std::end(systems)},
    m_paused{false},
    m_next_tick{0u},
    m_start_time{GetCurrentTime()}
  {
  }

  void GameLoop::WakeUp()
  {
    if (m_paused)
    {
      return;
    }

    auto total_time = GetTotalTime();
    while (m_next_tick.number * TargetFrameRate <= total_time)
    {
      Time time{m_next_tick, TargetFrameRate, GetTotalTime()};

      for (const auto system : m_systems)
      {
        system->Update(*m_world, time);
      }

      ++m_next_tick.number;
      total_time = GetTotalTime();
    }
  }

  void GameLoop::Pause()
  {
    m_paused = true;
  }

  void GameLoop::Unpause()
  {
    m_paused = false;
  }

  double GameLoop::GetTotalTime() const
  {
    return GetCurrentTime() - m_start_time;
  }
}


