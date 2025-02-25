#ifndef MARIO_HPP
#define MARIO_HPP

#include "Character.hpp"

class Mario : public Character {
public:
	explicit Mario(const std::string& ImagePath) : Character(ImagePath){}

	virtual void move(const float& d) override;
};

#endif // !MARIO_HPP
