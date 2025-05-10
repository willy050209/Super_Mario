#pragma once
#ifndef PIPEBRICK_HPP
#define PIPEBRICK_HPP

#include "Object/Brick/Brick.hpp"
#include "ObjectType.hpp"
#include "FilePath.hpp"

namespace MyAPP::Form::Object {
	class PipeBrick : public MyAPP::Form::Object::Brick {
	public:
		explicit PipeBrick(const std::string& name,
			const float zIndex,
			const glm::vec2& pivot = { 0, 0 })
			: Brick(name, (MyAPP::MyResourcesFilePath::BlockDarkImagePath), zIndex, pivot) {
			MyType = ObjectType::PipeBrick;
			collisionable = false;
			m_Visible = false;
		}


		PipeBrick(const PipeBrick& other) = delete;

		PipeBrick(PipeBrick&& other) = delete;

		PipeBrick() = delete;

		virtual void behavior(void* data = nullptr) override {};

		/// <summary>
		/// 取得方塊目前狀態
		/// </summary>
		/// <returns></returns>
		inline auto getState() const noexcept { return state; }
	};
}
#endif // !PIPEBRICK_HPP
