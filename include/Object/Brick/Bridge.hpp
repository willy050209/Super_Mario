#pragma once
#ifndef BRIDGE_HPP
#define BRIDGE_HPP

#include "Object/Brick/Brick.hpp"
#include "Object/ObjectType.hpp"
#include "FilePath.hpp"

namespace MyAPP::Form::Object {
	/// <summary>
	/// ¾ôª«¥ó Ä~©ÓBrick
	/// </summary>
	class Bridge : public Brick {
	public:
		explicit Bridge(const std::string& name,
			const float zIndex = -10,
			const glm::vec2& pivot = { 0, 0 })
			: Brick(name, MyAPP::MyResourcesFilePath::BridgeBrick,
				  zIndex, pivot) {
			MyType = ObjectType::Bridge;
			m_Visible = true;
			collisionable = true;
		}

		Bridge(const Bridge&) = delete;

		Bridge(Bridge&&) = delete;

		virtual void behavior(void* data = nullptr) override {};


	};
}

#endif