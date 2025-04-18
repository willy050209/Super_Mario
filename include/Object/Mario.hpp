#pragma once
#ifndef MARIO_HPP
#define MARIO_HPP
#include "config.hpp"
#include "Character.hpp"

#include <unordered_map>
#include <vector>
#include <string>

/// <summary>
/// ���O�ڪ��� �~��Character
/// </summary>
class Mario : public Character {
public:
	enum class State
	{
		UP, MOVE, DOWN, DIED
	};

	explicit Mario(const std::string& name, const std::string& ImagePath,int zindex) 
		: Character(name, ImagePath, zindex) {
		MyType = ObjectType::Mario;
	}

	/// <summary>
	/// ���o�ثe���A
	/// </summary>
	/// <returns>enum class State
	/// {
	/// 	UP, MOVE, DOWN, DIED
	/// };
	/// </returns>
	inline State GetState() const noexcept { return state; }

	/// <summary>
	/// �ǳƸ��D
	/// </summary>
	inline void jump() noexcept {
		if(jumpDelay == 0)
		{
			state = State::UP;
			displacement = 2 * DEFAULTDISPLACEMENT;
			index = 0;
			changeImg();
		}
	}

	/// <summary>
	/// ����s�ɰ���
	/// </summary>
	/// <param name="data">GameManager * </param>
	virtual void behavior(void* data = nullptr) override;

	//virtual void move(const float& d = DEFAULTDISPLACEMENT) override;

	/// <summary>
	/// ���ʨƥ�
	/// </summary>
	virtual void move() noexcept override;

	/// <summary>
	/// �����Ϥ�
	/// </summary>
	void changeImg() noexcept;

	/// <summary>
	/// ���`���D�ƥ�
	/// </summary>
	//void diedjump() noexcept;

	/// <summary>
	/// ���`�ƥ�
	/// </summary>
	virtual void died() noexcept override;

	/// <summary>
	/// �]�wstate ��ĳ�ϥ�changeState(State state_)
	/// </summary>
	inline void changeState(const std::string& str) noexcept {
		if (str == "UP")
			state = State::UP;
		else if (str == "MOVE")
			state = State::MOVE;
		else if (str == "DOWN")
			state = State::DOWN;
		else if (str == "DIED")
			state = State::DIED;
	}

	/// <summary>
	/// �]�wstate
	/// </summary>
	/// <param name="state_"></param>
	/// <returns>enum class State
	/// {
	/// 	UP, MOVE, DOWN, DIED
	/// };
	/// </returns>
	inline void changeState(State state_) noexcept {
		state = state_;
	}

	/// <summary>
	/// ���]���A
	/// </summary>
	inline void Reset() noexcept {
		state = State::MOVE;
		diedflag = false;
	}

private:

	/// <summary>
	/// ������D
	/// </summary>
	void doJump() noexcept;

	/// <summary>
	/// �Y���ƥ�
	/// </summary>
	virtual void comeDown() noexcept override;


	int index = 0;
	
	State state = State::MOVE;
	float displacement = DEFAULTDISPLACEMENT;

	int jumpDelay = 0;
	unsigned imgChangeDelay = 0;
	bool diedflag = false;

	std::unordered_map<State, std::vector<std::vector<const char*>>> imgs = 
	{ { State::MOVE, { { "imgs/super mario/1-1/Mario/frame0.png", "imgs/super mario/1-1/Mario/frame1.png", "imgs/super mario/1-1/Mario/frame2.png" }, { "imgs/super mario/1-1/Mario/Filp_frame0.png", "imgs/super mario/1-1/Mario/Filp_frame1.png", "imgs/super mario/1-1/Mario/Filp_frame2.png" } } },
		{ State::UP, { { "imgs/super mario/1-1/MarioJumping.png" }, { "imgs/super mario/1-1/Flip_MarioJumping.png" } } },
		{ State::DOWN, { { "imgs/super mario/1-1/MarioJumping.png" }, { "imgs/super mario/1-1/Flip_MarioJumping.png" } } },
		{ State::DIED, { { "imgs/super mario/1-1/MarioDied.png" }, { "imgs/super mario/1-1/MarioDied.png" } } } };


};

#endif // !MARIO_HPP
