#pragma once

#ifndef PROPBRICK_HPP
#define PROPBRICK_HPP

#include "Brick.hpp"
#include "ObjectType.hpp"

namespace MyAPP::Form::Object {

	class PropBrick : public Brick {
	public:
		explicit PropBrick(const std::string& name, const std::string& ImagePath,
			std::string_view proptype,
			BrickColor color,
			const float zIndex,
			const glm::vec2& pivot = { 0, 0 })
			: Brick(name, ImagePath, zIndex, pivot), color(color),proptype(proptype) {
			MyType = ObjectType::PropBrick;
		}

		PropBrick(const PropBrick&) = delete;

		PropBrick(PropBrick&&) = delete;

		PropBrick() = delete;

		/// <summary>
		/// 被敲擊事件
		/// </summary>
		virtual void bonk() noexcept override;

		/// <summary>
		/// 表單刷新時執行
		/// </summary>
		/// <param name="data"></param>
		virtual void behavior(void* data = nullptr) override;

	private:
		bool trigger = false;
		BrickColor color;
		std::string proptype;
	};
}

#endif