#pragma once
#ifndef MARIO_HPP
#define MARIO_HPP
#include "config.hpp"
#include "Character.hpp"

#include <unordered_map>
#include <vector>
#include <string>

/// <summary>
/// 馬力歐物件 繼承Character
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
	/// 取得目前狀態
	/// </summary>
	/// <returns>enum class State
	/// {
	/// 	UP, MOVE, DOWN, DIED
	/// };
	/// </returns>
	inline State GetState() const noexcept { return state; }

	/// <summary>
	/// 準備跳躍
	/// </summary>
	inline void jump() noexcept {
		if(jumpDelay == 0)
		{
			state = State::UP;
			displacement = WINDOW_HEIGHT / 15.f * 4.5f / 10;
			index = 0;
			jumpcount = 10;
			changeImg();
		}
	}

	/// <summary>
	/// 表單刷新時執行
	/// </summary>
	/// <param name="data">GameManager * </param>
	virtual void behavior(void* data = nullptr) override;

	//virtual void move(const float& d = DEFAULTDISPLACEMENT) override;

	/// <summary>
	/// 移動事件
	/// </summary>
	virtual void move() noexcept override;

	/// <summary>
	/// 切換圖片
	/// </summary>
	void changeImg() noexcept;

	/// <summary>
	/// 死亡跳躍事件
	/// </summary>
	//void diedjump() noexcept;

	/// <summary>
	/// 死亡事件
	/// </summary>
	virtual void died() noexcept override;

	/// <summary>
	/// 設定state 建議使用changeState(State state_)
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
	/// 設定state
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
	/// 重設狀態
	/// </summary>
	inline void Reset() noexcept {
		state = State::MOVE;
		diedflag = false;
	}

private:

	/// <summary>
	/// 執行跳躍
	/// </summary>
	void doJump() noexcept;

	/// <summary>
	/// 墜落事件
	/// </summary>
	virtual void comeDown() noexcept override;

	
	State state = State::MOVE;
	float displacement = DEFAULTDISPLACEMENT;
	int index = 0;
	int jumpDelay = 0;
	int jumpcount = 0;
	unsigned imgChangeDelay = 0;
	bool diedflag = false;

	std::unordered_map<State, std::vector<std::vector<const char*>>> imgs = 
	{ { State::MOVE, { { "imgs/super mario/1-1/Mario/frame0.png", "imgs/super mario/1-1/Mario/frame1.png", "imgs/super mario/1-1/Mario/frame2.png" }, { "imgs/super mario/1-1/Mario/Filp_frame0.png", "imgs/super mario/1-1/Mario/Filp_frame1.png", "imgs/super mario/1-1/Mario/Filp_frame2.png" } } },
		{ State::UP, { { "imgs/super mario/1-1/MarioJumping.png" }, { "imgs/super mario/1-1/Flip_MarioJumping.png" } } },
		{ State::DOWN, { { "imgs/super mario/1-1/MarioJumping.png" }, { "imgs/super mario/1-1/Flip_MarioJumping.png" } } },
		{ State::DIED, { { "imgs/super mario/1-1/MarioDied.png" }, { "imgs/super mario/1-1/MarioDied.png" } } } };


};

#endif // !MARIO_HPP
