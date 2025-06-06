#pragma once
#ifndef BRICK_HPP
#define BRICK_HPP

#include "ImageObject.hpp"
#include "ObjectType.hpp"

namespace MyAPP::Form::Object {

	enum class BrickColor {
		normal,
		dark,
		grey
	};
	/// <summary>
	/// �Ҧ��j�Y�������O �~��ImageObject
	/// </summary>
	class Brick : public ImageObject {
	public:
		enum class State {
			null,
			jump,
			down
		};

		explicit Brick(const std::string& name, const std::string& ImagePath,
			const float zIndex,
			const glm::vec2& pivot = { 0, 0 })
			: ImageObject(name, std::make_shared<Util::Image>(ImagePath), zIndex, pivot) {
			MyType = ObjectType::Brick;
		}

		/*Brick(
			const std::string& name,
			const std::shared_ptr<Core::Drawable>& drawable,
			const float zIndex,
			const glm::vec2& pivot = { 0, 0 },
			const bool visible = true,
			const std::vector<std::shared_ptr<GameObject>>& children = std::vector<std::shared_ptr<GameObject>>()) : ImageObject(name, drawable, zIndex, pivot, visible, children) {
			MyType = ObjectType::Brick;
		}*/

		Brick(const Brick& other) = delete;

		Brick(Brick&& other) = delete;

		Brick() = delete;

		virtual void behavior(void* data = nullptr) override;

		/// <summary>
		/// �Q�V���ƥ�
		/// </summary>
		virtual void bonk() noexcept;

		/// <summary>
		/// ���DĲ�o
		/// </summary>
		virtual void bonkJump() noexcept;

		/// <summary>
		/// ���o����ثe���A
		/// </summary>
		/// <returns></returns>
		inline auto getState() const noexcept { return state; }

		virtual void Reset() noexcept {
			m_Visible = resetVisible;
			collisionable = resetCollisionable;
		}

		virtual void setResetStatic() noexcept {
			resetVisible = m_Visible;
			resetCollisionable = collisionable;
		}

	protected:
		/// <summary>
		/// ������D
		/// </summary>
		void dojump() noexcept;

		/// <summary>
		/// �Y���ƥ�
		/// </summary>
		void comeDown() noexcept;

		bool jumpenable{ true };
		bool resetVisible{ true };
		bool resetCollisionable{ true };
		State state{ State::null };
		// bool jumpFlag{ false }, comeDownFlag{ false };
		int jumpcount = 0;
		glm::vec2 pos{ 0, 0 };
	};
}
#endif // !BRICK_HPP
