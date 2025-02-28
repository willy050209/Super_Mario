#ifndef FORMMANGER_HPP
#define FORMMANGER_HPP

#include "Form/Form.hpp"
#include "incallobj.hpp"
#include <unordered_map>
#include <string>


class FormManger {
public:

	FormManger() :nowForm("Form1") {  }

	FormManger(const std::string& formName) :nowForm(formName) {  }

	FormManger(std::string&& formName) :nowForm(formName) {}

	inline const std::string GetNowForm() const noexcept { return nowForm; }

	inline const std::string GetPrevForm() const noexcept { return prevForm.back(); }

	inline std::shared_ptr<Object> GetObject(const std::string& formName, ObjectType&& objtype, const std::string& objname) noexcept {
		switch (objtype)
		{
		case ObjectType::Character:
			return *std::find_if(m_Characters[formName].begin(), m_Characters[formName].end(), [&](auto& it) {return it->name == objname; });
			break;
		case ObjectType::ImageObject:
			return *std::find_if(m_Images[formName].begin(), m_Images[formName].end(), [&](auto& it) {return it->name == objname; });
			break;
		case ObjectType::TextObject:
			return *std::find_if(m_Texts[formName].begin(), m_Texts[formName].end(), [&](auto& it) {return it->name == objname; });
			break;
		case ObjectType::Button:
			return *std::find_if(m_Buttons[formName].begin(), m_Buttons[formName].end(), [&](auto& it) {return it->name == objname; });
			break;
		default:
			return nullptr;
			break;
		}
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
	std::string  nowForm;
	std::vector<std::string> prevForm;
};

#endif //!FORMMANGER_HPP