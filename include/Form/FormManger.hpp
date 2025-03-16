#ifndef FORMMANGER_HPP
#define FORMMANGER_HPP

#include "Form/Form.hpp"
#include "incallobj.hpp"
#include <unordered_map>
#include <string>

#include <algorithm>


class FormManger {
public:

	FormManger() :nowForm("null") {  }

	FormManger(const std::string& formName) :nowForm(formName) {  }

	FormManger(std::string&& formName) :nowForm(formName) {}

	inline const std::string GetNowForm() const noexcept { return nowForm; }

	inline const std::string GetPrevForm() const noexcept { return prevForm.back(); }

	inline std::shared_ptr<Object> GetFormObject(const std::string& formName, ObjectType objtype, const std::string& objName) noexcept {
		switch (objtype)
		{
		case ObjectType::Character:
			return *std::find_if(m_Characters[formName].begin(), m_Characters[formName].end(), [&](auto& it) {return it->name == objName; });
			break;
		case ObjectType::ImageObject:
			return *std::find_if(m_Images[formName].begin(), m_Images[formName].end(), [&](auto& it) {return it->name == objName; });
			break;
		case ObjectType::TextObject:
			return *std::find_if(m_Texts[formName].begin(), m_Texts[formName].end(), [&](auto& it) {return it->name == objName; });
			break;
		case ObjectType::Button:
			return *std::find_if(m_Buttons[formName].begin(), m_Buttons[formName].end(), [&](auto& it) {return it->name == objName; });
			break;
		case ObjectType::EventObject:
			return *std::find_if(m_Events[formName].begin(), m_Events[formName].end(), [&](auto& it) {return it->name == objName; });
			break;
		default:
			return nullptr;
			break;
		}
	}

	inline void removeObject(const std::string& formName, ObjectType objtype, const std::string& objName) noexcept {
		m_Forms[formName].removeFormObj(GetFormObject(formName, objtype, objName));
		switch (objtype)
		{
		case ObjectType::Character:
			m_Characters[formName].erase(std::find_if(m_Characters[formName].begin(), m_Characters[formName].end(), [&](auto& it) {return it->name == objName; }));
			break;
		case ObjectType::ImageObject:
			m_Images[formName].erase(std::find_if(m_Images[formName].begin(), m_Images[formName].end(), [&](auto& it) {return it->name == objName; }));
			break;
		case ObjectType::TextObject:
			m_Texts[formName].erase(std::find_if(m_Texts[formName].begin(), m_Texts[formName].end(), [&](auto& it) {return it->name == objName; }));
			break;
		case ObjectType::Button:
			m_Buttons[formName].erase(std::find_if(m_Buttons[formName].begin(), m_Buttons[formName].end(), [&](auto& it) {return it->name == objName; }));
			break;
		case ObjectType::EventObject:
			m_Events[formName].erase(std::find_if(m_Events[formName].begin(), m_Events[formName].end(), [&](auto& it) {return it->name == objName; }));
			break;
		default:
			
			break;
		}
	}

	inline void addObject(const std::string& formName, std::shared_ptr<EventObject>& event) noexcept {
		m_Events[formName].push_back(event);
		addForm(formName, event);
	}

	inline void addObject(const std::string& formName, std::shared_ptr<EventObject>&& event) noexcept {
		m_Events[formName].push_back(event);
		addForm(formName, event);
	}

	inline void addObject(const std::string& formName, std::shared_ptr<Button>& button) noexcept {
		m_Buttons[formName].push_back(button);
		addForm(formName, button);
	}

	inline void addObject(const std::string& formName, std::shared_ptr<Button>&& button) noexcept {
		m_Buttons[formName].push_back(button);
		addForm(formName, button);
	}

	inline void addObject(const std::string& formName, std::shared_ptr<ImageObject>& image) noexcept {
		m_Images[formName].push_back(image);
		addForm(formName, image);
	}

	inline void addObject(const std::string& formName, std::shared_ptr<ImageObject>&& image) noexcept {
		m_Images[formName].push_back(image);
		addForm(formName, image);
	}

	inline void addObject(const std::string& formName, std::shared_ptr<Character>& character) noexcept {
		m_Characters[formName].push_back(character);
		addForm(formName, character);
	}

	inline void addObject(const std::string& formName, std::shared_ptr<Character>&& character) noexcept {
		m_Characters[formName].push_back(character);
		addForm(formName, character);
	}

	inline void addObject(const std::string& formName, std::shared_ptr<TextObject>& text) noexcept {
		m_Texts[formName].push_back(text);
		addForm(formName, text);
	}

	inline void addObject(const std::string& formName, std::shared_ptr<TextObject>&& text) noexcept {
		m_Texts[formName].push_back(text);
		addForm(formName, text);
	}

	inline void UpdateForm(void* data) {
		if (m_Forms.count(nowForm))
		{
			doFormEvent(nowForm, data);
			m_Forms[nowForm].Update();
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


private:

	inline void doFormEvent(const std::string& formName, void* data) noexcept {
		m_Forms[formName].doAllEvent(data);
	}

	inline void addForm(const std::string& formName, std::shared_ptr<Object> obj) noexcept {
		m_Forms[formName].addForm(obj);
	}


	

protected:
	std::unordered_map<std::string, Form> m_Forms;
	//std::unordered_map<std::string, std::shared_ptr<Util::BGM>> m_bgm;
	std::unordered_map<std::string, std::vector<std::shared_ptr<TextObject>>> m_Texts;
	std::unordered_map<std::string, std::vector<std::shared_ptr<ImageObject>>> m_Images;
	std::unordered_map<std::string, std::vector<std::shared_ptr<Button>>> m_Buttons;
	std::unordered_map<std::string, std::vector<std::shared_ptr<Character>>> m_Characters;
	std::unordered_map<std::string, std::vector<std::shared_ptr<EventObject>>>m_Events;
	std::string  nowForm;
	std::vector<std::string> prevForm;
};

#endif //!FORMMANGER_HPP