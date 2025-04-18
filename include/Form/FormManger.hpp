#ifndef FORMMANGER_HPP
#define FORMMANGER_HPP

#include "Form/Form.hpp"
#include "incallobj.hpp"
#include <unordered_map>
#include <string>

#include <algorithm>

/// <summary>
/// �s����P����檺�Ҧ�����
/// </summary>
struct FormAndObject {
	/// <summary>
	/// ���
	/// </summary>
	Form m_Form;
	/// <summary>
	/// ��r���
	/// </summary>
	std::vector<std::shared_ptr<TextObject>> m_Texts;
	/// <summary>
	/// �Ϥ����
	/// </summary>
	std::vector<std::shared_ptr<ImageObject>> m_Images;
	/// <summary>
	/// ���s
	/// </summary>
	std::vector<std::shared_ptr<Button>> m_Buttons;
	/// <summary>
	/// ����
	/// </summary>
	std::vector<std::shared_ptr<Character>> m_Characters;
	/// <summary>
	/// �ƥ�
	/// </summary>
	std::vector<std::shared_ptr<EventObject>> m_Events;
};

/// <summary>
/// �޲z���P�ƥ�
/// </summary>
class FormManger {
public:
	FormManger() : nowForm("null") {}

	FormManger(std::string_view formName) : nowForm(formName) {}

	//FormManger(std::string_view formName) : nowForm(formName) {}

	/// <summary>
	/// ���o�ثe���W��
	/// </summary>
	/// <returns>���W��</returns>
	inline const std::string_view GetNowForm() const noexcept { return nowForm; }

	/// <summary>
	/// ���o�e�@�Ӫ��W��
	/// </summary>
	/// <returns>���W��</returns>
	inline const std::string_view GetPrevForm() const noexcept { return prevForm.back(); }

	/// <summary>
	/// ���o��檫��
	/// </summary>
	/// <param name="formName">����Ҧb�����W��</param>
	/// <param name="objtype">�������O</param>
	/// <param name="objName">����ID</param>
	/// <returns>���formName��椤
	/// ���O��objtype
	/// ID=objName
	/// ������</returns>
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
	/// �������w����
	/// </summary>
	/// <param name="formName">����Ҧb�����W��</param>
	/// <param name="objtype">�������O</param>
	/// <param name="objName">����ID</param>
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
	/// ���o������
	/// </summary>
	/// <param name="formName">���W��</param>
	/// <returns>���w���</returns>
	inline FormAndObject& GetFormAndObject(std::string_view formName) noexcept {
		return m_Forms[formName];
	}

	/// <summary>
	/// �N�ƥ󪫥�[�J���
	/// </summary>
	/// <param name="formName">�n�[�J�����</param>
	/// <param name="event">�ƥ󪫥�</param>
	inline void addObject(std::string_view formName, std::shared_ptr<EventObject>& event) noexcept {
		m_Forms[formName].m_Events.push_back(event);
		addForm(formName, event);
	}

	/// <summary>
	/// �N�ƥ󪫥�[�J���
	/// </summary>
	/// <param name="formName">�n�[�J�����</param>
	/// <param name="event">�ƥ󪫥�</param>
	inline void addObject(std::string_view formName, std::shared_ptr<EventObject>&& event) noexcept {
		m_Forms[formName].m_Events.push_back(event);
		addForm(formName, event);
	}

	/// <summary>
	/// �N���s����[�J���
	/// </summary>
	/// <param name="formName">�n�[�J�����</param>
	/// <param name="button">���s����</param>
	inline void addObject(std::string_view formName, std::shared_ptr<Button>& button) noexcept {
		m_Forms[formName].m_Buttons.push_back(button);
		addForm(formName, button);
	}

	/// <summary>
	/// �N���s����[�J���
	/// </summary>
	/// <param name="formName">�n�[�J�����</param>
	/// <param name="button">���s����</param>
	inline void addObject(std::string_view formName, std::shared_ptr<Button>&& button) noexcept {
		m_Forms[formName].m_Buttons.push_back(button);
		addForm(formName, button);
	}

	/// <summary>
	/// �N���Ϥ�����[�J���
	/// </summary>
	/// <param name="formName">�n�[�J�����</param>
	/// <param name="image">�Ϥ�����[</param>
	inline void addObject(std::string_view formName, std::shared_ptr<ImageObject>& image) noexcept {
		m_Forms[formName].m_Images.push_back(image);
		addForm(formName, image);
	}

	/// <summary>
	/// �N���Ϥ�����[�J���
	/// </summary>
	/// <param name="formName">�n�[�J�����</param>
	/// <param name="image">�Ϥ�����[</param>
	inline void addObject(std::string_view formName, std::shared_ptr<ImageObject>&& image) noexcept {
		m_Forms[formName].m_Images.push_back(image);
		addForm(formName, image);
	}

