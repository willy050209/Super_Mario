#ifndef IMAGEOBJECT_HPP
#define IMAGEOBJECT_HPP

#include "Object.hpp"
#include "Util/Image.hpp"

class ImageObject : public Object {

public:

	explicit ImageObject(const std::string& ImagePath,
		const float 	zIndex,
		const glm::vec2& pivot = { 0, 0 })
		: Object(std::make_shared<Util::Image>(ImagePath), zIndex, pivot) {
	}

	ImageObject(
		const std::shared_ptr< Core::Drawable >& drawable,
		const float 	zIndex,
		const glm::vec2& pivot = { 0, 0 },
		const bool 	visible = true,
		const std::vector< std::shared_ptr< GameObject > >& children = std::vector<std::shared_ptr<GameObject>>()
	) : Object(drawable, zIndex, pivot, visible, children) {}

	ImageObject(const ImageObject& other) = delete;

	ImageObject(ImageObject&& other) = delete;

	ImageObject() = delete;
};
#endif // !IMAGEOBJECT_HPP
