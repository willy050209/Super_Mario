#pragma once
#ifndef GOOMBA_HPP
#define GOOMBA_HPP

#include "config.hpp"
#include "Character.hpp"
#include "Interface/IFrames.hpp"
#include "Interface/ICollisionable.hpp"
#include <string>
namespace MyAPP {
	namespace Form {
		namespace Object {
			/// <summary>
			/// ®ßÄ_Ä_ª«¥ó Ä~©ÓCharacter
			/// </summary>
			class Goomba : Interface::ICollisionable, public Character {
			public:
				Goomba(const std::string& name, int zindex)
					: Character(name, Frames[0], zindex) {
					MyType = ObjectType::Goomba;
					left = 1;
				}

				Goomba(const Goomba&) = delete;

				Goomba(Goomba&&) = delete;

				Goomba& operator=(const Goomba&) = delete;

				Goomba& operator=(Goomba&&) = delete;

				virtual void behavior(void* data) override;

				virtual void died() noexcept override;

				inline auto IsLoop() const noexcept { return loop; }

				inline void SetLoop(bool val) noexcept { loop = val; }

				template <bool isDark>
				static constexpr auto GetFrames() noexcept { 
					if constexpr (isDark) {
						return FramesDark;
					}
					else {
						return Frames;
					}
				}

				inline void SetDark(bool val) noexcept { dark = val; }


			private:
				bool loop = true;
				bool dark = false;

				int imgIndex{ 0 }, imageChangeDelay{ 60 };

				void ChangeImg() noexcept;

				virtual void CheckCollision(void* data) override;

				//virtual void comeDown() noexcept override;
				//static constexpr inline char* const Frames[] = { R"(imgs\super mario\1-1\InvincibleMarioJumping\MarioJumpingframe0.png)", R"(imgs\super mario\1-1\InvincibleMarioJumping\MarioJumpingframe1.png)", R"(imgs\super mario\1-1\InvincibleMarioJumping\MarioJumpingframe2.png)", R"(imgs\super mario\1-1\InvincibleMarioJumping\MarioJumpingframe3.png)" };
				// use frame / 
				static constexpr inline char* const Frames[] = { "imgs/super mario/LittleGoomba/frame0.png", "imgs/super mario/LittleGoomba/frame1.png" };
				static constexpr inline char* const FramesDark[] = { "imgs/super mario/LittleGoombaDark/frame0.png", "imgs/super mario/LittleGoombaDark/frame1.png" };
			};
		}
	}
}
#endif // !GOOMBA_HPP
