#ifndef FORM_HPP
#define FORM_HPP

#include "Util/Renderer.hpp"
#include "Object/Object.hpp"

class Form {
public:

	Form() {}


	inline void addForm(std::shared_ptr<Object>& obj) noexcept {
		m_Root.AddChild(obj);
		m_Events.push_back(obj);
	}

	inline void removeFormObj(std::shared_ptr<Object>& obj) noexcept {
		m_Root.RemoveChild(obj);
		m_Events.erase(std::remove(m_Events.begin(), m_Events.end(), obj),m_Events.end());
	}

	inline void doAllEvent(void* data = nullptr) noexcept {
		std::for_each(m_Events.begin(), m_Events.end(), [&data](const auto& it) {it->behavior(data); });
	}

	inline void Update() noexcept {
		m_Root.Update();
	}

protected:
	Util::Renderer m_Root;
	std::vector<std::shared_ptr<Object>> m_Events;
};

#endif // !FORM_HPP
