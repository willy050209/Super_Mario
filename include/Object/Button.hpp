#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "TextObject.hpp"
#include "Util/Color.hpp"

class Button :public TextObject {
public:
	Button(
		const std::string& name,
		const std::string& font, int size, const std::string& text,
		const Util::Color& color,
		const float 	zIndex = 10,
		const glm::vec2& pivot = { 0, 0 },
		const bool 	visible = true,
		const std::vector< std::shared_ptr< GameObject > >& children = std::vector<std::shared_ptr<GameObject>>())
		: TextObject(name, std::make_unique<Util::Text>(font, size, text, color), zIndex, pivot, visible, children) {
		defultColor = textColor = color;
		this->text = text;
		ClickedColor = Util::Color::FromName(Util::Colors::RED);
	}

	Button(
		const std::string& name,
		const std::shared_ptr< Core::Drawable >& drawable,
		const float 	zIndex = 10,
		const glm::vec2& pivot = { 0, 0 },
		const bool 	visible = true,
		const std::vector< std::shared_ptr< GameObject > >& children = std::vector<std::shared_ptr<GameObject>>()
	) :TextObject(name, drawable, zIndex, pivot, visible, children) {
		ClickedColor = Util::Color::FromName(Util::Colors::RED);
	}

	Button(const Button& other) = delete;

	Button(Button&& other) = delete;

	Button() = delete;

	inline const Util::Color& GetClickedColor() const noexcept { return ClickedColor; }

	inline void* GetCallBackFunc() const noexcept { return CallBackFunc; }

	inline void SetCallBackFunc(void (*CallBackFunc)(Button* const self, void* data)) noexcept { this->CallBackFunc = CallBackFunc; }

	virtual void behavior(void* data = nullptr) override;


protected:
	void (*CallBackFunc)(Button* const self, void* data) = nullptr;
	Util::Color ClickedColor;
	Util::Color defultColor{ Util::Color::FromName(Util::Colors::BLACK) };
	bool trigger = false;
};

#endif // !BUTTON_HPP
