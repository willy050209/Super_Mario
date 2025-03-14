#ifndef MARIO_HPP
#define MARIO_HPP

#include "Character.hpp"

constexpr auto DEFAULTDISPLACEMENT = 3.f;

class Mario : public Character {
public:
	enum class State
	{
		UP, MOVE, DOWN
	};

	explicit Mario(const std::string& name, const std::string& ImagePath,int zindex) 
		: Character(name, ImagePath, zindex) {
		
	}

	inline State GetState() const noexcept { return state; }

	inline void jump() noexcept {
		state = State::UP;
		displacement = 2 * DEFAULTDISPLACEMENT;
	}

	virtual void behavior(void* data = nullptr) override;

	virtual void move(const float& d = DEFAULTDISPLACEMENT) override;

private:

	void doJump() noexcept;

	void comeDown() noexcept;

	int index = 0;
	
	State state = State::MOVE;
	float displacement = DEFAULTDISPLACEMENT;
};

#endif // !MARIO_HPP
