#pragma once
#ifndef IFRAMES_HPP
#define IFRAMES_HPP

#include <string>

namespace MyAPP {
	namespace Form {
		namespace Object {
			namespace Interface {
				struct Iframes {
					virtual std::string GetFrame() const noexcept = 0;
					virtual void PlayFrames() noexcept = 0;
				};
			}
		}
	}
}

#endif // !IFRAMES_HPP
