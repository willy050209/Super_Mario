#pragma once
#ifndef MUSHROOM_HPP
#define MUSHROOM_HPP

#include "Props.hpp"
#include "ObjectType.hpp"
#include "Interface/ICollisionable.hpp"
#include "Interface/IMovable.hpp"
#include "Interface/IComeDownable.hpp"
#include "Interface/IJumpable.hpp"


namespace MyAPP::Form::Object::Props {
	/// <summary>
	/// �Ҧ��D�㪺�����O �~��ImageObject
	/// </summary>
	class Mushroom : Interface::ICollisionable, Interface::IMovable, Interface::IComeDownable, Interface::IJumpable, public Props {
	public:
		enum class Category {
			Mushroom,
			MushroomDark,
			BigMushroom
		};


		explicit Mushroom(const std::string& name, const std::string& img, Category Category_,
			const float zIndex,
			const glm::vec2& pivot = { 0, 0 })
			: Props(name, img, zIndex, pivot), MyCategory(Category_) {
			MyType = ObjectType::Mushroom;
		}


		Mushroom(const Mushroom& other) = delete;

		Mushroom(Mushroom&& other) = delete;

		Mushroom() = delete;


		virtual void behavior(void* data = nullptr) override;


		template <Category category>
		static constexpr auto GetImages() noexcept { return Images[0]; }

		template <>
		static constexpr auto GetImages<Category::Mushroom>() noexcept { return Images[0]; }

		template <>
		static constexpr auto GetImages<Category::MushroomDark>() noexcept { return Images[1]; }

		template <>
		static constexpr auto GetImages<Category::BigMushroom>() noexcept { return Images[2]; }

		void SetUpDistance(int distance) { UpDistance = distance; }

		virtual void Move(glm::vec2 distance) noexcept override;
		virtual void MoveTo(glm::vec2 position) noexcept override {
			SetPosition(position);
		}

		bool m_movable = false;

	protected:

		virtual void CheckCollision(void* gm) override;


	private:
		int UpDistance = 0;
		Category MyCategory;
		static constexpr inline char* const Images[] = { R"(imgs\super mario\1upMushroom.png)", R"(imgs\super mario\1upMushroomDark.png)", R"(imgs\super mario\BigMushroom.png)" };
		
		virtual void doJump() noexcept override;
		virtual void Jump() noexcept override {};

		virtual void doDown() noexcept override;
	};
}


#endif // !BRICK_HPP
