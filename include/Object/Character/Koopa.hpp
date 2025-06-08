#pragma once
#ifndef KOOPA_HPP
#define KOOPA_HPP
#include "Character.hpp"
#include "Object/ImageObject.hpp"
#include "Interface/ICollisionable.hpp"
#include "Interface/IFrames.hpp"
#include "Interface/IMovable.hpp"
#include "FilePath.hpp"
namespace MyAPP::Form {
	class FormManger;
}
namespace MyAPP::Form::Object {
	class Koopa : public Character, Interface::ICollisionable,Interface::Iframes {
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

		template<bool is_left>
		static constexpr auto GetFrames() noexcept { 
			if constexpr (is_left) {
				return Frames;
			}
			else {
				return Flip_Frames;
			}
		}

		virtual std::string GetFrame() const noexcept {
			return left ? Frames[imgIndex] : Flip_Frames[imgIndex];
		}
		virtual void PlayFrames() noexcept override;
		
	private:
		void checkPosition() noexcept;
		void turn(void* data) noexcept;
		void shoot(void* data) noexcept;
		void random_shoot(void* data) noexcept;
		
		virtual void CheckCollision(void* data) override;
		static constexpr inline char* const Frames[] = { "imgs/super mario/Koopa/frame0.png", "imgs/super mario/Koopa/frame1.png" };
		static constexpr inline char* const Flip_Frames[] = { "imgs/super mario/Koopa/Flip_frame0.png", "imgs/super mario/Koopa/Flip_frame1.png" };

		enum class KoopaState {
			jump1,
			null,
			jump2

		} koopstate = KoopaState::jump1;

		int imgIndex{ 0 }, imageChangeDelay{ 0 };
		int delaycount = 0;
		int jumpcout = 0;
		int shootdelay = 0;
		bool jump = false;
		bool is_L_or_R = true;
	};

	class Koopa_Fire : Interface::ICollisionable, Interface::IMovable, public ImageObject {
	public:
		explicit Koopa_Fire(const std::string& name,
			const float zIndex,
			const glm::vec2& pivot = { 0, 0 })
			: ImageObject(name, std::make_shared<Util::Image>(MyAPP::MyResourcesFilePath::Koopa_Fire), zIndex, pivot) {
			MyType = ObjectType::Koopa_Fire;
		}

		Koopa_Fire(const Koopa_Fire& other) = delete;

		Koopa_Fire(Koopa_Fire&& other) = delete;

		Koopa_Fire() = delete;

		void behavior(void* data = nullptr) override;

		static void CreateFire(MyAPP::Form::FormManger& FM) noexcept;

		virtual void Move(const glm::vec2& distance) noexcept override;
		virtual void MoveTo(const glm::vec2& position) noexcept override {
			m_Transform.translation = position;
		}

		bool left = false; // ¬O§_¦V¥ª²¾°Ê

	private:
		virtual void CheckCollision(void* data) override;

		void destroyFire(FormManger& FM) noexcept;

		float Xcount = 0.f;
		bool touch_ground = false;
		bool destroyflag = false;
	};
}
#endif