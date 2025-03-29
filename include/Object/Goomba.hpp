#ifndef GOOMBA_HPP
#define GOOMBA_HPP

#include "config.hpp"
#include "Character.hpp"
#include <string>

class Goomba : public Character {
public:
	Goomba(const std::string& name, const std::string& ImagePath, int zindex)
		: Character(name, ImagePath, zindex) {
	}

	Goomba(const Goomba&) = delete;

	Goomba(Goomba&&) = delete;

	Goomba& operator=(const Goomba&) = delete;

	Goomba& operator=(Goomba&&) = delete;

	virtual void behavior(void* data) override;

	//virtual void move(const float& d) override;

	bool loop = true;

	static constexpr char* const imgs[] = { "imgs/super mario/1-1/LittleGoomba/frame0.png", "imgs/super mario/1-1/LittleGoomba/frame1.png" };

private:
	
	int imgIndex{ 0 }, imageChangeDelay{ 0 };

	void ChangeImg() noexcept;

	virtual void comeDown() override;

};

#endif // !GOOMBA_HPP
