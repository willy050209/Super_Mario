#pragma once
#ifndef MARIO_HPP
#define MARIO_HPP

#include "config.hpp"
#include "Character.hpp"
#include "Object/ImageObject.hpp"
#include "Interface/ICollisionable.hpp"
#include "Interface/IMovable.hpp"
#include "Interface/IFrames.hpp"
#include "FilePath.hpp"

#include "Object/PhysicsComponent.hpp"
#include "Object/AnimationComponent.hpp"
#include "Object/InputComponent.hpp"
#include "Object/AudioComponent.hpp"
#include "Object/Character/MarioEnums.hpp"

namespace MyAPP::Form {
	class FormManager;
}

namespace MyAPP::Form::Object {

	class Mario : public Character {
	public:
		using State = MarioState;
		using Mario_type = MarioType;

		explicit Mario(const std::string& name, int zindex);

		inline State GetState() const noexcept { return state; }
		inline Mario_type GetMario_type() const noexcept { return mario_type; }

		void jump(float d = 4.5f) noexcept;

		inline void down() noexcept {
			state = State::DOWN;
			changeImg();
		}

		virtual void behavior(void* data = nullptr) override;
		virtual void move() noexcept override;
		void changeImg() noexcept;
		virtual void died() noexcept override;

		inline void changeState(const std::string& str) noexcept {
			if (str == "UP") state = State::UP;
			else if (str == "MOVE") state = State::MOVE;
			else if (str == "DOWN") state = State::DOWN;
			else if (str == "DIED") state = State::DIED;
		}

		inline void changeState(State state_) noexcept { state = state_; }

		void changeType(Mario_type type_) noexcept;

		inline auto isInvincible() const noexcept { return invincibleCount > 0; }
		inline bool isdied() const noexcept { return state == State::DIED; }
		inline void setInvincible(int val) noexcept { invincibleCount = val; }

		virtual void Reset() noexcept override;

		bool isBigMario() const noexcept;
		bool isMiniMario() const noexcept;
		bool isFieryMario() const noexcept;

		inline void shootFire() noexcept {
			if (isFieryMario() && !shootFireTrigger) {
				shootFireTrigger = true;
			}
		}

		std::string GetCrouchingImg() const noexcept;

		inline void crouch() noexcept {
			state = State::CROUCH;
			changeImg();
		}

		void CheckPos(void* data);
		void SetDownFlag(const bool& val) { downFlag = val; }

		int jumpCobo = 0;

	private:
		void doJump() noexcept;
		virtual void comeDown() noexcept override;
		void checkInvincible(void* data) noexcept;
		void shoot(void* data) noexcept;
		void StandCheck() noexcept;

		// Components
		PhysicsComponent* m_Physics = nullptr;
		AnimationComponent* m_Animation = nullptr;
		InputComponent* m_Input = nullptr;
		AudioComponent* m_Audio = nullptr;

		// State
		State state = State::MOVE;
		Mario_type mario_type = Mario_type::Mario;
		int invincibleCount{ 0 };
		bool diedflag = false;
		bool shootFireTrigger = false;
		bool addpointflag = false;
		bool downFlag = true;
	};

	class Fire : public ImageObject, public Interface::ICollisionable, public Interface::IMovable, public Interface::Iframes {
	public:
		explicit Fire(const std::string& name, float zIndex, const glm::vec2& pivot = { 0, 0 });
		virtual void behavior(void* data = nullptr) override;
		static void CreateFire(MyAPP::Form::FormManager& FM) noexcept;
		virtual void Move(const glm::vec2& distance) noexcept override;
		virtual void MoveTo(const glm::vec2& position) noexcept override { m_Transform.translation = position; }
		virtual std::string GetFrame() const noexcept override { return Frame[imgIndex]; }
		virtual void PlayFrames() noexcept override;

		bool left = false;

	private:
		virtual void CheckCollision(void* data) override;
		void destroyFire(FormManager& FM) noexcept;
		
		bool touch_ground = false;
		bool destroyflag = false;
		float distance_y = 0.0f;
		float Xcount = 0.f;
		float angle = 0.f;
		int imgIndex = 0;
		int imgDelay = 0;
		static constexpr char* Frame[]{ (char*)R"(imgs\super mario\FireBall\01.png)", (char*)R"(imgs\super mario\FireBall\02.png)", (char*)R"(imgs\super mario\FireBall\03.png)", (char*)R"(imgs\super mario\FireBall\04.png)" };
	};
}

#endif
