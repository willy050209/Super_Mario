#include "ImageObject.hpp"

void ImageObject::setImage(const std::string& ImagePath) noexcept {
	m_Drawable = std::make_shared<Util::Image>(ImagePath);
}

ImageObject::ImageObject(const std::string& ImagePath, const float zIndex, const glm::vec2& pivot)
{
	setImage(ImagePath);
	m_Transform.translation = { 0.0f,0.0f };
	m_ZIndex = zIndex;
	m_Pivot = pivot;
}
