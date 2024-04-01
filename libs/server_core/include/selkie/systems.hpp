#pragma once

#include <memory>

#include "system.hpp"

namespace selkie
{
  class Systems
  {
    public:
      template<typename TFunc>
      void ForEach(TFunc for_each)
      {
        for (auto& system : m_systems)
        {
          for_each(*system);
        }
      }

      template<typename TSystem, typename ... TArgs>
      void Emplace(TArgs&& ... args)
      {
        m_systems.emplace_back(std::make_unique<TSystem>(args...));
      }

    private:
      std::vector<std::unique_ptr<BaseSystem>> m_systems{};
  };

  Systems CreateDefaultSystems(World& world);
}
