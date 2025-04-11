#ifndef POSITION_HPP
#define POSITION_HPP

#include "incallobj.hpp"
#include "config.hpp"

/// <summary>
/// 取得該物件要切齊畫面最左邊的X軸做座標
/// </summary>
/// <param name="obj"> 物件</param>
/// <returns>X軸做座標</returns>
inline static float GetX0(std::shared_ptr<Object> obj) noexcept {
	return -(WINDOW_WIDTH / 2 - obj->GetSize().x / 2);
}

/// <summary>
/// 取得該物件要切齊畫面最上面的Y軸做座標
/// </summary>
/// <param name="obj"> 物件</param>
/// <returns>Y軸做座標</returns>
inline static float GetY0(std::shared_ptr<Object> obj) noexcept {
	return (WINDOW_HEIGHT / 2 - obj->GetSize().y / 2);
}

/// <summary>
/// 取得該物件要切齊畫面最左邊的X軸做座標
/// </summary>
/// <param name="obj"> 物件</param>
/// <returns>X軸做座標</returns>
template<class T>
inline static float GetX0(T& obj) noexcept {
	return -(WINDOW_WIDTH / 2 - obj->GetSize().x / 2);
}

/// <summary>
/// 取得該物件要切齊畫面最上面的Y軸做座標
/// </summary>
/// <param name="obj"> 物件</param>
/// <returns>Y軸做座標</returns>
template<class T>
inline static float GetY0(T& obj) noexcept {
	return (WINDOW_HEIGHT / 2 - obj->GetSize().y / 2);
}

/// <summary>
/// 取得該物件要切齊畫面最左邊的X軸做座標
/// </summary>
/// <param name="obj"> 物件</param>
/// <returns>X軸做座標</returns>
template<class T>
inline static float GetX0(T* obj) noexcept {
	return -(WINDOW_WIDTH / 2 - (*obj)->GetSize().x / 2);
}

/// <summary>
/// 取得該物件要切齊畫面最上面的Y軸做座標
/// </summary>
/// <param name="obj"> 物件</param>
/// <returns>Y軸做座標</returns>
template<class T>
inline static float GetY0(T* obj) noexcept {
	return (WINDOW_HEIGHT / 2 - (*obj)->GetSize().y / 2);
}

#endif