#pragma once
#ifndef FORM_HPP
#define FORM_HPP

#include "Util/Renderer.hpp"
#include "Object/Object.hpp"
#include "Position.hpp"

namespace MyAPP{

	namespace Form{
		class Form {
		public:
			Form() {}

			/// <summary>
			/// �[�J���
			/// </summary>
			/// <param name="obj">����</param>
			inline void addForm(std::shared_ptr<MyAPP::Form::Object::Object> obj) noexcept {
				//m_Root.AddChild(obj);
				m_Events.push_back(obj);
			}

			/// <summary>
			/// �������
			/// </summary>
			/// <param name="obj">����</param>
			inline void removeFormObj(std::shared_ptr<MyAPP::Form::Object::Object> obj) noexcept {
				//m_Root.RemoveChild(obj);
				m_Events.erase(std::remove(m_Events.begin(), m_Events.end(), obj), m_Events.end());
			}

			/// <summary>
			/// ������ƥ�
			/// </summary>
			inline void free() noexcept {
				// for (auto& it : m_Events) {
				//	it.reset();
				// }
				m_Events.clear();
			}

			/// <summary>
			/// ����Ҧ��ƥ�
			/// </summary>
			/// <param name="data">GameManager *</param>
			inline void doAllEvent(void* data = nullptr) noexcept {
				auto inWindows = [](const auto& it) { return isInWindow(it); };
				decltype(m_Events) events;
				std::copy_if(m_Events.begin(), m_Events.end(), std::back_inserter(events), inWindows);
				std::for_each(events.begin(), events.end(), [&data](const auto& it) { it->behavior(data); });
			}

			/// <summary>
			/// ��ø���
			/// </summary>
			inline void Update() noexcept {
				m_Root.Update();
			}

			Util::Renderer m_Root;
		protected:
			/// <summary>
			/// �ƥ�}�C
			/// </summary>
			std::vector<std::shared_ptr<MyAPP::Form::Object::Object>> m_Events;
		};
	}
}

#endif // !FORM_HPP
