#ifndef FORMMANGER_HPP
#define FORMMANGER_HPP

#include "Form/Form.hpp"
#include "incallobj.hpp"
#include <unordered_map>
#include <string>

#include <algorithm>

/// <summary>
/// 存放表單與位於表單的所有物件
/// </summary>
struct FormAndObject {
	/// <summary>
	/// 表單
	/// </summary>
	Form m_Form;
	/// <summary>
	/// 文字方塊
	/// </summary>
	std::vector<std::shared_ptr<TextObject>> m_Texts;
	/// <summary>
	/// 圖片方塊
	/// </summary>
	std::vector<std::shared_ptr<ImageObject>> m_Images;
	/// <summary>
	/// 按鈕
	/// </summary>
	std::vector<std::shared_ptr<Button>> m_Buttons;
	/// <summary>
	/// 角色
	/// </summary>
	std::vector<std::shared_ptr<Character>> m_Characters;
	/// <summary>
	/// 事件
	/// </summary>
	std::vector<std::shared_ptr<EventObject>> m_Events;
};

/// <summary>
/// 管理表單與事件
/// </summary>
class FormManger {
public:
	FormManger() : nowForm("null") {}

	FormManger(std::string_view formName) : nowForm(formName) {}

	//FormManger(std::string_view formName) : nowForm(formName) {}

	/// <summary>
	/// 取得目前表單名稱
	/// </summary>
	/// <returns>表單名稱</returns>
	inline const std::string_view GetNowForm() const noexcept { return nowForm; }

	/// <summary>
	/// 取得前一個表單名稱
	/// </summary>
	/// <returns>表單名稱</returns>
	inline const std::string_view GetPrevForm() const noexcept { return prevForm.back(); }

	/// <summary>
	/// 取得表單物件
	/// </summary>
	/// <param name="formName">物件所在的表單名稱</param>
	/// <param name="objtype">物件類別</param>
	/// <param name="objName">物件ID</param>
	/// <returns>位於formName表單中
	/// 類別為objtype
	/// ID=objName
	/// 的物件</returns>
	inline std::shared_ptr<Object> GetFormObject(std::string_view formName, ObjectType objtype, std::string_view objName) noexcept {
		switch (objtype) {
		case ObjectType::Mario:
		case ObjectType::Goomba:
		case ObjectType::Character:
			return *std::find_if(m_Forms[formName].m_Characters.begin(), m_Forms[formName].m_Characters.end(), [&](auto& it) { return it->name == objName; });
			break;
		case ObjectType::QuestionBlock:
		case ObjectType::Brick:
		case ObjectType::CheckPoint:
		case ObjectType::ImageObject:
			return *std::find_if(m_Forms[formName].m_Images.begin(), m_Forms[formName].m_Images.end(), [&](auto& it) { return it->name == objName; });
			break;
		case ObjectType::TextObject:
			return *std::find_if(m_Forms[formName].m_Texts.begin(), m_Forms[formName].m_Texts.end(), [&](auto& it) { return it->name == objName; });
			break;
		case ObjectType::Button:
			return *std::find_if(m_Forms[formName].m_Buttons.begin(), m_Forms[formName].m_Buttons.end(), [&](auto& it) { return it->name == objName; });
			break;
		case ObjectType::EventObject:
			return *std::find_if(m_Forms[formName].m_Events.begin(), m_Forms[formName].m_Events.end(), [&](auto& it) { return it->name == objName; });
			break;
		default:
			return nullptr;
			break;
		}
	}

	/// <summary>
	/// 移除指定物件
	/// </summary>
	/// <param name="formName">物件所在的表單名稱</param>
	/// <param name="objtype">物件類別</param>
	/// <param name="objName">物件ID</param>
	inline void removeObject(std::string_view formName, ObjectType objtype, std::string_view objName) noexcept {
		m_Forms[formName].m_Form.removeFormObj(GetFormObject(formName, objtype, objName));
		switch (objtype) {
		case ObjectType::Character:
			m_Forms[formName].m_Characters.erase(std::find_if(m_Forms[formName].m_Characters.begin(), m_Forms[formName].m_Characters.end(), [&](auto& it) { return it->name == objName; }));
			break;
		case ObjectType::ImageObject:
			m_Forms[formName].m_Images.erase(std::find_if(m_Forms[formName].m_Images.begin(), m_Forms[formName].m_Images.end(), [&](auto& it) { return it->name == objName; }));
			break;
		case ObjectType::TextObject:
			m_Forms[formName].m_Texts.erase(std::find_if(m_Forms[formName].m_Texts.begin(), m_Forms[formName].m_Texts.end(), [&](auto& it) { return it->name == objName; }));
			break;
		case ObjectType::Button:
			m_Forms[formName].m_Buttons.erase(std::find_if(m_Forms[formName].m_Buttons.begin(), m_Forms[formName].m_Buttons.end(), [&](auto& it) { return it->name == objName; }));
			break;
		case ObjectType::EventObject:
			m_Forms[formName].m_Events.erase(std::find_if(m_Forms[formName].m_Events.begin(), m_Forms[formName].m_Events.end(), [&](auto& it) { return it->name == objName; }));
			break;
		default:

			break;
		}
	}

