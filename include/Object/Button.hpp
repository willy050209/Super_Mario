#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "TextObject.hpp"
#include "Util/Color.hpp"
#include <functional>

/// <summary>
/// 按鈕事件 繼承TextObject
/// </summary>
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
		MyType = ObjectType::Button;
	}

	/*Button(
		const std::string& name,
		const std::shared_ptr< Core::Drawable >& drawable,
		const float 	zIndex = 10,
		const glm::vec2& pivot = { 0, 0 },
		const bool 	visible = true,
		const std::vector< std::shared_ptr< GameObject > >& children = std::vector<std::shared_ptr<GameObject>>()
	) :TextObject(name, drawable, zIndex, pivot, visible, children) {
		ClickedColor = Util::Color::FromName(Util::Colors::RED);
		MyType = ObjectType::Button;
	}*/

	Button(const Button& other) = delete;

	Button(Button&& other) = delete;

	Button() = delete;

	/// <summary>
	/// 取得被選取到改變的顏色
	/// </summary>
	/// <returns></returns>
	inline const Util::Color& GetClickedColor() const noexcept { return ClickedColor; }

	/// <summary>
	/// 取得CallBack Function
	/// </summary>
	/// <returns></returns>
	inline std::function<void(Button* const, void*)> GetCallBackFunc() const noexcept { return CallBackFunc; }

	/// <summary>
	/// 設定CallBack Function
	/// </summary>
	/// <param name="CallBackFunc"></param>
	inline void SetCallBackFunc(std::function<void(Button* const, void*)> CallBackFunc) noexcept { this->CallBackFunc = CallBackFunc; }

	/// <summary>
	/// 表單刷新時執行
	/// </summary>
	/// <param name="data"></param>
	virtual void behavior(void* data = nullptr) override;


	/// <summary>
	/// CallBack Function
	/// </summary>
	std::function<void(Button* const, void*)> CallBackFunc = nullptr;

	/// <summary>
	/// 點擊顏色
	/// </summary>
	Util::Color ClickedColor;

	/// <summary>
	/// 預設顏色
	/// </summary>
	Util::Color defultColor{ Util::Color::FromName(Util::Colors::BLACK) };

	/// <summary>
	/// 觸發
	/// </summary>
	bool trigger = false;
};

#endif // !BUTTON_HPP
