#ifndef MARIO_HPP
#define MARIO_HPP

#include "Character.hpp"

constexpr auto DEFAULTDISPLACEMENT = 5.0f;

class Mario : public Character {
public:
	enum class State
	{
		UP, MOVE, DOWN
	};

	explicit Mario(const std::string& ImagePath,int zindex) : Character(ImagePath, zindex){}

	virtual void behavior(void* data = nullptr) override;

	virtual void move(const float& d = DEFAULTDISPLACEMENT) override;

private:

	void jump() noexcept;

	void comeDown() noexcept;

	State state = State::MOVE;
	float displacement = DEFAULTDISPLACEMENT;
};

#endif // !MARIO_HPP