	/// <summary>
	/// 取得完整表單
	/// </summary>
	/// <param name="formName">表單名稱</param>
	/// <returns>指定表單</returns>
	inline FormAndObject& GetFormAndObject(std::string_view formName) noexcept {
		return m_Forms[formName];
	}

	/// <summary>
	/// 將事件物件加入表單
	/// </summary>
	/// <param name="formName">要加入的表單</param>
	/// <param name="event">事件物件</param>
	inline void addObject(std::string_view formName, std::shared_ptr<EventObject>& event) noexcept {
		m_Forms[formName].m_Events.push_back(event);
		addForm(formName, event);
	}

	/// <summary>
	/// 將事件物件加入表單
	/// </summary>
	/// <param name="formName">要加入的表單</param>
	/// <param name="event">事件物件</param>
	inline void addObject(std::string_view formName, std::shared_ptr<EventObject>&& event) noexcept {
		m_Forms[formName].m_Events.push_back(event);
		addForm(formName, event);
	}

	/// <summary>
	/// 將按鈕物件加入表單
	/// </summary>
	/// <param name="formName">要加入的表單</param>
	/// <param name="button">按鈕物件</param>
	inline void addObject(std::string_view formName, std::shared_ptr<Button>& button) noexcept {
		m_Forms[formName].m_Buttons.push_back(button);
		addForm(formName, button);
	}

	/// <summary>
	/// 將按鈕物件加入表單
	/// </summary>
	/// <param name="formName">要加入的表單</param>
	/// <param name="button">按鈕物件</param>
	inline void addObject(std::string_view formName, std::shared_ptr<Button>&& button) noexcept {
		m_Forms[formName].m_Buttons.push_back(button);
		addForm(formName, button);
	}

	/// <summary>
	/// 將按圖片物件加入表單
	/// </summary>
	/// <param name="formName">要加入的表單</param>
	/// <param name="image">圖片物件加</param>
	inline void addObject(std::string_view formName, std::shared_ptr<ImageObject>& image) noexcept {
		m_Forms[formName].m_Images.push_back(image);
		addForm(formName, image);
	}

	/// <summary>
	/// 將按圖片物件加入表單
	/// </summary>
	/// <param name="formName">要加入的表單</param>
	/// <param name="image">圖片物件加</param>
	inline void addObject(std::string_view formName, std::shared_ptr<ImageObject>&& image) noexcept {
		m_Forms[formName].m_Images.push_back(image);
		addForm(formName, image);
	}

	/// <summary>
	/// 將按角色物件加入表單
	/// </summary>
	/// <param name="formName">要加入的表單</param>
	/// <param name="character">角色物件</param>
	inline void addObject(std::string_view formName, std::shared_ptr<Character>& character) noexcept {
		m_Forms[formName].m_Characters.push_back(character);
		addForm(formName, character);
	}

	/// <summary>
	/// 將按角色物件加入表單
	/// </summary>
	/// <param name="formName">要加入的表單</param>
	/// <param name="character">角色物件</param>
	inline void addObject(std::string_view formName, std::shared_ptr<Character>&& character) noexcept {
		m_Forms[formName].m_Characters.push_back(character);
		addForm(formName, character);
	}

	/// <summary>
	/// 將按文字物件加入表單
	/// </summary>
	/// <param name="formName">要加入的表單</param>
	/// <param name="text">文字物件</param>
	inline void addObject(std::string_view formName, std::shared_ptr<TextObject>& text) noexcept {
		m_Forms[formName].m_Texts.push_back(text);
		addForm(formName, text);
	}

