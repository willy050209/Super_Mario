#ifndef FORM_HPP
#define FORM_HPP

#include "Util/Renderer.hpp"
#include "Object/Object.hpp"

class Form {
public:

	Form() {}

	/// <summary>
	/// �[�J���
	/// </summary>
	/// <param name="obj">����</param>
	inline void addForm(std::shared_ptr<Object>& obj) noexcept {
		m_Root.AddChild(obj);
		m_Events.push_back(obj);
	}

	/// <summary>
	/// �������
	/// </summary>
	/// <param name="obj">����</param>
	inline void removeFormObj(std::shared_ptr<Object>& obj) noexcept {
		m_Root.RemoveChild(obj);
		m_Events.erase(std::remove(m_Events.begin(), m_Events.end(), obj),m_Events.end());
	}

	/// <summary>
	/// ������ƥ�
	/// </summary>
	inline void free() noexcept {
		for (auto& it : m_Events) {
			it.reset();
		}
		m_Events.clear();
	}

	/// <summary>
	/// ����Ҧ��ƥ�
	/// </summary>
	/// <param name="data">GameManager *</param>
	inline void doAllEvent(void* data = nullptr) noexcept {
		std::for_each(m_Events.begin(), m_Events.end(), [&data](const auto& it) {it->behavior(data); });
	}

	/// <summary>
	/// ��ø���
	/// </summary>
	inline void Update() noexcept {
		m_Root.Update();
	}

protected:
	Util::Renderer m_Root;
	/// <summary>
	/// �ƥ�}�C
	/// </summary>
	std::vector<std::shared_ptr<Object>> m_Events;
};

#endif // !FORM_HPP
