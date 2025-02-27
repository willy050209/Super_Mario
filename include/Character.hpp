#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "Util/GameObject.hpp"

class Character : public Util::GameObject {
public:
    explicit Character(const std::string& ImagePath);

    Character(const Character&) = delete;

    Character(Character&&) = delete;

    Character& operator=(const Character&) = delete;

    Character& operator=(Character&&) = delete;

    inline const std::string& GetImagePath() const noexcept { return m_ImagePath; }

    inline const glm::vec2& GetPosition() const noexcept { return m_Transform.translation; }

    inline bool GetVisibility() const noexcept { return m_Visible; }

    void SetImage(const std::string& ImagePath) noexcept;

    inline void SetPosition(const glm::vec2& Position) { m_Transform.translation = Position; }


    inline bool IfCollides(const std::shared_ptr<Character>& other) const noexcept {
        return fabs(other->GetPosition().x - GetPosition().x) <= 10.0 && fabs(other->GetPosition().y - GetPosition().y) <= 10.0;

    }

    virtual void behavior() = 0;

    virtual void move(const float& d) = 0;



private:
    inline void ResetPosition() noexcept { m_Transform.translation = { 0, 0 }; }

    std::string m_ImagePath;
};

#endif // !CHARACTER_HPP
