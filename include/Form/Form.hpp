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
			/// 加入表單
			/// </summary>
			/// <param name="obj">物件</param>
			inline void addForm(ObjectPtr obj) noexcept {
				//m_Root.AddChild(obj);
				m_Events.push_back(obj);
			}

			/// <summary>
			/// 移除表單
			/// </summary>
			/// <param name="obj">物件</param>
			inline void removeFormObj(ObjectPtr obj) noexcept {
				//m_Root.RemoveChild(obj);
				m_Events.erase(std::remove(m_Events.begin(), m_Events.end(), obj), m_Events.end());
			}

			/// <summary>
			/// 釋放表單事件
			/// </summary>
			inline void free() noexcept {
				// for (auto& it : m_Events) {
				//	it.reset();
				// }
				m_Events.clear();
			}

			/// <summary>
			/// 執行所有事件
			/// </summary>
			/// <param name="data">GameManager *</param>
			inline void doAllEvent(void* data = nullptr) noexcept {
				std::for_each(std::execution::seq,m_Events.begin(), m_Events.end(), [&data](const auto& it) { it->behavior(data); });
			}

			/// <summary>
			/// 重繪表單
			/// </summary>
			inline void Update() noexcept {
				m_Root.Update();
			}

			Util::Renderer m_Root;
			/// <summary>
			/// 事件陣列
			/// </summary>
			ObjectPtrVec m_Events;
		};
	}
}

#endif // !FORM_HPP
