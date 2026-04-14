#pragma once
#ifndef TURTLE_HPP
#define TURTLE_HPP

#include "config.hpp"
#include "Character.hpp"
#include "Object/PhysicsComponent.hpp"
#include "Object/AnimationComponent.hpp"
#include <string>
namespace MyAPP::Form::Object{
	class Turtle : public Character {
	public:
		Turtle(const std::string& name, int zindex);

		Turtle(const Turtle&) = delete;
		Turtle(Turtle&&) = delete;
		Turtle& operator=(const Turtle&) = delete;
		Turtle& operator=(Turtle&&) = delete;

		enum class TurtleColor {
			Default,
			Dark,
			Red
		} turtlecolor = TurtleColor::Default;

		virtual void behavior(void* data) override;
		virtual void died() noexcept override;
		virtual void Reset() noexcept override;

		inline void setMoveFlag(bool flag) noexcept { moveFlag = flag; }
		inline void SetDark(bool val) noexcept { dark = val; }

		bool diedFlag = false;

	private:
		bool moveFlag = true;
		bool dark = false;
		bool isShell = false;
		
		PhysicsComponent* m_Physics = nullptr;
		AnimationComponent* m_Animation = nullptr;

		virtual void CheckCollision(void* data);

		static constexpr inline char* const Frames[] = { "imgs/super mario/TurtleGreen_faceleft/frame0.png", "imgs/super mario/TurtleGreen_faceleft/frame1.png" };
		static constexpr inline char* const imgs_r[] = { "imgs/super mario/TurtleGreen/frame0.png", "imgs/super mario/TurtleGreen/frame1.png" };
		static constexpr inline char* const FramesDark[] = { "imgs/super mario/TurtleGreenDark_faceleft/frame0.png", "imgs/super mario/TurtleGreenDark_faceleft/frame1.png" };
		static constexpr inline char* const darkimgs_r[] = { "imgs/super mario/TurtleGreenDark/frame0.png", "imgs/super mario/TurtleGreenDark/frame1.png" };
		static constexpr inline char* const FramesRed[] = { "imgs/super mario/TrutleRed_faceleft/frame0.png", "imgs/super mario/TrutleRed_faceleft/frame1.png" };
		static constexpr inline char* const Redimgs_r[] = { "imgs/super mario/TrutleRed/frame0.png", "imgs/super mario/TrutleRed/frame1.png" };
		static constexpr inline char* const TortoiseShell = "imgs/super mario/1-1/KoopaTroopaShellGreen.png";
		static constexpr inline char* const DarkTortoiseShell = "imgs/super mario/KoopaTroopaShellGreenDark.png";
		static constexpr inline char* const RedTortoiseShell = "imgs/super mario/KoopaTroopaShellRed.png";
	};
}
#endif // !GOOMBA_HPP
