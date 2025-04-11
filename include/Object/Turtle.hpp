#ifndef TURTLE_HPP
#define TURTLE_HPP

#include "config.hpp"
#include "Character.hpp"
#include <string>

class Turtle : public Character {
public:
	Turtle(const std::string& name, const std::string& ImagePath, int zindex)
		: Character(name, ImagePath, zindex) {
		MyType = ObjectType::Turtle;
		left = 1;
	}

	Turtle(const Turtle&) = delete;

	Turtle(Turtle&&) = delete;

	Turtle& operator=(const Turtle&) = delete;

	Turtle& operator=(Turtle&&) = delete;

	virtual void behavior(void* data) override;

	virtual void died() noexcept override;

	bool diedFlag = false;

	//static constexpr char* const imgs[][2] = { { "imgs/super mario/1-1/TurtleGreen/frame0.png", "imgs/super mario/1-1/TurtleGreen/frame1.png" }, { "imgs/super mario/1-1/TurtleGreen_faceleft/frame0.png", "imgs/super mario/1-1/TurtleGreen_faceleft/frame1.png" } };
	
	static constexpr char* const imgs[2] =  { "imgs/super mario/TurtleGreen_faceleft/frame0.png", "imgs/super mario/TurtleGreen_faceleft/frame1.png" } ;
	static constexpr char* const imgs_r[2] = { "imgs/super mario/TurtleGreen/frame0.png", "imgs/super mario/TurtleGreen/frame1.png" };
	
	static constexpr char* const TortoiseShell[] = { "imgs/super mario/1-1/KoopaTroopaShellGreen.png" };

private:
	int imgIndex{ 0 }, imageChangeDelay{ 0 };

	void ChangeImg() noexcept;

	virtual void comeDown() noexcept override;

};

#endif // !GOOMBA_HPP
