#pragma once
#ifndef FIREFLOWER_HPP
#define FIREFLOWER_HPP

#include "Props.hpp"
#include "ObjectType.hpp"
#include "Object/Interface/IFrames.hpp"
#include "Interface/ICollisionable.hpp"
#include "Interface/IJumpable.hpp"

namespace MyAPP::Form::Object::Props {
	/// <summary>
	/// ¤õµKªá Ä~©ÓProps
	/// </summary>
	class FireFlower : Interface::ICollisionable, Interface::Iframes, Interface::IJumpable, public Props {
	public:
		explicit FireFlower(const std::string& name,
			const float zIndex,
			const glm::vec2& pivot = { 0, 0 })
			: Props(name, frames[0], zIndex, pivot) {
			MyType = ObjectType::FireFlower;
		}

		FireFlower(const FireFlower& other) = delete;

		FireFlower(FireFlower&& other) = delete;

		FireFlower() = delete;


		static constexpr auto GetFrames() noexcept { return frames; }

		virtual void behavior(void* data = nullptr) override;
		virtual std::string GetFrame() const noexcept { return frames[imgindex]; }
		void SetUpDistance(int distance) { UpDistance = distance; }
	private:
		virtual void PlayFrames() noexcept override;

		virtual void CheckCollision(void* data) override;

		virtual void doJump() noexcept override;
		virtual void Jump() noexcept override {};

	private:
		int UpDistance = 0;
		int count{ 0 }, imgindex{ 0 };
		static constexpr inline char* const frames[] = { R"(imgs\super mario\FireFlower\frame0.png)", R"(imgs\super mario\FireFlower\frame1.png)", R"(imgs\super mario\FireFlower\frame2.png)", R"(imgs\super mario\FireFlower\frame3.png)" };
	};
}

#endif // !BRICK_HPP
