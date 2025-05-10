#pragma once
#ifndef Foor_HPP
#define Foor_HPP

#include "Object/Brick/Brick.hpp"
#include "Object/ObjectType.hpp"
#include "FilePath.hpp"

namespace MyAPP::Form::Object {
	/// <summary>
	/// 存檔點物件 繼承Brick
	/// </summary>
	class Floor : public Brick {
	public:
		explicit Floor(const std::string& name, const std::string& filename,
			const float zIndex = 10,
			const glm::vec2& pivot = { 0, 0 })
			: Brick(name, filename,
				  zIndex, pivot) {
			MyType = ObjectType::Floor;
		}

		Floor(const Floor& floor) = delete;

		Floor(Floor&& floor) = delete;


	};
}

#endif