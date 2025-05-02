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
	enum class State {
		UP,
		MOVE,
		DOWN,
		SQUAT,
		DIED,
		Invincible,
	};

	enum class Mario_type {
		Mario,
		SuperMario,
		FieryMario
	};

	/*enum class Mario_Invincible {
		Invincible,
		notInvincible
	};*/

	explicit Mario(const std::string& name,  int zindex)
		: Character(name, R"(imgs\super mario\1-1\Mario\frame0.png)", zindex) {
		MyType = ObjectType::Mario;
	}

	/// <summary>
	/// 取得目前狀態
	/// </summary>
	inline State GetState() const noexcept { return state; }
	inline Mario_type GetMario_type() const noexcept { return mario_type; }
	//inline Mario_Invincible GetMario_Invincible() const noexcept { return mario_invincible; }

	/// <summary>
	/// 準備跳躍
	/// </summary>
	inline void jump() noexcept {
		if (jumpDelay == 0) {
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

	// virtual void move(const float& d = DEFAULTDISPLACEMENT) override;

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
	// void diedjump() noexcept;

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
	/// 設定mario_type
	/// </summary>
	/// <param name="type_"></param>
	inline void changeType(Mario_type type_) noexcept;

	/// <summary>
	/// 是否是無敵
	/// </summary>
	/// <param name="flag"></param>
	inline void isInvincible(bool flag) noexcept;

	/// <summary>
	/// 重設所有狀態
	/// </summary>
	inline void Reset() noexcept {
		state = State::MOVE;
		mario_type = Mario_type::Mario;
		//mario_invincible = Mario_Invincible::notInvincible;
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
	Mario_type mario_type = Mario_type::Mario;
	State mario_invincible = State::MOVE;
	float displacement = DEFAULTDISPLACEMENT;
	int index = 0;
	int jumpDelay = 0;
	int jumpcount = 0;
	unsigned imgChangeDelay = 0;
	bool diedflag = false;

	std::unordered_map<Mario_type, std::unordered_map<State, std::vector<std::vector<const char*>>>> imgs = 
{
		{ Mario_type::Mario, { { State::MOVE, { { "imgs/super mario/1-1/Mario/frame0.png", "imgs/super mario/1-1/Mario/frame1.png", "imgs/super mario/1-1/Mario/frame2.png" }, { "imgs/super mario/1-1/Mario/Filp_frame0.png", "imgs/super mario/1-1/Mario/Filp_frame1.png", "imgs/super mario/1-1/Mario/Filp_frame2.png" } } },
								 { State::UP, { { "imgs/super mario/1-1/MarioJumping.png" }, { "imgs/super mario/1-1/Flip_MarioJumping.png" } } },
								 { State::DOWN, { { "imgs/super mario/1-1/MarioJumping.png" }, { "imgs/super mario/1-1/Flip_MarioJumping.png" } } },
								 { State::DIED, { { "imgs/super mario/1-1/MarioDied.png" }, { "imgs/super mario/1-1/MarioDied.png" } } },
								 { State::Invincible, {} } } },
		{ Mario_type::SuperMario, { { State::MOVE, { { "imgs/super mario/1-1/Mario/frame0.png", "imgs/super mario/1-1/Mario/frame1.png", "imgs/super mario/1-1/Mario/frame2.png" }, { "imgs/super mario/1-1/Mario/Filp_frame0.png", "imgs/super mario/1-1/Mario/Filp_frame1.png", "imgs/super mario/1-1/Mario/Filp_frame2.png" } } },
								 { State::UP, { { "imgs/super mario/1-1/MarioJumping.png" }, { "imgs/super mario/1-1/Flip_MarioJumping.png" } } },
								 { State::DOWN, { { "imgs/super mario/1-1/MarioJumping.png" }, { "imgs/super mario/1-1/Flip_MarioJumping.png" } } },
								 { State::DIED, { { "imgs/super mario/1-1/MarioDied.png" }, { "imgs/super mario/1-1/MarioDied.png" } } },
								 { State::Invincible, {} } } 
		}
	};


};

#endif // !MARIO_HPP
