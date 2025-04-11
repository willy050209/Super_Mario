#ifndef BRICK_HPP
#define BRICK_HPP

#include "ImageObject.hpp"
#include "ObjectType.hpp"

/// <summary>
/// 所有磚頭的父類別 繼承ImageObject
/// </summary>
class Brick : public ImageObject {
public:
	explicit Brick(const std::string& name, const std::string& ImagePath,
		const float zIndex,
		const glm::vec2& pivot = { 0, 0 })
		:  ImageObject(name, std::make_shared<Util::Image>(ImagePath), zIndex, pivot) {
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

	/// <summary>
	/// 被敲擊事件
	/// </summary>
	virtual void bonk() noexcept;
};

#endif // !BRICK_HPP
