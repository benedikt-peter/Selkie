#pragma once

#include <span>

#include <imgui.h>

#include <entt/entity/entity.hpp>

namespace selkie
{

  class BaseView
  {
    public:
      explicit BaseView(World& world) :
        m_world{&world},
        m_view_origin{},
        m_scale{},
        m_offset{}
      {}

      virtual ~BaseView() = default;

      void UpdateView(Vector2 origin, float scale, Vector2 offset)
      {
        m_view_origin = origin;
        m_scale = scale;
        m_offset = offset;
      }

    protected:
      const World& GetWorld() const
      {
        return *m_world;
      }

      const auto& GetRegistry() const
      {
        return m_world->GetRegistry();
      }

      const Vector2& GetViewOrigin() const
      {
        return m_view_origin;
      }

      float GetScale() const
      {
        return m_scale;
      }

      const Vector2& GetOffset() const
      {
        return m_offset;
      }

      constexpr static ImVec2 ToIm(Vector2 position)
      {
        return ImVec2{position.x, position.y};
      }

      Vector2 ToView(Vector2 position) const
      {
        const auto scaled_offset = m_scale * m_offset;
        const auto scaled_position = m_scale * position;
        return m_view_origin + scaled_offset + scaled_position;
      }

      ImVec2 ToImGuiView(Vector2 position) const
      {
        return ToIm(ToView(position));
      }

      Vector2 GetWorldMin() const
      {
        return -m_world->GetMapData().size / 2.0f;
      }

      Vector2 GetWorldMax() const
      {
        return m_world->GetMapData().size / 2.0f;
      }

      bool ShouldRenderText() const
      {
        return GetScale() >= 25.0f;
      }

    private:
      World* m_world;
      Vector2 m_view_origin;
      float m_scale;
      Vector2 m_offset;
  };

  class BaseComponentView : public BaseView
  {
    public:
      explicit BaseComponentView(World& world) :
        BaseView{world}
      {}

      virtual void Render(entt::entity entity) = 0;

      virtual bool IsValid(entt::entity entity) const = 0;
  };

} // selkie
