#pragma once

#ifndef ICOLLISIONABLE_HPP
#define ICOLLISIONABLE_HPP
namespace MyAPP::Form::Object::Interface {
	struct ICollisionable {
		virtual void CheckCollision(void* data) = 0;
	};
}
#endif // !ICOLLISIONABLE_HPP
