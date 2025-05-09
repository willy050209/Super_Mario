#pragma once
#ifndef Stairs_HPP
#define Stairs_HPP

#include "Object/Brick.hpp"
#include "Object/ObjectType.hpp"
#include "FilePath.hpp"

namespace MyAPP::Form::Object {
	/// <summary>
	/// 存檔點物件 繼承Brick
	/// </summary>
	class Stairs : public Brick {
	public:
		explicit Stairs(const std::string& name, const std::string& filename, const float zIndex = 10,
			const glm::vec2& pivot = { 0, 0 })
			: Brick(name, filename,
				  zIndex, pivot) {
			MyType = ObjectType::Stairs;
		}

		Stairs(const Stairs& floor) = delete;

		Stairs(Stairs&& floor) = delete;
	};
}

#endif