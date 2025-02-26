#include "BackgroundObject.hpp"

BackgroundObject::BackgroundObject(const std::string& ImagePath) {
	setImage(ImagePath);
	m_Transform.translation = { 0.0f,0.0f };
}

void BackgroundObject::setImage(const std::string& ImagePath) noexcept {
	m_Drawable = std::make_shared<Util::Image>(ImagePath);
}