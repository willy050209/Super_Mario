#pragma once
#ifndef HIDDENBRICK_HPP
#define HIDDENBRICK_HPP

#include "Brick.hpp"
#include "ObjectType.hpp"
#include "FilePath.hpp"
#include "Object\Interface\ICollisionable.hpp"
namespace MyAPP ::Form:: Object {
	class HiddenBrick : public Brick ,Interface::ICollisionable{
	public:
		explicit HiddenBrick(const std::string& name, const std::string& ImagePath,
			const float zIndex = 10,
			const glm::vec2& pivot = { 0, 0 })
			: Brick(name, ImagePath, zIndex, pivot) {
			MyType = ObjectType::HiddenBrick;
			this->collisionable = false;
			this->m_Visible = false;
		}

		HiddenBrick(const HiddenBrick& other) = delete;

		HiddenBrick(HiddenBrick&& other) = delete;

		HiddenBrick() = delete;

		virtual void behavior(void* data = nullptr) override;

		virtual void CheckCollision(void* data) override;

	};
}

#endif // !QUESTIONBLOCK_HPP
