#ifndef FORMMANGER_HPP
#define FORMMANGER_HPP

#include "Form/Form.hpp"
#include "Object/Object.hpp"
#include <unordered_map>
#include <string>

class FormManger {
public:

	FormManger() :nowForm("Form1") {  }

	FormManger(const std::string& formName) :nowForm(formName) {  }

	FormManger(std::string&& formName) :nowForm(formName) {}

	inline const std::string& GetNowForm() const noexcept { return nowForm; }

	inline void addObject(const std::string& formName, std::shared_ptr<Object> obj) noexcept {
		if (m_Forms.count(formName)) {
			m_Forms[formName].addForm(obj);
		}
		else{
			m_Forms[formName] = Form();
			m_Forms[formName].addForm(obj);
		}
	}

	inline void UpdateForm(void* data) {
		if (m_Forms.count(nowForm))
		{
			doFormEvent(nowForm, data);
			m_Forms[nowForm].Update();
		}
	}

	inline void changeForm(const std::string& formname) noexcept { nowForm = formname; }

	inline void changeForm(std::string&& formname) noexcept { nowForm = formname; }
	
private:

	inline void doFormEvent(const std::string& formName, void* data) noexcept {
		m_Forms[formName].doAllEvent(data);
	}

protected:
	std::unordered_map<std::string, Form> m_Forms;
	std::string  nowForm;
};

#endif //!FORMMANGER_HPP