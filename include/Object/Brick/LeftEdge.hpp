#pragma once
#ifndef LEFTEDGE_HPP
#define LEFTEDGE_HPP

#include "Object/Brick/Brick.hpp"
#include "Interface/ICollisionable.hpp"
namespace MyAPP::Form ::Object {
	/// <summary>
	/// 存檔點物件 繼承Brick
	/// </summary>
	class LeftEdge : public Brick {
	public:

		explicit LeftEdge(const std::string& name,
			const float zIndex = 100,
			const glm::vec2& pivot = { 0, 0 })
			: Brick(name, LeftEdgeImagePath, zIndex, pivot) {
			MyType = ObjectType::LeftEdge;
			collisionable = true;
			m_Visible = false;
		}


		LeftEdge(const Brick& LeftEdge) = delete;

		LeftEdge(Brick&& LeftEdge) = delete;

		LeftEdge() = delete;

		virtual void behavior(void* data = nullptr) override{};
		
		virtual void Reset() noexcept {
			m_Visible = false;
			collisionable = true;
		}

		/// <summary>
		/// 圖片路徑
		/// </summary>
		static constexpr inline char* const LeftEdgeImagePath = "imgs/super mario/LeftEdge.png";

	};
}

#endif