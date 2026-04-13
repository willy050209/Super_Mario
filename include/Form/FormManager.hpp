#pragma once
#ifndef FORMMANAGER_HPP
#define FORMMANAGER_HPP

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
	/// Unified content for a Form, containing all its objects.
	/// </summary>
	struct FormContent {
		/// <summary>
		/// Associated Form.
		/// </summary>
		Form m_Form;

		/// <summary>
		/// Unified map for all objects in this form, indexed by their unique ID.
		/// </summary>
		std::unordered_map<size_t, ObjectPtr> m_AllObjects;
	};

	using FormAndObject = FormContent; // Backward compatibility alias

	/// <summary>
	/// Manages forms and their associated events/objects.
	/// </summary>
	class FormManager {
	public:
		FormManager() : nowForm("null") {}

		FormManager(const std::string& formName) : nowForm(formName) {}

		/// <summary>
		/// Gets the name of the current form.
		/// </summary>
		inline const auto& GetNowForm() const noexcept { return nowForm; }

		/// <summary>
		/// Gets the name of the previous form.
		/// </summary>
		inline const auto GetPrevForm() const noexcept { return prevForm.back(); }

		/// <summary>
		/// Gets an object from a specific form by its ID.
		/// </summary>
		template <typename T = Object::Object>
		inline std::shared_ptr<T> GetFormObject(const std::string& formName, const size_t& ID) const noexcept {
			auto form_it = m_Forms.find(formName);
			if (form_it == m_Forms.end()) {
				return nullptr;
			}
			auto& form = form_it->second;
			auto obj_it = form.m_AllObjects.find(ID);
			if (obj_it != form.m_AllObjects.end()) {
				return std::dynamic_pointer_cast<T>(obj_it->second);
			}
			return nullptr;
		}

		/// <summary>
		/// Gets an object from a specific form that satisfies a predicate.
		/// </summary>
		template <typename T = Object::Object, class _Pr>
		inline std::shared_ptr<T> GetFormObject_if(const std::string& formName, _Pr _Pred) const noexcept {
			auto form_it = m_Forms.find(formName);
			if (form_it == m_Forms.end()) {
				return nullptr;
			}
			auto& form = form_it->second;
			for (auto& [id, obj] : form.m_AllObjects) {
				auto casted = std::dynamic_pointer_cast<T>(obj);
				if (casted && _Pred(casted)) {
					return casted;
				}
			}
			return nullptr;
		}

		/// <summary>
		/// Gets an object from a specific form by its name.
		/// </summary>
		template <typename T = Object::Object>
		inline std::shared_ptr<T> GetFormObject(const std::string& formName, std::string_view objName) const noexcept {
			auto form_it = m_Forms.find(formName);
			if (form_it == m_Forms.end()) {
				return nullptr;
			}
			auto& form = form_it->second;
			for (auto& [id, obj] : form.m_AllObjects) {
				if (obj && obj->name == objName) {
					auto casted = std::dynamic_pointer_cast<T>(obj);
					if (casted) return casted;
				}
			}
			return nullptr;
		}

		/// <summary>
		/// Removes an object from a specific form by its ID.
		/// </summary>
		template <typename T = Object::Object>
		inline void removeObject(const std::string& formName, const size_t& ID) noexcept {
			auto form_it = m_Forms.find(formName);
			if (form_it != m_Forms.end()) {
				form_it->second.m_AllObjects.erase(ID);
			}
		}

		/// <summary>
		/// Removes all objects with a specific name from a form.
		/// </summary>
		template <typename T = Object::Object>
		inline void removeObject(const std::string& formName, const std::string& objName) noexcept {
			auto form_it = m_Forms.find(formName);
			if (form_it != m_Forms.end()) {
				auto& objects = form_it->second.m_AllObjects;
				for (auto it = objects.begin(); it != objects.end();) {
					if (it->second->name == objName && std::dynamic_pointer_cast<T>(it->second)) {
						it = objects.erase(it);
					} else {
						++it;
					}
				}
			}
		}

		/// <summary>
		/// Removes the first object with a specific name from a form.
		/// </summary>
		template <typename T = Object::Object>
		inline void removeFirstObject(const std::string& formName, const std::string& objName) noexcept {
			auto form_it = m_Forms.find(formName);
			if (form_it != m_Forms.end()) {
				auto& objects = form_it->second.m_AllObjects;
				for (auto it = objects.begin(); it != objects.end(); ++it) {
					if (it->second->name == objName && std::dynamic_pointer_cast<T>(it->second)) {
						objects.erase(it);
						return;
					}
				}
			}
		}

		/// <summary>
		/// Removes an object if it satisfies a predicate.
		/// </summary>
		template <typename T = Object::Object, class _Pr>
		inline void remove_if_Object(const std::string& formName, _Pr _Pred) noexcept {
			auto form_it = m_Forms.find(formName);
			if (form_it != m_Forms.end()) {
				auto& objects = form_it->second.m_AllObjects;
				for (auto it = objects.begin(); it != objects.end();) {
					auto casted = std::dynamic_pointer_cast<T>(it->second);
					if (casted && _Pred(casted)) {
						it = objects.erase(it);
					} else {
						++it;
					}
				}
			}
		}

		/// <summary>
		/// Gets the content (form and objects) of a specific form.
		/// </summary>
		inline auto& GetFormAndObject(const std::string& formName) noexcept {
			return m_Forms[formName];
		}

		/// <summary>
		/// Adds an object to a form.
		/// </summary>
		template<typename T>
		inline void addObject(const std::string& formName, std::shared_ptr<T> obj) noexcept {
			if (!obj) return;
			m_Forms[formName].m_AllObjects[obj->m_ID] = obj;
			addForm(formName, obj);
		}

		/// <summary>
		/// Adds an object to a form (rvalue reference).
		/// </summary>
		template<typename T>
		inline void addObject(const std::string& formName, std::shared_ptr<T>&& obj) noexcept {
			if (!obj) return;
			size_t id = obj->m_ID;
			m_Forms[formName].m_AllObjects[id] = std::move(obj);
			addForm(formName, m_Forms[formName].m_AllObjects[id]);
		}

		/// <summary>
		/// Updates the current form.
		/// </summary>
		inline void UpdateForm(void* data) {
			if (m_Forms.count(nowForm)) {
				auto& currentFormContent = m_Forms[nowForm];
				auto& form = currentFormContent.m_Form;
				
				auto isInWindows = [](const ObjectPtr& obj) {
					if (!obj) return false;
					auto& pos = obj->m_Transform.translation;
					auto size = obj->GetSize();
					// Use a slightly larger window for events to allow them to trigger just before coming on screen
					return std::abs(pos.x) - size.x <= WINDOW_WIDTH && std::abs(pos.y) - size.y <= WINDOW_HEIGHT;
				};

				auto isInStrictWindow = [](const ObjectPtr& obj) {
					if (!obj) return false;
					auto& pos = obj->m_Transform.translation;
					auto size = obj->GetSize();
					return std::abs(pos.x) - size.x <= WINDOW_WIDTH / 2 && std::abs(pos.y) - size.y <= WINDOW_HEIGHT / 2;
				};

				// 1. Prepare events for objects currently in the window
				for (auto& [id, obj] : currentFormContent.m_AllObjects) {
					if (isInWindows(obj)) {
						form.m_Events.push_back(obj);
					}
				}

				// 2. Execute behaviors
				doFormEvent(nowForm, data);
				form.m_Events.clear();

				// 3. Prepare rendering for objects in the window
				for (auto& [id, obj] : currentFormContent.m_AllObjects) {
					if (obj->MyType != Object::ObjectType::EventObject && isInStrictWindow(obj)) {
						form.m_Root.AddChild(obj);
					}
				}

				form.Update();
				form.m_Root.clear();
			}
		}

		/// <summary>
		/// Change form
		/// </summary>
		/// <param name="formname">form name</param>
		inline void changeForm(const std::string& formname) noexcept {
			if (std::find(prevForm.begin(), prevForm.end(), nowForm) == prevForm.end()) {
				prevForm.push_back(std::move(nowForm));
			}
			nowForm = formname;
		}

		/// <summary>
		/// Return to previous form
		/// </summary>
		inline void returnPrevForm() noexcept {
			if (!prevForm.empty()) {
				nowForm = prevForm.back();
				prevForm.pop_back();
			}
		}

		/// <summary>
		/// Pause
		/// </summary>
		inline void Pause() noexcept {
			isPause = true;
		}

		/// <summary>
		/// Resume
		/// </summary>
		inline void rePause() noexcept {
			isPause = false;
		}

		/// <summary>
		/// Free form
		/// </summary>
		/// <param name="formName">form name</param>
		inline void freeForm(const std::string& formName) {
			m_Forms.erase(formName);
			prevForm.erase(std::remove(prevForm.begin(), prevForm.end(), formName), prevForm.end());
		}

	private:
		/// <summary>
		/// Execute form events
		/// </summary>
		/// <param name="formName">form name</param>
		/// <param name="data">GameManager *</param>
		inline void doFormEvent(const std::string& formName, void* data) noexcept {
			if (!isPause)
				m_Forms[formName].m_Form.doAllEvent(data);
		}

		/// <summary>
		/// Add to form
		/// </summary>
		/// <param name="formName">form name</param>
		/// <param name="obj">object</param>
		inline void addForm(const std::string& formName, ObjectPtr obj) noexcept {
			m_Forms[formName].m_Form.addForm(obj);
		}

	protected:
		/// <summary>
		/// Map of form names to their content
		/// </summary>
		std::unordered_map<std::string, FormAndObject> m_Forms;
		/// <summary>
		/// Current form name
		/// </summary>
		std::string nowForm;
		/// <summary>
		/// Stack of previous forms
		/// </summary>
		std::vector<std::string> prevForm;
		/// <summary>
		/// Pause state
		/// </summary>
		bool isPause = false;
	};
}
#endif //! FORMMANAGER_HPP
