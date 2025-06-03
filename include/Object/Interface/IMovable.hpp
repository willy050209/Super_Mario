#pragma once
#ifndef IMOVABLE_FPP
#define IMOVABLE_FPP

namespace MyAPP::Form::Object::Interface {

	struct IMovable {
		virtual void Move(const glm::vec2& distance) noexcept = 0;
		virtual void MoveTo(const glm::vec2& position) noexcept = 0;
	};

}


#endif // !IMOVEABLE_FPP
