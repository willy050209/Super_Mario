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

	explicit Mario(const std::string& name, const std::string& ImagePath,int zindex) 
		: Character(name, ImagePath, zindex) {
		
	}

	virtual void behavior(void* data = nullptr) override;

	virtual void move(const float& d = DEFAULTDISPLACEMENT) override;

private:

	void jump() noexcept;

	void comeDown() noexcept;

	int index = 0;
	std::vector < std::string > imgs = { "D:\\University\\22\\OOP\\Super_Mario\\Resources\\Image\\Character\\bee_1.png","D:\\University\\22\\OOP\\Super_Mario\\Resources\\Image\\Character\\ball-1.png" };
	State state = State::MOVE;
	float displacement = DEFAULTDISPLACEMENT;
};

#endif // !MARIO_HPP
