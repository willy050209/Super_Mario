#pragma once
#ifndef MARIO_HPP
#define MARIO_HPP
#include "config.hpp"
#include "Character.hpp"
#include "Object/ImageObject.hpp"
#include "Interface/ICollisionable.hpp"
#include "Interface/IMovable.hpp"
#include "FilePath.hpp"

#include <unordered_map>
#include <vector>
#include <string>
namespace MyAPP::Form {
	class FormManger;
}

namespace MyAPP::Form::Object {
	/// <summary>
	/// ���O�ڪ��� �~��Character
	/// </summary>
	class Mario : public Character {
	public:
		enum class State {
			UP,
			MOVE,
			DOWN,
			CROUCH,
			DIED,
			Invincible
		};

		enum class Mario_type {
			Mario,
			SuperMario,
			FieryMario,
			InvincibleMario,
			InvincibleSuperMario,
			InvincibleFieryMario
		};

		/*enum class Mario_Invincible {
			Invincible,
			notInvincible
		};*/

		explicit Mario(const std::string& name, int zindex)
			: Character(name, R"(imgs\super mario\1-1\Mario\frame0.png)", zindex) {
			MyType = ObjectType::Mario;
		}

		/// <summary>
		/// ���o�ثe���A
		/// </summary>
		inline State GetState() const noexcept { return state; }
		inline Mario_type GetMario_type() const noexcept { return mario_type; }
		// inline Mario_Invincible GetMario_Invincible() const noexcept { return mario_invincible; }

		/// <summary>
		/// �ǳƸ��D
		/// </summary>
		void jump(float d = 4.5) noexcept;

		/// <summary>
		/// ����U�Y
		/// </summary>
		inline void down() noexcept {
			state = State::DOWN;
			jumpcount = 0;
			changeImg();
		}

		/// <summary>
		/// ����s�ɰ���
		/// </summary>
		/// <param name="data">GameManager * </param>
		virtual void behavior(void* data = nullptr) override;

		// virtual void move(const float& d = DEFAULTDISPLACEMENT) override;

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
		// void diedjump() noexcept;

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
		/// �]�wmario_type
		/// </summary>
		/// <param name="type_"></param>
		inline void changeType(Mario_type type_) noexcept {
			mario_type = type_;
			changeImg();
		}

		/// <summary>
		/// �O�_�O�L��
		/// </summary>
		inline auto isInvincible() const noexcept {
			return mario_invincible == State::Invincible || state == State::DIED || invincibleCount > 0;
		}

		inline void setInvincible(int val) noexcept {
			invincibleCount = val;
		}

		/// <summary>
		/// ���]�Ҧ����A
		/// </summary>
		virtual void Reset() noexcept override {
			state = State::MOVE;
			mario_type = Mario_type::Mario;
			index = 0;
			left = 0;
			jumpCobo = 0;
			changeImg();
			// mario_invincible = Mario_Invincible::notInvincible;
			diedflag = false;
		}

		inline bool isBigMario() const noexcept {
			return	mario_type == Mario_type::SuperMario ||
					mario_type == Mario_type::FieryMario ||
					mario_type == Mario_type::InvincibleSuperMario ||
					mario_type == Mario_type::InvincibleFieryMario;
		}

		inline bool isMiniMario() const noexcept {
			return mario_type == Mario_type::Mario || mario_type == Mario_type::InvincibleMario;
		}

		inline bool isFieryMario() const noexcept {
			return mario_type == Mario_type::FieryMario || mario_type == Mario_type::InvincibleFieryMario;
		}

		inline void shootFire() noexcept {
			if (isFieryMario() && !shootFireTrigger) {
				shootFireTrigger = true;
			}
		}

		int jumpCobo = 0;
	private:
		/// <summary>
		/// ������D
		/// </summary>
		void doJump() noexcept;

		/// <summary>
		/// �Y���ƥ�
		/// </summary>
		virtual void comeDown() noexcept override;

		void checkInvincible() noexcept;

		void shoot(void* data) noexcept;

