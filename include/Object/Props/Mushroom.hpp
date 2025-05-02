#pragma once
#ifndef MUSHROOM_HPP
#define MUSHROOM_HPP

#include "Props.hpp"
#include "ObjectType.hpp"


/// <summary>
/// �Ҧ��D�㪺�����O �~��ImageObject
/// </summary>
class Mushroom : public Props {
public:

	enum class Category {
		Mushroom,
		MushroomDark,
		BigMushroom
	};

	explicit Mushroom(const std::string& name, const std::string& img,
		const float zIndex,
		const glm::vec2& pivot = { 0, 0 })
		: Props(name, img, zIndex, pivot) {
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

protected:
	virtual void playFrames() override {};

	virtual void touch(void* gm) override;


private:

	static constexpr inline char* const Images[] = { R"(imgs\super mario\1upMushroom.png)", R"(imgs\super mario\1upMushroomDark.png)", R"(imgs\super mario\BigMushroom.png)" };
};

#endif // !BRICK_HPP
