#pragma once
#ifndef FORM_HPP
#define FORM_HPP

#include "Util/Renderer.hpp"
#include "Object/Object.hpp"
#include "Position.hpp"
#include "userType.hpp"

#include <algorithm>
#include <execution>

namespace MyAPP{

	namespace Form{
		class Form {
		public:
			Form() {}

			/// <summary>
			/// �[�J���
			/// </summary>
			/// <param name="obj">����</param>
			inline void addForm(ObjectPtr obj) noexcept {
				//m_Root.AddChild(obj);
				m_Events.push_back(obj);
			}

			/// <summary>
			/// �������
			/// </summary>
			/// <param name="obj">����</param>
			inline void removeFormObj(ObjectPtr obj) noexcept {
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
				std::for_each(std::execution::seq,m_Events.begin(), m_Events.end(), [&data](const auto& it) { it->behavior(data); });
			}

			/// <summary>
			/// ��ø���
			/// </summary>
			inline void Update() noexcept {
				m_Root.Update();
			}

			Util::Renderer m_Root;
			/// <summary>
			/// �ƥ�}�C
			/// </summary>
			ObjectPtrVec m_Events;
		};
	}
}

#endif // !FORM_HPP