		State state = State::MOVE;
		Mario_type mario_type = Mario_type::Mario;
		State mario_invincible = State::MOVE;
		float displacement = DEFAULTDISPLACEMENT;
		int index = 0;
		//int jumpDelay = 0;
		int jumpcount = 0;
		unsigned imgChangeDelay = 0;
		int invincibleCount{ 0 };
		bool diedflag = false;
		bool shootFireTrigger = false;


		std::unordered_map<Mario_type, std::unordered_map<State, std::vector<std::vector<const char*>>>> imgs = {
			{ Mario_type::Mario, { { State::MOVE, { { "imgs/super mario/1-1/Mario/frame0.png", "imgs/super mario/1-1/Mario/frame1.png", "imgs/super mario/1-1/Mario/frame2.png" }, { "imgs/super mario/1-1/Mario/Flip_frame0.png", "imgs/super mario/1-1/Mario/Flip_frame1.png", "imgs/super mario/1-1/Mario/Flip_frame2.png" } } },
										{ State::UP, { { "imgs/super mario/1-1/MarioJumping.png" }, { "imgs/super mario/1-1/Flip_MarioJumping.png" } } },
										{ State::DOWN, { { "imgs/super mario/1-1/MarioJumping.png" }, { "imgs/super mario/1-1/Flip_MarioJumping.png" } } },
										{ State::CROUCH, { { "imgs/super mario/1-1/Mario/frame0.png", "imgs/super mario/1-1/Mario/frame1.png", "imgs/super mario/1-1/Mario/frame2.png" }, { "imgs/super mario/1-1/Mario/Flip_frame0.png", "imgs/super mario/1-1/Mario/Flip_frame1.png", "imgs/super mario/1-1/Mario/Flip_frame2.png" } } },
										{ State::DIED, { { "imgs/super mario/1-1/MarioDied.png" }, { "imgs/super mario/1-1/MarioDied.png" } } } } },
			{ Mario_type::SuperMario, { { State::MOVE, { { "imgs/super mario/1-1/SuperMario/frame0.png", "imgs/super mario/1-1/SuperMario/frame1.png", "imgs/super mario/1-1/SuperMario/frame2.png" }, { "imgs/super mario/1-1/SuperMario/Flip_frame0.png", "imgs/super mario/1-1/SuperMario/Flip_frame1.png", "imgs/super mario/1-1/SuperMario/Flip_frame2.png" } } },
											{ State::UP, { { "imgs/super mario/1-1/SuperMarioJumping.png" }, { "imgs/super mario/1-1/Flip_SuperMarioJumping.png" } } },
											{ State::DOWN, { { "imgs/super mario/1-1/SuperMarioJumping.png" }, { "imgs/super mario/1-1/Flip_SuperMarioJumping.png" } } },
											{ State::CROUCH, { { "imgs/super mario/1-1/SuperMarioCrouching.png" }, { "imgs/super mario/1-1/Flip_SuperMarioCrouching.png" } } },
											{ State::DIED, { { "imgs/super mario/1-1/MarioDied.png" }, { "imgs/super mario/1-1/MarioDied.png" } } } } },
			{ Mario_type::FieryMario, { { State::MOVE, { { "imgs/super mario/1-1/FieryMario/frame0.png", "imgs/super mario/1-1/FieryMario/frame1.png", "imgs/super mario/1-1/FieryMario/frame2.png" }, { "imgs/super mario/1-1/FieryMario/Flip_frame0.png", "imgs/super mario/1-1/FieryMario/Flip_frame1.png", "imgs/super mario/1-1/FieryMario/Flip_frame2.png" } } },
											{ State::UP, { { "imgs/super mario/1-1/FieryMarioJumping.png" }, { "imgs/super mario/1-1/Flip_FieryMarioJumping.png" } } },
											{ State::DOWN, { { "imgs/super mario/1-1/FieryMarioJumping.png" }, { "imgs/super mario/1-1/Flip_FieryMarioJumping.png" } } },
											{ State::CROUCH, { { "imgs/super mario/1-1/FieryMarioCrouching.png" }, { "imgs/super mario/1-1/Flip_FieryMarioCrouching.png" } } },
											{ State::DIED, { { "imgs/super mario/1-1/MarioDied.png" }, { "imgs/super mario/1-1/MarioDied.png" } } } } },
			{ Mario_type::InvincibleMario, { { State::MOVE, { { "imgs/super mario/InvincibleMario/frame0.png", "imgs/super mario/InvincibleMario/frame1.png", "imgs/super mario/InvincibleMario/frame2.png", "imgs/super mario/InvincibleMario/frame3.png", "imgs/super mario/InvincibleMario/frame4.png", "imgs/super mario/InvincibleMario/frame5.png", "imgs/super mario/InvincibleMario/frame6.png", "imgs/super mario/InvincibleMario/frame7.png", "imgs/super mario/InvincibleMario/frame8.png", "imgs/super mario/InvincibleMario/frame9.png", "imgs/super mario/InvincibleMario/frame10.png", "imgs/super mario/InvincibleMario/frame11.png" }, {"imgs/super mario/InvincibleMario/Flip_frame0.png", "imgs/super mario/InvincibleMario/Flip_frame1.png", "imgs/super mario/InvincibleMario/Flip_frame2.png" }, { "imgs/super mario/InvincibleMario/Flip_frame3.png", "imgs/super mario/InvincibleMario/Flip_frame4.png", "imgs/super mario/InvincibleMario/Flip_frame5.png", "imgs/super mario/Flip_InvincibleMario/frame6.png", "imgs/super mario/InvincibleMario/Flip_frame7.png", "imgs/super mario/InvincibleMario/Flip_frame8.png", "imgs/super mario/InvincibleMario/Flip_frame9.png", "imgs/super mario/Flip_InvincibleMario/Flip_frame10.png", "imgs/super mario/Flip_InvincibleMario/frame11.png" } } },
												{ State::UP, { { "imgs/super mario/InvincibleMarioJumping/MarioJumpingframe0.png", "imgs/super mario/InvincibleMarioJumping/MarioJumpingframe1.png", "imgs/super mario/InvincibleMarioJumping/MarioJumpingframe2.png", "imgs/super mario/InvincibleMarioJumping/MarioJumpingframe3.png" }, { "imgs/super mario/InvincibleMarioJumping/Flip_MarioJumpingframe0.png", "imgs/super mario/InvincibleMarioJumping/Flip_MarioJumpingframe1.png", "imgs/super mario/InvincibleMarioJumping/Flip_MarioJumpingframe2.png", "imgs/super mario/InvincibleMarioJumping/Flip_MarioJumpingframe3.png" } } },
												{ State::DOWN, { { "imgs/super mario/InvincibleMarioJumping/MarioJumpingframe0.png", "imgs/super mario/InvincibleMarioJumping/MarioJumpingframe1.png", "imgs/super mario/InvincibleMarioJumping/MarioJumpingframe2.png", "imgs/super mario/InvincibleMarioJumping/MarioJumpingframe3.png" }, { "imgs/super mario/InvincibleMarioJumping/Flip_MarioJumpingframe0.png", "imgs/super mario/InvincibleMarioJumping/Flip_MarioJumpingframe1.png", "imgs/super mario/InvincibleMarioJumping/Flip_MarioJumpingframe2.png", "imgs/super mario/InvincibleMarioJumping/Flip_MarioJumpingframe3.png" } } },
												{ State::CROUCH, { { "imgs/super mario/InvincibleMario/frame0.png", "imgs/super mario/InvincibleMario/frame1.png", "imgs/super mario/InvincibleMario/frame2.png", "imgs/super mario/InvincibleMario/frame3.png", "imgs/super mario/InvincibleMario/frame4.png", "imgs/super mario/InvincibleMario/frame5.png", "imgs/super mario/InvincibleMario/frame6.png", "imgs/super mario/InvincibleMario/frame7.png", "imgs/super mario/InvincibleMario/frame8.png", "imgs/super mario/InvincibleMario/frame9.png", "imgs/super mario/InvincibleMario/frame10.png", "imgs/super mario/InvincibleMario/frame11.png" }, { "imgs/super mario/InvincibleMario/Flip_frame0.png", "imgs/super mario/InvincibleMario/Flip_frame1.png", "imgs/super mario/InvincibleMario/Flip_frame2.png" }, { "imgs/super mario/InvincibleMario/Flip_frame3.png", "imgs/super mario/InvincibleMario/Flip_frame4.png", "imgs/super mario/InvincibleMario/Flip_frame5.png", "imgs/super mario/Flip_InvincibleMario/frame6.png", "imgs/super mario/InvincibleMario/Flip_frame7.png", "imgs/super mario/InvincibleMario/Flip_frame8.png", "imgs/super mario/InvincibleMario/Flip_frame9.png", "imgs/super mario/Flip_InvincibleMario/Flip_frame10.png", "imgs/super mario/Flip_InvincibleMario/frame11.png" } } },
												{ State::DIED, { { "imgs/super mario/1-1/MarioDied.png" }, { "imgs/super mario/1-1/MarioDied.png" } } } } },
			{ Mario_type::InvincibleSuperMario, { { State::MOVE, { { "imgs/super mario/InvincibleSuperMario/frame0.png", "imgs/super mario/InvincibleSuperMario/frame1.png", "imgs/super mario/InvincibleSuperMario/frame2.png", "imgs/super mario/InvincibleSuperMario/frame3.png", "imgs/super mario/InvincibleSuperMario/frame4.png", "imgs/super mario/InvincibleSuperMario/frame5.png", "imgs/super mario/InvincibleSuperMario/frame6.png", "imgs/super mario/InvincibleSuperMario/frame7.png", "imgs/super mario/InvincibleSuperMario/frame8.png", "imgs/super mario/InvincibleSuperMario/frame9.png", "imgs/super mario/InvincibleSuperMario/frame10.png", "imgs/super mario/InvincibleSuperMario/frame11.png" }, { "imgs/super mario/InvincibleSuperMario/Flip_frame0.png", "imgs/super mario/InvincibleSuperMario/Flip_frame1.png", "imgs/super mario/InvincibleSuperMario/Flip_frame2.png" }, { "imgs/super mario/InvincibleSuperMario/Flip_frame3.png", "imgs/super mario/InvincibleSuperMario/Flip_frame4.png", "imgs/super mario/InvincibleSuperMario/Flip_frame5.png", "imgs/super mario/Flip_InvincibleSuperMario/frame6.png", "imgs/super mario/InvincibleSuperMario/Flip_frame7.png", "imgs/super mario/InvincibleSuperMario/Flip_frame8.png", "imgs/super mario/InvincibleSuperMario/Flip_frame9.png", "imgs/super mario/Flip_InvincibleSuperMario/Flip_frame10.png", "imgs/super mario/Flip_InvincibleSuperMario/frame11.png" } } },
													{ State::UP, { { "imgs/super mario/InvincibleSuperMarioJumping/InvincibleSuperMarioJumpingframe0.png", "imgs/super mario/InvincibleSuperMarioJumping/InvincibleSuperMarioJumpingframe1.png", "imgs/super mario/InvincibleSuperMarioJumping/InvincibleSuperMarioJumpingframe2.png", "imgs/super mario/InvincibleSuperMarioJumping/InvincibleSuperMarioJumpingframe3.png" }, { "imgs/super mario/InvincibleSuperMarioJumping/Flip_InvincibleSuperMarioJumpingframe0.png", "imgs/super mario/InvincibleSuperMarioJumping/Flip_InvincibleSuperMarioJumpingframe1.png", "imgs/super mario/InvincibleSuperMarioJumping/Flip_InvincibleSuperMarioJumpingframe2.png", "imgs/super mario/InvincibleSuperMarioJumping/Flip_InvincibleSuperMarioJumpingframe3.png" } } },
													{ State::DOWN, { { "imgs/super mario/InvincibleSuperMarioJumping/InvincibleSuperMarioJumpingframe0.png", "imgs/super mario/InvincibleSuperMarioJumping/InvincibleSuperMarioJumpingframe1.png", "imgs/super mario/InvincibleSuperMarioJumping/InvincibleSuperMarioJumpingframe2.png", "imgs/super mario/InvincibleSuperMarioJumping/InvincibleSuperMarioJumpingframe3.png" }, { "imgs/super mario/InvincibleSuperMarioJumping/Flip_InvincibleSuperMarioJumpingframe0.png", "imgs/super mario/InvincibleSuperMarioJumping/Flip_InvincibleSuperMarioJumpingframe1.png", "imgs/super mario/InvincibleSuperMarioJumping/Flip_InvincibleSuperMarioJumpingframe2.png", "imgs/super mario/InvincibleSuperMarioJumping/Flip_InvincibleSuperMarioJumpingframe3.png" } } },
													{ State::CROUCH, { { "imgs/super mario/InvincibleSuperMarioCrouching/InvincibleSuperMarioCrouchingframe0.png", "imgs/super mario/InvincibleSuperMarioCrouching/InvincibleSuperMarioCrouchingframe1.png", "imgs/super mario/InvincibleSuperMarioCrouching/InvincibleSuperMarioCrouchingframe2.png", "imgs/super mario/InvincibleSuperMarioCrouching/InvincibleSuperMarioCrouchingframe3.png" }, { "imgs/super mario/InvincibleSuperMarioCrouching/Flip_InvincibleSuperMarioCrouchingframe0.png", "imgs/super mario/InvincibleSuperMarioCrouching/Flip_InvincibleSuperMarioCrouchingframe1.png", "imgs/super mario/InvincibleSuperMarioCrouching/Flip_InvincibleSuperMarioCrouchingframe2.png", "imgs/super mario/InvincibleSuperMarioCrouching/Flip_InvincibleSuperMarioCrouchingframe3.png" } } },
													{ State::DIED, { { "imgs/super mario/1-1/MarioDied.png" }, { "imgs/super mario/1-1/MarioDied.png" } } } } }
			/*std::unordered_map<State, std::vector<std::vector<const char*>>> imgs =Flip_
			{ { State::MOVE, { { "imgs/super mario/1-1/Mario/frame0.png", "imgs/super mario/1-1/Mario/frame1.png", "imgs/super mario/1-1/Mario/frame2.png" }, { "imgs/super mario/1-1/Mario/Flip_frame0.png", "imgs/super mario/1-1/Mario/Flip_frame1.png", "imgs/super mario/1-1/Mario/Flip_frame2.png" } } },
				{ State::UP, { { "imgs/super mario/1-1/MarioJumping.png" }, { "imgs/super mario/1-1/Flip_MarioJumping.png" } } },
				{ State::DOWN, { { "imgs/super mario/1-1/MarioJumping.png" }, { "imgs/super mario/1-1/Flip_MarioJumping.png" } } },
				{ State::DIED, { { "imgs/super mario/1-1/MarioDied.png" }, { "imgs/super mario/1-1/MarioDied.png" } } },
				{ State::Invincible, {  } } };*/


		};
	};

	class Fire :Interface::ICollisionable,Interface::IMovable, public ImageObject {
	public:
		explicit Fire(const std::string& name,
			const float zIndex,
			const glm::vec2& pivot = { 0, 0 })
			: ImageObject(name, std::make_shared<Util::Image>(MyAPP::MyResourcesFilePath::FrieBall), zIndex, pivot) {
			MyType = ObjectType::Fire;
		}

		Fire(const Fire& other) = delete;

		Fire(Fire&& other) = delete;

		Fire() = delete;

		void behavior(void* data = nullptr) override;

		static void CreateFire(MyAPP::Form::FormManger& FM) noexcept;

		virtual void Move(const glm::vec2& distance) noexcept override;
		virtual void MoveTo(const glm::vec2& position) noexcept override {
			m_Transform.translation = position;
		}

		bool left = false; // �O�_�V������

	private:
		virtual void CheckCollision(void* data) override;
		
		float yposition = 0.0f; // Y�b��m

		float angle = 0.f;

	};
}



#endif // !MARIO_HPP
