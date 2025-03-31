#ifndef FORMMANGER_HPP
#define FORMMANGER_HPP

#include "Form/Form.hpp"
#include "incallobj.hpp"
#include <unordered_map>
#include <string>

#include <algorithm>

struct FormAndObject {
	Form m_Form;
	std::vector<std::shared_ptr<TextObject>> m_Texts;
	std::vector<std::shared_ptr<ImageObject>> m_Images;
	std::vector<std::shared_ptr<Button>> m_Buttons;
	std::vector<std::shared_ptr<Character>> m_Characters;
	std::vector<std::shared_ptr<EventObject>> m_Events;
};

class FormManger {
public:
	FormManger() : nowForm("null") {}

	FormManger(const std::string& formName) : nowForm(formName) {}

	FormManger(std::string&& formName) : nowForm(formName) {}

	inline const std::string GetNowForm() const noexcept { return nowForm; }

	inline const std::string GetPrevForm() const noexcept { return prevForm.back(); }

	inline std::shared_ptr<Object> GetFormObject(const std::string& formName, ObjectType objtype, const std::string& objName) noexcept {
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

	inline void removeObject(const std::string& formName, ObjectType objtype, const std::string& objName) noexcept {
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

	inline const FormAndObject& GetFormAndObject(const std::string& formName) noexcept {
		return m_Forms[formName];
	}

	inline void addObject(const std::string& formName, std::shared_ptr<EventObject>& event) noexcept {
		m_Forms[formName].m_Events.push_back(event);
		addForm(formName, event);
	}

	inline void addObject(const std::string& formName, std::shared_ptr<EventObject>&& event) noexcept {
		m_Forms[formName].m_Events.push_back(event);
		addForm(formName, event);
	}

	inline void addObject(const std::string& formName, std::shared_ptr<Button>& button) noexcept {
		m_Forms[formName].m_Buttons.push_back(button);
		addForm(formName, button);
	}

	inline void addObject(const std::string& formName, std::shared_ptr<Button>&& button) noexcept {
		m_Forms[formName].m_Buttons.push_back(button);
		addForm(formName, button);
	}

	inline void addObject(const std::string& formName, std::shared_ptr<ImageObject>& image) noexcept {
		m_Forms[formName].m_Images.push_back(image);
		addForm(formName, image);
	}

	inline void addObject(const std::string& formName, std::shared_ptr<ImageObject>&& image) noexcept {
		m_Forms[formName].m_Images.push_back(image);
		addForm(formName, image);
	}

	inline void addObject(const std::string& formName, std::shared_ptr<Character>& character) noexcept {
		m_Forms[formName].m_Characters.push_back(character);
		addForm(formName, character);
	}

	inline void addObject(const std::string& formName, std::shared_ptr<Character>&& character) noexcept {
		m_Forms[formName].m_Characters.push_back(character);
		addForm(formName, character);
	}

	inline void addObject(const std::string& formName, std::shared_ptr<TextObject>& text) noexcept {
		m_Forms[formName].m_Texts.push_back(text);
		addForm(formName, text);
	}

	inline void addObject(const std::string& formName, std::shared_ptr<TextObject>&& text) noexcept {
		m_Forms[formName].m_Texts.push_back(text);
		addForm(formName, text);
	}

	inline void UpdateForm(void* data) {
		if (m_Forms.count(nowForm)) {
			doFormEvent(nowForm, data);
			m_Forms[nowForm].m_Form.Update();
		}
	}

	inline void changeForm(const std::string& formname) noexcept {
		if (std::find(prevForm.begin(), prevForm.end(), nowForm) == prevForm.end()) {
			prevForm.push_back(nowForm);
		}
		nowForm = formname;
	}

	inline void changeForm(std::string&& formname) noexcept {
		if (std::find(prevForm.begin(), prevForm.end(), nowForm) == prevForm.end()) {
			prevForm.push_back(nowForm);
		}
		nowForm = formname;
	}

	inline void returnPrevForm() noexcept {
		nowForm = prevForm.back();
		prevForm.pop_back();
	}

	inline void Pause() noexcept {
		isPause = true;
	}

	inline void rePause() noexcept {
		isPause = false;
	}

private:
	inline void doFormEvent(const std::string& formName, void* data) noexcept {
		if (!isPause)
			m_Forms[formName].m_Form.doAllEvent(data);
	}

	inline void addForm(const std::string& formName, std::shared_ptr<Object> obj) noexcept {
		m_Forms[formName].m_Form.addForm(obj);
	}




protected:
	std::unordered_map<std::string, FormAndObject> m_Forms;
	std::string nowForm;
	std::vector<std::string> prevForm;
	bool isPause = false;
};

#endif //! FORMMANGER_HPP