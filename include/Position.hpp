#ifndef POSITION_HPP
#define POSITION_HPP

#include "incallobj.hpp"
#include "config.hpp"

/// <summary>
/// ���o�Ӫ���n�����e���̥��䪺X�b���y��
/// </summary>
/// <param name="obj"> ����</param>
/// <returns>X�b���y��</returns>
inline static float GetX0(std::shared_ptr<Object> obj) noexcept {
	return -(WINDOW_WIDTH / 2 - obj->GetSize().x / 2);
}

/// <summary>
/// ���o�Ӫ���n�����e���̤W����Y�b���y��
/// </summary>
/// <param name="obj"> ����</param>
/// <returns>Y�b���y��</returns>
inline static float GetY0(std::shared_ptr<Object> obj) noexcept {
	return (WINDOW_HEIGHT / 2 - obj->GetSize().y / 2);
}

/// <summary>
/// ���o�Ӫ���n�����e���̥��䪺X�b���y��
/// </summary>
/// <param name="obj"> ����</param>
/// <returns>X�b���y��</returns>
template<class T>
inline static float GetX0(T& obj) noexcept {
	return -(WINDOW_WIDTH / 2 - obj->GetSize().x / 2);
}

/// <summary>
/// ���o�Ӫ���n�����e���̤W����Y�b���y��
/// </summary>
/// <param name="obj"> ����</param>
/// <returns>Y�b���y��</returns>
template<class T>
inline static float GetY0(T& obj) noexcept {
	return (WINDOW_HEIGHT / 2 - obj->GetSize().y / 2);
}

/// <summary>
/// ���o�Ӫ���n�����e���̥��䪺X�b���y��
/// </summary>
/// <param name="obj"> ����</param>
/// <returns>X�b���y��</returns>
template<class T>
inline static float GetX0(T* obj) noexcept {
	return -(WINDOW_WIDTH / 2 - (*obj)->GetSize().x / 2);
}

/// <summary>
/// ���o�Ӫ���n�����e���̤W����Y�b���y��
/// </summary>
/// <param name="obj"> ����</param>
/// <returns>Y�b���y��</returns>
template<class T>
inline static float GetY0(T* obj) noexcept {
	return (WINDOW_HEIGHT / 2 - (*obj)->GetSize().y / 2);
}

#endif