#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"

class Object : public Util::GameObject {
public:
    Object() = delete;

    Object(const std::shared_ptr<Core::Drawable>& drawable,
        const float zIndex, const glm::vec2& pivot = { 0, 0 },
        const bool visible = true,
        const std::vector<std::shared_ptr<GameObject>>& children =
        std::vector<std::shared_ptr<GameObject>>())
        : GameObject(drawable,zIndex,pivot,visible,children) {}

    Object(const Object&) = delete;

    Object(Object&&) = delete;

    Object& operator=(const Object&) = delete;

    Object& operator=(Object&&) = delete;

    inline std::shared_ptr<Core::Drawable> GetDrawable() const { return m_Drawable; }

    virtual inline const glm::vec2& GetPosition() const noexcept { return m_Transform.translation; }

    inline bool GetVisibility() const noexcept { return m_Visible; }

    inline void SetPosition(const glm::vec2& Position) { m_Transform.translation = Position; }

    void setImage(const std::string& ImagePath) noexcept{ m_Drawable = std::make_shared<Util::Image>(ImagePath); }

    virtual inline glm::vec2&& GetSize() const noexcept {
        return std::dynamic_pointer_cast<Util::Image>(m_Drawable)->GetSize();
    }
};

#endif