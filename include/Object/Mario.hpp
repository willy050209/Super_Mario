#pragma once
#ifndef MARIO_HPP
#define MARIO_HPP
#include "config.hpp"
#include "Character.hpp"

#include <unordered_map>
#include <vector>
#include <string>
namespace MyAPP {
	namespace Form {
		namespace Object {
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
				inline void jump() noexcept {
					state = State::UP;
					displacement = WINDOW_HEIGHT / 15.f * 4.5f / 15;
					index = 0;
					jumpcount = 15;
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
					return mario_invincible == State::Invincible;
				}


				/// <summary>
				/// ���]�Ҧ����A
				/// </summary>
				inline void Reset() noexcept {
					state = State::MOVE;
					mario_type = Mario_type::Mario;
					index = 0;
					left = 0;
					changeImg();
					// mario_invincible = Mario_Invincible::notInvincible;
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


				State state = State::MOVE;
				Mario_type mario_type = Mario_type::Mario;
				State mario_invincible = State::MOVE;
				float displacement = DEFAULTDISPLACEMENT;
				int index = 0;
				//int jumpDelay = 0;
				int jumpcount = 0;
				unsigned imgChangeDelay = 0;
				bool diedflag = false;

				std::unordered_map<Mario_type, std::unordered_map<State, std::vector<std::vector<const char*>>>> imgs = {
					{ Mario_type::Mario, { { State::MOVE, { { "imgs/super mario/1-1/Mario/frame0.png", "imgs/super mario/1-1/Mario/frame1.png", "imgs/super mario/1-1/Mario/frame2.png" }, { "imgs/super mario/1-1/Mario/Flip_frame0.png", "imgs/super mario/1-1/Mario/Flip_frame1.png", "imgs/super mario/1-1/Mario/Flip_frame2.png" } } },
											 { State::UP, { { "imgs/super mario/1-1/MarioJumping.png" }, { "imgs/super mario/1-1/Flip_MarioJumping.png" } } },
											 { State::DOWN, { { "imgs/super mario/1-1/MarioJumping.png" }, { "imgs/super mario/1-1/Flip_MarioJumping.png" } } },
											 { State::CROUCH, { { "imgs/super mario/1-1/Mario/frame0.png", "imgs/super mario/1-1/Mario/frame1.png", "imgs/super mario/1-1/Mario/frame2.png" }, { "imgs/super mario/1-1/Mario/Flip_frame0.png", "imgs/super mario/1-1/Mario/Flip_frame1.png", "imgs/super mario/1-1/Mario/Flip_frame2.png" } } },
											 { State::DIED, { { "imgs/super mario/1-1/MarioDied.png" }, { "imgs/super mario/1-1/MarioDied.png" } } },
											 { State::Invincible, {} } } },
					{ Mario_type::SuperMario, { { State::MOVE, { { "imgs/super mario/1-1/SuperMario/frame0.png", "imgs/super mario/1-1/SuperMario/frame1.png", "imgs/super mario/1-1/SuperMario/frame2.png" }, { "imgs/super mario/1-1/SuperMario/Flip_frame0.png", "imgs/super mario/1-1/SuperMario/Flip_frame1.png", "imgs/super mario/1-1/SuperMario/Flip_frame2.png" } } },
												  { State::UP, { { "imgs/super mario/1-1/SuperMarioJumping.png" }, { "imgs/super mario/1-1/Flip_SuperMarioJumping.png" } } },
												  { State::DOWN, { { "imgs/super mario/1-1/SuperMarioJumping.png" }, { "imgs/super mario/1-1/Flip_SuperMarioJumping.png" } } },
												  { State::CROUCH, { { "imgs/super mario/1-1/SuperMarioCrouching.png" }, { "imgs/super mario/1-1/Flip_SuperMarioCrouching.png" } } },
												  { State::DIED, { { "imgs/super mario/1-1/MarioDied.png" }, { "imgs/super mario/1-1/MarioDied.png" } } },
												  { State::Invincible, {} } } },
					{ Mario_type::FieryMario, { { State::MOVE, { { "imgs/super mario/1-1/FieryMario/frame0.png", "imgs/super mario/1-1/FieryMario/frame1.png", "imgs/super mario/1-1/FieryMario/frame2.png" }, { "imgs/super mario/1-1/FieryMario/Flip_frame0.png", "imgs/super mario/1-1/FieryMario/Flip_frame1.png", "imgs/super mario/1-1/FieryMario/Flip_frame2.png" } } },
												  { State::UP, { { "imgs/super mario/1-1/FieryMarioJumping.png" }, { "imgs/super mario/1-1/Flip_FieryMarioJumping.png" } } },
												  { State::DOWN, { { "imgs/super mario/1-1/FieryMarioJumping.png" }, { "imgs/super mario/1-1/Flip_FieryMarioJumping.png" } } },
												  { State::CROUCH, { { "imgs/super mario/1-1/FieryMarioCrouching.png" }, { "imgs/super mario/1-1/Flip_FieryMarioCrouching.png" } } },
												  { State::DIED, { { "imgs/super mario/1-1/MarioDied.png" }, { "imgs/super mario/1-1/MarioDied.png" } } },
												  { State::Invincible, { { "imgs/super mario/1-1/InvincibleFieryMario/frame0.png" }, { "imgs/super mario/1-1/InvincibleFieryMario/frame1.png" }, { "imgs/super mario/1-1/InvincibleFieryMario/frame2.png" }, { "imgs/super mario/1-1/InvincibleFieryMario/fram3.png" }, { "imgs/super mario/1-1/InvincibleFieryMario/Flip_frame0.png" }, { "imgs/super mario/1-1/InvincibleFieryMario/Flip_frame1.png" }, { "imgs/super mario/1-1/InvincibleFieryMario/Flip_frame2.png" }, { "imgs/super mario/1-1/InvincibleFieryMario/Flip_frame3.png" } } } } }

					/*std::unordered_map<State, std::vector<std::vector<const char*>>> imgs =
					{ { State::MOVE, { { "imgs/super mario/1-1/Mario/frame0.png", "imgs/super mario/1-1/Mario/frame1.png", "imgs/super mario/1-1/Mario/frame2.png" }, { "imgs/super mario/1-1/Mario/Flip_frame0.png", "imgs/super mario/1-1/Mario/Flip_frame1.png", "imgs/super mario/1-1/Mario/Flip_frame2.png" } } },
						{ State::UP, { { "imgs/super mario/1-1/MarioJumping.png" }, { "imgs/super mario/1-1/Flip_MarioJumping.png" } } },
						{ State::DOWN, { { "imgs/super mario/1-1/MarioJumping.png" }, { "imgs/super mario/1-1/Flip_MarioJumping.png" } } },
						{ State::DIED, { { "imgs/super mario/1-1/MarioDied.png" }, { "imgs/super mario/1-1/MarioDied.png" } } },
						{ State::Invincible, {  } } };*/


				};
			};
		}
	}
}
#endif // !MARIO_HPP
