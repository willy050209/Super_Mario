#pragma once
#ifndef PIRANAPLANTDARK_HPP
#define PIRANAPLANTDARK_HPP
#include "Character.hpp"
#include "Interface/ICollisionable.hpp"
#include "Interface/IFrames.hpp"

namespace MyAPP::Form::Object {
	class PiranaPlant : public Character, Interface::ICollisionable, Interface::Iframes {
	public:
		PiranaPlant(const std::string& name, int zindex)
			: Character(name, *Frames, zindex) {
			MyType = ObjectType::PiranaPlant;
		}

		PiranaPlant(const PiranaPlant&) = delete;

		PiranaPlant(PiranaPlant&&) = delete;

		PiranaPlant& operator=(const PiranaPlant&) = delete;

		PiranaPlant& operator=(PiranaPlant&&) = delete;

		virtual void behavior(void* data) override;

		virtual void died() noexcept override;

		virtual void move() noexcept override;

		static constexpr auto GetFrames() noexcept { return Frames; }

		virtual std::string GetFrame() const noexcept {
			return (isDark ? FramesDark[FramesCount] : Frames[FramesCount]);
		}
		virtual void PlayFrames() noexcept override;

		constexpr void SetPos(const glm::vec2& position) noexcept { pos = position; }

		bool isDark{ false };

		static void nextFrame() noexcept {
			++FramesCount;
			if (FramesCount >= 2) FramesCount = 0;
		}

		virtual void Reset() noexcept override {
			Character::Reset();
			static_count = 0;
			m_static = PiranaPlantStatic::up;
			dead = false;
		}

	private:
		virtual void CheckCollision(void* data) override;

		void up() noexcept;

		void down() noexcept;

		void wait() noexcept;

		static constexpr inline char* const Frames[] = { "imgs/super mario/PiranaPlant/frame0.png", "imgs/super mario/PiranaPlant/frame1.png" };
		static constexpr inline char* const FramesDark[] = { "imgs/super mario/PiranaPlantDark/frame0.png", "imgs/super mario/PiranaPlantDark/frame1.png" };
		int imageChangeDelay{ 0 };

		size_t static_count = 0;

		static inline size_t FramesCount = 0;

		enum class PiranaPlantStatic {
			up,
			wait,
			down,
			wait_
		} m_static = PiranaPlantStatic::up;

		glm::vec2 pos{ 0.0f, 0.0f };

		bool dead{ false };
	};


}
#endif