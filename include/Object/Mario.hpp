#ifndef MARIO_HPP
#define MARIO_HPP
#include "config.hpp"
#include "Character.hpp"

#include <unordered_map>
#include <vector>
#include <string>


const auto DEFAULTDISPLACEMENT = WINDOW_HEIGHT/15.f/5;

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
			index = 0;
			changeImg();
		}
	}

	virtual void behavior(void* data = nullptr) override;

	virtual void move(const float& d = DEFAULTDISPLACEMENT) override;

private:

	void doJump() noexcept;

	void comeDown() noexcept;

	void changeImg() noexcept;

	int index = 0;
	
	State state = State::MOVE;
	float displacement = DEFAULTDISPLACEMENT;

	int jumpDelay = 0;
	unsigned imgChangeDelay = 0;

	std::unordered_map<State, std::vector<const char*>> imgs = { { State::MOVE,
																	 { "out/super mario/1-1/Mario/frame0.png", "out/super mario/1-1/Mario/frame1.png", "out/super mario/1-1/Mario/frame2.png" } },
		{ State::UP, { "out/super mario/1-1/MarioJumping.png" } }, { State::DOWN, { "out/super mario/1-1/MarioJumping.png" } } };

};

#endif // !MARIO_HPP
