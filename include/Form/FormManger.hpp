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

	inline const std::string GetPrevForm() const noexcept { return prevForm; }

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
		prevForm = nowForm;
		nowForm = formname;
	}

	inline void changeForm(std::string&& formname) noexcept {
		prevForm = nowForm;
		nowForm = formname;
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
	std::unordered_map<std::string, std::shared_ptr<Util::BGM>> m_bgm;
	std::unordered_map<std::string, std::vector<std::shared_ptr<TextObject>>> m_Texts;
	std::unordered_map<std::string, std::vector<std::shared_ptr<ImageObject>>> m_Images;
	std::unordered_map<std::string, std::vector<std::shared_ptr<Button>>> m_Buttons;
	std::unordered_map<std::string, std::vector<std::shared_ptr<Character>>> m_Characters;
	std::string  nowForm;
	std::string prevForm;
};

#endif //!FORMMANGER_HPP