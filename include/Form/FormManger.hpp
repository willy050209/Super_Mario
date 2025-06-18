#pragma once
#ifndef FORMMANGER_HPP
#define FORMMANGER_HPP

#include "Form/Form.hpp"
#include "incallobj.hpp"
#include "Position.hpp"
#include <unordered_map>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <type_traits>

namespace MyAPP::Form {
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
		TextObjectPtrVec m_Texts;
		/// <summary>
		/// �Ϥ����
		/// </summary>
		ImageObjectPtrVec m_Images;
		/// <summary>
		/// ���s
		/// </summary>
		ButtonPtrVec m_Buttons;
		/// <summary>
		/// ����
		/// </summary>
		CharacterPtrVec m_Characters;
		/// <summary>
		/// �ƥ�
		/// </summary>
		EventObjectPtrVec m_Events;
	};

	/// <summary>
	/// �޲z���P�ƥ�
	/// </summary>
	class FormManger {
	public:
		FormManger() : nowForm("null") {}

		FormManger(const std::string& formName) : nowForm(formName) {}

		// FormManger(std::string formName) : nowForm(formName) {}

		/// <summary>
		/// ���o�ثe���W��
		/// </summary>
		/// <returns>���W��</returns>
		inline const auto& GetNowForm() const noexcept { return nowForm; }

		/// <summary>
		/// ���o�e�@�Ӫ��W��
		/// </summary>
		/// <returns>���W��</returns>
		inline const auto GetPrevForm() const noexcept { return prevForm.back(); }

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
		// inline std::shared_ptr<MyAPP::Form::Object::Object> GetFormObject(const std::string& formName, ObjectType objtype,std::string_view objName) noexcept {
		//	switch (objtype) {
		//	case ObjectType::Mario:
		//	case ObjectType::Goomba:
		//	case ObjectType::Character:
		//		return *std::find_if(m_Forms[formName].m_Characters.begin(), m_Forms[formName].m_Characters.end(), [&](auto& it) { return it->name == objName; });
		//		break;
		//	case ObjectType::QuestionBlock:
		//	case ObjectType::Brick:
		//	case ObjectType::CheckPoint:
		//	case ObjectType::ImageObject:
		//		return *std::find_if(m_Forms[formName].m_Images.begin(), m_Forms[formName].m_Images.end(), [&](auto& it) { return it->name == objName; });
		//		break;
		//	case ObjectType::TextObject:
		//		return *std::find_if(m_Forms[formName].m_Texts.begin(), m_Forms[formName].m_Texts.end(), [&](auto& it) { return it->name == objName; });
		//		break;
		//	case ObjectType::Button:
		//		return *std::find_if(m_Forms[formName].m_Buttons.begin(), m_Forms[formName].m_Buttons.end(), [&](auto& it) { return it->name == objName; });
		//		break;
		//	case ObjectType::EventObject:
		//		return *std::find_if(m_Forms[formName].m_Events.begin(), m_Forms[formName].m_Events.end(), [&](auto& it) { return it->name == objName; });
		//		break;
		//	default:
		//		return nullptr;
		//		break;
		//	}
		// }

		/// <summary>
		/// ���o��檫��
		/// </summary>
		/// <typeparam name="T">�������O</typeparam>
		/// <param name="formName">����Ҧb�����W��</param>
		/// <param name="ID">����ID</param>
		/// <returns>���formName��椤
		/// ���O��objtype
		/// m_ID == ID
		/// ������</returns>
		template <typename T>
		inline std::shared_ptr<T> GetFormObject(const std::string& formName, const size_t& ID) const noexcept {
			// 1. �ˬd���O�_�s�b
			auto form_it = m_Forms.find(formName);
			if (form_it == m_Forms.end()) {
				return nullptr; // ��椣�s�b
			}
			auto& form = form_it->second;

			if constexpr (std::is_same_v<Object::Mario, T>) {
				auto it = std::find_if(form.m_Characters.begin(), form.m_Characters.end(),
					[&](const auto& ptr) { return ptr && ptr->MyType == Object::ObjectType::Mario && ptr->m_ID == ID; });
				if (it != form.m_Characters.end()) {
					return std::static_pointer_cast<Object::Mario>(*it);
				}
			}
			else if constexpr (std::is_base_of_v<Object::Character, T>) {
				auto it = std::find_if(form.m_Characters.begin(), form.m_Characters.end(),
					[&](const auto& ptr) { return ptr && ptr->m_ID == ID; });
				if (it != form.m_Characters.end()) {
					return std::dynamic_pointer_cast<T>(*it);
				}
			}
			else if constexpr (std::is_base_of_v<Object::ImageObject, T>) {
				auto it = std::find_if(form.m_Images.begin(), form.m_Images.end(),
					[&](const auto& ptr) { return ptr && ptr->m_ID == ID; });
				if (it != form.m_Images.end()) {
					return std::dynamic_pointer_cast<T>(*it);
				}
			}
			else if constexpr (std::is_same_v<Object::TextObject, T>) {
				auto it = std::find_if(form.m_Texts.begin(), form.m_Texts.end(),
					[&](const auto& ptr) { return ptr && ptr->m_ID == ID; });
				return (it != form.m_Texts.end()) ? *it : nullptr;
			}
			else if constexpr (std::is_same_v<Object::Button, T>) {
				auto it = std::find_if(form.m_Buttons.begin(), form.m_Buttons.end(),
					[&](const auto& ptr) { return ptr && ptr->m_ID == ID; });
				return (it != form.m_Buttons.end()) ? *it : nullptr;
			}
			else if constexpr (std::is_same_v<Object::EventObject, T>) {
				auto it = std::find_if(form.m_Events.begin(), form.m_Events.end(),
					[&](const auto& ptr) { return ptr && ptr->m_ID == ID; });
				return (it != form.m_Events.end()) ? *it : nullptr;
			}

			return nullptr;
		}

		/// <summary>
		/// ���o��檫��
		/// </summary>
		/// <typeparam name="T">�������O</typeparam>
		/// <param name="formName">����Ҧb�����W��</param>
		/// <param name="_Pred">����</param>
		/// <returns>���formName��椤
		/// ���O��objtype
		/// _Pred ��^true
		/// ������</returns>
		template <typename T, class _Pr>
		inline std::shared_ptr<T> GetFormObject_if(const std::string& formName, _Pr _Pred) const noexcept {
			// 1. �ˬd���O�_�s�b
			auto form_it = m_Forms.find(formName);
			if (form_it == m_Forms.end()) {
				return nullptr; // ��椣�s�b
			}
			auto& form = form_it->second;

			if constexpr (std::is_same_v<Object::Mario, T>) {
				auto it = std::find_if(form.m_Characters.begin(), form.m_Characters.end(), _Pred);
				if (it != form.m_Characters.end()) {
					return std::static_pointer_cast<Object::Mario>(*it);
				}
			}
			else if constexpr (std::is_base_of_v<Object::Character, T>) {
				auto it = std::find_if(form.m_Characters.begin(), form.m_Characters.end(), _Pred);
				if (it != form.m_Characters.end()) {
					return std::dynamic_pointer_cast<T>(*it);
				}
			}
			else if constexpr (std::is_base_of_v<Object::ImageObject, T>) {
				auto it = std::find_if(form.m_Images.begin(), form.m_Images.end(), _Pred);
				if (it != form.m_Images.end()) {
					return std::dynamic_pointer_cast<T>(*it);
				}
			}
			else if constexpr (std::is_same_v<Object::TextObject, T>) {
				auto it = std::find_if(form.m_Texts.begin(), form.m_Texts.end(), _Pred);
				return (it != form.m_Texts.end()) ? *it : nullptr;
			}
			else if constexpr (std::is_same_v<Object::Button, T>) {
				auto it = std::find_if(form.m_Buttons.begin(), form.m_Buttons.end(),_Pred);
				return (it != form.m_Buttons.end()) ? *it : nullptr;
			}
			else if constexpr (std::is_same_v<Object::EventObject, T>) {
				auto it = std::find_if(form.m_Events.begin(), form.m_Events.end(), _Pred);
				return (it != form.m_Events.end()) ? *it : nullptr;
			}

			return nullptr;
		}

		/// <summary>
		/// ���o��檫��
		/// </summary>
		/// <typeparam name="T">�������O</typeparam>
		/// <param name="formName">����Ҧb�����W��</param>
		/// <param name="objName">����W��</param>
		/// <returns>���formName��椤
		/// ���O��objtype
		/// name == objName
		/// ������</returns>
		template <typename T>
		inline std::shared_ptr<T> GetFormObject(const std::string& formName, std::string_view objName) const noexcept {
			// 1. �ˬd���O�_�s�b
			auto form_it = m_Forms.find(formName);
			if (form_it == m_Forms.end()) {
				return nullptr; // ��椣�s�b
			}
			auto& form = form_it->second;

			if constexpr (std::is_same_v<Object::Mario, T>) {
				auto it = std::find_if(form.m_Characters.begin(), form.m_Characters.end(),
					[&](const auto& ptr) { return ptr && ptr->MyType == Object::ObjectType::Mario && ptr->name == objName; });
				if (it != form.m_Characters.end()) {
					return std::static_pointer_cast<Object::Mario>(*it);
				}
			}
			else if constexpr (std::is_base_of_v<Object::Character, T>) {
				auto it = std::find_if(form.m_Characters.begin(), form.m_Characters.end(),
					[&](const auto& ptr) { return ptr && ptr->name == objName; });
				if (it != form.m_Characters.end()) {
					return std::dynamic_pointer_cast<T>(*it);
				}
			}
			else if constexpr (std::is_base_of_v<Object::ImageObject, T>) {
				auto it = std::find_if(form.m_Images.begin(), form.m_Images.end(),
					[&](const auto& ptr) { return ptr && ptr->name == objName; });
				if (it != form.m_Images.end()) {
					return std::dynamic_pointer_cast<T>(*it);
				}
			}
			else if constexpr (std::is_same_v<Object::TextObject, T>) {
				auto it = std::find_if(form.m_Texts.begin(), form.m_Texts.end(),
					[&](const auto& ptr) { return ptr && ptr->name == objName; });
				return (it != form.m_Texts.end()) ? *it : nullptr;
			}
			else if constexpr (std::is_same_v<Object::Button, T>) {
				auto it = std::find_if(form.m_Buttons.begin(), form.m_Buttons.end(),
					[&](const auto& ptr) { return ptr && ptr->name == objName; });
				return (it != form.m_Buttons.end()) ? *it : nullptr;
			}
			else if constexpr (std::is_same_v<Object::EventObject, T>) {
				auto it = std::find_if(form.m_Events.begin(), form.m_Events.end(),
					[&](const auto& ptr) { return ptr && ptr->name == objName; });
				return (it != form.m_Events.end()) ? *it : nullptr;
			}

			return nullptr;
		}

		/// <summary>
		/// �������w����
		/// </summary>
		/// <typeparam name="T">�������O</typeparam>
		/// <param name="formName">����Ҧb�����W��</param>
		/// <param name="ID">����ID</param>
		template <typename T>
		inline void removeObject(const std::string& formName, const size_t& ID) noexcept {
			auto form_it = m_Forms.find(formName);
			//if (form_it == m_Forms.end()) {
			//	return; // ��椣�s�b
			//}
			auto& form = form_it->second;

			if constexpr (std::is_base_of_v<Object::Character, T>) {
				form.m_Characters.erase(std::remove_if(form.m_Characters.begin(), form.m_Characters.end(), [&](auto& it) {
					return it->m_ID == ID;
				}),
					form.m_Characters.end());
			}
			else if constexpr (std::is_base_of_v<Object::ImageObject, T>) {
				form.m_Images.erase(std::remove_if(form.m_Images.begin(), form.m_Images.end(), [&](auto& it) {
					return it->m_ID == ID;
				}),
					form.m_Images.end());
			}
			else if constexpr (std::is_same_v<Object::TextObject, T>) {
				form.m_Texts.erase(std::remove_if(form.m_Texts.begin(), form.m_Texts.end(), [&](auto& it) {
					return it->m_ID == ID;
				}),
					form.m_Texts.end());
			}
			else if constexpr (std::is_same_v<Object::Button, T>) {
				form.m_Buttons.erase(std::remove_if(form.m_Buttons.begin(), form.m_Buttons.end(), [&](auto& it) {
					return it->m_ID == ID;
				}),
					form.m_Buttons.end());
			}
			else if constexpr (std::is_same_v<Object::EventObject, T>) {
				form.m_Events.erase(std::remove_if(form.m_Events.begin(), form.m_Events.end(), [&](auto& it) {
					return it->m_ID == ID;
				}),
					form.m_Events.end());
			}
		}

		/// <summary>
		/// �������w����
		/// </summary>
		/// <typeparam name="T">�������O</typeparam>
		/// <param name="formName">����Ҧb�����W��</param>
		/// <param name="objName">����W��</param>
		template <typename T>
		inline void removeObject(const std::string& formName, const std::string& objName) noexcept {
			auto form_it = m_Forms.find(formName);
			// if (form_it == m_Forms.end()) {
			//	return; // ��椣�s�b
			// }
			auto& form = form_it->second;

			if constexpr (std::is_base_of_v<Object::Character, T>) {
				form.m_Characters.erase(std::remove_if(form.m_Characters.begin(), form.m_Characters.end(), [&](auto& it) {
					return it->name == objName;
				}),
					form.m_Characters.end());
			}
			else if constexpr (std::is_base_of_v<Object::ImageObject, T>) {
				form.m_Images.erase(std::remove_if(form.m_Images.begin(), form.m_Images.end(), [&](auto& it) {
					return it->name == objName;
				}),
					form.m_Images.end());
			}
			else if constexpr (std::is_same_v<Object::TextObject, T>) {
				form.m_Texts.erase(std::remove_if(form.m_Texts.begin(), form.m_Texts.end(), [&](auto& it) {
					return it->name == objName;
				}),
					form.m_Texts.end());
			}
			else if constexpr (std::is_same_v<Object::Button, T>) {
				form.m_Buttons.erase(std::remove_if(form.m_Buttons.begin(), form.m_Buttons.end(), [&](auto& it) {
					return it->name == objName;
				}),
					form.m_Buttons.end());
			}
			else if constexpr (std::is_same_v<Object::EventObject, T>) {
				form.m_Events.erase(std::remove_if(form.m_Events.begin(), form.m_Events.end(), [&](auto& it) {
					return it->name == objName;
				}),
					form.m_Events.end());
			}
		}

		/// <summary>
		/// �������w����
		/// </summary>
		/// <typeparam name="T">�������O</typeparam>
		/// <param name="formName">����Ҧb�����W��</param>
		/// <param name="objName">����ID</param>
		template <typename T>
		inline void removeFirstObject(const std::string& formName, const std::string& objName) noexcept {
			auto form_it = m_Forms.find(formName);

			auto& form = form_it->second;

			if constexpr (std::is_base_of_v<Object::Character, T>) {
				form.m_Characters.erase(std::find_if(form.m_Characters.begin(), form.m_Characters.end(), [&](auto& it) {
					return it->name == objName;
				}));
			}
			else if constexpr (std::is_base_of_v<Object::ImageObject, T>) {
				form.m_Images.erase(std::find_if(form.m_Images.begin(), form.m_Images.end(), [&](auto& it) {
					return it->name == objName;
				}));
			}
			else if constexpr (std::is_same_v<Object::TextObject, T>) {
				form.m_Texts.erase(std::find_if(form.m_Texts.begin(), form.m_Texts.end(), [&](auto& it) {
					return it->name == objName;
				}));
			}
			else if constexpr (std::is_same_v<Object::Button, T>) {
				form.m_Buttons.erase(std::find_if(form.m_Buttons.begin(), form.m_Buttons.end(), [&](auto& it) {
					return it->name == objName;
				}));
			}
			else if constexpr (std::is_same_v<Object::EventObject, T>) {
				form.m_Events.erase(std::find_if(form.m_Events.begin(), form.m_Events.end(), [&](auto& it) {
					return it->name == objName;
				}));
			}
		}

		/// <summary>
		/// �������w����
		/// </summary>
		/// <typeparam name="T">�������O</typeparam>
		/// <param name="formName">����Ҧb�����W��</param>
		/// <param name="objName">����ID</param>
		template <typename T,class _Pr>
		inline void remove_if_Object(const std::string& formName, _Pr _Pred) noexcept {
			auto form_it = m_Forms.find(formName);

			auto& form = form_it->second;

			if constexpr (std::is_base_of_v<Object::Character, T>) {
				form.m_Characters.erase(std::find_if(form.m_Characters.begin(), form.m_Characters.end(), _Pred));
			}
			else if constexpr (std::is_base_of_v<Object::ImageObject, T>) {
				form.m_Images.erase(std::find_if(form.m_Images.begin(), form.m_Images.end(), _Pred));
			}
			else if constexpr (std::is_same_v<Object::TextObject, T>) {
				form.m_Texts.erase(std::find_if(form.m_Texts.begin(), form.m_Texts.end(), _Pred));
			}
			else if constexpr (std::is_same_v<Object::Button, T>) {
				form.m_Buttons.erase(std::find_if(form.m_Buttons.begin(), form.m_Buttons.end(), _Pred));
			}
			else if constexpr (std::is_same_v<Object::EventObject, T>) {
				form.m_Events.erase(std::find_if(form.m_Events.begin(), form.m_Events.end(), _Pred));
			}

		}

		/// <summary>
		/// ���o������
		/// </summary>
		/// <param name="formName">���W��</param>
		/// <returns>���w���</returns>
		inline auto& GetFormAndObject(const std::string& formName) noexcept {
			return m_Forms[formName];
		}

		/// <summary>
		/// �N�ƥ󪫥�[�J���
		/// </summary>
		/// <param name="formName">�n�[�J�����</param>
		/// <param name="event">�ƥ󪫥�</param>
		inline void addObject(const std::string& formName, EventObjectPtr& event) noexcept {
			m_Forms[formName].m_Events.push_back(event);
			addForm(formName, event);
		}

		/// <summary>
		/// �N�ƥ󪫥�[�J���
		/// </summary>
		/// <param name="formName">�n�[�J�����</param>
		/// <param name="event">�ƥ󪫥�</param>
		inline void addObject(const std::string& formName, EventObjectPtr&& event) noexcept {
			m_Forms[formName].m_Events.push_back(event);
			addForm(formName, event);
		}

		/// <summary>
		/// �N���s����[�J���
		/// </summary>
		/// <param name="formName">�n�[�J�����</param>
		/// <param name="button">���s����</param>
		inline void addObject(const std::string& formName, ButtonPtr& button) noexcept {
			m_Forms[formName].m_Buttons.push_back(button);
			addForm(formName, button);
		}

		/// <summary>
		/// �N���s����[�J���
		/// </summary>
		/// <param name="formName">�n�[�J�����</param>
		/// <param name="button">���s����</param>
		inline void addObject(const std::string& formName, ButtonPtr&& button) noexcept {
			m_Forms[formName].m_Buttons.push_back(button);
			addForm(formName, button);
		}

		/// <summary>
		/// �N���Ϥ�����[�J���
		/// </summary>
		/// <param name="formName">�n�[�J�����</param>
		/// <param name="image">�Ϥ�����[</param>
		inline void addObject(const std::string& formName, ImageObjectPtr& image) noexcept {
			if (image->name == "Background") {
				m_Forms[formName].m_Images.insert(m_Forms[formName].m_Images.begin(), image);
			}
			else {
				m_Forms[formName].m_Images.push_back(image);
			}
			addForm(formName, image);
		}

		/// <summary>
		/// �N���Ϥ�����[�J���
		/// </summary>
		/// <param name="formName">�n�[�J�����</param>
		/// <param name="image">�Ϥ�����[</param>
		inline void addObject(const std::string& formName, ImageObjectPtr&& image) noexcept {
			if (image->name == "Background") {
				m_Forms[formName].m_Images.insert(m_Forms[formName].m_Images.begin(), image);
			}
			else {
				m_Forms[formName].m_Images.push_back(image);
			}
			addForm(formName, image);
		}

		/// <summary>
		/// �N�����⪫��[�J���
		/// </summary>
		/// <param name="formName">�n�[�J�����</param>
		/// <param name="character">���⪫��</param>
		inline void addObject(const std::string& formName, CharacterPtr& character) noexcept {
			m_Forms[formName].m_Characters.push_back(character);
			addForm(formName, character);
		}

		/// <summary>
		/// �N�����⪫��[�J���
		/// </summary>
		/// <param name="formName">�n�[�J�����</param>
		/// <param name="character">���⪫��</param>
		inline void addObject(const std::string& formName, CharacterPtr&& character) noexcept {
			m_Forms[formName].m_Characters.push_back(character);
			addForm(formName, character);
		}

		/// <summary>
		/// �N����r����[�J���
		/// </summary>
		/// <param name="formName">�n�[�J�����</param>
		/// <param name="text">��r����</param>
		inline void addObject(const std::string& formName, TextObjectPtr& text) noexcept {
			m_Forms[formName].m_Texts.push_back(text);
			addForm(formName, text);
		}

		/// <summary>
		/// �N����r����[�J���
		/// </summary>
		/// <param name="formName">�n�[�J�����</param>
		/// <param name="text">��r����</param>
		inline void addObject(const std::string& formName, TextObjectPtr&& text) noexcept {
			m_Forms[formName].m_Texts.push_back(text);
			addForm(formName, text);
		}

		/// <summary>
		/// ��s���
		/// </summary>
		/// <param name="data">GameManager *</param>
		inline void UpdateForm(void* data) {
			auto addToRoot = [&](auto& it) {
			    auto isInWindows = [](auto& it) {
			        auto& pos = (it)->m_Transform.translation;
			        auto size = (it)->GetSize();
			        return std::abs(pos.x) - size.x <= WINDOW_WIDTH / 2 && std::abs(pos.y) - size.y <= WINDOW_HEIGHT / 2;
			    };
				if (isInWindows(it))
					m_Forms[nowForm].m_Form.m_Root.AddChild(it);
			};
			auto addEvent = [&](auto& it) {
				auto isInWindows = [](auto& it) {
					auto& pos = it->m_Transform.translation;
					auto size = it->GetSize();
					return std::abs(pos.x) - size.x <= WINDOW_WIDTH && std::abs(pos.y) - size.y <= WINDOW_HEIGHT;
				};
				if (isInWindows(it)) {
					m_Forms[nowForm].m_Form.m_Events.push_back(it);
				}
			};
			if (m_Forms.count(nowForm)) {
				// ����ثe��檺�ƥ�
				std::for_each(m_Forms[nowForm].m_Characters.begin(), m_Forms[nowForm].m_Characters.end(), addEvent);
				std::for_each(m_Forms[nowForm].m_Texts.begin(), m_Forms[nowForm].m_Texts.end(), addEvent);
				std::for_each(m_Forms[nowForm].m_Buttons.begin(), m_Forms[nowForm].m_Buttons.end(), addEvent);
				std::for_each(m_Forms[nowForm].m_Images.begin(), m_Forms[nowForm].m_Images.end(), addEvent);
				std::for_each(m_Forms[nowForm].m_Events.begin(), m_Forms[nowForm].m_Events.end(), addEvent);
				doFormEvent(nowForm, data);
				m_Forms[nowForm].m_Form.m_Events.clear();

				// ��s�ثe��檺����
				std::for_each(m_Forms[nowForm].m_Texts.begin(), m_Forms[nowForm].m_Texts.end(), addToRoot);
				std::for_each(m_Forms[nowForm].m_Buttons.begin(), m_Forms[nowForm].m_Buttons.end(), addToRoot);
				std::for_each(m_Forms[nowForm].m_Images.begin(), m_Forms[nowForm].m_Images.end(), addToRoot);
				std::for_each(m_Forms[nowForm].m_Characters.begin(), m_Forms[nowForm].m_Characters.end(), addToRoot);
				m_Forms[nowForm].m_Form.Update();
				m_Forms[nowForm].m_Form.m_Root.clear();
			}
		}


		///// <summary>
		///// ������ܪ��
		///// </summary>
		///// <param name="formname">���W��</param>
		// inline void changeForm(std::string formname) noexcept {
		//	if (std::find(prevForm.begin(), prevForm.end(), nowForm) == prevForm.end()) {
		//		prevForm.push_back(nowForm);
		//	}
		//	nowForm = formname;
		// }

		///// <summary>
		///// ������ܪ��
		///// </summary>
		///// <param name="formname">���W��</param>
		// inline void changeForm(std::string formname) noexcept {
		//	if (std::find(prevForm.begin(), prevForm.end(), nowForm) == prevForm.end()) {
		//		prevForm.push_back(nowForm);
		//	}
		//	nowForm = formname;
		// }

		/// <summary>
		/// ������ܪ��
		/// </summary>
		/// <param name="formname">���W��</param>
		inline void changeForm(const std::string& formname) noexcept {
			if (std::find(prevForm.begin(), prevForm.end(), nowForm) == prevForm.end()) {
				prevForm.push_back(std::move(nowForm));
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
		inline void freeForm(const std::string& formName) {
			m_Forms.erase(formName);
			prevForm.erase(std::remove(prevForm.begin(), prevForm.end(), formName), prevForm.end());
		}

		// inline void refresh() noexcept {
		// 	auto addToRoot = [&](auto& it) {
		// 		if (isInWindow(it))
		// 			m_Forms[nowForm].m_Form.m_Root.AddChild(it);
		// 	};
		// 	if (m_Forms.count(nowForm)) {
		//
		// 		// ��s�ثe��檺����
		// 		std::for_each(m_Forms[nowForm].m_Texts.begin(), m_Forms[nowForm].m_Texts.end(), addToRoot);
		// 		std::for_each(m_Forms[nowForm].m_Buttons.begin(), m_Forms[nowForm].m_Buttons.end(), addToRoot);
		// 		std::for_each(m_Forms[nowForm].m_Images.begin(), m_Forms[nowForm].m_Images.end(), addToRoot);
		// 		std::for_each(m_Forms[nowForm].m_Characters.begin(), m_Forms[nowForm].m_Characters.end(), addToRoot);
		// 		m_Forms[nowForm].m_Form.Update();
		// 		m_Forms[nowForm].m_Form.m_Root.clear();
		// 	}
		// }

		//template<class T>
		//std::vector<std::shared_ptr<T>> GetAllObject(const std::string& formName, std::string_view objName) {
		//	auto form_it = m_Forms.find(formName);
		//	if (form_it == m_Forms.end()) {
		//		return nullptr; // ��椣�s�b
		//	}
		//	auto& form = form_it->second;
		//	std::vector<std::shared_ptr<T>> result;
		//	if constexpr (std::is_same_v<Object::Mario, T>) {
		//		std::transform(form.m_Characters.begin(), form.m_Characters.end(), std::back_inserter(result),
		//			[&](auto& it) {
		//				if (it->name == objName) {
		//					return std::static_pointer_cast<T>(it);
		//				}
		//			});
		//		return result;
		//	}
		//	else if constexpr (std::is_base_of_v<Object::Character, T>) {
		//		std::transform(form.m_Characters.begin(), form.m_Characters.end(), std::back_inserter(result),
		//			[&](auto& it) {
		//				if (it->name == objName) {
		//					return std::static_pointer_cast<T>(it);
		//				}
		//			});
		//		return result;
		//	}
		//	else if constexpr (std::is_base_of_v<Object::ImageObject, T>) {
		//		std::transform(form.m_Characters.begin(), form.m_Characters.end(), std::back_inserter(result),
		//			[&](auto& it) {
		//				if (it->name == objName) {
		//					return std::static_pointer_cast<T>(it);
		//				}
		//			});
		//		return result;
		//	}
		//	else if constexpr (std::is_same_v<Object::TextObject, T>) {
		//		std::transform(form.m_Characters.begin(), form.m_Characters.end(), std::back_inserter(result),
		//			[&](auto& it) {
		//				if (it->name == objName) {
		//					return std::static_pointer_cast<T>(it);
		//				}
		//			});
		//		return result;
		//	}
		//	else if constexpr (std::is_same_v<Object::Button, T>) {
		//		std::transform(form.m_Characters.begin(), form.m_Characters.end(), std::back_inserter(result),
		//			[&](auto& it) {
		//				if (it->name == objName) {
		//					return std::static_pointer_cast<T>(it);
		//				}
		//			});
		//		return result;
		//	}
		//	else if constexpr (std::is_same_v<Object::EventObject, T>) {
		//		std::transform(form.m_Characters.begin(), form.m_Characters.end(), std::back_inserter(result),
		//			[&](auto& it) {
		//				if (it->name == objName) {
		//					return std::static_pointer_cast<T>(it);
		//				}
		//			});
		//		return result;
		//	}

		//	return nullptr;
		//}

	private:
		/// <summary>
		/// �����椺���Ҧ��ƥ�
		/// </summary>
		/// <param name="formName">���W��</param>
		/// <param name="data">GameManager *</param>
		inline void doFormEvent(const std::string& formName, void* data) noexcept {
			if (!isPause)
				m_Forms[formName].m_Form.doAllEvent(data);
		}

		/// <summary>
		/// �[�J���
		/// </summary>
		/// <param name="formName">���W��</param>
		/// <param name="obj">����@�P�����O</param>
		inline void addForm(const std::string& formName, ObjectPtr obj) noexcept {
			m_Forms[formName].m_Form.addForm(obj);
		}




	protected:
		/// <summary>
		/// ���W�ٻP��Z��������ǦC
		/// </summary>
		std::unordered_map<std::string, FormAndObject> m_Forms;
		/// <summary>
		/// �ثe���
		/// </summary>
		std::string nowForm;
		/// <summary>
		/// ���������|
		/// </summary>
		std::vector<std::string> prevForm;
		/// <summary>
		/// �Ȱ��X��
		/// </summary>
		bool isPause = false;
	};
}
#endif //! FORMMANGER_HPP