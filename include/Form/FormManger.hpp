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
		TextObjectPtrVec m_Texts;
		/// <summary>
		/// 圖片方塊
		/// </summary>
		ImageObjectPtrVec m_Images;
		/// <summary>
		/// 按鈕
		/// </summary>
		ButtonPtrVec m_Buttons;
		/// <summary>
		/// 角色
		/// </summary>
		CharacterPtrVec m_Characters;
		/// <summary>
		/// 事件
		/// </summary>
		EventObjectPtrVec m_Events;
	};

	/// <summary>
	/// 管理表單與事件
	/// </summary>
	class FormManger {
	public:
		FormManger() : nowForm("null") {}

		FormManger(const std::string& formName) : nowForm(formName) {}

		// FormManger(std::string formName) : nowForm(formName) {}

		/// <summary>
		/// 取得目前表單名稱
		/// </summary>
		/// <returns>表單名稱</returns>
		inline const auto& GetNowForm() const noexcept { return nowForm; }

		/// <summary>
		/// 取得前一個表單名稱
		/// </summary>
		/// <returns>表單名稱</returns>
		inline const auto GetPrevForm() const noexcept { return prevForm.back(); }

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
		/// 取得表單物件
		/// </summary>
		/// <typeparam name="T">物件類別</typeparam>
		/// <param name="formName">物件所在的表單名稱</param>
		/// <param name="objName">物件ID</param>
		/// <returns>位於formName表單中
		/// 類別為objtype
		/// ID=objName
		/// 的物件</returns>
		template <typename T>
		inline std::shared_ptr<T> GetFormObject(const std::string& formName, std::string_view objName) const noexcept {
			// 1. 檢查表單是否存在
			auto form_it = m_Forms.find(formName);
			if (form_it == m_Forms.end()) {
				return nullptr; // 表單不存在
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
		/// 移除指定物件
		/// </summary>
		/// <typeparam name="T">物件類別</typeparam>
		/// <param name="formName">物件所在的表單名稱</param>
		/// <param name="objName">物件ID</param>
		template <typename T>
		inline void removeObject(const std::string& formName, const std::string &objName) noexcept {
			auto form_it = m_Forms.find(formName);
			//if (form_it == m_Forms.end()) {
			//	return; // 表單不存在
			//}
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
		/// 移除指定物件
		/// </summary>
		/// <typeparam name="T">物件類別</typeparam>
		/// <param name="formName">物件所在的表單名稱</param>
		/// <param name="objName">物件ID</param>
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
		/// 移除指定物件
		/// </summary>
		/// <typeparam name="T">物件類別</typeparam>
		/// <param name="formName">物件所在的表單名稱</param>
		/// <param name="objName">物件ID</param>
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
		/// 取得完整表單
		/// </summary>
		/// <param name="formName">表單名稱</param>
		/// <returns>指定表單</returns>
		inline auto& GetFormAndObject(const std::string& formName) noexcept {
			return m_Forms[formName];
		}

		/// <summary>
		/// 將事件物件加入表單
		/// </summary>
		/// <param name="formName">要加入的表單</param>
		/// <param name="event">事件物件</param>
		inline void addObject(const std::string& formName, EventObjectPtr& event) noexcept {
			m_Forms[formName].m_Events.push_back(event);
			addForm(formName, event);
		}

		/// <summary>
		/// 將事件物件加入表單
		/// </summary>
		/// <param name="formName">要加入的表單</param>
		/// <param name="event">事件物件</param>
		inline void addObject(const std::string& formName, EventObjectPtr&& event) noexcept {
			m_Forms[formName].m_Events.push_back(event);
			addForm(formName, event);
		}

		/// <summary>
		/// 將按鈕物件加入表單
		/// </summary>
		/// <param name="formName">要加入的表單</param>
		/// <param name="button">按鈕物件</param>
		inline void addObject(const std::string& formName, ButtonPtr& button) noexcept {
			m_Forms[formName].m_Buttons.push_back(button);
			addForm(formName, button);
		}

		/// <summary>
		/// 將按鈕物件加入表單
		/// </summary>
		/// <param name="formName">要加入的表單</param>
		/// <param name="button">按鈕物件</param>
		inline void addObject(const std::string& formName, ButtonPtr&& button) noexcept {
			m_Forms[formName].m_Buttons.push_back(button);
			addForm(formName, button);
		}

		/// <summary>
		/// 將按圖片物件加入表單
		/// </summary>
		/// <param name="formName">要加入的表單</param>
		/// <param name="image">圖片物件加</param>
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
		/// 將按圖片物件加入表單
		/// </summary>
		/// <param name="formName">要加入的表單</param>
		/// <param name="image">圖片物件加</param>
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
		/// 將按角色物件加入表單
		/// </summary>
		/// <param name="formName">要加入的表單</param>
		/// <param name="character">角色物件</param>
		inline void addObject(const std::string& formName, CharacterPtr& character) noexcept {
			m_Forms[formName].m_Characters.push_back(character);
			addForm(formName, character);
		}

		/// <summary>
		/// 將按角色物件加入表單
		/// </summary>
		/// <param name="formName">要加入的表單</param>
		/// <param name="character">角色物件</param>
		inline void addObject(const std::string& formName, CharacterPtr&& character) noexcept {
			m_Forms[formName].m_Characters.push_back(character);
			addForm(formName, character);
		}

		/// <summary>
		/// 將按文字物件加入表單
		/// </summary>
		/// <param name="formName">要加入的表單</param>
		/// <param name="text">文字物件</param>
		inline void addObject(const std::string& formName, TextObjectPtr& text) noexcept {
			m_Forms[formName].m_Texts.push_back(text);
			addForm(formName, text);
		}

		/// <summary>
		/// 將按文字物件加入表單
		/// </summary>
		/// <param name="formName">要加入的表單</param>
		/// <param name="text">文字物件</param>
		inline void addObject(const std::string& formName, TextObjectPtr&& text) noexcept {
			m_Forms[formName].m_Texts.push_back(text);
			addForm(formName, text);
		}

		/// <summary>
		/// 刷新表單
		/// </summary>
		/// <param name="data">GameManager *</param>
		inline void UpdateForm(void* data) {
			auto addToRoot = [&](auto& it) {
				if (isInWindow(it))
					m_Forms[nowForm].m_Form.m_Root.AddChild(it);
			};
			auto addEvent = [&](auto& it) {
				if (isInWindow(it)) {
					m_Forms[nowForm].m_Form.m_Events.push_back(it);
				}
			};
			if (m_Forms.count(nowForm)) {
				// 執行目前表單的事件
				std::for_each(m_Forms[nowForm].m_Texts.begin(), m_Forms[nowForm].m_Texts.end(), addEvent);
				std::for_each(m_Forms[nowForm].m_Buttons.begin(), m_Forms[nowForm].m_Buttons.end(), addEvent);
				std::for_each(m_Forms[nowForm].m_Images.begin(), m_Forms[nowForm].m_Images.end(), addEvent);
				std::for_each(m_Forms[nowForm].m_Characters.begin(), m_Forms[nowForm].m_Characters.end(), addEvent);
				std::for_each(m_Forms[nowForm].m_Events.begin(), m_Forms[nowForm].m_Events.end(), addEvent);
				doFormEvent(nowForm, data);
				m_Forms[nowForm].m_Form.m_Events.clear();

				// 更新目前表單的物件
				std::for_each(m_Forms[nowForm].m_Texts.begin(), m_Forms[nowForm].m_Texts.end(), addToRoot);
				std::for_each(m_Forms[nowForm].m_Buttons.begin(), m_Forms[nowForm].m_Buttons.end(), addToRoot);
				std::for_each(m_Forms[nowForm].m_Images.begin(), m_Forms[nowForm].m_Images.end(), addToRoot);
				std::for_each(m_Forms[nowForm].m_Characters.begin(), m_Forms[nowForm].m_Characters.end(), addToRoot);
				m_Forms[nowForm].m_Form.Update();
				m_Forms[nowForm].m_Form.m_Root.clear();
			}
		}


		///// <summary>
		///// 改變顯示表單
		///// </summary>
		///// <param name="formname">表單名稱</param>
		// inline void changeForm(std::string formname) noexcept {
		//	if (std::find(prevForm.begin(), prevForm.end(), nowForm) == prevForm.end()) {
		//		prevForm.push_back(nowForm);
		//	}
		//	nowForm = formname;
		// }

		///// <summary>
		///// 改變顯示表單
		///// </summary>
		///// <param name="formname">表單名稱</param>
		// inline void changeForm(std::string formname) noexcept {
		//	if (std::find(prevForm.begin(), prevForm.end(), nowForm) == prevForm.end()) {
		//		prevForm.push_back(nowForm);
		//	}
		//	nowForm = formname;
		// }

		/// <summary>
		/// 改變顯示表單
		/// </summary>
		/// <param name="formname">表單名稱</param>
		inline void changeForm(const std::string& formname) noexcept {
			if (std::find(prevForm.begin(), prevForm.end(), nowForm) == prevForm.end()) {
				prevForm.push_back(std::move(nowForm));
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
		inline void freeForm(const std::string& formName) {
			m_Forms.erase(formName);
			prevForm.erase(std::remove(prevForm.begin(), prevForm.end(), formName), prevForm.end());
		}

		//template<class T>
		//std::vector<std::shared_ptr<T>> GetAllObject(const std::string& formName, std::string_view objName) {
		//	auto form_it = m_Forms.find(formName);
		//	if (form_it == m_Forms.end()) {
		//		return nullptr; // 表單不存在
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
		/// 執行表單內的所有事件
		/// </summary>
		/// <param name="formName">表單名稱</param>
		/// <param name="data">GameManager *</param>
		inline void doFormEvent(const std::string& formName, void* data) noexcept {
			if (!isPause)
				m_Forms[formName].m_Form.doAllEvent(data);
		}

		/// <summary>
		/// 加入表單
		/// </summary>
		/// <param name="formName">表單名稱</param>
		/// <param name="obj">物件共同父類別</param>
		inline void addForm(const std::string& formName, ObjectPtr obj) noexcept {
			m_Forms[formName].m_Form.addForm(obj);
		}




	protected:
		/// <summary>
		/// 表單名稱與表班物件對應序列
		/// </summary>
		std::unordered_map<std::string, FormAndObject> m_Forms;
		/// <summary>
		/// 目前表單
		/// </summary>
		std::string nowForm;
		/// <summary>
		/// 表單切換堆疊
		/// </summary>
		std::vector<std::string> prevForm;
		/// <summary>
		/// 暫停旗標
		/// </summary>
		bool isPause = false;
	};
}
#endif //! FORMMANGER_HPP