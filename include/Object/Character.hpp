#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "Util/GameObject.hpp"
#include "Object.hpp"
#include "config.hpp"

const auto DEFAULTDISPLACEMENT = WINDOW_HEIGHT / 15.f / 4;

class Character : public Object {
public:
    explicit Character(const std::string& name, const std::string& ImagePath, int zindex) 
        :Object(name, std::make_shared<Util::Image>(ImagePath), zindex) {  }


    Character(const Character&) = delete;

    Character(Character&&) = delete;

    Character& operator=(const Character&) = delete;

    Character& operator=(Character&&) = delete;

    inline bool IfCollides(const std::shared_ptr<Character>& other) const noexcept {
        return fabs(other->GetPosition().x - GetPosition().x) <= 10.0 && fabs(other->GetPosition().y - GetPosition().y) <= 10.0;

    }

    //virtual void move(const float& d) = 0;

private:
    inline void ResetPosition() noexcept { m_Transform.translation = { 0, 0 }; }
	virtual void comeDown() = 0;
};

#endif // !CHARACTER_HPP
