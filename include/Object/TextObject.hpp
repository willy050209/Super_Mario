#ifndef TEXTOBJECT_HPP
#define TEXTOBJECT_HPP

#include "Object.hpp"
#include "Util/Color.hpp"
#include "Util/Text.hpp"

class TextObject : public Object {

public:

	TextObject(
		const std::string& name,
		const std::string& font, int size, const std::string& text,
		const Util::Color& color,
		const float 	zIndex = 10,
		const glm::vec2& pivot = { 0, 0 },
		const bool 	visible = true,
		const std::vector< std::shared_ptr< GameObject > >& children = std::vector<std::shared_ptr<GameObject>>())
		: Object(name, std::make_unique<Util::Text>(font, size, text, color), zIndex, pivot, visible, children) {
		textColor = color;
		this->text = text;
		MyType = ObjectType::TextObject;
	}

	TextObject(
		const std::string& name,
		const std::shared_ptr< Core::Drawable >& drawable,
		const float 	zIndex = 10,
		const glm::vec2& pivot = { 0, 0 },
		const bool 	visible = true,
		const std::vector< std::shared_ptr< GameObject > >& children = std::vector<std::shared_ptr<GameObject>>()
	) :Object(name, drawable, zIndex, pivot, visible, children) {
		MyType = ObjectType::TextObject;
	}

	TextObject(const TextObject& other) = delete;

	TextObject(TextObject&& other) = delete;

	TextObject() = delete;

	inline const Util::Color& GetColor()const noexcept { return textColor; }

	inline const std::string& GetText() const noexcept { return text; }

	inline void setText(const std::string& text) noexcept;

	void setText(std::string&& text) noexcept;

	void setColor(const Util::Color& color);

	/// <summary>
	/// 取得自身大小
	/// </summary>
	/// <returns>矩形大小</returns>
	inline glm::vec2 GetSize() const noexcept override {
		return std::dynamic_pointer_cast<Util::Text>(m_Drawable)->GetSize();
	}

	virtual void behavior(void* data = nullptr) {}

protected:
	Util::Color textColor = Util::Color::FromName(Util::Colors::BLUE);
	std::string text;
};

#endif // !BackgroundObject
