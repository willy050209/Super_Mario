#pragma once
#ifndef ICOMEDOWNABLE_FPP
#define ICOMEDOWNABLE_FPP

namespace MyAPP::Form::Object::Interface {

	struct IComeDownable {
		virtual void doDown() noexcept = 0;
	};

}


#endif // !IMOVEABLE_FPP