	/// <summary>
	/// �N�����⪫��[�J���
	/// </summary>
	/// <param name="formName">�n�[�J�����</param>
	/// <param name="character">���⪫��</param>
	inline void addObject(std::string_view formName, std::shared_ptr<Character>& character) noexcept {
		m_Forms[formName].m_Characters.push_back(character);
		addForm(formName, character);
	}

	/// <summary>
	/// �N�����⪫��[�J���
	/// </summary>
	/// <param name="formName">�n�[�J�����</param>
	/// <param name="character">���⪫��</param>
	inline void addObject(std::string_view formName, std::shared_ptr<Character>&& character) noexcept {
		m_Forms[formName].m_Characters.push_back(character);
		addForm(formName, character);
	}

	/// <summary>
	/// �N����r����[�J���
	/// </summary>
	/// <param name="formName">�n�[�J�����</param>
	/// <param name="text">��r����</param>
	inline void addObject(std::string_view formName, std::shared_ptr<TextObject>& text) noexcept {
		m_Forms[formName].m_Texts.push_back(text);
		addForm(formName, text);
	}

	/// <summary>
	/// �N����r����[�J���
	/// </summary>
	/// <param name="formName">�n�[�J�����</param>
	/// <param name="text">��r����</param>
	inline void addObject(std::string_view formName, std::shared_ptr<TextObject>&& text) noexcept {
		m_Forms[formName].m_Texts.push_back(text);
		addForm(formName, text);
	}

	/// <summary>
	/// ��s���
	/// </summary>
	/// <param name="data">GameManager *</param>
	inline void UpdateForm(void* data) {
		if (m_Forms.count(nowForm)) {
			doFormEvent(nowForm, data);
			m_Forms[nowForm].m_Form.Update();
		}
	}

	///// <summary>
	///// ������ܪ��
	///// </summary>
	///// <param name="formname">���W��</param>
	//inline void changeForm(std::string_view formname) noexcept {
	//	if (std::find(prevForm.begin(), prevForm.end(), nowForm) == prevForm.end()) {
	//		prevForm.push_back(nowForm);
	//	}
	//	nowForm = formname;
	//}

	///// <summary>
	///// ������ܪ��
	///// </summary>
	///// <param name="formname">���W��</param>
	//inline void changeForm(std::string_view formname) noexcept {
	//	if (std::find(prevForm.begin(), prevForm.end(), nowForm) == prevForm.end()) {
	//		prevForm.push_back(nowForm);
	//	}
	//	nowForm = formname;
	//}

	/// <summary>
	/// ������ܪ��
	/// </summary>
	/// <param name="formname">���W��</param>
	inline void changeForm(std::string_view formname) noexcept {
		if (std::find(prevForm.begin(), prevForm.end(), nowForm) == prevForm.end()) {
			prevForm.push_back(nowForm);
		}
		nowForm = formname;
	}

	/// <summary>
	/// ��^�W�@�Ӫ��
	/// </summary>
	inline void returnPrevForm() noexcept {
		nowForm = prevForm.back();
		prevForm.pop_back();
	}

	/// <summary>
	/// ���Ȱ�
	/// </summary>
	inline void Pause() noexcept {
		isPause = true;
	}

	/// <summary>
	/// �����Ȱ�
	/// </summary>
	inline void rePause() noexcept {
		isPause = false;
	}

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="formName">���W��</param>
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
	/// �����椺���Ҧ��ƥ�
	/// </summary>
	/// <param name="formName">���W��</param>
	/// <param name="data">GameManager *</param>
	inline void doFormEvent(std::string_view formName, void* data) noexcept {
		if (!isPause)
			m_Forms[formName].m_Form.doAllEvent(data);
	}

	/// <summary>
	/// �[�J���
	/// </summary>
	/// <param name="formName">���W��</param>
	/// <param name="obj">����@�P�����O</param>
	inline void addForm(std::string_view formName, std::shared_ptr<Object> obj) noexcept {
		m_Forms[formName].m_Form.addForm(obj);
	}




protected:
	/// <summary>
	/// ���W�ٻP��Z��������ǦC
	/// </summary>
	std::unordered_map<std::string_view, FormAndObject> m_Forms;
	/// <summary>
	/// �ثe���
	/// </summary>
	std::string nowForm;
	/// <summary>
	/// ���������|
	/// </summary>
	std::vector<std::string_view> prevForm;
	/// <summary>
	/// �Ȱ��X��
	/// </summary>
	bool isPause = false;
};

#endif //! FORMMANGER_HPP