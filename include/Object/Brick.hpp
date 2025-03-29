#ifndef BRICK_HPP
#define BRICK_HPP

#include "ImageObject.hpp"
#include "ObjectType.hpp"

class Brick : public ImageObject {
public:
	explicit Brick(const std::string& name, const std::string& ImagePath,
		const float zIndex,
		const glm::vec2& pivot = { 0, 0 })
		:  ImageObject(name, std::make_shared<Util::Image>(ImagePath), zIndex, pivot) {
	}

	Brick(
		const std::string& name,
		const std::shared_ptr<Core::Drawable>& drawable,
		const float zIndex,
		const glm::vec2& pivot = { 0, 0 },
		const bool visible = true,
		const std::vector<std::shared_ptr<GameObject>>& children = std::vector<std::shared_ptr<GameObject>>()) : ImageObject(name, drawable, zIndex, pivot, visible, children) {
	}

	Brick(const Brick& other) = delete;

	Brick(Brick&& other) = delete;

	Brick() = delete;

	virtual void bonk() noexcept;

	ObjectType MyType = ObjectType::Brick;
};

#endif // !BRICK_HPP
