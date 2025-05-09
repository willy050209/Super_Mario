#pragma once
#ifndef Door_HPP
#define Door_HPP

#include "Object/Brick.hpp"
#include "Object/ObjectType.hpp"
#include "FilePath.hpp"

namespace MyAPP::Form::Object {
	/// <summary>
	/// 存檔點物件 繼承Brick
	/// </summary>
	class Door : public Brick {
	public:

		explicit Door(const std::string& name,
			const float zIndex = -10,
			const glm::vec2& pivot = { 0, 0 })
			: Brick(name, MyAPP::MyResourcesFilePath::BlockImagePath,
				zIndex, pivot) {
			MyType = ObjectType::Door;
			m_Visible = false;
			collisionable = false;
		}

		Door(const Door& door) = delete;

		Door(Door&& door) = delete;

		// CheckPoint() = delete;

		virtual void behavior(void* data = nullptr) override;

		bool Enable = true;
	};
}

#endif