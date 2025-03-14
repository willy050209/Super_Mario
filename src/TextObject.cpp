#include "TextObject.hpp"


inline void TextObject::setText(const std::string& text) noexcept{
	std::static_pointer_cast<Util::Text>(m_Drawable)->SetText(text);
	//this->text = text;
}

inline void TextObject::setText(std::string&& text) noexcept {
	std::static_pointer_cast<Util::Text>(m_Drawable)->SetText(text);
	//this->text = text;
}

void TextObject::setColor(const Util::Color& color)
{
	std::static_pointer_cast<Util::Text>(m_Drawable)->SetColor(color);
	textColor = color;
}