	/// <summary>
	/// 將按文字物件加入表單
	/// </summary>
	/// <param name="formName">要加入的表單</param>
	/// <param name="text">文字物件</param>
	inline void addObject(std::string_view formName, std::shared_ptr<TextObject>&& text) noexcept {
		m_Forms[formName].m_Texts.push_back(text);
		addForm(formName, text);
	}

	/// <summary>
	/// 刷新表單
	/// </summary>
	/// <param name="data">GameManager *</param>
	inline void UpdateForm(void* data) {
		if (m_Forms.count(nowForm)) {
			doFormEvent(nowForm, data);
			m_Forms[nowForm].m_Form.Update();
		}
	}

	///// <summary>
	///// 改變顯示表單
	///// </summary>
	///// <param name="formname">表單名稱</param>
	//inline void changeForm(std::string_view formname) noexcept {
	//	if (std::find(prevForm.begin(), prevForm.end(), nowForm) == prevForm.end()) {
	//		prevForm.push_back(nowForm);
	//	}
	//	nowForm = formname;
	//}

	///// <summary>
	///// 改變顯示表單
	///// </summary>
	///// <param name="formname">表單名稱</param>
	//inline void changeForm(std::string_view formname) noexcept {
	//	if (std::find(prevForm.begin(), prevForm.end(), nowForm) == prevForm.end()) {
	//		prevForm.push_back(nowForm);
	//	}
	//	nowForm = formname;
	//}

	/// <summary>
	/// 改變顯示表單
	/// </summary>
	/// <param name="formname">表單名稱</param>
	inline void changeForm(std::string_view formname) noexcept {
		if (std::find(prevForm.begin(), prevForm.end(), nowForm) == prevForm.end()) {
			prevForm.push_back(nowForm);
		}
		nowForm = formname;
	}

	/// <summary>
	/// 返回上一個表單
	/// </summary>
	inline void returnPrevForm() noexcept {
		nowForm = prevForm.back();
		prevForm.pop_back();
	}

	/// <summary>
	/// 表單暫停
	/// </summary>
	inline void Pause() noexcept {
		isPause = true;
	}

	/// <summary>
	/// 取消暫停
	/// </summary>
	inline void rePause() noexcept {
		isPause = false;
	}

	/// <summary>
	/// 釋放表單
	/// </summary>
	/// <param name="formName">表單名稱</param>
	inline void freeForm(std::string_view formName) {
		for (auto& it : m_Forms[formName].m_Buttons) {
			it.reset();
		}
		m_Forms[formName].m_Buttons.clear();
		for (auto& it : m_Forms[formName].m_Characters) {
			it.reset();
		}
		m_Forms[formName] .m_Characters.clear();
		for (auto& it : m_Forms[formName].m_Events) {
			it.reset();
		}
		m_Forms[formName].m_Events.clear();
		for (auto& it : m_Forms[formName].m_Images) {
			it.reset();
		}
		m_Forms[formName].m_Images.clear();
		for (auto& it : m_Forms[formName].m_Texts) {
			it.reset();
		}
		m_Forms[formName].m_Texts.clear();
		m_Forms[formName].m_Form.free();
		m_Forms.erase(formName);
	}

private:

	/// <summary>
	/// 執行表單內的所有事件
	/// </summary>
	/// <param name="formName">表單名稱</param>
	/// <param name="data">GameManager *</param>
	inline void doFormEvent(std::string_view formName, void* data) noexcept {
		if (!isPause)
			m_Forms[formName].m_Form.doAllEvent(data);
	}

	/// <summary>
	/// 加入表單
	/// </summary>
	/// <param name="formName">表單名稱</param>
	/// <param name="obj">物件共同父類別</param>
	inline void addForm(std::string_view formName, std::shared_ptr<Object> obj) noexcept {
		m_Forms[formName].m_Form.addForm(obj);
	}




protected:
	/// <summary>
	/// 表單名稱與表班物件對應序列
	/// </summary>
	std::unordered_map<std::string_view, FormAndObject> m_Forms;
	/// <summary>
	/// 目前表單
	/// </summary>
	std::string nowForm;
	/// <summary>
	/// 表單切換堆疊
	/// </summary>
	std::vector<std::string_view> prevForm;
	/// <summary>
	/// 暫停旗標
	/// </summary>
	bool isPause = false;
};

#endif //! FORMMANGER_HPP