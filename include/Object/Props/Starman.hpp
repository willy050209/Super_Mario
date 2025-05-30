#pragma once
#ifndef STARMAN_HPP
#define STARMAN_HPP

#include "Props.hpp"
#include "ObjectType.hpp"
#include "Object/Interface/IFrames.hpp"
#include "Object/Interface/ICollisionable.hpp"
#include "Interface/IComeDownable.hpp"
#include "Interface/IJumpable.hpp"
#include "Interface/IMovable.hpp"

namespace MyAPP::Form::Object:: Props {
	/// <summary>
	/// µL¼Ä¬P¬P Ä~©ÓProps
	/// </summary>
	class Starman :Interface::ICollisionable, Interface::Iframes,Interface::IComeDownable,Interface::IJumpable,Interface::IMovable, public Props {
	public:
		explicit Starman(const std::string& name,
			const float zIndex,
			const glm::vec2& pivot = { 0, 0 })
			: Props(name, frames[0], zIndex, pivot) {
			MyType = ObjectType::Starman;
		}

		Starman(const Starman& other) = delete;

		Starman(Starman&& other) = delete;

		Starman() = delete;


		virtual void behavior(void* data = nullptr) override;

		virtual std::string GetFrame() const noexcept { return *frames; }

		static constexpr auto GetFrames() noexcept { return frames; }

		virtual void Move(glm::vec2 distance) noexcept override;

		virtual void MoveTo(glm::vec2 position) noexcept override {
			SetPosition(position);
		}

		void SetUpDistance(int distance) { UpDistance = distance; }

		bool m_movable = true;

	private:
		virtual void PlayFrames() noexcept override;

		virtual void CheckCollision(void* gm) override;

		virtual void doDown() noexcept override;

		virtual void doJump() noexcept override;

		virtual void Jump() noexcept override {};

	private:
		int count{ 0 }, imgindex{ 0 };
		int UpDistance = 0;
		static constexpr inline char* const frames[] = { R"(imgs\super mario\Starman\frame0.png)", R"(imgs\super mario\Starman\frame1.png)", R"(imgs\super mario\Starman\frame2.png)", R"(imgs\super mario\Starman\frame3.png)" };
	};
	}
#endif // !BRICK_HPP
