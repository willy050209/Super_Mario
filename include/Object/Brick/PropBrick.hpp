#pragma once

#ifndef PROPBRICK_HPP
#define PROPBRICK_HPP

#include "Brick.hpp"
#include "ObjectType.hpp"
#include "FilePath.hpp"

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
		/// �Q�V���ƥ�
		/// </summary>
		virtual void bonk() noexcept override;

		virtual void Reset() noexcept override {
			Brick::Reset();
			trigger = false;
			Enable = true;
			switch (color) {
			case MyAPP::Form::Object::BrickColor::normal:
				std::static_pointer_cast<Util::Image>(GetDrawable())->SetImage(MyAPP::MyResourcesFilePath::BlockImagePath);
				break;
			case MyAPP::Form::Object::BrickColor::dark:
				std::static_pointer_cast<Util::Image>(GetDrawable())->SetImage(MyAPP::MyResourcesFilePath::BlockDarkImagePath);
				break;
			case MyAPP::Form::Object::BrickColor::grey:
				std::static_pointer_cast<Util::Image>(GetDrawable())->SetImage(MyAPP::MyResourcesFilePath::BlockGreyImagePath);
				break;
			default:
				break;
			}
		}

		/// <summary>
		/// ����s�ɰ���
		/// </summary>
		/// <param name="data"></param>
		virtual void behavior(void* data = nullptr) override;

	private:
		bool trigger = false;
		bool Enable = true;
		BrickColor color;
		std::string proptype;
	};
}

#endif