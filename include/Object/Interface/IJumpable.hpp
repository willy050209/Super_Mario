#pragma once
#ifndef IJUMPABLE_FPP
#define IJUMPABLE_FPP

namespace MyAPP::Form::Object::Interface {

	struct IJumpable {
		virtual void doJump() noexcept = 0;
		virtual void Jump() noexcept = 0;
	};

}


#endif // !IMOVEABLE_FPP
