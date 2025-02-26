#ifndef BACKGROUNDOBJECT_HPP
#define BACKGROUNDOBJECT_HPP

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"

class BackgroundObject : public Util::GameObject {
	
public:

	explicit BackgroundObject(const std::string& ImagePath);

	BackgroundObject(
		const std::shared_ptr< Core::Drawable >& drawable,
		const float 	zIndex,
		const glm::vec2& pivot = { 0, 0 },
		const bool 	visible = true,
		const std::vector< std::shared_ptr< GameObject > >& children = std::vector<std::shared_ptr<GameObject>>()
	) : Util::GameObject(drawable,zIndex,pivot,visible,children) {}
	
	BackgroundObject(const BackgroundObject& other) = default;

	BackgroundObject(BackgroundObject&& other) = default;

	BackgroundObject() = default;

	void setImage(const std::string& ImagePath) noexcept;


};

#endif // !BackgroundObject
