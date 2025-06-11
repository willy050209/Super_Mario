#pragma once
#ifndef TURTLE_HPP
#define TURTLE_HPP

#include "config.hpp"
#include "Character.hpp"
#include "Interface/ICollisionable.hpp"
#include <string>
namespace MyAPP::Form::Object{
	class Turtle : Interface::ICollisionable, public Character {
	public:
		Turtle(const std::string& name, int zindex)
			: Character(name, *Frames, zindex) {
			MyType = ObjectType::Turtle;
			left = 1;
		}

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

		virtual void move() noexcept override;

		virtual void Reset() noexcept override;

		inline void setMoveFlag(bool flag) noexcept {
			moveFlag = flag;
		}

		bool diedFlag = false;

		// static constexpr inline char* const imgs[][2] = { { "imgs/super mario/1-1/TurtleGreen/frame0.png", "imgs/super mario/1-1/TurtleGreen/frame1.png" }, { "imgs/super mario/1-1/TurtleGreen_faceleft/frame0.png", "imgs/super mario/1-1/TurtleGreen_faceleft/frame1.png" } };

		template <TurtleColor Color>
		static constexpr auto GetFrames() noexcept {
			if constexpr (Color == TurtleColor::Dark) {
				return FramesDark;
			}
			else if constexpr (Color == TurtleColor::Red) {
				return FramesRed;
			}
			else {
				return Frames;
			}
		}

		template <TurtleColor Color>
		static constexpr auto GetFrames_R() noexcept {
			if constexpr (Color == TurtleColor::Dark) {
				return darkimgs_r;
			}
			else if constexpr (Color == TurtleColor::Red) {
				return Redimgs_r;
			}
			else {
				return imgs_r;
			}
		}

		template <bool isDark>
		static constexpr auto GetTortoiseShellImagePath() noexcept {
			if constexpr (isDark) {
				return FramesDark;
			}
			else {
				return Frames;
			}
		}

		//static constexpr auto GetFrames() noexcept { return Frames; }
		//static constexpr auto GetFrames_R() noexcept { return imgs_r; }
		//static constexpr auto GetTortoiseShellImagePath() noexcept { return Frames; }


		inline void SetDark(bool val) noexcept { dark = val; }

	private:
		int imgIndex{ 0 }, imageChangeDelay{ 0 };
		
		bool moveFlag = true;
		bool dark = false;

		void ChangeImg() noexcept;

		virtual void comeDown() noexcept override;
				
		virtual void CheckCollision(void* data) override;

		static constexpr inline char* const Frames[] = { "imgs/super mario/TurtleGreen_faceleft/frame0.png", "imgs/super mario/TurtleGreen_faceleft/frame1.png" };
		static constexpr inline char* const imgs_r[] = { "imgs/super mario/TurtleGreen/frame0.png", "imgs/super mario/TurtleGreen/frame1.png" };
		static constexpr inline char* const FramesDark[] = { "imgs/super mario/TurtleGreenDark_faceleft/frame0.png", "imgs/super mario/TurtleGreenDark_faceleft/frame1.png" };
		static constexpr inline char* const darkimgs_r[] = { "imgs/super mario/TurtleGreenDark/frame0.png", "imgs/super mario/TurtleGreenDark/frame1.png" };
		static constexpr inline char* const FramesRed[] = { "imgs/super mario/TrutleRed_faceleft/frame0.png", "imgs/super mario/TrutleRed_faceleft/frame1.png" };
		static constexpr inline char* const Redimgs_r[] = { "imgs/super mario/TrutleRed/frame0.png", "imgs/super mario/TrutleRed/frame1.png" };
		static constexpr inline char* const TortoiseShell = { "imgs/super mario/1-1/KoopaTroopaShellGreen.png" };
		static constexpr inline char* const DarkTortoiseShell = { "imgs/super mario/KoopaTroopaShellGreenDark.png" };
		static constexpr inline char* const RedTortoiseShell = { "imgs/super mario/KoopaTroopaShellGreenDark.png" };
	};
}
#endif // !GOOMBA_HPP
