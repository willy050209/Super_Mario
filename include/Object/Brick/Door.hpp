#pragma once
#ifndef Door_HPP
#define Door_HPP

#include "Object/Brick/Brick.hpp"
#include "Object/ObjectType.hpp"
#include "FilePath.hpp"
#include "Interface/ICollisionable.hpp"

namespace MyAPP::Form::Object {
	/// <summary>
	/// �s���I���� �~��Brick
	/// </summary>
	class Door :Interface::ICollisionable, public Brick {
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

		Door(const Door&) = delete;

		Door(Door&&) = delete;

		// CheckPoint() = delete;

		virtual void behavior(void* data = nullptr) override;

		bool Enable = true;

	private:

		void CheckCollision(void* data) noexcept;
	};
}

#endif