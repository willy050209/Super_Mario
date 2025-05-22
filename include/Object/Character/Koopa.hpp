#pragma once
#ifndef KOOPA_HPP
#define KOOPA_HPP
#include "Character.hpp"
#include "Interface/ICollisionable.hpp"

namespace MyAPP::Form::Object {
	class Koopa : public Character, Interface::ICollisionable {
	public:
		Koopa(const std::string& name, int zindex)
			: Character(name, *Frames, zindex) {
			MyType = ObjectType::Koopa;
			left = 1;
		}

		Koopa(const Koopa&) = delete;

		Koopa(Koopa&&) = delete;

		Koopa& operator=(const Koopa&) = delete;

		Koopa& operator=(Koopa&&) = delete;

		virtual void behavior(void* data) override;

		virtual void died() noexcept override;

		virtual void move() noexcept override;

		static constexpr auto GetFrames() noexcept { return Frames; }
		
		private:
		void checkPosition() noexcept;
		virtual void CheckCollision(void* data) override;
		static constexpr inline char* const Frames[] = { "imgs/super mario/Koopa/frame0.png", "imgs/super mario/Koopa/frame1.png" };
		int imgIndex{ 0 }, imageChangeDelay{ 0 };
	};

	
}
#endif