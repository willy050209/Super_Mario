#pragma once
#ifndef GOOMBA_HPP
#define GOOMBA_HPP

#include "config.hpp"
#include "Character.hpp"
#include "Interface/IFrames.hpp"
#include <string>
namespace MyAPP {
	namespace Form {
		namespace Object {
			/// <summary>
			/// ®ßÄ_Ä_ª«¥ó Ä~©ÓCharacter
			/// </summary>
			class Goomba : public Character {
			public:
				Goomba(const std::string& name, int zindex)
					: Character(name, Frames[0], zindex) {
					MyType = ObjectType::Goomba;
				}

				Goomba(const Goomba&) = delete;

				Goomba(Goomba&&) = delete;

				Goomba& operator=(const Goomba&) = delete;

				Goomba& operator=(Goomba&&) = delete;

				virtual void behavior(void* data) override;

				virtual void died() noexcept override;

				inline auto IsLoop() const noexcept { return loop; }

				inline void SetLoop(bool val) noexcept { loop = val; }

				static constexpr auto GetFrames() noexcept { return Frames; }


			private:
				bool loop = true;

				int imgIndex{ 0 }, imageChangeDelay{ 0 };

				void ChangeImg() noexcept;

				virtual void comeDown() noexcept override;
				static constexpr inline char* const Frames[] = { R"(imgs\super mario\1-1\InvincibleMarioJumping\MarioJumpingframe0.png)", R"(imgs\super mario\1-1\InvincibleMarioJumping\MarioJumpingframe1.png)", R"(imgs\super mario\1-1\InvincibleMarioJumping\MarioJumpingframe2.png)", R"(imgs\super mario\1-1\InvincibleMarioJumping\MarioJumpingframe3.png)" };
				// use frame / 7 up
				//static constexpr inline char* const Frames[] = { "imgs/super mario/1-1/LittleGoomba/frame0.png", "imgs/super mario/1-1/LittleGoomba/frame1.png" };
			};
		}
	}
}
#endif // !GOOMBA_HPP
