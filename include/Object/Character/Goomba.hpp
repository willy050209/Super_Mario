#pragma once
#ifndef GOOMBA_HPP
#define GOOMBA_HPP

#include "config.hpp"
#include "Character.hpp"
#include "Object/PhysicsComponent.hpp"
#include "Object/AnimationComponent.hpp"
#include <string>
namespace MyAPP {
	namespace Form {
		namespace Object {
			/// <summary>
			/// 栗寶寶物件 繼承Character
			/// </summary>
			class Goomba : public Character {
			public:
				Goomba(const std::string& name, int zindex);

				Goomba(const Goomba&) = delete;
				Goomba(Goomba&&) = delete;
				Goomba& operator=(const Goomba&) = delete;
				Goomba& operator=(Goomba&&) = delete;

				virtual void behavior(void* data) override;
				virtual void died() noexcept override;

				inline void SetDark(bool val) noexcept { dark = val; }

			private:
				bool dark = false;
				bool isDied = false;
				
				PhysicsComponent* m_Physics = nullptr;
				AnimationComponent* m_Animation = nullptr;

				virtual void CheckCollision(void* data);

				static constexpr inline char* const Frames[] = { "imgs/super mario/LittleGoomba/frame0.png", "imgs/super mario/LittleGoomba/frame1.png" };
				static constexpr inline char* const FramesDark[] = { "imgs/super mario/LittleGoombaDark/frame0.png", "imgs/super mario/LittleGoombaDark/frame1.png" };
			};
		}
	}
}
#endif // !GOOMBA_HPP
