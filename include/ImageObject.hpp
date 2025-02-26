#ifndef IMAGEOBJECT_HPP
#define IMAGEOBJECT_HPP

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"

class ImageObject : public Util::GameObject {
	
public:

	explicit ImageObject(const std::string& ImagePath,
		const float 	zIndex,
		const glm::vec2& pivot = { 0, 0 } );

	ImageObject(
		const std::shared_ptr< Core::Drawable >& drawable,
		const float 	zIndex,
		const glm::vec2& pivot = { 0, 0 },
		const bool 	visible = true,
		const std::vector< std::shared_ptr< GameObject > >& children = std::vector<std::shared_ptr<GameObject>>()
	) : Util::GameObject(drawable,zIndex,pivot,visible,children) {}
	
	ImageObject(const ImageObject& other) = default;

	ImageObject(ImageObject&& other) = default;

	ImageObject() = default;

	void setImage(const std::string& ImagePathconst) noexcept;


};

#endif // !IMAGEOBJECT_HPP
