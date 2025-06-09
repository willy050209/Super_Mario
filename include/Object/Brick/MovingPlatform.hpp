#pragma once
#ifndef MOVINGPLATFORM_HPP
#define MOVINGPLATFORM_HPP

#include "Object/Brick/Brick.hpp"
#include "Interface/ICollisionable.hpp"
#include "FilePath.hpp"

namespace MyAPP::Form::Object {
	/// <summary>
	/// 平台物件 繼承Brick
	/// </summary>
	class MovingPlatform :Interface::ICollisionable, public Brick {
	public:
		/// <summary>
		///
		/// </summary>
		/// <param name="name">ID</param>
		/// <param name="ImagePath">圖片路徑(預設 CheckPoint::CheckPointImagePath)</param>
		explicit MovingPlatform(const std::string& name,
			const float zIndex = 20,
			const glm::vec2& pivot = { 0, 0 })
			: Brick(name,MyAPP::MyResourcesFilePath::MovingPlatform , zIndex, pivot) {
			MyType = ObjectType::MovingPlatform;
		}

		MovingPlatform(const MovingPlatform& brick) = delete;

		MovingPlatform(MovingPlatform&& brick) = delete;

		virtual void behavior(void* data = nullptr) override;

		virtual void CheckCollision(void* data) override;

		bool up = { true };
	};
}

#endif