#pragma once
#ifndef CHECKPOINT_HPP
#define CHECKPOINT_HPP

#include "Object/Brick/Brick.hpp"
#include "Interface/ICollisionable.hpp"
namespace MyAPP::Form ::Object {
	/// <summary>
	/// 存檔點物件 繼承Brick
	/// </summary>
	class CheckPoint : Interface::ICollisionable, public Brick {
	public:
		/// <summary>
		///
		/// </summary>
		/// <param name="name">ID</param>
		/// <param name="ImagePath">圖片路徑(預設 CheckPoint::CheckPointImagePath)</param>
		explicit CheckPoint(const std::string& name,
			const float zIndex = -10,
			const glm::vec2& pivot = { 0, 0 })
			: Brick(name, CheckPointImagePath, zIndex, pivot) {
			MyType = ObjectType::CheckPoint;
			collisionable = false;
		}


		CheckPoint(const Brick& CheckPoint) = delete;

		CheckPoint(Brick&& CheckPoint) = delete;

		CheckPoint() = delete;

		virtual void behavior(void* data = nullptr) override;

		virtual void CheckCollision(void* data) override;

		/// <summary>
		/// 圖片路徑
		/// </summary>
		static constexpr inline char* const CheckPointImagePath = "imgs/super mario/CheckPoint.png";

		bool Enable = true;
	};
}

#endif