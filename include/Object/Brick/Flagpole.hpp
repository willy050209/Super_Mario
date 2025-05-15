#pragma once
#ifndef Flagpole_HPP
#define Flagpole_HPP

#include "Object/Brick/Brick.hpp"
#include "Object/ObjectType.hpp"
#include "FilePath.hpp"

namespace MyAPP::Form::Object {
	/// <summary>
	/// ºX±ìª«¥ó Ä~©ÓBrick
	/// </summary>
	class Flagpole : public Brick {
	public:
		explicit Flagpole(const std::string& name,
			const float zIndex = -10,
			const glm::vec2& pivot = { 0, 0 })
			: Brick(name, MyAPP::MyResourcesFilePath::BlockImagePath,
				  zIndex, pivot) {
			MyType = ObjectType::Flagpole;
			m_Visible = false;
			collisionable = false;
		}

		Flagpole(const Flagpole& ) = delete;

		Flagpole(Flagpole&& ) = delete;

		Flagpole() = delete;

		virtual void behavior(void* data = nullptr) override {};

	};
}

#endif