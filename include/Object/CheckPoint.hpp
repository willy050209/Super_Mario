#ifndef CHECKPOINT_HPP
#define CHECKPOINT_HPP

#include "Object/Brick.hpp"

class CheckPoint : public Brick {
public:
	explicit CheckPoint(const std::string& name, const std::string& ImagePath,
		const float zIndex,
		const glm::vec2& pivot = { 0, 0 })
		: Brick(name, std::make_shared<Util::Image>(ImagePath), zIndex, pivot) {
		MyType = ObjectType::CheckPoint;
	}

	CheckPoint(
		const std::string& name,
		const std::shared_ptr<Core::Drawable>& drawable,
		const float zIndex,
		const glm::vec2& pivot = { 0, 0 },
		const bool visible = true,
		const std::vector<std::shared_ptr<GameObject>>& children = std::vector<std::shared_ptr<GameObject>>()) : Brick(name, drawable, zIndex, pivot, visible, children) {
		MyType = ObjectType::CheckPoint;
	}

	CheckPoint(const Brick& CheckPoint) = delete;

	CheckPoint(Brick&& CheckPoint) = delete;

	//CheckPoint() = delete;

	bool Enable = true;
};
#endif