#pragma once
#ifndef POSITION_HPP
#define POSITION_HPP

#include "incallobj.hpp"
#include "config.hpp"

/// <summary>
/// 取得該物件要切齊畫面最左邊的X軸做座標
/// </summary>
/// <param name="obj"> 物件</param>
/// <returns>X軸做座標</returns>
inline static int GetX0(std::shared_ptr<MyAPP::Form::Object::Object> obj) noexcept {
	return -((static_cast<int>(WINDOW_WIDTH) >> 1) - (static_cast<int>(obj->GetSize().x) >> 1));
}

/// <summary>
/// 取得該物件要切齊畫面最上面的Y軸做座標
/// </summary>
/// <param name="obj"> 物件</param>
/// <returns>Y軸做座標</returns>
inline static int GetY0(std::shared_ptr<MyAPP::Form::Object::Object> obj) noexcept {
	return ((static_cast<int>(WINDOW_HEIGHT) >> 1) - (static_cast<int>(obj->GetSize().y) >> 1));
}

/// <summary>
/// 取得該物件要切齊畫面最左邊的X軸做座標
/// </summary>
/// <param name="obj"> 物件</param>
/// <returns>X軸做座標</returns>
template<class T>
inline static int GetX0(T& obj) noexcept {
	return -((static_cast<int>(WINDOW_WIDTH) >> 1) - (static_cast<int>(obj->GetSize().x) >> 1));
}

/// <summary>
/// 取得該物件要切齊畫面最上面的Y軸做座標
/// </summary>
/// <param name="obj"> 物件</param>
/// <returns>Y軸做座標</returns>
template<class T>
inline static int GetY0(T& obj) noexcept {
	return ((static_cast<int>(WINDOW_HEIGHT) >> 1) - (static_cast<int>(obj->GetSize().y) >> 1));
}

/// <summary>
/// 取得該物件要切齊畫面最左邊的X軸做座標
/// </summary>
/// <param name="obj"> 物件</param>
/// <returns>X軸做座標</returns>
template<class T>
inline static int GetX0(T* obj) noexcept {
	return -((static_cast<int>(WINDOW_WIDTH) >> 1) - (static_cast<int>((*obj)->GetSize().x) >> 1));
}

/// <summary>
/// 取得該物件要切齊畫面最上面的Y軸做座標
/// </summary>
/// <param name="obj"> 物件</param>
/// <returns>Y軸做座標</returns>
template<class T>
inline static int GetY0(T* obj) noexcept {
	return ((static_cast<int>(WINDOW_HEIGHT) >> 1) - (static_cast<int>((*obj)->GetSize().y) >> 1));
}

#endif