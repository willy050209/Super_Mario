#ifndef MARIO_HPP
#define MARIO_HPP
#include "config.hpp"
#include "Character.hpp"


const auto DEFAULTDISPLACEMENT = WINDOW_HEIGHT/20.f/5;

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
		if(jumpDelay == 0)
		{
			state = State::UP;
			displacement = 2 * DEFAULTDISPLACEMENT;
		}
	}

	virtual void behavior(void* data = nullptr) override;

	virtual void move(const float& d = DEFAULTDISPLACEMENT) override;

private:

	void doJump() noexcept;

	void comeDown() noexcept;

	int index = 0;
	
	State state = State::MOVE;
	float displacement = DEFAULTDISPLACEMENT;

	int jumpDelay = 0;
};

#endif // !MARIO_HPP
