#pragma once

#ifndef POSITION_HPP
#define POSITION_HPP


#include "config.hpp"

/// <summary>
/// ���o�Ӫ���n�����e���̥��䪺X�b���y��
/// </summary>
/// <param name="obj"> ����</param>
/// <returns>X�b���y��</returns>
template <class T>
inline int GetLeftEdge(T& obj) noexcept {
	return -((static_cast<int>(WINDOW_WIDTH) >> 1) - (static_cast<int>(obj->GetSize().x) >> 1));
}

/// <summary>
/// ���o�Ӫ���n�����e���̤W����Y�b���y��
/// </summary>
/// <param name="obj"> ����</param>
/// <returns>Y�b���y��</returns>
template <class T>
inline int GetTopEdge(T& obj) noexcept {
	return ((static_cast<int>(WINDOW_HEIGHT) >> 1) - (static_cast<int>(obj->GetSize().y) >> 1));
}

#include "incallobj.hpp"
#include "userType.hpp"

/// <summary>
/// ���o�Ӫ���n�����e���̥��䪺X�b���y��
/// </summary>
/// <param name="obj"> ����</param>
/// <returns>X�b���y��</returns>
inline int GetLeftEdge(ObjectPtr obj) noexcept {
	return -((static_cast<int>(WINDOW_WIDTH) >> 1) - (static_cast<int>(obj->GetSize().x) >> 1));
}


/// <summary>
/// ���o�Ӫ���n�����e���̤W����Y�b���y��
/// </summary>
/// <param name="obj"> ����</param>
/// <returns>Y�b���y��</returns>
inline int GetTopEdge(ObjectPtr obj) noexcept {
	return ((static_cast<int>(WINDOW_HEIGHT) >> 1) - (static_cast<int>(obj->GetSize().y) >> 1));
}


/// <summary>
/// ���o�Ӫ���n�����e���̥��䪺X�b���y��
/// </summary>
/// <param name="obj"> ����</param>
/// <returns>X�b���y��</returns>
template<class T>
inline int GetLeftEdge(T* obj) noexcept {
	return -((static_cast<int>(WINDOW_WIDTH) >> 1) - (static_cast<int>((obj)->GetSize().x) >> 1));
}

/// <summary>
/// ���o�Ӫ���n�����e���̤W����Y�b���y��
/// </summary>
/// <param name="obj"> ����</param>
/// <returns>Y�b���y��</returns>
template<class T>
inline int GetTopEdge(T* obj) noexcept {
	return ((static_cast<int>(WINDOW_HEIGHT) >> 1) - (static_cast<int>((obj)->GetSize().y) >> 1));
}


inline bool isInWindow(MyAPP::Form::Object::Object* obj) {
	auto &pos = obj->GetPosition();
	auto size = obj->GetSize();
	return std::abs(pos.x) - size.x <= WINDOW_WIDTH / 2 && std::abs(pos.y) - size.y <= WINDOW_HEIGHT / 2;
}

inline bool isInWindow(ObjectPtr obj) {
	auto& pos = obj->m_Transform.translation;
	auto size = obj->GetSize();
	return std::abs(pos.x) - size.x <= WINDOW_WIDTH / 2 && std::abs(pos.y) - size.y <= WINDOW_HEIGHT / 2;
}

#endif