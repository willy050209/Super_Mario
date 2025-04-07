#ifndef POSITION_HPP
#define POSITION_HPP

#include "incallobj.hpp"
#include "config.hpp"

inline static float GetX0(std::shared_ptr<Object> obj) noexcept {
	return -(WINDOW_WIDTH / 2 - obj->GetSize().x / 2);
}

inline static float GetY0(std::shared_ptr<Object> obj) noexcept {
	return (WINDOW_HEIGHT / 2 - obj->GetSize().y / 2);
}

template<class T>
inline static float GetX0(T& obj) noexcept {
	return -(WINDOW_WIDTH / 2 - obj->GetSize().x / 2);
}

template<class T>
inline static float GetY0(T& obj) noexcept {
	return (WINDOW_HEIGHT / 2 - obj->GetSize().y / 2);
}

template<class T>
inline static float GetX0(T* obj) noexcept {
	return -(WINDOW_WIDTH / 2 - (*obj)->GetSize().x / 2);
}

template<class T>
inline static float GetY0(T* obj) noexcept {
	return (WINDOW_HEIGHT / 2 - (*obj)->GetSize().y / 2);
}

#endif