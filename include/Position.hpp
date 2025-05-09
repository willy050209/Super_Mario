#pragma once
#ifndef POSITION_HPP
#define POSITION_HPP

#include "incallobj.hpp"
#include "config.hpp"

/// <summary>
/// ���o�Ӫ���n�����e���̥��䪺X�b���y��
/// </summary>
/// <param name="obj"> ����</param>
/// <returns>X�b���y��</returns>
inline static int GetX0(std::shared_ptr<MyAPP::Form::Object::Object> obj) noexcept {
	return -((static_cast<int>(WINDOW_WIDTH) >> 1) - (static_cast<int>(obj->GetSize().x) >> 1));
}

/// <summary>
/// ���o�Ӫ���n�����e���̤W����Y�b���y��
/// </summary>
/// <param name="obj"> ����</param>
/// <returns>Y�b���y��</returns>
inline static int GetY0(std::shared_ptr<MyAPP::Form::Object::Object> obj) noexcept {
	return ((static_cast<int>(WINDOW_HEIGHT) >> 1) - (static_cast<int>(obj->GetSize().y) >> 1));
}

/// <summary>
/// ���o�Ӫ���n�����e���̥��䪺X�b���y��
/// </summary>
/// <param name="obj"> ����</param>
/// <returns>X�b���y��</returns>
template<class T>
inline static int GetX0(T& obj) noexcept {
	return -((static_cast<int>(WINDOW_WIDTH) >> 1) - (static_cast<int>(obj->GetSize().x) >> 1));
}

/// <summary>
/// ���o�Ӫ���n�����e���̤W����Y�b���y��
/// </summary>
/// <param name="obj"> ����</param>
/// <returns>Y�b���y��</returns>
template<class T>
inline static int GetY0(T& obj) noexcept {
	return ((static_cast<int>(WINDOW_HEIGHT) >> 1) - (static_cast<int>(obj->GetSize().y) >> 1));
}

/// <summary>
/// ���o�Ӫ���n�����e���̥��䪺X�b���y��
/// </summary>
/// <param name="obj"> ����</param>
/// <returns>X�b���y��</returns>
template<class T>
inline static int GetX0(T* obj) noexcept {
	return -((static_cast<int>(WINDOW_WIDTH) >> 1) - (static_cast<int>((obj)->GetSize().x) >> 1));
}

/// <summary>
/// ���o�Ӫ���n�����e���̤W����Y�b���y��
/// </summary>
/// <param name="obj"> ����</param>
/// <returns>Y�b���y��</returns>
template<class T>
inline static int GetY0(T* obj) noexcept {
	return ((static_cast<int>(WINDOW_HEIGHT) >> 1) - (static_cast<int>((obj)->GetSize().y) >> 1));
}

#endif